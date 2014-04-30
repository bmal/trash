#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <algorithm>
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

template<typename Iterator, typename Func>
void parallel_for_each_v1(Iterator first, Iterator last, Func f)
{
   const unsigned long length = std::distance(first, last);

   if(!length)
      return;

   const unsigned long min_per_thread = 25;
   const unsigned long max_threads = 
      (length + min_per_thread - 1)/min_per_thread;

   const unsigned long hardware_threads = std::thread::hardware_concurrency();
   const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
   const unsigned long block_size = length/num_threads;

   std::vector<std::future<void> > futures(num_threads - 1);
   std::vector<std::thread> threads(num_threads - 1);
   join_threads joiner(threads);

   Iterator block_start = first;
   for(unsigned long i = 0; i < num_threads - 1; ++i)
   {
      Iterator block_end = block_start;
      std::advance(block_end, block_size);
      std::packaged_task<void(void)> task([=]{std::for_each(block_start, block_end, f);});
      futures[i] = task.get_future();
      threads[i] = std::thread(std::move(task));
      block_start = block_end;
   }
   std::for_each(block_start, last, f);
   for(unsigned long i = 0; i < num_threads - 1; ++i)
      futures[i].get();
}

template<typename Iterator, typename Func>
void parallel_for_each_v2(Iterator first, Iterator last, Func f)
{
   const unsigned long length = std::distance(first, last);

   if(!length)
      return;

   const unsigned long min_per_thread = 25;
   if(length <= min_per_thread)
      std::for_each(first, last, f);
   else
   {
      Iterator mid_point = first;
      std::advance(mid_point, length/2);
      std::future<void> first_half = 
         std::async(&parallel_for_each_v2<Iterator, Func>, first, mid_point, f);
      parallel_for_each_v2(mid_point, last, f); 
      first_half.get();
   }
}

void add_3(int& val)
{
   val += 3;
}

int main()
{
   std::vector<int> v;
   for(int i = 0; i < 1000000; ++i)
      v.push_back(i);

   auto start = std::chrono::steady_clock::now();
   std::for_each(v.begin(), v.end(), add_3);
   auto end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (standard): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

   start = std::chrono::steady_clock::now();
   parallel_for_each_v1(v.begin(), v.end(), add_3); 
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v1): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
   
   start = std::chrono::steady_clock::now();
   parallel_for_each_v2(v.begin(), v.end(), add_3);
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v2): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
