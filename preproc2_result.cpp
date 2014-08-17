struct none
{};
template< class T0 , class T1 , class T2>
struct tiny_size;
        template<> struct tiny_size< none , none , none > : boost::mpl::int_<0> {};
        template< class T0> struct tiny_size< T0 , none , none > : boost::mpl::int_<1> {};
        template< class T0 , class T1> struct tiny_size< T0 , T1 , none > : boost::mpl::int_<2> {};
