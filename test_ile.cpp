#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include <string>
#include <stdexcept>

using namespace std;

int main()
{
    try
    {
        boost::regex wzor( "\\[id:\\d+\\]");
        ifstream plik("lista.txt");
        if ( !plik )
            throw runtime_error( "Nie można otworzyć pliku" );
        string linia;
        vector< string > v;
        istringstream bufor;
        while ( getline( plik, linia ) )
        {
            if( plik.fail() || plik.bad() )
                throw runtime_error( "plik padł");
            if ( !bufor.good() )
                bufor.clear();
            bufor.str( linia );
            string slowo;
            while ( bufor >> slowo )
            {
                v.push_back( slowo );
            }
        }
        boost::smatch trafienia;
        int counter = 0;
        for( vector<string>::size_type i = 0; i < v.size(); ++i )
        {
            if ( boost::regex_search( v[ i ], trafienia, wzor ) )
            {
                ++counter;
                cout << "Trafienie nr " << counter << '\t' << trafienia[ 0 ] << '\n';
            }
        }
    }
    catch( runtime_error& e )
    {
        cerr << e.what();
    }
    catch( ... )
    {
        cerr << "nieznany blad";
    }
}
