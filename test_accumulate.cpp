#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <numeric>
#include <functional>
#include <vector>

class join_threads
{
   public:
      explicit join_threads(std::vector<std::thread>& threads)
         : threads_(threads)
      {}

      ~join_threads()
      {
         for(unsigned long i = 0; i < threads_.size(); ++i)
            if(threads_[i].joinable())
               threads_[i].join();
      }

   private:
      std::vector<std::thread>& threads_;
};

template<typename Iterator, typename T>
struct accumulate_block
{
   T operator() (Iterator first, Iterator last)
   {
      return std::accumulate(first, last, T());
   }
};

template<typename Iterator, typename T>
T parallel_accumulate_v1(Iterator first, Iterator last, T init)
{
   const unsigned long length = std::distance(first, last);

   if(!length)
      return init;

   const unsigned long min_per_thread = 25;
   const unsigned long max_threads = 
      (length + min_per_thread - 1)/min_per_thread;

   const unsigned long hardware_threads = std::thread::hardware_concurrency();
   const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
   const unsigned long block_size = length/num_threads;

   std::vector<std::future<T> > futures(num_threads - 1);
   std::vector<std::thread> threads(num_threads - 1);
   join_threads joiner(threads);

   Iterator block_start = first;
   for(unsigned long i = 0; i < num_threads - 1; ++i)
   {
      Iterator block_end = block_start;
      std::advance(block_end, block_size);
      std::packaged_task<T(Iterator, Iterator)> task{accumulate_block<Iterator, T>()};
      futures[i] = task.get_future();
      threads[i] = std::thread(std::move(task), block_start, block_end);
      block_start = block_end;
   }
   T last_result = accumulate_block<Iterator, T>()(block_start, last);

   T result = init;
   for(unsigned long i = 0; i < num_threads - 1; ++i)
      result += futures[i].get();
   result += last_result;
   return result;
}

template<typename Iterator, typename T>
T parallel_accumulate_v2(Iterator first, Iterator last, T init)
{
   const unsigned long length = std::distance(first, last);
   const unsigned long max_chunk_size = 25;

   if(length <= max_chunk_size)
      return std::accumulate(first, last, init);

   Iterator mid_point = first;
   std::advance(mid_point, length/2);
   std::future<T> first_half_result = 
      std::async(&parallel_accumulate_v2<Iterator, T>, first, mid_point, T());
   T second_half_result = parallel_accumulate_v2(mid_point, last, T());

   return first_half_result.get() + second_half_result + init;
}

int main()
{
   std::vector<int> v;
   for(int i = 0; i < 1000000; ++i)
      v.push_back(i);

   auto start = std::chrono::steady_clock::now();
   std::accumulate(v.begin(), v.end(), 0);
   auto end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (standard): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

   start = std::chrono::steady_clock::now();
   parallel_accumulate_v1(v.begin(), v.end(), 0);
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v1): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
   
   start = std::chrono::steady_clock::now();
   parallel_accumulate_v2(v.begin(), v.end(), 0);
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v2): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
