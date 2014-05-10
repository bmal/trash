#ifndef TEST_STATIC_ASSERT_HPP
#define TEST_STATIC_ASSERT_HPP

#ifdef _MSC_VER
#pragma once
#endif

template<bool>
struct Compile_time_checker
{
   Compile_time_checker(...);
};

template<>
struct Compile_time_checker<false>
{};

#define STATIC_CHECKER(expr, msg) \
{ \
   class ERROR_##msg; \
   (void) sizeof(Compile_time_checker< \
         (expr) != 0>((ERROR_##msg()))); \
}

/*
example:
template<class To, class From>
To safe_reinterpret_cast(From from)
{
   STATIC_CHECKER(sizeof(From) <= sizeof(To),
      Destination_Type_Too_Narrow);
   return reinterpret_cast<To>(from);
}
*/

#endif
