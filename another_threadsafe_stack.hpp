#include <stack>
#include <mutex> 
#include <condition_variable>
#include <memory>
#include <iostream>

using namespace std;

template<typename T>
class threadsafe_stack
{
   public:
      threadsafe_stack()
      {}

      threadsafe_stack(threadsafe_stack&& other_stack)
      {
         unique_lock<mutex> lock_other(other_stack.mutex_);
         swap(internal_stack_, other_stack.internal_stack_);
      }

      threadsafe_stack(const threadsafe_stack& other_stack)
      {
         unique_lock<mutex> lock_other(other_stack.mutex_);
         internal_stack_ = other_stack.internal_stack_;
      }

      threadsafe_stack& operator=(threadsafe_stack&& other_stack)
      {
         if(this != &other_stack)
         {
            unique_lock<mutex> lock_this(mutex_, defer_lock);
            unique_lock<mutex> lock_other(other_stack.mutex_, defer_lock);
            lock(lock_this, lock_other);

            swap(internal_stack_, other_stack.internal_stack_);
         
            if(!internal_stack_.empty())
               data_cond.notify_one();
         }
         return *this;
      }

      threadsafe_stack& operator=(const threadsafe_stack& other_stack)
      {
         if(this != &other_stack)
         {
            unique_lock<mutex> lock_this(mutex_, defer_lock);
            unique_lock<mutex> lock_other(other_stack.mutex_, defer_lock);
            lock(lock_this, lock_other);

            internal_stack_ = other_stack.internal_stack_;
         
            if(!internal_stack_.empty())
               data_cond.notify_one();
         }
         return *this;
      }

      void swap(threadsafe_stack& other_stack)
      {
         if(this != &other_stack)
         {
            unique_lock<mutex> lock_this(mutex_, defer_lock);
            unique_lock<mutex> lock_other(other_stack.mutex_, defer_lock);
            lock(lock_this, lock_other);

            swap(internal_stack_, other_stack.internal_stack_);
         
            if(!internal_stack_.empty())
               data_cond.notify_one();
         }
      }

      void push(const T& val)
      {
         lock_guard<mutex> lk(mutex_);
         internal_stack_.push(val);
         data_cond.notify_one();
      }

      void push(T&& val)
      {
         lock_guard<mutex> lk(mutex_);
         internal_stack_.push(move(val));
         data_cond.notify_one();
      }

      shared_ptr<T> try_pop()
      {
         lock_guard<mutex> lk(mutex_);
         if(internal_stack_.empty())
            return shared_ptr<T>();
         auto tmp = make_shared<T>(internal_stack_.top());
         internal_stack_.pop();
         return tmp;
      }

      shared_ptr<T> wait_and_pop()
      {
         unique_lock<mutex> lk(mutex_);
         data_cond.wait(lk, [this]{ return !internal_stack_.empty(); });
         auto tmp = make_shared<T>(internal_stack_.top());
         internal_stack_.pop();
         return tmp;
      }

      bool empty()
      {
         lock_guard<mutex> lk(mutex_);
         return internal_stack_.empty();
      }

   private:
      stack<T> internal_stack_;
      mutable mutex mutex_;
      condition_variable data_cond;
};
