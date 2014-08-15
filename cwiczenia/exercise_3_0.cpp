#include "boost/mpl/int.hpp"
#include "boost/static_assert.hpp"

#include "boost/mpl/assert.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/modulus.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/multiplies.hpp"
#include "boost/mpl/divides.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/or.hpp"
#include <type_traits>
#include <iostream>

namespace mpl = boost::mpl;

template<unsigned long N>
struct binary
{
   static const unsigned end_digit = N%10;
   BOOST_STATIC_ASSERT((
            end_digit == 0 || end_digit == 1));

   static const unsigned value = binary<N/10>::value*2 + end_digit;
};

template<>
struct binary<0>
{
   static const unsigned value = 0;
};

BOOST_STATIC_ASSERT((binary<10001>::value == 17));

template<class N>
struct binary_mpl
{
   typedef typename mpl::modulus<N, mpl::int_<10>>::type end_digit;

/*   BOOST_MPL_ASSERT((
            mpl::or_<
               mpl::equal_to<end_digit, mpl::int_<1>>,
               mpl::equal_to<end_digit, mpl::int_<0>>
            >));
*/

   BOOST_MPL_ASSERT_MSG(
         end_digit::value == 1 || end_digit::value == 0,
         TO_NIE_JEST_LICZBA_BINARNA,
         (N));

   typedef typename mpl::plus<
      end_digit,
      typename mpl::multiplies<
         typename binary_mpl<
            typename mpl::divides<N, mpl::int_<10>>::type
         >::type,
         mpl::int_<2>
      >::type
   >::type type;

   static const int value = type::value;
};

template<>
struct binary_mpl<mpl::integral_c<int, 0>>
{
   typedef mpl::int_<0> type;
   static const int value = 0;
};

BOOST_MPL_ASSERT_RELATION(
            binary_mpl<mpl::int_<10001>>::value, ==, 17);
