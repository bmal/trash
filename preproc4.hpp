#ifndef PREPROC4_HPP
#   define PREPROC4_HPP

#   include "boost/preprocessor/repetition.hpp"
#   include "boost/preprocessor/arithmetic/sub.hpp"
#   include "boost/preprocessor/punctuation/comma_if.hpp"
#   include "boost/preprocessor/iteration/iterate.hpp"

#   ifndef TINY_MAX_SIZE
#      define TINY_MAX_SIZE 3
#   endif

struct none
{};

template<BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, class T)>
struct tiny_size
   : mpl::int_<TINY_MAX_SIZE>
{};

#   define BOOST_PP_ITERATION_LIMITS (0, TINY_MAX_SIZE - 1)
#   define BOOST_PP_FILENAME_1 <preproc4.hpp>
#   include BOOST_PP_ITERATE()

#else

#   define n BOOST_PP_ITERATION()

#   define TINY_print(z, n, data) data

template<BOOST_PP_ENUM_PARAMS(n, class T)>
struct tiny_size<
   BOOST_PP_ENUM_PARAMS(n, T) BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM(BOOST_PP_SUB(TINY_MAX_SIZE, n), TINY_print, none)
>
   : mpl::int_<n>
{};

#   undef TINY_print
#   undef n

#endif
