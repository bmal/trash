#ifndef BOOST_MPL_TINY_HPP
#define BOOST_MPL_TINY_HPP

#include "boost/mpl/iterator_tags.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/push_back.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/minus.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/insert.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/pop_back.hpp"
#include "boost/static_assert.hpp"

struct none
{};

struct tiny_tag
{};

template
<
   class T0 = none,
   class T1 = none,
   class T2 = none
>
struct tiny
{
   typedef tiny type;
   typedef tiny_tag tag;

   typedef T0 t0;
   typedef T1 t1;
   typedef T2 t2;
};

template<class Tiny, class Pos>
struct tiny_iterator
{
   typedef boost::mpl::random_access_iterator_tag category;
};

//#############################################################

template<class Tiny, int N>
struct tiny_at;

template<class Tiny>
struct tiny_at<Tiny, 0>
{
   typedef typename Tiny::t0 type;
};

template<class Tiny>
struct tiny_at<Tiny, 1>
{
   typedef typename Tiny::t1 type;
};

template<class Tiny>
struct tiny_at<Tiny, 2>
{
   typedef typename Tiny::t2 type;
};

//#############################################################

template
<
   class T0,
   class T1,
   class T2
>
struct tiny_size
: boost::mpl::int_<3>
{};

template
<
   class T0,
   class T1
>
struct tiny_size<T0, T1, none>
: boost::mpl::int_<2>
{};

template<class T0>
struct tiny_size<T0, none, none>
: boost::mpl::int_<1>
{};

template<>
struct tiny_size<none, none, none>
: boost::mpl::int_<0>
{};

/*#############################################################

template<class Tiny, class T, int N>
struct tiny_push_back;

template<class Tiny, class T>
struct tiny_push_back<Tiny, T, 0>
: tiny<T, none, none>
{};

template<class Tiny, class T>
struct tiny_push_back<Tiny, T, 1>
: tiny<typename Tiny::t0, T, none>
{};

template<class Tiny, class T>
struct tiny_push_back<Tiny, T, 2>
: tiny<typename Tiny::t0, typename Tiny::t1, T>
{};

//#############################################################*/

template<class Tiny, int size>
struct tiny_pop_back;

template<class Tiny>
struct tiny_pop_back<Tiny, 1>
: tiny<>
{};

template<class Tiny>
struct tiny_pop_back<Tiny, 2>
: tiny<typename Tiny::t0>
{};

template<class Tiny>
struct tiny_pop_back<Tiny, 3>
: tiny<typename Tiny::t0, typename Tiny::t1>
{};

//#############################################################*/

template<class Tiny, class T, int N>
struct tiny_push_front;

template<class Tiny, class T>
struct tiny_push_front<Tiny, T, 0>
: tiny<T, none, none>
{};

template<class Tiny, class T>
struct tiny_push_front<Tiny, T, 1>
: tiny<T, typename Tiny::t0, none>
{};

template<class Tiny, class T>
struct tiny_push_front<Tiny, T, 2>
: tiny<T, typename Tiny::t0, typename Tiny::t1>
{};

//#############################################################

template<class Tiny, class T, class Pos, bool Is_full>
struct tiny_insert;

template<class Tiny, class T> 
struct tiny_insert<Tiny, T, tiny_iterator<Tiny, boost::mpl::int_<0>>, false>
: tiny<T, typename Tiny::t0, typename Tiny::t1>
{};

template<class Tiny, class T>
struct tiny_insert<Tiny, T, tiny_iterator<Tiny, boost::mpl::int_<1>>, false> 
: tiny<typename Tiny::t0, T, typename Tiny::t1>
{};

template<class Tiny, class T>
struct tiny_insert<Tiny, T, tiny_iterator<Tiny, boost::mpl::int_<2>>, false>
: tiny<typename Tiny::t0, typename Tiny::t1, T>
{};

//#############################################################

namespace boost
{
   namespace mpl
   {
      template<class Tiny, class Pos>
      struct next<tiny_iterator<Tiny, Pos>>
      {
         typedef tiny_iterator<Tiny, typename boost::mpl::next<Pos>::type> type;
      };

      template<class Tiny, class Pos>
      struct prior<tiny_iterator<Tiny, Pos>>
      {
         typedef tiny_iterator<Tiny, typename boost::mpl::prior<Pos>::type> type;
      };

      template<class Tiny, class Pos>
      struct deref<tiny_iterator<Tiny, Pos>>
      : at<Tiny, Pos>
      {};

      template<class Tiny, class Pos, class N>
      struct advance<tiny_iterator<Tiny, Pos>, N>
      {
         typedef tiny_iterator<
            Tiny,
            typename mpl::plus<Pos, N>::type
         > type;
      };

      template<class Tiny, class Pos1, class Pos2>
      struct distance<
         tiny_iterator<Tiny, Pos1>,
         tiny_iterator<Tiny, Pos2>
      >
      : mpl::minus<Pos2, Pos1>
      {};

//#############################################################

      template<>
      struct at_impl<tiny_tag>
      {
         template<class Tiny, class N>
         struct apply
         : tiny_at<Tiny, N::value>
         {};
      };

//#############################################################

      template<>
      struct begin_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         {
            typedef tiny_iterator<Tiny, int_<0>> type;
         };
      };

      template<>
      struct end_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         {
            typedef tiny_iterator<
               Tiny,
               typename tiny_size<
                  typename Tiny::t0,
                  typename Tiny::t1,
                  typename Tiny::t2
               >::type
            > type;
         };
      };

//#############################################################

      template<>
      struct size_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         : tiny_size<
              typename Tiny::t0,
              typename Tiny::t1,
              typename Tiny::t2>
         {};
      };

//#############################################################

      template<>
      struct clear_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         : tiny<>
         {};
      };

      template<>
      struct push_front_impl<tiny_tag>
      {
         template<class Tiny, class T>
         struct apply
         : tiny_push_front<Tiny, T, size<Tiny>::value>
         {};
      };

      template<>
      struct push_back_impl<tiny_tag>
      {
         template<class Tiny, class T>
         struct apply
         : boost::mpl::insert<Tiny, T, typename end<Tiny>::type>
         {};
      };

      template<>
      struct insert_impl<tiny_tag>
      {
         template<class Tiny, class T, class Iter>
         struct apply
         : tiny_insert<Tiny, T, Iter,
            equal_to<
               typename size<Tiny>::type,
               int_<3>
            >::value
           >
         {};
      };

      template<>
      struct pop_front_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         : tiny<typename Tiny::t1, typename Tiny::t2, none>
         {}; 
      };

      template<>
      struct pop_back_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         : tiny_pop_back<Tiny, size<Tiny>::type::value>
         {};
      };
   }
}

#endif
