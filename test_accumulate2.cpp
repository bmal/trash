#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

using namespace std;

class join_threads
{
   public:
      explicit join_threads(vector<thread>& threads)
         : threads_(threads)
      {}

      ~join_threads()
      {
         for(auto& elem : threads_)
            if(elem.joinable())
               elem.join();
      }
   private:
      vector<thread>& threads_;
};

template<class Iterator, typename T>
T parallel_accumulate(Iterator beg, Iterator end, T init)
{
   auto length = distance(beg, end);
   if(length == 0)
      return init;

   const unsigned long min_per_thread = 1000;
   const unsigned long max_threads = (length + min_per_thread - 1)/min_per_thread;
   const unsigned long hardware_threads = thread::hardware_concurrency();
   const unsigned long num_threads = min(
         (hardware_threads != 0 ? hardware_threads : 2), max_threads);
   const unsigned long block_size = length/num_threads;
   
   vector<future<T>> futures(num_threads - 1);
   vector<thread> threads(num_threads - 1);
   join_threads joiner(threads);
   
   Iterator block_start = beg;
   for(unsigned long i = 0; i < threads.size(); ++i)
   {
      Iterator block_end = block_start;
      advance(block_end, block_size);
      packaged_task<T(Iterator, Iterator)> task(
            [](Iterator beg, Iterator end){return accumulate(beg, end, T()); });
      futures[i] = task.get_future();
      threads[i] = thread(move(task), block_start, block_end);
      block_start = block_end;
   }

   T last_result = accumulate(block_start, end, T());
   T result = init;
   for(auto& elem : futures)
      result += elem.get();

   result += last_result;
   return result;
}

int main()
{
   vector<int> v;
   for(int i = 0; i < 1000000; ++i)
      v.push_back(i);

   auto start = chrono::steady_clock::now();
   unsigned long sum = accumulate(v.begin(), v.end(), 0);
   auto end = chrono::steady_clock::now();
   cout << "STD: sum = " << sum << ", t = " 
      << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

   start = chrono::steady_clock::now();
   sum = parallel_accumulate(v.begin(), v.end(), 0);
   end = chrono::steady_clock::now();
   cout << "MY: sum = " << sum << ", t = " 
      << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
}
