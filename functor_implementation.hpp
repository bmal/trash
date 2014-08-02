#ifndef FUNCTOR_IMPLEMENTATION_HPP
#define FUNCTOR_IMPLEMENTATION_HPP

#include "trash/typelist.hpp"
#include "trash/null_type.h"

template<typename ResultType, class TList>
class Functor_imp;

template<typename ResultType>
class Functor_imp<ResultType, Null_type>
{
   public:
      virtual ResultType operator()() = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, typename P1>
class Functor_imp<ResultType, TYPELIST_1(P1)>
{
   public:
      virtual ResultType operator()(P1) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, typename P1, typename P2>
class Functor_imp<ResultType, TYPELIST_2(P1, P2)>
{
   public:
      virtual ResultType operator()(P1, P2) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, 
   typename P1, 
   typename P2,
   typename P3>
class Functor_imp<ResultType, TYPELIST_3(P1, P2, P3)>
{
   public:
      virtual ResultType operator()(P1, P2, P3) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, 
   typename P1, 
   typename P2,
   typename P3,
   typename P4>
class Functor_imp<ResultType, TYPELIST_4(P1, P2, P3, P4)>
{
   public:
      virtual ResultType operator()(P1, P2, P3, P4) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, 
   typename P1, 
   typename P2,
   typename P3,
   typename P4,
   typename P5>
class Functor_imp<ResultType, TYPELIST_5(P1, P2, P3, P4, P5)>
{
   public:
      virtual ResultType operator()(P1, P2, P3, P4, P5) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, 
   typename P1, 
   typename P2,
   typename P3,
   typename P4,
   typename P5,
   typename P6>
class Functor_imp<ResultType, TYPELIST_6(P1, P2, P3, P4, P5, P6)>
{
   public:
      virtual ResultType operator()(P1, P2, P3, P4, P5, P6) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

template<typename ResultType, 
   typename P1, 
   typename P2,
   typename P3,
   typename P4,
   typename P5,
   typename P6,
   typename P7>
class Functor_imp<ResultType, TYPELIST_7(P1, P2, P3, P4, P5, P6, P7)>
{
   public:
      virtual ResultType operator()(P1, P2, P3, P4, P5, P6, P7) = 0;
      virtual Functor_imp* Clone() const = 0;
      virtual ~Functor_imp() {}
};

//#####################################################

template<class ParentFunctor, typename Fun>
class Functor_handler
: public Functor_imp<
   typename ParentFunctor::Result_type,
   typename ParentFunctor::Parametr_list>
{
   public:
      typedef typename ParentFunctor::Result_type Result_type;
      
      Functor_handler(const Fun& fun)
         : fun_(fun)
      {}

      Functor_handler* Clone() const
      {
         return new Functor_handler(*this);
      }

      Result_type operator()()
      {
         return fun_();
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1)
      {
         return fun_(p1);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2)
      {
         return fun_(p1, p2);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3)
      {
         return fun_(p1, p2, p3);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3,
            typename ParentFunctor::Parametr_4 p4)
      {
         return fun_(p1, p2, p3, p4);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3,
            typename ParentFunctor::Parametr_4 p4,
            typename ParentFunctor::Parametr_5 p5)
      {
         return fun_(p1, p2, p3, p4, p5);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3,
            typename ParentFunctor::Parametr_4 p4,
            typename ParentFunctor::Parametr_5 p5,
            typename ParentFunctor::Parametr_6 p6)
      {
         return fun_(p1, p2, p3, p4, p5, p6);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3,
            typename ParentFunctor::Parametr_4 p4,
            typename ParentFunctor::Parametr_5 p5,
            typename ParentFunctor::Parametr_6 p6,
            typename ParentFunctor::Parametr_7 p7)
      {
         return fun_(p1, p2, p3, p4, p5, p6, p7);
      }

      Result_type operator()(typename ParentFunctor::Parametr_1 p1,
            typename ParentFunctor::Parametr_2 p2,
            typename ParentFunctor::Parametr_3 p3,
            typename ParentFunctor::Parametr_4 p4,
            typename ParentFunctor::Parametr_5 p5,
            typename ParentFunctor::Parametr_6 p6,
            typename ParentFunctor::Parametr_7 p7,
            typename ParentFunctor::Parametr_8 p8)
      {
         return fun_(p1, p2, p3, p4, p5, p6, p7, p8);
      }

   private:
      Fun fun_;
};

#endif
