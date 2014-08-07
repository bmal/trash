#include "is_class_or_union.hpp"
#include "boost/static_assert.hpp"

struct s
{};

union u
{};

BOOST_STATIC_ASSERT(!is_class_or_union<int>::value);
BOOST_STATIC_ASSERT(is_class_or_union<s>::value);
BOOST_STATIC_ASSERT(is_class_or_union<u>::value);
