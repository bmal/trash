#ifndef TUPLE_PRINT_HPP
#   define TUPLE_PRINT_HPP

#include <tuple>
#include <iostream>

template<int Index, int Max, typename... Args>
struct Print_tuple
{
   static void print(std::ostream& o, const std::tuple<Args...>& t)
   {
      o << std::get<Index>(t) << (Index + 1 == Max ? "" : ",");
      Print_tuple<Index + 1, Max, Args...>::print(o, t);
   }
};

template<int Max, typename... Args>
struct Print_tuple<Max, Max, Args...>
{
   static void print(std::ostream&, const std::tuple<Args...>&)
   {}
};

template<typename... Args>
std::ostream& operator<<(std::ostream& o, std::tuple<Args...>& t)
{
   o << "[";
   Print_tuple<0, sizeof...(Args), Args...>::print(o, t);
   return o << "]";
}

#endif
