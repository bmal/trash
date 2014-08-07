#include "boost/mpl/joint_view.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/advance.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

template<class Seq, class Iter>
struct rotate_view
 : mpl::joint_view<
      mpl::iterator_range<
         Iter,
         typename mpl::end<Seq>::type
      >,
      mpl::iterator_range<
         typename mpl::begin<Seq>::type,
         Iter
      >
   >::type
{};

typedef mpl::vector_c<int, 5,6,7,8,9,0,1,2,3,4> v;
typedef rotate_view<
   v,
   mpl::advance<
      mpl::begin<v>::type,
      mpl::int_<5>
   >::type
> view;

BOOST_STATIC_ASSERT((
         mpl::equal<
            view,
            mpl::range_c<int, 0, 10>
         >::value));
