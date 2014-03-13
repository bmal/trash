#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

struct iword_indexes
{
    static const int space_index;
    static const int dot_index;
};

const int iword_indexes::space_index = ios::xalloc();
const int iword_indexes::dot_index = ios::xalloc();

template< typename charT,
          typename traits >
inline
basic_ostream< charT, traits >& 
space( basic_ostream< charT, traits >& o )
{
    o.iword( iword_indexes::space_index ) = true;
    return o;
}

template< typename charT,
          typename traits >
inline
basic_ostream< charT, traits >& 
dot( basic_ostream< charT, traits >& o )
{
    o.iword( iword_indexes::dot_index ) = true;
    return o;
}

template< typename charT,
          typename traits >
inline
basic_ostream< charT, traits >& 
undot( basic_ostream< charT, traits >& o )
{
    o.iword( iword_indexes::dot_index ) = false;
    return o;
}

template< typename charT,
          typename traits >
inline
basic_ostream< charT, traits >& 
newline( basic_ostream< charT, traits >& o )
{
    o.put( o.widen( '\n') );
    return o;
}

struct ulamek
{
    ulamek( int l, int m )
        : licznik( l ), mianownik( m )
    {}

    int licznik;
    int mianownik;
};

template< typename charT,
          typename traits >
inline
basic_ostream< charT, traits >&
operator<< ( basic_ostream< charT, traits >& strm, const ulamek& u )
{
    basic_stringstream< charT, traits > ss;
    ss.copyfmt( strm );
    ss.width( 0 );
    if ( ss.iword( iword_indexes::dot_index ))
    {
        ss << showpoint << static_cast< double >( u.licznik ) / u.mianownik;
    }
    else if ( ss.iword( iword_indexes::space_index ))
        ss << u.licznik << " / " << u.mianownik;
    else
        ss << u.licznik << '/' << u.mianownik;
    strm << ss.str();
    return strm;
}

int main()
{
    ulamek u( 5, 2 );
    cout << u << newline << dot << u;
    cout << undot << newline << space << u;
}
