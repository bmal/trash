#include <iostream>
#include "boost/operators.hpp"

using namespace std;

template< typename T >
class my_less_than1
{
   public:
      friend bool operator> ( const T& lhs, const T& rhs )
      {
         return rhs < lhs;
      }

      friend bool operator<= ( const T& lhs, const T& rhs )
      {
         return !( rhs < lhs );
      }

      friend bool operator>= ( const T& lhs, const T& rhs )
      {
         return !( lhs < rhs );
      }
};

template< typename T, typename U >
class my_less_than2
{
   public:
      friend bool operator> ( const T& lhs, const U& rhs )
      {
         return rhs < lhs;
      }

      friend bool operator<= ( const T& lhs, const U& rhs )
      {
         return !( rhs < lhs );
      }

      friend bool operator>= ( const T& lhs, const U& rhs )
      {
         return !( lhs < rhs );
      }

      friend bool operator> ( const U& lhs, const T& rhs )
      {
         return rhs < lhs;
      }

      friend bool operator<= ( const U& lhs, const T& rhs )
      {
         return !( rhs < lhs );
      }

      friend bool operator>= ( const U& lhs, const T& rhs )
      {
         return !( lhs < rhs );
      }
};

struct nothing {};

template< typename U >
struct selector
{
   template< typename T >
   struct type
   {
      typedef my_less_than2< T, U > value;
   };
};

template <>
struct selector< nothing >
{
   template< typename T >
   struct type {
      typedef my_less_than1< T > value;
   };
};

template< typename T, typename U >
struct select_implementation
{
   typedef typename selector< U >::template type< T >::value type;
};

template< typename T, typename U = nothing >
class my_less_than
 : select_implementation< T, U >::type
{
};

//------------------------------------------------

struct B
 : private my_less_than< B >
{
   B( int val ) : _obj( val ) {}
   int _obj;

   friend bool operator< ( const B& lhs, const B& rhs )
   {
      return lhs._obj < rhs._obj;
   }
};

struct A
 : private boost::less_than_comparable1< A,
           boost::addable1< A,
           boost::addable2< A, B > > >
{
   int _obj;
   A(int val) : _obj( val ) {}

   friend bool operator< ( const A& lhs, const A& rhs )
   {
      return lhs._obj < rhs._obj;
   }

   A& operator+= ( const B& other )
   {
      _obj += other._obj;
      return *this;
   }

   A& operator+= ( const A& other )
   {
      _obj += other._obj;
      return *this;
   }
};

int main()
{
   A a1( 5 );
   A a2( 15 );
   B b1( 10 );
   B b2( 10 );

   cout << boolalpha;
   cout << ( a1 < a2 ) << endl;
   cout << ( a1 + a2 )._obj << endl;
   cout << ( a2 + b1 )._obj << endl;

   cout << ( b1 > b2 ) << endl;
}
