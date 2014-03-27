#ifndef TEST_THREAD_GUARD_HPP
#define TEST_THREAD_GUARD_HPP

#include <thread>
#include "boost/utility.hpp"

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

#endif
