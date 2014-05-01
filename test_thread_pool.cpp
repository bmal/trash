#include <thread>
#include <future>
#include <atomic>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>
#include "test_threadsafe_queue.hpp"
#include "test_join_threads.hpp"

class function_wrapper
{
   public:
      template<typename F>
      function_wrapper(F&& f)
        : impl(new impl_type<F>(std::move(f)))
      {}

      void operator()()
      {
         impl->call();
      }

      function_wrapper() = default;

      function_wrapper(function_wrapper&& other)
         : impl(std::move(other.impl))
      {}

      function_wrapper& operator=(function_wrapper&& other)
      {
         impl = std::move(other.impl);
         return *this;
      }

      function_wrapper(const function_wrapper&) = delete;
      function_wrapper& operator=(const function_wrapper&) = delete;

   private:
      struct impl_base
      {
         virtual void call() = 0;
         virtual ~impl_base()
         {}
      };
      
      template<typename F>
      struct impl_type : public impl_base
      {
         F f;
         impl_type(F&& f_)
            : f(std::move(f_))
         {}

         void call()
         {
            f();
         }
      };

      std::unique_ptr<impl_base> impl;
};

class work_stealing_queue
{
   public:
      typedef function_wrapper data_type;

      work_stealing_queue()
      {}

      work_stealing_queue(const work_stealing_queue&) = delete;
      work_stealing_queue& operator=(const work_stealing_queue&) = delete;

      void push(data_type data)
      {
         std::lock_guard<std::mutex> lk(the_mutex);
         the_queue.push_front(std::move(data));
      }

      bool try_pop(data_type& res)
      {
         std::lock_guard<std::mutex> lk(the_mutex);

         if(the_queue.empty())
            return false;

         res=std::move(the_queue.front());
         the_queue.pop_front();
         return true;
      }

      bool try_steal(data_type& res)
      {
         std::lock_guard<std::mutex> lk(the_mutex);

         if(the_queue.empty())
            return false;

         res = std::move(the_queue.back());
         the_queue.pop_back();
         return true;
      }

      bool empty() const
      {
         std::lock_guard<std::mutex> lk(the_mutex);
         return the_queue.empty();
      }

   private:
      std::deque<data_type> the_queue;
      mutable std::mutex the_mutex;
};

class thread_pool
{
   public:
      typedef std::queue<function_wrapper> local_queue_type;
      typedef function_wrapper task_type;

      thread_pool()
         : done(false), joiner(threads)
      {
         const unsigned thread_count = std::thread::hardware_concurrency();

         try
         {
            for(unsigned i = 0; i < thread_count; ++i)
            {
               queues.push_back(std::unique_ptr<work_stealing_queue>
                     (new work_stealing_queue));

               threads.push_back(std::thread(&thread_pool::worker_thread, this, i));
            }
         }
         catch(...)
         {
            done.store(true);
            throw;
         }
      }

      ~thread_pool()
      {
         done.store(true);
      }

      template<typename Function_Type>
      std::future<typename std::result_of<Function_Type()>::type>
      submit(Function_Type f)
      {
         typedef typename std::result_of<Function_Type()>::type result_type;

         std::packaged_task<result_type()> task(std::move(f));
         std::future<result_type> res(task.get_future());
         if(local_work_queue)
            local_work_queue->push(std::move(task));
         else
            pool_work_queue.push(std::move(task));

         return res;
      }

      void run_pending_task()
      {
         task_type task;
         if(pop_task_from_local_queue(task) ||
               pop_task_from_pool_queue(task) ||
               pop_task_from_other_task_queue(task))
            task();
         else
            std::this_thread::yield();
      }

   private:
      std::atomic<bool> done;
      threadsafe_queue<task_type> pool_work_queue;
      std::vector<std::unique_ptr<work_stealing_queue> > queues;
      std::vector<std::thread> threads;
      static thread_local work_stealing_queue* local_work_queue;
      static thread_local unsigned my_index;
      join_threads joiner;

      void worker_thread(const unsigned my_index_)
      {
         my_index = my_index_;
         local_work_queue = queues[my_index].get();
         while(!done)
         {
            run_pending_task();
         }
      }

      bool pop_task_from_local_queue(task_type& task)
      {
         return local_work_queue && local_work_queue->try_pop(task);
      }

      bool pop_task_from_pool_queue(task_type& task)
      {
         return pool_work_queue.try_pop(task);
      }

      bool pop_task_from_other_task_queue(task_type& task)
      {
         for(unsigned i = 0; i < queues.size(); ++i)
         {
            const unsigned index = (my_index + i + 1)%queues.size();
            if(queues[index]->try_steal(task))
               return true;
         }
         return false;
      }

};
