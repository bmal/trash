#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <bitset>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream plik( "binary.txt" );
    ofstream of("znaczenie.txt");

    istream_iterator<string> i(plik);
    istream_iterator<string> eos;
    ostream_iterator<char> o(of);
    vector< char > v;

    for(; i != eos; ++i )
        v.push_back( bitset<8>(*i).to_ulong());

    copy( v.begin(), v.end(), o );
    return 0;
}
