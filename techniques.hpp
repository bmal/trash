#ifndef TECHNIQUES_HPP
#define TECHNIQUES_HPP

template<bool>
struct Compile_time_checker
{
   Compile_time_checker(...);
};

template<>
struct Compile_time_checker<true>
{};

#define STATIC_CHECK(expr, msg)\
{\
   class ERROR_##msg;\
   (void)sizeof(Compile_time_checker<(expr) != 0>\
         ((ERROR_##msg())));\
}

/* Example:
template<class TO, class FROM>
TO safe_reinterpret_cast(FROM from)
{
   STATIC_CHECK(sizeof(FROM) <= sizeof(TO), Destination_type_too_narrow);
   return reinterpret_cast<TO>(from);
}
*/

//#####################################################

template<int v>
struct Int2Type
{
   enum{value = v};
};

//#####################################################

template<typename T>
struct Type2Type
{
   typedef T Original_type;
};

//#####################################################

template<bool flag, typename T, typename U>
struct Select
{
   typedef T Result;
};

template<typename T, typename U>
struct Select<false, T, U>
{
   typedef U Result;
};

/* Example:
template<typename T, bool is_polymorphic>
class Nifty_container
{
   ...
   typedef typename Select<is_polymorphic, T*, T>::Result value_type;
   ...
};
*/

//#####################################################

template<class T, class U>
class Conversion
{
private:
   typedef char Small;
   class Big
   {
      char dummy[2];
   };

   static Small test(const U&);
   static Big test(...);
   static T make_T();

public:
   enum {
      exist = sizeof(test(make_T()) == sizeof(Small)),
      same_type = false};
};

template<class T>
class Conversion<T, T>
{
public:
   enum {
      exist = true,
      same_type = true};
};

#define SUPERSUBCLASS(T, U)\
   (Conversion<const U*, const T*>::exist &&\
    !Conversion<const T*, const void*>::same_type)

#define SUPERSUBCLASS_STRICT(T, U)\
   (SUPERSUBCLASS(T, U) && \
    !Conversion<const T*, const U*>::same_type)

#endif
