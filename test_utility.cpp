// UZUPELNIC !!!

#include "boost/assert.hpp"
#include "boost/static_assert.hpp"
#include "boost/type_traits.hpp"
#include "boost/checked_delete.hpp"
#include "boost/utility.hpp"
#include "boost/utility/enable_if.hpp"

using namespace std;

template< typename T, typename Enable = void >
class Klasa : private boost::noncopyable
{
    BOOST_STATIC_ASSERT( ! boost::is_reference< T >::value );
    public:
        Klasa() { cout << "Podstawa" << endl; }
};

template< typename T >
class Klasa< T, typename boost::enable_if< boost::is_integral< T > >::type >
{
    BOOST_STATIC_ASSERT( ! boost::is_reference< T >::value );
    public:
        Klasa() { cout << "Specjalizacja" << endl; }
};

class A
{
    public:
        typedef int type;
        A( type i ) : _p( i ) {}
        type _p;
};

void f( int i ) { cout << "Zwykla " << i; }

template< typename T >
void f( T i, typename boost::enable_if< boost::is_class< T > >::type* = 0 ) 
{ cout << "Szablon " << i._p; }

int main()
{
    Klasa< int > a;
    Klasa< double > b;
    cout << boost::addressof( a );
    cout << endl;
    f( int( 5 ));
    cout << endl;
    f( A( 5 ));
}
