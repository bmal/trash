#include <iterator>
#include <iostream>
#include <map>

using namespace std;

template< class Container >
class asso_insert_iterator
 : public iterator< output_iterator_tag,
             void, void, void, void >
{
    protected:
        Container& c;

    public:
        explicit asso_insert_iterator (Container& cont )
            : c( cont )
        {}

        asso_insert_iterator< Container >& operator= ( const typename Container::value_type& val )
        {
            c.insert( val );
            return *this;
        }

        asso_insert_iterator< Container >& operator++ ()
        {
            return *this;
        }

        asso_insert_iterator< Container >& operator++ (int)
        {
            return *this;
        }

        asso_insert_iterator< Container >& operator* ()
        {
            return *this;
        }
};

template< typename Container >
inline asso_insert_iterator< Container > asso_inserter( Container& c )
{
    return asso_insert_iterator< Container > ( c );
} 

int main()
{
    map< int, int > m;
    for ( int i = 0; i < 10; ++i )
        asso_inserter( m ) = make_pair( i , 2*i );

    for( map<int, int>::const_iterator i = m.begin(); i != m.end(); ++i )
        cout << i->first << ' ' << i->second << endl;
}
