#ifndef BOOST_MPL_TINY_HPP
#define BOOST_MPL_TINY_HPP

include <boost/mpl/iterator_tags.hpp>
include <boost/mpl/next.hpp>
include <boost/mpl/prior.hpp>
include <boost/mpl/at.hpp>
include <boost/mpl/begin_end.hpp>
include <boost/mpl/size.hpp>
include <boost/mpl/clear.hpp>
include <boost/mpl/push_front.hpp>
include <boost/mpl/push_back.hpp>
include <boost/mpl/plus.hpp>
include <boost/mpl/minus.hpp>
include <boost/mpl/equal_to.hpp>
include <boost/mpl/insert.hpp>
include <boost/mpl/pop_front.hpp>
include <boost/mpl/pop_back.hpp>
include <boost/static_assert.hpp>

#include <boost/preprocessor.hpp>

struct none
{};

struct tiny_tag
{};

#ifndef TINY_MAX_SIZE
#   define TINY_MAX_SIZE 3
#endif

#define BOOST_TINY_typedef_helper(z, n, data)           \
   typedef BOOST_PP_CAT(T, n) BOOST_PP_CAT(t, n);

template
<
   BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(TINY_MAX_SIZE, class T, none)
>
struct tiny
{
   typedef tiny type;
   typedef tiny_tag tag;

#define BOOST_PP_LOCAL_MACRO(n) BOOST_TINY_typedef_helper(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, TINY_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()
};

#undef BOOST_TINY_typedef_helper

template<class Tiny, class Pos>
struct tiny_iterator
{
   typedef boost::mpl::random_access_iterator_tag category;
};

//#############################################################

template<class Tiny, int N>
struct tiny_at;

#define BOOST_TINY_at(z, n, data)                       \
   template<class Tiny>                                 \
   struct tiny_at<Tiny, n>                              \
   {                                                    \
      typedef typename BOOST_PP_CAT(Tiny::t, n) type;   \
   };

#define BOOST_PP_LOCAL_MACRO(n) BOOST_TINY_at(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, TINY_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_TINY_at

//#############################################################

template<BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, class T)>
struct tiny_size
   : boost::mpl::int_<TINY_MAX_SIZE>
{};

#define TINY_print(z, n, data) data

#define TINY_size(z, n, unused)                                 \
   template<BOOST_PP_ENUM_PARAMS(n, class T)>                   \
   struct tiny_size<                                            \
      BOOST_PP_ENUM_PARAMS(n, T)                                \
      BOOST_PP_COMMA_IF(n)                                      \
      BOOST_PP_ENUM(                                            \
            BOOST_PP_SUB(TINY_MAX_SIZE, n), TINY_print, none)   \
   >                                                            \
      : boost::mpl::int_<n>                                     \
   {};

#define BOOST_PP_LOCAL_MACRO(n) TINY_size(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, TINY_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

#undef TINY_size
#undef TINY_print

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

#define TINY_typename_helper(z, n, end)                                         \
   BOOST_PP_CAT(typename Tiny::t, n)                                            \
   BOOST_PP_COMMA_IF(BOOST_PP_LESS(n, BOOST_PP_DEC(end)))

#define TINY_pop_back(z, n, data)                                         \
template<class Tiny>                                                            \
struct tiny_pop_back<Tiny, n>                                                   \
: tiny<BOOST_PP_REPEAT(BOOST_PP_DEC(n), TINY_typename_helper, BOOST_PP_DEC(n))> \
{};

#define BOOST_PP_LOCAL_MACRO(n) TINY_pop_back(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (1, TINY_MAX_SIZE)
#include BOOST_PP_LOCAL_ITERATE()

#undef TINY_typename_helper
#undef TINY_pop_back

//#############################################################*/

template<class Tiny, class T, int N>
struct tiny_push_front;

#define TINY_print(z, n, data) data

#define TINY_push_front_helper(n)                                               \
   BOOST_PP_NOT_EQUAL(n, BOOST_PP_DEC(TINY_MAX_SIZE))

#define TINY_push_front(z, n, unused)                                           \
template<class Tiny, class T>                                                   \
struct tiny_push_front<Tiny, T, n>                                              \
: tiny<T, BOOST_PP_ENUM_PARAMS(n, typename Tiny::t)                             \
   BOOST_PP_COMMA_IF(BOOST_PP_AND(n, TINY_push_front_helper(n)))                \
   BOOST_PP_ENUM(                                                               \
         BOOST_PP_SUB(BOOST_PP_DEC(TINY_MAX_SIZE), n), TINY_print, none)>       \
{};

#define BOOST_PP_LOCAL_MACRO(n) TINY_push_front(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, TINY_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

#undef TINY_push_front_helper
#undef TINY_print
#undef TINY_push_front

//#############################################################

template<class Tiny, class T, class Pos, bool Is_full>
struct tiny_insert;

#define TINY_insert_max BOOST_PP_SUB(TINY_MAX_SIZE, 1)
#define TINY_counter (0)
#define TINY_insert_helper(n) BOOST_PP_NOT_EQUAL(n, TINY_insert_max)
#define TINY_insert_helper2(n) BOOST_PP_SUB(TINY_insert_max, n)
#define TINY_print(z, n, data) data                                                     //TODO

#define TINY_insert(z, n, unused)                                                       \
template<class Tiny, class T>                                                           \
struct tiny_insert<Tiny, T, tiny_iterator<Tiny, boost::mpl::int_<n>>, false>            \
: tiny<                                                                                 \
         BOOST_PP_ENUM_PARAMS(n, typename Tiny::t)                                      \
         BOOST_PP_COMMA_IF(n)                                                           \
         T                                                                              \
         BOOST_PP_COMMA_IF(TINY_insert_helper(n))                                       \
         BOOST_PP_ENUM(TINY_insert_helper2(n), TINY_print, typename Tiny::t)            \//i need counter... and sleep.
>                                                                                       \
{};

#define BOOST_PP_LOCAL_MACRO(n) TINY_insert(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, TINY_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

#undef TINY_insert_helper
#undef TINY_insert_helper2
#undef TINY_print
#undef TINY_insert_size
#undef TINY_insert

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
                  BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, typename Tiny::t)
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
               BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, typename Tiny::t)
           >
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
               int_<TINY_MAX_SIZE>
            >::value
           >
         {};
      };

#define TINY_pop_front_imp(z, n, data)                    \
           BOOST_PP_CAT(typename Tiny::t, n) BOOST_PP_COMMA()

#define BOOST_PP_LOCAL_MACRO(n) TINY_pop_front_imp(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (1, TINY_MAX_SIZE - 1)

      template<>
      struct pop_front_impl<tiny_tag>
      {
         template<class Tiny>
         struct apply
         : tiny<
#          include BOOST_PP_LOCAL_ITERATE() 
           none
           >
         {}; 
      };

#undef TINY_pop_front_imp

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
