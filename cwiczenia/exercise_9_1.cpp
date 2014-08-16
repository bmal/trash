#include <type_traits>
#include "boost/mpl/bool.hpp"

template<
   class F, bool F_empty,
   class G, bool G_empty
>
class storage;

template<class F, class G>
class storage<
   F, false,
   G, false
>
{
   protected:
      storage(const F& f, const G& g)
         : f(f), g(g)
      {}

      const F& get_f() const
      {
         return f;
      }

      const G& get_g() const
      {
         return g;
      }

   private:
      F f;
      G g;
};

template<class F, class G>
class storage<
   F, true,
   G, false
>
 : private F
{
   protected:
      storage(const F& f, const G& g)
         : F(f), g(g)
      {}

      const F& get_f() const
      {
         return *this;
      }

      const G& get_g() const
      {
         return g;
      }

   private:
      G g;
};

template<class F, class G>
class storage<
   F, false,
   G, true
>
 : private G
{
   protected:
      storage(const F& f, const G& g)
         : f(f), G(g)
      {}

      const F& get_f() const
      {
         return f;
      }

      const G& get_g() const
      {
         return *this;
      }

   private:
      F f;
};

template<typename F, typename G, bool Both_Empty>
class storage_both_empty;

template<class F, class G>
class storage_both_empty<F, G, false>
 : storage<F, true,
           G, false>
{
   protected:
      storage_both_empty(const F& f, const G& g)
         : storage<F, true,
                   G, false>(f, g)
   {}
};

template<class F, class G>
class storage_both_empty<F, G, true>
 : F, G
{
   protected:
      storage_both_empty(const F& f, const G& g)
         : F(f), G(g)
      {}

      const F& get_f() const 
      {
         return *this;
      }

      const G& get_g() const
      {
         return *this;
      }
};

template<class F, class G>
struct use_both_as_base
#ifdef NO_MI_EBO
 : boost::mpl::false_
#else
 : boost::mpl::true_
#endif
{};

template<class F, class G>
class storage<F, true,
              G, true>
 : storage_both_empty<F, G, 
      use_both_as_base<F, G>::value>
{
   protected:
      typedef storage_both_empty<F, G, 
              use_both_as_base<F, G>::value> base;

      storage(const F& f, const G& g)
         : base(f, g)
      {}
};

//just a simple specialization
template<class F>
class storage<F, true,
              F, true>
 : F
{
   protected:
      storage(const F& f, const F&)
         : F(f)
      {}

      const F& get_f() const
      {
         return *this;
      }

      const F& get_g() const
      {
         return *this;
      }
};

template<class Result, class F, class G>
class compose_fg
 : storage<
      F, std::is_empty<F>::value,
      G, std::is_empty<G>::value
   >
{
      typedef storage<
         F, std::is_empty<F>::value,
         G, std::is_empty<G>::value
      > base;

   public:
      compose_fg(const F& f, const G& g)
         : base(f, g)
      {}

      template<class T>
      Result operator()(const T& x) const
      {
         const F& f = this->get_f();
         const G& g = this->get_g();
         return f(g(x));
      }
};

template<typename Result, class F, class G>
compose_fg<Result, F, G> compose(const F& f, const G& g)
{
   return compose_fg<Result, F, G>(f, g);
}

int main()
{}
