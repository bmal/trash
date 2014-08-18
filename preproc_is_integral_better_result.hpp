template<class T>
struct is_integral
   : mpl::false_
{};
        template<> struct is_integral<bool>: mpl::true_ {};
        template<> struct is_integral<char>: mpl::true_ {};
        template<> struct is_integral<signed char>: mpl::true_ {};
        template<> struct is_integral<unsigned char>: mpl::true_ {};
        template<> struct is_integral<signed short>: mpl::true_ {};
        template<> struct is_integral<unsigned short>: mpl::true_ {};
        template<> struct is_integral<signed int>: mpl::true_ {};
        template<> struct is_integral<unsigned int>: mpl::true_ {};
        template<> struct is_integral<signed long>: mpl::true_ {};
        template<> struct is_integral<unsigned long>: mpl::true_ {};
