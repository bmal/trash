#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#ifndef TINY_MAX_SIZE
#   define TINY_MAX_SIZE 3
#endif

struct none
{};

template<BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE, class T)>
struct tiny_size;

#define BOOST_PP_ITERATION_LIMITS (0, TINY_MAX_SIZE - 1)
#define BOOST_PP_FILENAME_1 <preproc_spec.hpp>

#include BOOST_PP_ITERATE()

//compilation:
//g++ -P -E -I. preproc3.cpp -o preproc3_result.cpp
