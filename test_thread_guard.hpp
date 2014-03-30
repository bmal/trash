#ifndef TEST_THREAD_GUARD_HPP
#define TEST_THREAD_GUARD_HPP

#include <thread>
#include <stdexcept>
#include "boost/noncopyable.hpp"

class Thread_guard
 : boost::noncopyable
{
   public:
      explicit Thread_guard(std::thread& t)
         : t_(t)
      {}

      ~Thread_guard()
      {
         if(t_.joinable())
            t_.join();
      }
   private:
      std::thread& t_;
};

class Scoped_thread
 : boost::noncopyable
{
   public:
      explicit Scoped_thread(std::thread t)
         : t_(std::move(t))
      {
         if(!t_.joinable())
            throw std::logic_error("Brak watku");
      }

      ~Scoped_thread()
      {
         t_.join();
      }
   private:
      std::thread t_;
};

#endif
