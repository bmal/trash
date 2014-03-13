#include <iostream>
#include <list>
#include <functional>
#include <iterator>
#include <vector>
#include <string>

#include "boost/any.hpp"

using namespace std;

namespace any_tools
{

  struct Streamer
  {
    virtual void print( ostream& stream, const boost::any& object ) const = 0;
    virtual Streamer* clone() const = 0;
    virtual ~Streamer() {}
  };

  template< typename T >
  struct Streamer_imp
    : public Streamer
  {
    virtual void print( ostream& stream, const boost::any& object ) const
    {
      stream << *boost::any_cast< T >( &object );
    }

    virtual Streamer* clone() const
    {
      return new Streamer_imp< T >();
    }
  };

  class any_out
  {
    public:
      any_out() : _streamer( 0 ), _object() {}
      
      template< typename T >
      any_out( const T& value )
        : _streamer( new Streamer_imp< T > ), _object( value )
      {}

      any_out( const any_out& other )
        : _streamer( other._streamer ? other._streamer->clone() : 0 ), _object( other._object )
      {}

      template< typename T >
      any_out& operator=( const T& value )
      {
        any_out( value ).swap( *this );
        return *this;
      }

      ~any_out() { delete _streamer; }

      any_out& swap( any_out& other )
      {
        std::swap( _streamer, other._streamer );
        std::swap( _object, other._object );
        return *this;
      }

      friend ostream& operator<<( ostream& stream, const any_out& object )
      {
        if( object._streamer )
          object._streamer->print( stream, object._object );

        return stream;
      }

    private:
      Streamer* _streamer;
      boost::any _object;
  };

  template< typename T >
  struct contains_t
    : unary_function< T, bool >
  {
    bool operator() ( boost::any object ) const
    {
      return typeid( T ) == object.type();
    }
  };

  template< typename T >
  contains_t< T > contains()
  {
    return contains_t< T >();
  }

  template< typename T >
  bool contains( const boost::any& object )
  {
    return contains_t< T >()( object );
  }

  template< typename Type, typename OutIter >
  class extractor_t
  {
    public:
      extractor_t( OutIter iter ) : _iterator( iter )
      {}

      void operator() ( boost::any& object )
      {
        Type* type_ptr( boost::any_cast< Type >( &object ));
        if( type_ptr )
          *_iterator ++ = *type_ptr;
      }

    private:
      OutIter _iterator;
  };

  template< typename Type, typename OutIter >
  extractor_t< Type, OutIter >
  extractor( OutIter iter )
  {
    return extractor_t< Type, OutIter >( iter );
  }

}

int main()
{
  using namespace any_tools;
  vector< any_out > v1;
  
  v1.push_back( any_out( string( "Tralalala" )));
  v1.push_back( 3 );
  v1.push_back( 123.32 );

  copy( v1.begin(), v1.end(), ostream_iterator< any_out >( cout, ", " ));
  cout << endl;

  boost::any a( string( "Cos" ) );
  if( contains< string >( a ) )
    cout << "To jest string" << endl;
  else
    cout << "To nie jest string" << endl;

  vector< boost::any > v2;

  v2.push_back( boost::any( string( "Tralalala" )));
  v2.push_back( 3 );
  v2.push_back( 123.32 );

  v2.erase( remove_if( v2.begin(), v2.end(), contains< int >() ), v2.end() );
  cout << v2.size();
  cout << endl;

  list< int > l;
  for( int i = 0; i < 5; ++i )
    v2.push_back( i );

  random_shuffle( v2.begin(), v2.end() );

  for_each( v2.begin(), v2.end(), extractor< int >( back_inserter( l )));
  copy( l.begin(), l.end(), ostream_iterator< int >( cout, ", " ));
}
