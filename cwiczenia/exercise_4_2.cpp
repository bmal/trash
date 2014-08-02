#include "boost/static_assert.hpp"
#include "boost/mpl/eval_if.hpp"
#include "boost/mpl/bool.hpp"

namespace mpl =  boost::mpl;
 
template<typename T1, typename T2, typename T3 = mpl::false_, typename T4 = mpl::false_, typename T5 = mpl::false_>
struct logical_or
: mpl::eval_if<T1, mpl::true_,
   mpl::eval_if<T2, mpl::true_,
   mpl::eval_if<T3, mpl::true_,
   mpl::eval_if<T4, mpl::true_,
   mpl::eval_if<T5, mpl::true_,
   mpl::false_>>>>>::type       //hmmm, there is no value
{};
 
template<typename T1, typename T2, typename T3 = mpl::true_, typename T4 = mpl::true_, typename T5 = mpl::true_>
struct logical_and 
: mpl::eval_if<T1,
   mpl::eval_if<T2,
   mpl::eval_if<T3,
   mpl::eval_if<T4,
   mpl::eval_if<T5, mpl::true_, mpl::false_>,
   mpl::false_>, mpl::false_>, mpl::false_>, mpl::false_>::type         //hmmm
{};

using namespace mpl;
 
BOOST_STATIC_ASSERT((logical_or<false_, mpl::false_, mpl::true_>::value));
BOOST_STATIC_ASSERT((logical_or<false_, mpl::false_>::value == mpl::false_::value));
BOOST_STATIC_ASSERT((logical_or<true_, mpl::true_, mpl::true_>::value == mpl::true_::value));

BOOST_STATIC_ASSERT((logical_and<false_, mpl::true_>::value == mpl::false_::value));
BOOST_STATIC_ASSERT((logical_and<true_, mpl::true_>::value == mpl::true_::value));
BOOST_STATIC_ASSERT((logical_and<false_, mpl::false_>::value == mpl::false_::value));

int main()
{
}
