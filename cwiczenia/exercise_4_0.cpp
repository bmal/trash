#include "boost/static_assert.hpp"
#include "boost/mpl/or.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/equal_to.hpp"

using namespace boost::mpl;

BOOST_STATIC_ASSERT((or_<false_, false_, true_>::value));
BOOST_STATIC_ASSERT((or_<false_, false_>::value == false_::value));
BOOST_STATIC_ASSERT((or_<true_, true_, true_>::value == true_::value));

BOOST_STATIC_ASSERT((and_<false_, true_>::value == false_::value));
BOOST_STATIC_ASSERT((and_<true_, true_>::value == true_::value));
BOOST_STATIC_ASSERT((and_<false_, false_>::value == false_::value));

int main()
{
}
