#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include "trash/typelist.hpp"
#include "trash/empty_type.h"
#include "functor_implementation.hpp"
#include <memory>

template<typename ResultType, class TList>
class Functor
{
      typedef Functor_imp<ResultType, TList> Imp;
   public:
      typedef TList Parametr_list;
      typedef ResultType Result_type;

      typedef typename TL::Type_at_non_strict<TList, 0, Empty_type>::Result Parametr_1;
      typedef typename TL::Type_at_non_strict<TList, 1, Empty_type>::Result Parametr_2;
      typedef typename TL::Type_at_non_strict<TList, 2, Empty_type>::Result Parametr_3;
      typedef typename TL::Type_at_non_strict<TList, 3, Empty_type>::Result Parametr_4;
      typedef typename TL::Type_at_non_strict<TList, 4, Empty_type>::Result Parametr_5;
      typedef typename TL::Type_at_non_strict<TList, 5, Empty_type>::Result Parametr_6;
      typedef typename TL::Type_at_non_strict<TList, 6, Empty_type>::Result Parametr_7;
      typedef typename TL::Type_at_non_strict<TList, 7, Empty_type>::Result Parametr_8;

      Functor() = default;
      Functor(const Functor& fun);
      Functor& operator=(const Functor&);;
      explicit Functor(std::unique_ptr<Imp> implementation)
         : implementation_(implementation.release())
      {}

      template<class Fun>
      Functor(const Fun& fun)
      : implementation_(new Functor_handler<Functor, Fun>(fun))
      {}

      Result_type operator()()
      {
         return (*implementation_)();
      }

      Result_type operator()(Parametr_1 p1)
      {
         return (*implementation_)(p1);
      }

      Result_type operator()(Parametr_1 p1, Parametr_2 p2)
      {
         return (*implementation_)(p1, p2);
      }

      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3)
      {
         return (*implementation_)(p1, p2, p3);
      }

      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3,
            Parametr_4 p4)
      {
         return (*implementation_)(p1, p2, p3, p4);
      }

      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3,
            Parametr_4 p4, Parametr_5 p5)
      {
         return (*implementation_)(p1, p2, p3, p4, p5);
      }
      
      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3,
            Parametr_4 p4, Parametr_5 p5, Parametr_6 p6)
      {
         return (*implementation_)(p1, p2, p3, p4, p5, p6);
      }
      
      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3,
            Parametr_4 p4, Parametr_5 p5, Parametr_6 p6, Parametr_7 p7)
      {
         return (*implementation_)(p1, p2, p3, p4, p5, p6, p7);
      }

      Result_type operator()(Parametr_1 p1, Parametr_2 p2, Parametr_3 p3,
            Parametr_4 p4, Parametr_5 p5, Parametr_6 p6, Parametr_7 p7,
            Parametr_8 p8)
      {
         return (*implementation_)(p1, p2, p3, p4, p5, p6, p7, p8);
      }

   private:
      std::unique_ptr<Imp> implementation_;
};

#endif
