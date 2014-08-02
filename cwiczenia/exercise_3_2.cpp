#include <iostream>
#include "boost/mpl/transform.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/multiplies.hpp"

using namespace std;

int main()
{
   using namespace boost::mpl::placeholders;

   typedef boost::mpl::vector_c<int, 1, 2, 3> v;
   typedef boost::mpl::vector_c<int, 1, 4, 9> v_2;
   typedef boost::mpl::transform<v, boost::mpl::multiplies<_1, _1>>::type type; 

   cout << boolalpha << "v^2 = v_2 to " << boost::mpl::equal<v_2, type>::type::value;
}
