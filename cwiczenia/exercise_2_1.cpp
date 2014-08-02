#include <iostream>

using namespace std;

template<typename T>
struct add_const_ref
{
   typedef const T& type;
};

template<typename T>
struct add_const_ref<T&>
{
   typedef T& type;
};

int main()
{
   cout << boolalpha << "Dla int: " << is_same<const int&, add_const_ref<int>::type>::value << endl;
   cout << "Dla int&: " << is_same<int&, add_const_ref<int&>::type>::value << endl;
}
