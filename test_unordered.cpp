#include <iostream>
#include <unordered_set>
#include <iomanip>
#include <utility>
#include <iterator>
#include <typeinfo>
#include <functional>

//boost/functional/hash
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
   seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
   hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_value(std::size_t& seed, const T& val, const Types&... args)
{
   hash_combine(seed, val);
   hash_value(seed, args...);
}

template<typename... Types>
inline std::size_t hast_value(const Types&... args)
{
   std::size_t seed = 0;
   hash_value(seed, args...);
   return seed;
}


template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& o, const std::pair<T1, T2>& p)
{
   return o << "[" << p.first << "," << p.second << "]";
}

template<typename T>
void print_hash_table_state (const T& col)
{
   std::cout << "rozmiar:               " << col.size() << '\n';
   std::cout << "liczba kubelkow:       " << col.bucket_count() << '\n';
   std::cout << "wsp.obciazenia:        " << col.load_factor() << '\n';
   std::cout << "maks. wsp. obciazenia: " << col.max_load_factor() << '\n';

   if(typeid(typename std::iterator_traits<
         typename T::iterator
      >::iterator_category)
      == typeid(std::bidirectional_iterator_tag))
   {
      std::cout << "typ polaczenia:        lista dwukierunkowa\n\n";
   }
   else
      std::cout << "typ polaczenia:        lista jednokierunkowa\n\n";

   std::cout << "dane:\n";
   for(auto i = 0; i != col.bucket_count(); ++i)
   {
      std::cout << "bucket[" << std::setw(2) << i << "]: ";
      for(auto pos = col.begin(i); pos != col.end(i); ++pos)
         std::cout << *pos << " ";

      std::cout << std::endl;
   }
   std::cout << std::endl;
}

int main()
{
   std::unordered_set<int> us = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30};
   print_hash_table_state(us);
}
