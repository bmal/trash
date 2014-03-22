#include <iostream>
#include <typeinfo>
#include "boost/ref.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"

using namespace std;

void print_tuple( const boost::tuples::null_type& )
{}

template<typename T>
void print_tuple( T& obj )
{
   cout << obj.get_head() << ", ";
   print_tuple(obj.get_tail());
}

int main()
{
   typedef boost::tuple<int, string> my_tuple;
   int a = 10;
   double b = 13.23;
   cout << boost::make_tuple(a, boost::ref(b)) << endl;
   
   boost::tuple<int, string> krotka1(10);
   krotka1.get<1>() = "Domek w lesie";
   cout << krotka1.get<1>() << ' ' << boost::get<0>( krotka1 ) << " wielkosc: " << boost::tuples::length<my_tuple>::value << endl;

   boost::tuple<double, string> krotka2(krotka1);
   cout << krotka2 << endl;

   string s;
   boost::tie(boost::tuples::ignore, s) = krotka1;
   cout << s << endl;

   cout << boost::tuples::set_open('[')
   << boost::tuples::set_close(']')
   << boost::tuples::set_delimiter(';')
   << krotka1 << endl;

   print_tuple(krotka1);

   if( typeid(boost::tuples::element<0, boost::tuple<int,string> >::type) == typeid( int ))
         cout << "\n0 = int" << endl;
}
