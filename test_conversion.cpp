#include <iostream>
#include <string>
#include "boost/cast.hpp"
#include "boost/lexical_cast.hpp"
#include <sstream>

using namespace std;

template< typename T, typename U>
T f( const U& u )
{
    T temp;
    stringstream s;
    if( !( s << u )
      ||!( s >> temp )
      ||!( s >> ws ).eof() )
        throw runtime_error( "Nie da sie" );
    return temp;
}

class A
{
    public:
        A( int i ) : _num( i ) {}
        int get() { return _num; }
        virtual void get_name() { cout << "klasa A"; }

    protected:
        int _num;
};

class Second_A
{
    public:
        Second_A( int i ) : _sth( i ) {}
        void only_second() { cout << "only " << _sth; }

    protected:
        int _sth;
};

class B : public A, public Second_A
{
    public:
        B( int i ) : A( i ), Second_A( 5 ) {}
        virtual void get_name() { cout << "klasa B"; }
        void only_b() { cout << "only b"; }
};

int main()
{
    double d = 312332.244;
    int a = boost::numeric_cast< int >( d );
    cout << a << endl;
    float f = boost::numeric_cast< float >( d );
    cout << f << endl;
//    short s = boost::numeric_cast< short >( d );
//    cout << s << endl;

    /*
    A* ptr = new B( 10 );
    B* ptrB = boost::polymorphic_cast< B* >( ptr );
    ptrB->only_b();
    cout << endl;
    Second_A* ptrS = boost::polymorphic_cast< Second_A* >( ptr );
    ptrS->only_second();
    */

    A* ptr = new B( 10 );
    B* ptrB = boost::polymorphic_downcast< B* >( ptr );
    ptrB->only_b();
    cout << endl;
    Second_A* ptrS = boost::polymorphic_downcast< Second_A* >( ptrB );
    ptrS->only_second();
    cout << endl;

    int i = 4;
    string str = boost::lexical_cast< string >( i );
    cout << str << endl;
}
