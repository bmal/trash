#include "boost/mpl/int.hpp"
#include "boost/mpl/print.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/copy.hpp"
#include "boost/mpl/find_if.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/modulus.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/static_assert.hpp"
#include <type_traits>

#include "boost/mpl/equal.hpp"
#include "boost/mpl/vector_c.hpp"

using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;

template<class Prime, class N>
struct dividable
 : mpl::equal_to<
      typename mpl::modulus<
         N,
         Prime
      >::type,
      mpl::int_<0>
   >
{};

template<class Prime_Seq, class N>
struct is_prime
 : std::is_same<
      typename mpl::find_if<
         Prime_Seq,
         dividable<
            _1,
            N
         >
      >::type,
      typename mpl::end<Prime_Seq>::type
   >
{};

template<class Prime_Seq>
struct is_prime<Prime_Seq, mpl::int_<2>>
 : mpl::true_
{};

template<int N>
struct prime_series
: mpl::copy<
     mpl::range_c<int, 2, N+1>,
     mpl::inserter<
        mpl::vector<>,
        mpl::if_<
           is_prime<_1, _2>,
           mpl::push_back<_1, _2>,
           _1
        >
     >
  >::type
{};

//test
typedef prime_series<10>::type zero_to_ten;
BOOST_STATIC_ASSERT((mpl::equal<zero_to_ten, mpl::vector_c<int, 2,3,5,7>>::value));
