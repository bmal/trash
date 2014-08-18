#include "boost/preprocessor/seq.hpp"

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
   struct is_integral<t>                        \
      : mpl::true_                              \
   {};

BOOST_PP_SEQ_FOR_EACH(BOOST_TT_is_integral_spec, ~, BOOST_TT_ints)

#undef BOOST_TT_ints
#undef BOOST_TT_int_pair
#undef BOOST_TT_basic_ints
#undef BOOST_TT_is_integral_spec
