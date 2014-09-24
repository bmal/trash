#ifndef FUNCTOR_HPP
#   define FUNCTOR_HPP

#include <memory>

template<class Result, class... Params>
class Functor_impl
{
   public:
      virtual Result operator() (Params... args) = 0;
      virtual ~Functor_impl()
      {}
};

template<typename Function, class Result, class... Params>
class Functor_handler
   : public Functor_impl
     <
        Result,
        Params...
     >
{
   public:
      typedef Result result_type;

      Functor_handler() = delete;
      Functor_handler(const Functor_handler&) = default;
      Functor_handler& operator= (const Functor_handler&) = default;

      Functor_handler(const Function& fun)
         : function_(fun)
      {}

      result_type operator() (Params... args)
      {
         return function_(args...);
      }

   private:
      Function function_;
};

template<typename Method_ptr, class Object, class Result, class... Params>
class Mem_fun_handler
   : public Functor_impl
     <
        Result,
        Params...
     >
{
   public:
      typedef Result result_type;

      Mem_fun_handler() = delete;
      Mem_fun_handler(const Mem_fun_handler&) = default;
      Mem_fun_handler& operator= (const Mem_fun_handler&) = default;

      Mem_fun_handler(Method_ptr method, const Object& obj)
         : method_(method), object_(obj)
      {}

      result_type operator() (Params... args)
      {
         return (object_.*method_)(args...);
      }

   private:
      Method_ptr method_;
      Object object_;
};

template<class Result, class... Params>
class Functor;

template<class Result, class... Params>
class Functor<Result(Params...)>
{
   typedef Functor_impl<Result, Params...> Impl;

   public:
      typedef Result result_type;

      Functor() = default;

      template<class Function>
      Functor(Function fun)
         : impl_(new Functor_handler<Function, Result, Params...>(fun))
      {}

      template<typename Method_ptr, class Object>
      Functor(Method_ptr method, const Object& obj)
         : impl_(new Mem_fun_handler<Method_ptr, Object, Result, Params...>(method, obj))
      {}

      Functor(const Functor& other)
      {
         impl_ = std::move(other);
      };

      Functor& operator= (Functor&& other)
      {
         if(this == &other)
            return *this;

         impl_ = std::move(other.impl_);
      }

      Result operator() (Params... args)
      {
         return (*impl_)(args...);
      }

   private:
      std::unique_ptr<Impl> impl_;
};

#endif
