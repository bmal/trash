#include <iostream>

template<
   class Result,
   class F, F f,
   class G, G g
>
struct compose_fg
{
   template<class T>
   Result operator()(const T& x) const
   {
      return f(g(x));
   }
};

int sum(int val)
{
   return val + 1;
}

struct multi
{
   int operator()(int val) const
   {
      return val*2;
   }
};

multi mu;

int main()
{
   std::cout << compose_fg<
      int, 
      int(*)(int), sum,
      int(*)(int), sum
   >()(10); //ok

   std::cout << compose_fg<
      int,
      multi&, mu,
      int(*)(int), sum
   >()(10); //ok
}
