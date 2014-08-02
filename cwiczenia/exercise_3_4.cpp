#include <iostream>
#include <type_traits>
#include "boost/mpl/apply.hpp"

using namespace std;

template<class F, class X>
struct twice
: boost::mpl::apply<F, typename boost::mpl::apply<F, X>::type>
{};

int main()
{
   using namespace boost::mpl::placeholders;
   typedef int val;
   typedef int**** four_pointer;

   cout << boolalpha << is_same<four_pointer, twice<
      add_pointer<_>, twice<add_pointer<_>, int>::type>
      ::type>::value;
}
