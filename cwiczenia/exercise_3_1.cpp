#include <iostream>
#include "boost/mpl/transform.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/equal.hpp"

using namespace std;

int main()
{
   using namespace boost::mpl::placeholders;

   typedef boost::mpl::vector_c<int, 1, 2, 3> v;
   typedef boost::mpl::vector_c<int, 2, 3, 4> v_2;
   typedef boost::mpl::int_<1> int_val;
   typedef boost::mpl::transform<v, boost::mpl::plus<_1, boost::mpl::int_<1>>>::type type; 

   cout << boolalpha << "v + int_1 = v_2 to " << boost::mpl::equal<v_2, type>::type::value;
}
