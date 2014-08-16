#include "boost/mpl/fold.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/static_assert.hpp"
#include <type_traits>

using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;

template<class T, class Base>
struct store
 : Base
{
   T value;
};

typedef mpl::vector<short[2], long, char*, int> member_types;

struct empty
{};

typedef mpl::fold<
   member_types,
   empty,
   store<_2, _1>
>::type generated;

BOOST_STATIC_ASSERT((
         std::is_same<
            store<int,
               store<char*,
                  store<long,
                     store<short[2], empty>>>>,
            generated
         >::value));

//mozna zlapac tylko z wierzchu
BOOST_STATIC_ASSERT((
         std::is_same<
            int,
            decltype(generated::value)
         >::value));

//rozwiazanie problemu ^
template<class T, class U>
const store<T, U>& get(const store<T, U>& e)
{
   return e;
}

//przyklad uzycia:
//long a = get<long*>(generated).value


//INNE ROZWIAZANIE #################################################

template<class T>
struct wrap
{
   T value;
};

template<class U, class V>
struct inherit
 : U, V
{};

typedef mpl::fold<
   member_types, empty, inherit<wrap<_2>, _1>
>::type generated_better;

//przyklad uzycia:
//long a = static_cast<wrap<long>&>(generated_better).value;

//GENEROWANIE HIERARCHII LINIOWEj####################################

template<class Types, class Node, class Root = empty>
struct inherit_linearly
 : mpl::fold<Types, Root, Node>
{};

//przyklad uzycia:
typedef inherit_linearly<
   member_types, inherit<wrap<_2>, _1>
>::type generated_best;
