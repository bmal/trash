#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef TINY_MAX_SIZE
#   define TINY_MAX_SIZE 3
#endif

struct none
{};

template<BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, class T)>
struct tiny_size;

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

//compilation:
//g++ -P -E -Wall preproc2.cpp -o preproc2_result.cpp
