#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include "boost/variant.hpp"
#include "boost/lexical_cast.hpp"

using namespace std;

class print_visitor_gen
 : public boost::static_visitor< void >
{
   public:
      print_visitor_gen( ostream& o ) : _strm( o ) {}

      template< typename T >
      void operator() ( const T& object )
      {
         _strm << object << endl;
      }

      void operator() ( int i )
      {
         cout << "int: " << i << endl;
      }

   private:
      ostream& _strm;
};

class print_visitor
 : public boost::static_visitor< void >
{
   public:
      void operator() ( int i )
      {
         cout << "int: " << i << endl;
      }

      void operator() ( const string& i )
      {
         cout << "string: " << i << endl;
      }

      void operator() ( double i )
      {
         cout << "double: " << i << endl;
      }
};

class lex_vis
 : public boost::static_visitor< bool >
{
   public:
      template< typename LHS, typename RHS >
      bool operator() ( const LHS& lhs, const RHS& rhs )
      {
         return boost::lexical_cast< string >( lhs ) < boost::lexical_cast< string >( rhs );
      }
};

int main()
{
   boost::variant< int, char, string > var( 45 );
   cout << var.which() << endl;

   var = "Domek w lesie";
   cout << var.which() << endl;
   boost::get< string >( var ) = "Nowy lesny domek";
   if( ! boost::get< int >( &var ) )
      cout << boost::get< string >( var );

   print_visitor_gen pv_g( cout );
   boost::apply_visitor( pv_g, var );
   var = 'c';
   boost::apply_visitor( pv_g, var );
   var = 23134;
   boost::apply_visitor( pv_g, var );

   cout << endl;

   var = "Nowy lesny domek";
   print_visitor pv;
   boost::apply_visitor( pv, var );
   var = 'c';
   boost::apply_visitor( pv, var );
   var = 123432;
   boost::apply_visitor( pv, var );

   boost::variant< int, string, char > var2 = 'a';
   boost::variant< double, int > var3 = 32.4;
   boost::variant< int, string > var4 = "321";

   lex_vis lv;
   cout << boolalpha;
   cout << boost::apply_visitor( lv, var2, var3 );
   cout << endl;
   cout << boost::apply_visitor( lv, var3, var2 );
   cout << endl;
   cout << boost::apply_visitor( lv, var4, var3 );

   vector< boost::variant< int, char, string, double > > vec;
   vec.push_back( "234" );
   vec.push_back( 123 );
   vec.push_back( 13.43 );
   vec.push_back( 1.000 );

   cout << "\n***************************\n";

   cout << "vector: \n";
   for_each( vec.begin(), vec.end(), boost::apply_visitor( pv_g ) );

   cout << "\nsorted vector: \n";
   sort( vec.begin(), vec.end(), boost::apply_visitor( lv ));
   for_each( vec.begin(), vec.end(), boost::apply_visitor( pv_g ) );
}
