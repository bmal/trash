#include <iostream>

template<char...>
struct sumator;

template<char last>
struct sumator<last>
{
   static constexpr int result()
   {
      return last - 48;
   }
};

template<char head, char... tail>
struct sumator<head, tail...>
{
   static constexpr int result()
   {
      return head - 48 + sumator<tail...>::result();
   } 
};


template<char... args>
constexpr int operator"" _sum()
{
   return sumator<args...>::result();
}

int main()
{
   using namespace std;
   cout << 1232_sum;
}
