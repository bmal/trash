#ifndef IS_CLASS_OR_UNION_HPP
#define IS_CLASS_OR_UNION_HPP

#include "boost/mpl/bool.hpp"

template<class T>
struct is_class_or_union
{
   typedef char yes;
   typedef char (&no)[2];

   template<class U>
   static yes tester(int U::*arg);

   template<class U>
   static no tester(...);

   static const bool value = 
      sizeof(is_class_or_union::tester<T>(0)) == sizeof(yes);

   typedef boost::mpl::bool_<value> type;
};

#endif
