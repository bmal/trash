#include <iostream>
#include <string>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    filebuf buffer;
    ostream out( &buffer );
    istream in( &buffer );
    buffer.open( "plik.txt", ios::out | ios::in | ios::trunc );
    if ( !out || !in )
        cerr << "BLAD!";
    for ( int i = 0; i < 4; ++i )
    {
        ios::streampos pos = out.tellp();
        out << i << ". wiersz" << endl;
        char c;
        in.seekg( pos );
        while ( in.get( c ) )
            cout.put( c );
        in.clear();
    }
    in.seekg( 0, ios::beg );
    cout << in.rdbuf();
}
