#include <type_traits>

template<
   class F, bool F_empty,
   class G, bool G_empty
>
class storage;

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

template<class F, class G>
class storage<
   F, true,
   G, true
>
 : private G,
   private F
{
   protected:
      storage(const F& f, const G& g)
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

int main()
{}
