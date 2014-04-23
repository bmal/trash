#include <chrono>
#include <limits>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include "test_quicksort_v2.cpp"

using namespace std;

template<typename T>
list<T> sequential_quicksort(list<T> input)
{
   if(input.empty())
      return input;

   list<T> result;
   result.splice(result.begin(), input, input.begin());
   const T& privot = *result.begin();

   auto divide_point = partition(input.begin(), input.end(), 
         [&](T const& t){return t < privot;});

   list<T> lower_part;
   lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

   auto new_lower(sequential_quicksort(move(lower_part)));
   auto new_higher(sequential_quicksort(move(input)));

   result.splice(result.end(), new_higher);
   result.splice(result.begin(), new_lower);
   return result;
};

template<typename T>
list<T> parallel_quicksort(list<T> input)
{
   if(input.empty())
      return input;

   list<T> result;
   result.splice(result.begin(), input, input.begin());
   const T& privot = *result.begin();

   auto divide_point = partition(input.begin(), input.end(), 
         [&](T const& t){return t < privot;});

   list<T> lower_part;
   lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

   future<list<T> > new_lower(async(&parallel_quicksort<T>, move(lower_part)));
   auto new_higher(parallel_quicksort(move(input)));

   result.splice(result.end(), new_higher);
   result.splice(result.begin(), new_lower.get());
   return result;
};

int main()
{
   vector<int> v;
   for(int i = 0; i < 100000; ++i)
      v.push_back(i);
   random_shuffle(v.begin(), v.end());
   list<int> l;
   for(vector<int>::size_type i = 0; i < v.size(); ++i)
      l.push_back(v[i]);
   auto s_start = chrono::steady_clock::now();
   l = sequential_quicksort(l);
   auto s_end = chrono::steady_clock::now();
   cout << "Calkowity czas (sequential): " << chrono::duration_cast<chrono::milliseconds>(s_end - s_start).count() << endl;

   l.clear();
   for(vector<int>::size_type i = 0; i < v.size(); ++i)
      l.push_back(v[i]);
   auto p_start_1 = chrono::steady_clock::now();
   l = parallel_quicksort(l);
   auto p_end_1 = chrono::steady_clock::now();
   cout << "Calkowity czas (parallel v1): " << chrono::duration_cast<chrono::milliseconds>(p_end_1 - p_start_1).count() << endl;

   l.clear();
   for(vector<int>::size_type i = 0; i < v.size(); ++i)
      l.push_back(v[i]);
   auto start = chrono::steady_clock::now();
   l.sort();
   auto end = chrono::steady_clock::now();
   cout << "Calkowity czasi (std): " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

   l.clear();
   for(vector<int>::size_type i = 0; i < v.size(); ++i)
      l.push_back(v[i]);
   auto p_start_2 = chrono::steady_clock::now();
   l = parallel_quick_sort(l);
   auto p_end_2 = chrono::steady_clock::now();
   cout << "Calkowity czas (parallel v2): " << chrono::duration_cast<chrono::milliseconds>(p_end_2 - p_start_2).count() << endl;
}
