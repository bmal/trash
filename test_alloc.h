#ifndef TEST_ALLOC_H
#define TEST_ALLOC_H

#include <iterator>
#include <limits>
#include <vector>

template <typename T>
class My_allocator
{
    public:
        typedef T                   value_type;
        typedef T&                  reference;
        typedef const T&            const_reference;
        typedef T*                  pointer;
        typedef const T*            const_pointer;
        typedef std::ptrdiff_t      difference_type;
        typedef std::size_t         size_type;

        template <typename U>
        struct rebind
        {
            typedef My_allocator<U> other;
        };

        size_type max_size() const
        {
            return std::numeric_limits<std::size_t>::max() / sizeof( T );
        }

        My_allocator()
        {}

        My_allocator( const My_allocator<T>& )
        {}

        template <typename U>
        My_allocator( const My_allocator<U>& )
        {}

        ~My_allocator()
        {}

        pointer allocate( size_type num )
        {
            return static_cast< pointer >( ::operator new ( num * sizeof( value_type )));
        }

        void construct( pointer ptr, const_reference val )
        {
            new ( static_cast<void*>( ptr )) value_type( val );
        }

        void destroy( pointer ptr )
        {
            ptr->~T();
        }

        void deallocate( pointer ptr, size_type )
        {
            ::operator delete ( static_cast<void*>( ptr ));
        }
};

template <typename T, typename U>
bool operator==( My_allocator<T>, My_allocator<U> )
{
    return true;
}

template <typename T, typename U>
bool operator!=( My_allocator<T>, My_allocator<U> )
{
    return false;
}

template <typename ForwardIter, typename T>
void uninitialized_fill( ForwardIter beg, ForwardIter end, const T& val )
{
    typedef typename std::iterator_traits< ForwardIter>::value_type VT;
    ForwardIter save = beg;

    try
    {
        for( ; beg != end; ++beg )
            new ( static_cast<void*>( &*beg )) VT( val );
    }
    catch(...)
    {
        for( ; save != beg; ++save )
            save->~VT();
        throw;
    }
}

template <typename ForwardIter, typename Size, typename T>
void uninitialized_fill_n( ForwardIter beg, Size num, const T& val )
{
    typedef typename std::iterator_traits< ForwardIter>::value_type VT;
    ForwardIter save = beg;

    try
    {
        for( Size i = 0; i < num; ++i, ++beg )
            new ( static_cast<void*>( &*beg )) VT( val );
    }
    catch(...)
    {
        for( ; save != beg; ++save )
            save->~VT();
        throw;
    }
}

template <typename ForwardIter, typename InputIter>
void uninitialized_copy( ForwardIter beg, ForwardIter end, InputIter dest )
{
    typedef typename std::iterator_traits< InputIter>::value_type VT;
    InputIter save = dest;

    try
    {
        for( ; beg != end; ++beg, ++dest )
            new ( static_cast<void*>( &*dest )) VT( *beg );
    }
    catch(...)
    {
        for( ; save != dest; ++save )
            save->~VT();
        throw;
    }
}

#endif
