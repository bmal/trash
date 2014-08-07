#include "boost/mpl/deref.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/iterator_tags.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/advance.hpp"
#include "boost/mpl/or.hpp"
#include "boost/mpl/int.hpp"
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

   typedef typename Index::category category;
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
         > type;
      };

      template<class Seq, class Index>
      struct deref<permutation_iterator<Seq, Index>>
      {
         typedef typename at<
            Seq,
            typename deref<Index>::type
         >::type type;
      };

      template<class Seq, class Index>
      struct prior<permutation_iterator<Seq, Index>>
      {
/*       BOOST_STATIC_ASSERT((
                     std::is_convertible<
                     typename Index::category,
                     mpl::bidirectional_iterator_tag
                  >::value));
*/
         BOOST_STATIC_ASSERT((
                  mpl::or_<
                     typename std::is_same<
                        typename Index::category,
                        mpl::bidirectional_iterator_tag
                     >::type,
                     typename std::is_same<
                        typename Index::category,
                        mpl::random_access_iterator_tag
                     >::type
                  >::value));

         typedef typename ::permutation_iterator<
            Seq,
            typename mpl::prior<Index>::type
         > type;
      };

      template<class Seq, class Index, class N>
      struct advance<permutation_iterator<Seq, Index>, N>
      {
         BOOST_STATIC_ASSERT((
                  std::is_same<
                     typename Index::category,
                     mpl::random_access_iterator_tag
                  >::value));

         typedef typename ::permutation_iterator<
            Seq,
            typename mpl::advance<
               Index,
               N
            >::type
         > type;
      };

      template<class Seq, class Index1, class Index2>
      struct distance<
         permutation_iterator<Seq, Index1>,
         permutation_iterator<Seq, Index2>
      >
      {
         BOOST_STATIC_ASSERT((
                  std::is_same<
                     typename Index1::category,
                     mpl::random_access_iterator_tag
                  >::value));

         typedef typename mpl::distance<Index1, Index2>::type type;
      };
   }
}

typedef mpl::vector_c<int, 10, 20, 30, 40, 50> sequence;
typedef mpl::vector_c<int, 2, 0, 1, 0, 4> index;

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
               mpl::next<
                  permutation_iterator<
                     sequence, 
                     mpl::begin<index>::type
                  >
               >::type
            >::type,
            mpl::int_<10>
         >::value));

BOOST_STATIC_ASSERT((
         mpl::equal_to<
            mpl::deref<
               mpl::prior<
                  permutation_iterator<
                     sequence, 
                     mpl::end<index>::type
                  >
               >::type
            >::type,
            mpl::int_<50>
         >::value));

BOOST_STATIC_ASSERT((
         mpl::equal_to<
            mpl::deref<
               mpl::advance<
                  permutation_iterator<
                     sequence,
                     mpl::begin<index>::type
                  >,
                  mpl::int_<1>
               >::type
            >::type,
            mpl::int_<10>
         >::value));


BOOST_STATIC_ASSERT((
         mpl::equal_to<
            mpl::distance<
               permutation_iterator<
                  sequence,
                  mpl::begin<index>::type
               >,
               mpl::next<
                  permutation_iterator<
                     sequence,
                     mpl::begin<index>::type
                  >
               >::type
            >::type,
            mpl::int_<1>
         >::value));
