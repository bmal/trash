#include <iostream>
#include <iterator>
#include "boost/shared_ptr.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/intrusive_ptr.hpp"
#include <functional>
#include "boost/weak_ptr.hpp"
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

class A
{
    public:
        A( int a ) : _a( a ), _counter( 0 ) {}
        int get() { return _a; }
        void add() { ++_counter; }
        int relase() { return --_counter; }
    private:
        int _a;
        int _counter;
};

template <typename T>
void intrusive_ptr_add_ref( T* t )
{
    t->add();
}

template <typename T>
void intrusive_ptr_release( T* t )
{
    if( !t->relase() )
        delete t;
}

int main()
{
    int a = 10;
    boost::shared_ptr< int > ptr1( new int(a) );
    boost::shared_ptr< int > ptr2( ptr1 );
    boost::weak_ptr< int > wptr = ptr1;
    boost::intrusive_ptr< A > iptr1( new A(10) );
    boost::intrusive_ptr< A > iptr2( new A(10) );
}
