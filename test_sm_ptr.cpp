#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template < typename T >
class Smart_ptr
{
    private:
        T* ptr;
        long* count;

    public:
        explicit Smart_ptr( T* p = 0 )
            : ptr( p ), count( new long( 1 ))
        {}

        Smart_ptr ( Smart_ptr< T >& p )
            : ptr( p.ptr ), count( p.count )
        {
            ++ *count;
        }

        ~Smart_ptr()
        {
            dispose();
        }

        Smart_ptr< T >& operator= ( Smart_ptr< T >& p )
        {
            if ( this != &p )
            {
                dispose();
                ptr = p.ptr;
                count = p.count;
                ++ *count;
            }
            return *this;
        }

        T* operator->() const
        {
            return ptr;
        }

        T& operator*() const
        {
            return *ptr;
        }

    private:
        void dispose()
        {
            if ( -- *count == 0 )
            {
                delete count;
                delete ptr;
            }
        }
};

int main()
{
}
