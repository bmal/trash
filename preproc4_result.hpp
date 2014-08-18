struct none
{};
template< class T0 , class T1 , class T2>
struct tiny_size
   : mpl::int_<3>
{};
template<>
struct tiny_size<
   none , none , none
>
   : mpl::int_<0>
{};
template< class T0>
struct tiny_size<
   T0 , none , none
>
   : mpl::int_<1>
{};
template< class T0 , class T1>
struct tiny_size<
   T0 , T1 , none
>
   : mpl::int_<2>
{};
