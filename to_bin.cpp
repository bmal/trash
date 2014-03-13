#include <stdlib.h>
#include <bitset>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
{
    ifstream plik("plik.txt"); 
    if ( !plik ) 
        throw runtime_error( "Nie można otworzyć pliku" ); 
    ofstream of("binary.txt");
    while( !plik.eof() )
    {
        int i = plik.get();
        of << bitset<8>(i) << ' ';
    }
}
