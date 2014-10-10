#ifndef STATIC_MULTIMETHOD_HPP
#   define STATIC_MULTIMETHOD_HPP

#include "trash/typelist.hpp"
#include "trash/null_type.h"

template
<
   class Executor,
   bool symmetric,
   class Base_Lhs,
   class Types_Lhs,
   class Base_Rhs = Base_Lhs,
   class Types_Rhs = Types_Lhs,
   typename Result_Type = void
>
class Static_Dispatcher
{
      typedef typename Types_Lhs::Head Head;
      typedef typename Types_Lhs::Tail Tail;

      template<bool swap_args, class Some_Lhs, class Some_Rhs>
      struct Invocation_Traits
      {
         static Result_Type do_dispatch(Some_Lhs& lhs, Some_Rhs& rhs,
               Executor exec)
         {
            return exec.fire(lhs, rhs);
         }
      };

      template<class Some_Lhs, class Some_Rhs>
      struct Invocation_Traits<true, Some_Lhs, Some_Rhs>
      {
         static Result_Type do_dispatch(Some_Lhs& lhs, Some_Rhs& rhs,
               Executor exec)
         {
            return exec.fire(rhs, lhs);
         }
      };

   public:
      static Result_Type go(Base_Lhs& lhs, Base_Rhs& rhs, Executor exec)
      {
         if(Head* p1 = dynamic_cast<Head*>(&lhs))
            return Static_Dispatcher<Executor, symmetric, Base_Lhs,
                  Types_Lhs, Base_Rhs, Types_Rhs, 
                  Result_Type>::dispatch_rhs(*p1, rhs, exec);
         else
            return Static_Dispatcher<Executor, symmetric, Base_Lhs,
                   Tail, Base_Rhs, Types_Rhs, 
                   Result_Type>::go(lhs, rhs, exec);
      }

      template<class Some_Lhs>
      static Result_Type dispatch_rhs(Some_Lhs& lhs, Base_Rhs& rhs, Executor exec)
      {
         typedef typename Types_Rhs::Head Head;
         typedef typename Types_Rhs::Tail Tail;

         if(Head* p2 = dynamic_cast<Head*>(&rhs))
         {
            enum
            {
               swap_args = symmetric &&
                  TL::Index_of<Head, Types_Rhs>::result < 
                  TL::Index_of<Some_Lhs, Types_Lhs>::result
            };

            typedef Invocation_Traits<swap_args, Some_Lhs, Head> call_traits;
            return call_traits::do_dispatch(lhs, *p2);
         }
         else
           return Static_Dispatcher<Executor, symmetric, Some_Lhs, Types_Lhs, 
                  Base_Rhs, Tail, 
                  Result_Type>::dispatch_rhs(lhs, rhs, exec); 
      }
};

template
<
   class Executor,
   bool symmetric,
   class Base_Lhs,
   class Base_Rhs,
   class Types_Rhs,
   typename Result_Type
>
class Static_Dispatcher<Executor, symmetric, Base_Lhs, Null_type,
      Base_Rhs, Types_Rhs, Result_Type>
{
   static void go(Base_Lhs& lhs, Base_Rhs& rhs, Executor exec)
   {
      exec.on_error(lhs, rhs);
   }
};

template
<
   class Executor,
   bool symmetric,
   class Base_Lhs,
   class Types_Lhs,
   class Base_Rhs,
   typename Result_Type
>
class Static_Dispatcher<Executor, symmetric, Base_Lhs, Types_Lhs,
      Base_Rhs, Null_type, Result_Type>
{
   static void go(Base_Lhs& lhs, Base_Rhs& rhs, Executor exec)
   {
      exec.on_error(lhs, rhs);
   }
};

#endif
