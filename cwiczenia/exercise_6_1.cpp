#include "boost/static_assert.hpp"
#include "boost/mpl/reverse_fold.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/iterator_tags.hpp"
#include "boost/mpl/begin.hpp"
#include "boost/mpl/end.hpp"
#include "boost/mpl/deref.hpp"
#include "boost/mpl/times.hpp"

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

struct binary_sequence_tag
{};

template<unsigned long Q, unsigned long R>
struct binary_iterator
{
   typedef mpl::forward_iterator_tag category;
   typedef binary_iterator type;
   typedef binary_iterator<Q/10, Q%10> next;
};

template<>
struct binary_iterator<0,0> 
{
   typedef binary_iterator type;
};

template<unsigned long N>
struct binary_sequence 
{
   typedef binary_sequence_tag tag;
};

template<unsigned long N>
struct binary 
: mpl::reverse_fold<
      binary_sequence<N>, 
      mpl::int_<0>, 
      mpl::plus<mpl::times<_1, mpl::int_<2>>, _2>
   >::type
{};

namespace boost
{
   namespace mpl
   {
      template<>
      struct begin_impl<binary_sequence_tag>
      {
         template<typename Seq>
         struct apply;

         template<unsigned long N>
         struct apply<binary_sequence<N>> 
         : binary_iterator<N/10, N%10>
         {};
      };

      template<>
      struct end_impl<binary_sequence_tag>
      {
         template<typename Seq>
         struct apply 
         : binary_iterator<0, 0>
         {};
      };

      template<unsigned long Q, unsigned long R>
      struct deref<binary_iterator<Q, R>> 
      : mpl::int_<R> 
      {};
   }
}

//###################################################################

struct decimal_sequence_tag 
{};

template<unsigned long Q, unsigned long R>
struct decimal_iterator 
{
   typedef mpl::forward_iterator_tag category;
   typedef decimal_iterator type;
   typedef decimal_iterator<Q/2, Q%2> next;
};

template<>
struct decimal_iterator<0,0> 
{
   typedef decimal_iterator type;
};

template<unsigned long N>
struct decimal_sequence 
{
   typedef decimal_sequence_tag tag;
};

template<unsigned long N>
struct decimal 
: mpl::reverse_fold<
      decimal_sequence<N>, 
      mpl::int_<0>, 
      mpl::plus<mpl::times<_1, mpl::int_<10>>, _2>
   >::type
{};

namespace boost
{
   namespace mpl
   {
      template<>
      struct begin_impl<decimal_sequence_tag>
      {
         template<typename Seq>
         struct apply;

         template<unsigned long N>
         struct apply<decimal_sequence<N>> 
         : decimal_iterator<N/2, N%2>
         {};
      };

      template<>
      struct end_impl<decimal_sequence_tag>
      {
         template<typename Seq>
         struct apply 
         : decimal_iterator<0, 0>
         {};
      };

      template<unsigned long Q, unsigned long R>
      struct deref<decimal_iterator<Q, R>> 
      : mpl::int_<R>
      {};
   }
}

   BOOST_STATIC_ASSERT((binary<0>::value == 0));
   BOOST_STATIC_ASSERT((binary<1>::value == 1));
   BOOST_STATIC_ASSERT((binary<10>::value == 2));
   BOOST_STATIC_ASSERT((binary<11>::value == 3));
   BOOST_STATIC_ASSERT((binary<100>::value == 4));
   BOOST_STATIC_ASSERT((binary<101>::value == 5));
   BOOST_STATIC_ASSERT((binary<110>::value == 6));
   BOOST_STATIC_ASSERT((binary<111>::value == 7));

   BOOST_STATIC_ASSERT((decimal<0>::value == 0));
   BOOST_STATIC_ASSERT((decimal<1>::value == 1));
   BOOST_STATIC_ASSERT((decimal<2>::value == 10));
   BOOST_STATIC_ASSERT((decimal<3>::value == 11));
   BOOST_STATIC_ASSERT((decimal<4>::value == 100));
   BOOST_STATIC_ASSERT((decimal<5>::value == 101));
   BOOST_STATIC_ASSERT((decimal<6>::value == 110));
   BOOST_STATIC_ASSERT((decimal<7>::value == 111));
