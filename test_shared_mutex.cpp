#include <iostream>
#include <algorithm>
#include <mutex>
#include "boost/thread/shared_mutex.hpp"
#include <thread>

using namespace std;

class A
{
   public:
      A() : object(0) {}

      void read() const
      {
         boost::shared_lock<decltype(m)> lk(m);
         cout << "Czytamy: " << object << endl;
      }

      void write(int val)
      {
         lock_guard<decltype(m)> lk(m);
         object = val;
         //cout << "Zmiana na: " << val << endl;
      }

      A(const A& obj)
         : object(obj.object)
      {}

   private:
      mutable boost::shared_mutex m;
      int object;
};

int main()
{
   A a;
   vector<thread> v;
   for(int i = 0; i < 20; ++i)
      if(i%4 == 0)
         v.push_back(thread(&A::write, &a, i));
      else
         v.push_back(thread(&A::read, &a));

   for_each(v.begin(), v.end(), bind(&thread::join, placeholders::_1));
}
