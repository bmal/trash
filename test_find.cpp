#include <thread>
#include <future>
#include <atomic>
#include <chrono>
#include <iostream>
#include <algorithm>
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

template<typename Iterator, typename Match_Type>
Iterator parallel_find_v1(Iterator first, Iterator last, Match_Type match)
{
   struct find_element
   {
      void operator() (Iterator begin, Iterator end,
            Match_Type match, std::promise<Iterator>* result,
            std::atomic<bool>* done_flag)
      {
         try
         {
            for(; begin != end && !done_flag->load(); ++begin)
               if(*begin == match)
               {
                  result->set_value(begin);
                  done_flag->store(true);
                  return;
               }
         }
         catch(...)
         {
            try
            {
               result->set_exception(std::current_exception());
               done_flag->store(true);
            }
            catch(...)
            {}
         }
      }
   };

   const unsigned long length = std::distance(first, last);

   if(!length)
      return last;

   const unsigned long min_per_thread = 25;
   const unsigned long max_threads = 
      (length + min_per_thread - 1)/min_per_thread;

   const unsigned long hardware_threads = std::thread::hardware_concurrency();
   const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
   const unsigned long block_size = length/num_threads;

   std::promise<Iterator> result;
   std::atomic<bool> done_flag(false);
   std::vector<std::thread> threads(num_threads - 1);

   {
      join_threads joiner(threads);

      Iterator block_start = first;
      for(unsigned long i = 0; i < num_threads - 1; ++i)
      {
         Iterator block_end = block_start;
         std::advance(block_end, block_size);
         threads[i] = std::thread(find_element(), block_start, block_end,
               match, &result, &done_flag);
         block_start = block_end;
      }
      find_element()(block_start, last, match, &result, &done_flag);
   }
   if(!done_flag)
      return last;
   return result.get_future().get();
}

template<typename Iterator, typename Match_Type>
Iterator parallel_find_imp_v2(Iterator first, Iterator last, Match_Type match, std::atomic<bool>& done_flag)
{
   try
   {
      const unsigned long length = std::distance(first, last);
      const unsigned long min_per_thread = 25;
      if(length <= 2*min_per_thread)
      {
         for(; first != last && !done_flag.load(); ++first)
            if(*first == match)
            {
               done_flag.store(true);
               return first;
            }
         return last;
      }
      else
      {
         Iterator mid_point = first;
         std::advance(mid_point, length/2);
         std::future<Iterator> async_result = 
            std::async(&parallel_find_imp_v2<Iterator, Match_Type>, mid_point, last, match, std::ref(done_flag));

         Iterator direct_result = parallel_find_imp_v2(first, mid_point, match, std::ref(done_flag));
         return (direct_result == mid_point) ? async_result.get() : direct_result;
      }
   }
   catch(...)
   {
      done_flag = true;
      throw;
   }
}

template<typename Iterator, typename Match_Type>
Iterator parallel_find_v2(Iterator first, Iterator last, Match_Type match)
{
   std::atomic<bool> done(false);
   return parallel_find_imp_v2(first, last, match, done);
}

int main()
{
   std::vector<int> v;
   for(int i = 0; i < 1000000; ++i)
      v.push_back(i);

   auto start = std::chrono::steady_clock::now();
   std::find(v.begin(), v.end(), 500000);
   auto end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (standard): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

   start = std::chrono::steady_clock::now();
   parallel_find_v1(v.begin(), v.end(), 500000); 
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v1): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
   
   start = std::chrono::steady_clock::now();
   parallel_find_v2(v.begin(), v.end(), 500000);
   end = std::chrono::steady_clock::now();
   std::cout << "Calkowity czas (v2): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
