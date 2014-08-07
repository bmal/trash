#include "boost/mpl/deref.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/iterator_tags.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/equal_to.hpp"
#include <type_traits>
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

template<class Seq, class Index>
class permutation_iterator
{
   BOOST_STATIC_ASSERT((
            std::is_same<
               typename mpl::begin<Seq>::type::category,
               mpl::random_access_iterator_tag
            >::value));

   typedef mpl::forward_iterator_tag category;
   typedef permutation_iterator<Seq, Index> type;
};

namespace boost
{
   namespace mpl
   {
      template<class Seq, class Index>
      struct next<permutation_iterator<Seq, Index>>
      {
         typedef typename ::permutation_iterator<
            Seq,
            typename next<Index>::type
         >::type type;
      };

      template<class Seq, class Index>
      struct deref<permutation_iterator<Seq, Index>>
      {
         typedef typename at<
            Seq,
            typename deref<Index>::type
         >::type type;
      };
   }
}

typedef mpl::vector_c<int, 10, 20, 30, 40, 50> sequence;
typedef mpl::list_c<int, 2, 0, 1, 0, 4> index;

BOOST_STATIC_ASSERT((
         mpl::equal_to<
            mpl::deref<
               permutation_iterator<
                  sequence, 
                  mpl::begin<index>::type
               >::type
            >::type,
            mpl::int_<30>
         >::value));

BOOST_STATIC_ASSERT((
         mpl::equal_to<
            mpl::deref<
               permutation_iterator<
                  sequence, 
                  mpl::next<
                     mpl::begin<index>::type
                  >::type
               >::type
            >::type,
            mpl::int_<10>
         >::value));
