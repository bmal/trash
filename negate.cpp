#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

struct razy
{
    int operator()(int x) { return x *= 10; }
};

int main()
{
    vector<int> v;
    for( int i = 0; i < 20; ++i )
        v.push_back( i );

    cout << "Przed testami:\n";
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, " " ) );

    cout << "\nnegate<int>()\n";
    transform( v.begin(), v.end(), v.begin(), negate<int>() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, " " ) );

    cout << "\nbind2nd\n";
    transform( v.begin(), v.end(), v.begin(), bind2nd( multiplies<int>(), 10 ));
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, " " ) );

    cout << "\nto samo\n";
    transform( v.begin(), v.end(), v.begin(), razy() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, " " ) );
}
