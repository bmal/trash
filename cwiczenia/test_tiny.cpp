#include "tiny.hpp"
#include "boost/static_assert.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/int.hpp"
#include <type_traits>
#include <iostream>

typedef tiny<int, bool> tiny_ib;
typedef tiny<int, bool, double> tiny_ibd;
typedef tiny<double, int, bool> tiny_dib;
typedef tiny<> tiny_empty;

//push_front
BOOST_STATIC_ASSERT((
         boost::mpl::equal<
            tiny_dib, boost::mpl::push_front<tiny_ib, 
            double>::type>
         ::value));

//push_back
BOOST_STATIC_ASSERT((
         boost::mpl::equal<
            tiny_ibd, 
            boost::mpl::push_back<tiny_ib, double>::type>
         ::value));

//begin + deref
BOOST_STATIC_ASSERT((
         std::is_same<
            int, 
            boost::mpl::deref<
               boost::mpl::begin<tiny_ib>::type>
            ::type>
         ::value));

//at
BOOST_STATIC_ASSERT((
         std::is_same<
            bool, 
            boost::mpl::at<
               tiny_ibd, 
               boost::mpl::int_<1>>
            ::type>
         ::value));

//next
BOOST_STATIC_ASSERT((
         std::is_same<
            bool,
            boost::mpl::deref<
               boost::mpl::next<
                  boost::mpl::begin<tiny_ibd>::type>
               ::type>
            ::type>
         ::value));

//prior + end
BOOST_STATIC_ASSERT((
         std::is_same<
            double,
            boost::mpl::deref<
               boost::mpl::prior<
                  boost::mpl::end<tiny_ibd>::type>
               ::type>
            ::type>
         ::value));

//advance
BOOST_STATIC_ASSERT((
         std::is_same<
            double,
            boost::mpl::deref<
               boost::mpl::advance<
                  boost::mpl::begin<tiny_ibd>::type,
                  boost::mpl::int_<2>>
               ::type>
            ::type>
         ::value));

//distance
BOOST_STATIC_ASSERT((
         boost::mpl::equal_to<
            boost::mpl::distance<
               boost::mpl::begin<tiny_ibd>::type,
               boost::mpl::advance<
                  boost::mpl::begin<tiny_ibd>::type,
                  boost::mpl::int_<2>>
               ::type>
            ::type,
            boost::mpl::int_<2>>
         ::value));

//clear
BOOST_STATIC_ASSERT((
         boost::mpl::equal<
            tiny_empty,
            boost::mpl::clear<tiny_ib>::type>
         ::value));

//size(2)
BOOST_STATIC_ASSERT((
            boost::mpl::equal_to<
               boost::mpl::size<tiny_ib>::type,
               boost::mpl::int_<2>>
            ::value));

//size(3)
BOOST_STATIC_ASSERT((
            boost::mpl::equal_to<
               boost::mpl::size<tiny_ibd>::type,
               boost::mpl::int_<3>>
            ::value));

//size(0)
BOOST_STATIC_ASSERT((
            boost::mpl::equal_to<
               boost::mpl::size<
                  boost::mpl::clear<tiny_ib>::type
               >::type,
               boost::mpl::int_<0>>
            ::value));
