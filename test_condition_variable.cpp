#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

struct S
{
   S() : is_(false) {}

   void put_object(int o)
   {
      object_ = o;
      is_ = true;
      is.notify_one();
   }

   int get_object()
   {
      is_ = false;
      return object_;
   }

   bool available()
   {
      return is_;
   }

   condition_variable is;


   private:
      int object_;
      bool is_;
};

class A
{
   private:
      mutex m;
      S& ref;
   public:
      A(S& obj) : ref(obj) {}
      void set_value(int val)
      {
         lock_guard<mutex> lk(m);
         ref.put_object(val);
         cout << "Ustawiona wartość: " << val << endl;
      }

      void get_value()
      {
         unique_lock<mutex> lk(m);
         ref.is.wait(lk, [this]()->bool{return ref.available();});
         int i = ref.get_object();
         lk.unlock();
         cout << "Otrzymano wartosc: " << i << endl;
      }
};

void thread_a(S& obj)
{
   A ob_a(obj);
   ob_a.get_value();
   ob_a.set_value(10);
   ob_a.set_value(12);
}

void thread_b(S& obj)
{
   A ob_a(obj);
   ob_a.set_value(3);
   ob_a.set_value(2);
   ob_a.get_value();
}

int main()
{
   S s;
   thread t1(thread_a, ref(s));
   thread t2(thread_b, ref(s));
   t1.join();
   t2.join();
}
