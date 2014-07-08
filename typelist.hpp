#ifndef TECHNIQUES_HPP
#define TECHNIQUES_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "null_type.h"

template<class T, class U>
struct Typelist
{
   typedef T Head;
   typedef U Tail;
};

namespace TL
{
#define TYPELIST_1(T1) Typelist<T1, Null_type>
#define Typelist_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define Typelist_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define Typelist_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>
#define Typelist_5(T1, T2, T3, T4, T5) Typelist<T1, TYPELIST_4(T2, T3, T4, T5)>
#define Typelist_6(T1, T2, T3, T4, T5, T6) Typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6)>
#define Typelist_7(T1, T2, T3, T4, T5, T6, T7) Typelist<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7)>
#define Typelist_8(T1, T2, T3, T4, T5, T6, T7, T8) Typelist<T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8)>
#define Typelist_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) Typelist<T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9)>

//#####################################################

   template<class TList>
   struct Length;

   template<>
   struct Length<Null_type>
   {
      enum{ value = 0 };
   };

   template<class T, class U>
   struct Length<Typelist<T, U> >
   {
      enum{ value = 1 + Length<U>::value };
   };

//#####################################################

   template<class Tlist, unsigned int index>
   struct Type_at;

   template<class Head, class Tail>
   struct Type_at<Typelist<Head, Tail>, 0>
   {
      typedef Head Result;
   };

   template<class Head, class Tail, unsigned int i>
   struct Type_at<Typelist<Head, Tail>, i>
   {
      typedef typename Type_at<Tail, i - 1>::Result Result;
   };

//#####################################################

   template<class TList, class T>
   struct Index_of;

   template<class T>
   struct Index_of<Null_type, T>
   {
      enum{ value = -1 };
   };

   template<class T, class Tail>
   struct Index_of<Typelist<T, Tail>, T>
   {
      enum{ value = 0 };
   };

   template<class Head, class Tail, class T>
   struct Index_of<Typelist<Head, Tail>, T>
   {
   private:
      enum{ tmp = Index_of<Tail, T>::value };
   public:
      enum{ value = tmp == -1 ? -1 : 1 + tmp };
   };

//#####################################################

   template<class TList, class T>
   struct Append;

   template<>
   struct Append<Null_type, Null_type>
   {
      typedef Null_type Result;
   };

   template<class T>
   struct Append<Null_type, T>
   {
      typedef TYPELIST_1(T) Result;
   };

   template<class Head, class Tail>
   struct Append<Null_type, Typelist<Head, Tail> >
   {
      typedef Typelist<Head, Tail> Result;
   };

   template<class Head, class Tail, class T>
   struct Append<Typelist<Head, Tail>, T>
   {
      typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
   };

//#####################################################

   template<class TList, class T>
   struct Erase;

   template<class T>
   struct Erase<Null_type, T>
   {
      typedef Null_type Result;
   };

   template<class T, class Tail>
   struct Erase<Typelist<T, Tail>, T>
   {
      typedef Tail Result;
   };

   template<class Head, class Tail, class T>
   struct Erase<Typelist<Head, Tail>, T>
   {
      typedef Typelist<Head, typename Erase<Tail, T>::Result> Result;
   };

//#####################################################

   template<class TList, class T>
   struct Erase_all;

   template<class T>
   struct Erase_all<Null_type, T>
   {
      typedef Null_type Result;
   };

   template<class T, class Tail>
   struct Erase_all<Typelist<T, Tail>, T>
   {
      typedef typename Erase_all<Tail, T>::Result Result;
   };

   template<class Head, class Tail, class T>
   struct Erase_all<Typelist<Head, Tail>, T>
   {
      typedef Typelist<Head, typename Erase_all<Tail, T>::Result> Result;
   };

//#####################################################

   template<class TList>
   struct Unique;

   template<>
   struct Unique<Null_type>
   {
      typedef Null_type Result;
   };

   template<class Head, class Tail>
   struct Unique<Typelist<Head, Tail> >
   {
   private:
      typedef typename Unique<Tail>::Result L1;
      typedef typename Erase<L1, Head>::Result L2;
   public:
      typedef Typelist<Head, L2> Result;
   };

//#####################################################

   template<class TList, class T, class U>
   struct Replace;

   template<class T, class U>
   struct Replace<Null_type, T, U>
   {
      typedef Null_type Result;
   };

   template<class T, class Tail, class U>
   struct Replace<Typelist<T, Tail>, T, U>
   {
      typedef Typelist<U, Tail> Result;
   };

   template<class Head, class Tail, class T, class U>
   struct Replace<Typelist<Head, Tail>, T, U>
   {
      typedef Typelist<Head, typename Replace<Tail, T, U>::Result> Result;
   };

//#####################################################

   template<class TList, class T, class U>
   struct Replace_all;

   template<class T, class U>
   struct Replace_all<Null_type, T, U>
   {
      typedef Null_type Result;
   };

   template<class T, class Tail, class U>
   struct Replace_all<Typelist<T, Tail>, T, U>
   {
      typedef Typelist<U, typename Replace_all<Tail, T, U>::Result> Result;
   };

   template<class Head, class Tail, class T, class U>
   struct Replace_all<Typelist<Head, Tail>, T, U>
   {
      typedef Typelist<Head, typename Replace_all<Tail, T, U>::Result> Result;
   };
}

#endif
