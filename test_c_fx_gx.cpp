#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template < typename O1,
         typename O2,
         typename O3 >
class compose_fx_gx
        : public unary_function< typename O2::argument_type,
                                typename O1::result_type >
{
    public:
        compose_fx_gx( O1 o1, O2 o2, O3 o3 )
            : op1( o1 ), op2( o2 ), op3( o3 )
        {}

        typename O1::result_type operator() ( const typename O2::argument_type x)
        {
            return op1( op2( x ), op2( x ));
        }

    private:
        O1 op1;
        O2 op2;
        O3 op3;
};

template < typename O1,
         typename O2,
         typename O3 >
inline compose_fx_gx< O1, O2, O3 >
compose( const O1& op1, const O2& op2, const O3& op3 )
{
    return compose_fx_gx< O1, O2, O3 > ( op1, op2, op3 );
}

int main()
{
    vector< int > v;
    for ( int i = 0; i < 10; ++i )
        v.push_back( i );
    copy( v.begin(), v.end(), ostream_iterator< int > ( cout, ", " ));
    cout << '\n';
    copy_if( v.begin(), v.end(), ostream_iterator< int > (cout, ", " ), 
            compose( logical_and<bool>(), bind2nd( greater<int>(), 3 ), bind2nd( less<int>(), 6)));
}
