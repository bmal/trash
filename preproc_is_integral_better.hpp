#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/local.hpp>

template<class T>
struct is_integral
   : mpl::false_
{};

#define BOOST_TT_basic_ints (char)(short)(int)(long)
#define BOOST_TT_int_pair(r, data, t) (signed t)(unsigned t)

#define BOOST_TT_ints                           \
   (bool)(char)                                 \
   BOOST_PP_SEQ_FOR_EACH(BOOST_TT_int_pair, ~, BOOST_TT_basic_ints)

#define BOOST_TT_is_integral_spec(r, data, t)   \
   template<>                                   \
   struct is_integral<t>: mpl::true_ {};

#define BOOST_TT_size                           \
   BOOST_PP_SEQ_SIZE(BOOST_TT_ints)

#define BOOST_PP_LOCAL_MACRO(n)                 \
   BOOST_TT_is_integral_spec(~, ~, BOOST_PP_SEQ_ELEM(n, BOOST_TT_ints))

#define BOOST_PP_LOCAL_LIMITS (0, BOOST_TT_size - 1)

#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_TT_ints
#undef BOOST_TT_int_pair
#undef BOOST_TT_basic_ints
#undef BOOST_TT_is_integral_spec
#undef BOOST_TT_size
