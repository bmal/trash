#ifndef HIERARCHY_GENERATORS_HPP
#define HIERARCHY_GENERATORS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "typelist.hpp"
#include "empty_type.h"

template<class TList, template<class> class Unit>
class Gen_scatter_hierarchy;

template<class Head, class Tail, template<class> class Unit>
class Gen_scatter_hierarchy<Typelist<Head, Tail>, Unit>
: public Gen_scatter_hierarchy<Head, Unit>,
  public Gen_scatter_hierarchy<Tail, Unit>
{
public:
   typedef Typelist<Head, Tail> TList;
   typedef Gen_scatter_hierarchy<Head, Unit> Left_base;
   typedef Gen_scatter_hierarchy<Tail, Unit> Right_base;

   template<typename T>
   struct Rebind
   {
      typedef Unit<T> Result;
   };
};

template<class Atomic_type, template<class> class Unit>
class Gen_scatter_hierarchy
: public Unit<Atomic_type>
{
   typedef Unit<Atomic_type> Left_base;

   template<typename T>
   struct Rebind
   {
      typedef Unit<T> Result;
   };
};

template<template<class> class Unit>
class Gen_scatter_hierarchy<Null_type, Unit>
{
   template<typename T>
   struct Rebind
   {
      typedef Unit<T> Result;
   };
};

//#####################################################

template<class T, class H>
typename H::template Rebind<T>::Result& 
field(H& obj)
{
   return obj;
}

//#####################################################

template<class H, typename R>
inline R& field_helper(H& obj, Type2Type<R>, Int2Type<0>)
{
   typename H::Left_base& subobj = obj;
   return subobj;
}

template<class H, typename R, int i>
inline R& field_helper(H& obj, Type2Type<R> tt, Int2Type<i>)
{
   typename H::Right_base& subobj = obj;
   return field_helper(subobj, tt, Int2Type<i - 1>());
}

template<int i, class H>
typename H::template Rebind<
   typename TL::Type_at<typename H::TList, i>::Result
   >::Result&
field(H& obj)
{
   typedef typename TL::Type_at<typename H::TList, i>::Result Type;
   typedef typename H::template Rebind<Type>::Result Struct_type;
   return field_helper(obj, Type2Type<Struct_type>(), Int2Type<i>());
}

//#####################################################

template
<
   class TList,
   template<class Atomic_type, class Base> class Unit,
   class Root = Empty_type
>
class Gen_linear_hierarchy;

template
<
   class T1,
   class T2,
   template<class, class> class Unit,
   class Root
>
class Gen_linear_hierarchy<Typelist<T1, T2>, Unit, Root>
: public Unit<T1, Gen_linear_hierarchy<T2, Unit, Root> >
{};

template
<
   class T,
   template<class, class> class Unit,
   class Root
>
class Gen_linear_hierarchy<TYPELIST_1(T), Unit, Root>
: public Unit<T, Root>
{};

#endif
