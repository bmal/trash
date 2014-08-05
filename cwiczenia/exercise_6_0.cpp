#include "boost/static_assert.hpp"
#include "boost/mpl/copy.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/inserter.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/sizeof.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/min_element.hpp"

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template<class Seq>
struct smallest
: mpl::copy<
     Seq,
     mpl::inserter<
        typename mpl::front<Seq>::type,
        mpl::if_<
           mpl::less<mpl::sizeof_<_1>, mpl::sizeof_<_2>>,
            _1, 
            _2
        >
     >
  >
{};

BOOST_STATIC_ASSERT((
         std::is_same<
            smallest<mpl::vector<int[2], char, double&, long>>::type,
            char
         >::value
));

//we have mpl::min_element
BOOST_STATIC_ASSERT((
         std::is_same<
            mpl::deref<
               mpl::min_element<
                  mpl::vector<int[2], char, double&, long>,
                  mpl::less<
                     mpl::sizeof_<_1>,
                     mpl::sizeof_<_2>
                  >
               >::type
            >::type,
            char
         >::value
));
