template<bool, class Result = void>
struct enable_if_c
{
   typedef Result type;
};

template<class Result>
struct enable_if_c<false, Result>
{};

template<class Cond, class Result = void>
struct enable_if
 : enable_if_c<Cond::value, Result>
{};

//itd
