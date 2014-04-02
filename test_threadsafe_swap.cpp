#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class Big
{
   private:
      int a;
      int b;
      mutex m;
   public:
      Big(int a, int b) : a(a), b(b) {}
      friend void swap(Big& lhs, Big& rhs)
      {
         lock(lhs.m, rhs.m);
         lock_guard<mutex>(lhs.m, adopt_lock);
         lock_guard<mutex>(rhs.m, adopt_lock);
         swap(lhs.a, rhs.a);
         swap(lhs.b, rhs.b);
      }

      friend ostream& operator<<(ostream& o, const Big& obj)
      {
         o << obj.a << ' ' << obj.b << endl;
         return o;
      }
};

int main()
{
}
