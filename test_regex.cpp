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
        string co = ".,/1234567890!@#$%^&*()_+-=[]{}:\";'";
        vector< string > v;
        istringstream bufor;
        while ( getline( plik, linia ) )
        {
            if( plik.fail() || plik.bad() )
                throw runtime_error( "plik padł");

            for ( string::size_type iter = 0; iter < linia.size(); ++iter )
                for ( string::size_type i = 0; i < co.size(); ++i )
                    if ( linia[iter] == co[i] )
                        linia[iter] = ' ';

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
        map<string, int> lista;
        for( vector<string>::size_type i = 0; i < v.size(); ++i )
        {
            if ( boost::regex_search( v[ i ], trafienia, wzor ) )
            {
                ++counter;
                cout << "Trafienie nr " << counter << '\t' << trafienia[ 0 ] << '\n';
                ++lista[ v[i] ];
            }
        }
        ofstream slownik( "slownik.txt" );
        for ( map<string,int>::const_iterator iter = lista.begin(); iter != lista.end(); ++iter )
            slownik << iter->first << '\t' << iter->second << '\n';
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
