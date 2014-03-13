#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v;
    for(int i =0; i < 20; ++i )
        v.push_back( i % 10 );
    v[10]=v[11];
    copy(v.begin(), v.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    deque<int> d;
    copy( v.begin(), v.end(), front_inserter( d ) );
    copy(d.begin(), d.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    deque<int> d1;
    copy( v.begin(), v.end(), inserter( d1, d1.end()) );
    copy(d1.begin(), d1.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    deque<int> d3;
    back_insert_iterator< deque<int> > d_b_ins1( d3 );
    for ( vector<int>::size_type i = 0; i < v.size(); ++i )
        *d_b_ins1 = v[ i ];
    copy(d3.begin(), d3.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    vector<int>::iterator iter = remove_if( v.begin(), v.end(), bind2nd( greater<int>(), 4 ));
    copy(v.begin(), v.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    v.erase( iter, v.end() );
    copy(v.begin(), v.end(), ostream_iterator<int> (cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    vector<int>::iterator i = find( v.begin(), v.end(), 4 );
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    vector<int>::reverse_iterator ri = find( v.rbegin(), v.rend(), 4 );
    cout << "Odleglosc od poczatku: " << distance( v.rbegin(), ri );
    cout << '\n';

    vector<int> s;
    s.push_back( 3 );
    s.push_back( 4 );
    i = find_end( v.begin(), v.end(), s.begin(), s.end() );
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    i = search( v.begin(), v.end(), s.begin(), s.end() );
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    ri = search( v.rbegin(), v.rend(), s.rbegin(), s.rend() );
    cout << "Odleglosc od poczatku: " << distance( v.rbegin(), ri );
    cout << '\n';

    i = search_n( v.begin(), v.end(), 2, 1);
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    i = find_first_of( v.begin(), v.end(), s.begin(), s.end() );
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    i = adjacent_find( v.begin(), v.end() );
    cout << "Odleglosc od poczatku: " << distance( v.begin(), i );
    cout << '\n';

    cout << "---------------------------------------------\n";

    s = v;
    v.push_back( 7 );
    cout << "Ciągi: \n";
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    cout << "Maksymalny element: " << *max_element( v.begin(), v.end() );
    cout << '\n';
    cout << "Minimalny element: " << *min_element( v.begin(), v.end() );
    cout << '\n';

    if( equal( v.begin(), v.end(), s.begin() ) )
        cout << "Ciągi są równe";
    else
        cout << "Ciągi nie są równe";
    cout << '\n';

    typedef vector<int>::iterator viter;

    pair< viter, viter > p = mismatch( v.begin(), v.end(), s.begin() );
    if ( p.first != v.end() )
        cout << "Pierwszy błąd: " << *p.first << ' ' << *p.second;
    cout << '\n';

    if ( lexicographical_compare( v.begin(), v.end(), s.begin(), s.end() ) )
        cout << "Wektor v jest mniejszy od wektora s";
    else
        cout << "Wektor v jest większy od wektora s";
    cout << '\n';

    cout << "---------------------------------------------\n";

    s.clear();
    s.resize( v.size() );
    copy_backward( v.begin(), v.end(), s.end() );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    copy_backward( s.begin(), s.end(), s.end() );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    transform( s.begin(), s.end(), s.begin(), bind2nd( multiplies<int>(), 10 ));
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    transform( s.begin(), s.end(), s.begin(), s.begin(), plus<int>());
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    swap_ranges( v.begin(), v.end()-4, s.begin() );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    fill( s.begin(), s.end(), 6 );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    fill_n( s.begin(), 5, 10 );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    generate( s.begin(), s.end(), rand );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    generate_n( s.begin(), 3, rand );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    s[5]=3;
    replace( s.begin(), s.end(), 3, 10 );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    replace_if( s.begin(), s.end(), not1( bind2nd (equal_to<int>(), 10)), 3 );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    remove_if( s.begin(), s.end(), not1( bind2nd (equal_to<int>(), 10)));
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    unique( s.begin(), s.end());
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    cout << "v: ";
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\ns: ";
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\n\n";

    reverse( s.begin(), s.end() -1 );
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    rotate( v.begin(), v.end()-1, v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    s.clear();
    s.push_back( 1 );
    s.push_back( 2 );
    s.push_back( 3 );
    cout << "s: ";
    copy( s.begin(), s.end(), ostream_iterator<int>(cout, ", "));
    cout << "\n\n";
    while( next_permutation( s.begin(), s.end() ))
    {
        copy( s.begin(), s.end(), ostream_iterator<int>(cout, ", "));
        cout << '\n';
    }

    cout << '\n';
    while( prev_permutation( s.begin(), s.end() ))
    {
        copy( s.begin(), s.end(), ostream_iterator<int>(cout, ", "));
        cout << '\n';
    }
    while( prev_permutation( s.begin(), s.end() ))
    {
        copy( s.begin(), s.end(), ostream_iterator<int>(cout, ", "));
        cout << '\n';
    }

    cout << "---------------------------------------------\n";

    random_shuffle( v.begin(), v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    partition( v.begin(), v.end(), bind2nd( modulus<int>(), 2 ) );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    stable_partition( v.begin(), v.end(), bind2nd( modulus<int>(), 2 ) );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    sort( v.begin(), v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    random_shuffle( v.begin(), v.end() );
    partial_sort( v.begin(), v.begin() +4,  v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    random_shuffle( v.begin(), v.end() );
    nth_element( v.begin(), v.begin() +4,  v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    make_heap( v.begin(), v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    pop_heap( v.begin(), v.end() );
    v.erase( --v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    v.push_back( 34 );
    push_heap( v.begin(), v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    sort_heap( v.begin(), v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    make_heap( v.begin(), v.end(), greater<int>() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    pop_heap( v.begin(), v.end(), greater<int>() );
    v.erase( --v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    v.push_back( 34 );
    push_heap( v.begin(), v.end(), greater<int>()  );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    sort_heap( v.begin(), v.end(), greater<int>()  );
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << '\n';

    cout << "---------------------------------------------\n";

    sort( v.begin(), v.end(), greater<int>() );
    sort( s.begin(), s.end(), greater<int>() );
    cout << "v: ";
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\ns: ";
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\n\n";

    if( binary_search( v.begin(), v.end(), 7, greater<int>()))
    {
        cout << "Liczba 7 należy do wektora v";
        pair< vector<int>::iterator, vector<int>::iterator > p = equal_range( v.begin(), v.end(), 7, greater<int>() );
        cout << ". Należy do przedziału [" << distance( v.begin(), p.first ) + 1
            << ';' << distance( v.begin(), p.second ) + 1 << ')';
    }
    else
        cout << "Liczba 7 nie należy do wektora v";
    cout << "\n\n";  
   
    sort( v.begin(), v.end() );
    sort( s.begin(), s.end() );
    cout << "v: ";
    copy( v.begin(), v.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\ns: ";
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", " ));
    cout << "\n\n";

    if( binary_search( v.begin(), v.end(), 7 ))
    {
        cout << "Liczba 7 należy do wektora v";
        pair< vector<int>::iterator, vector<int>::iterator > p = equal_range( v.begin(), v.end(), 7 );
        cout << ". Należy do przedziału [" << distance( v.begin(), p.first ) + 1
            << ';' << distance( v.begin(), p.second ) + 1 << ')';
    }
    else
        cout << "Liczba 7 nie należy do wektora v";
    cout << "\n\n";

    vector<int> m;
    merge( v.begin(), v.end(), s.begin(), s.end(), back_inserter( m ) );
    copy( m.begin(), m.end(), ostream_iterator<int>( cout, ", "));
    cout << '\n';

    set_union( m.begin(), m.end(), v.begin(), v.end(), back_inserter( s ));
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", "));
    cout << '\n';

    sort( s.begin(), s.end() );
    s.erase( find( s.begin(), s.end(), 20 ), s.end() );
    m.clear();
    set_intersection( s.begin(), s.end(), v.begin(), v.end(), back_inserter( m ));
    copy( m.begin(), m.end(), ostream_iterator<int>( cout, ", "));
    cout << '\n';

    s.clear();
    set_difference( v.begin(), v.end(), m.begin(), m.end(), back_inserter( s ));
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", "));
    cout << '\n';

    s.clear();
    set_symmetric_difference( v.begin(), v.end(), m.begin(), m.end(), back_inserter( s ));
    copy( s.begin(), s.end(), ostream_iterator<int>( cout, ", "));
    cout << '\n';

    random_shuffle( v.begin(), v.end() );
    sort( v.begin(), v.begin() + 7 );
    sort( v.begin() + 7, v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
    cout << '\n';

    inplace_merge( v.begin(), v.begin() + 7, v.end() );
    copy( v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
    cout << '\n';

    if ( includes( m.begin(), m.end(), s.begin(), s.end() ))
        cout << "s zawiera sie w m";
    else
        cout << "s nie zawiera się w m";
    cout << '\n';
}
