/*
 * *** Gramatyka ***
 *
 * Statement:
 *      Expression
 *      Print
 *      Quit
 *
 * Print:
 *      ;
 *
 * Quit:
 *      q
 *
 * Expression:
 *      Term
 *      Expression + Term
 *      Expression - Term
 *
 * Term:
 *      Primary
 *      Term * Primary
 *      Term / Primary
 *      Term % Primary
 *
 * Special:
 *      Primary
 *      Primary !
 *      Primary ^ Primary
 *
 * Primary:
 *      Number
 *      ( Expression )
 *      - Primary
 *      + Primary
 *
 * Number:
 *      floating-point-literal
 *
 */

#include <stdlib.h>
#include "token_stream.h"

using namespace std;

Token_stream::Token_stream()
    : full( false ), buffer( 0 )
{}

Token Token_stream::get()
{
    if ( full )
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch ( ch )
    {
        case quit:
        case print:
        case '(':
        case ')':
        case '{':
        case '}':
        case '=':
        case '!':
        case '^':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            return Token( ch );
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
                cin.putback( ch );
                double val;
                cin >> val;
                return Token( number, val );
        }
        default:
        {
            if ( isalpha( ch ) )
            {
                string s;
                s += ch;
                while ( cin.get( ch ) && ( isalpha( ch ) || isdigit( ch ) ) )
                    s += ch;
                cin.putback( ch );
                if ( s == "let" )
                    return Token( let );
                else
                    return Token( name, s );
            }
            else
                throw runtime_error( "Nieprawidłowy token" );
        }
    }
}

void Token_stream::putback( Token t )
{
    if ( full )
        throw runtime_error( "Bufor jest pełny" );
    buffer = t;
    full = true;
}

void Token_stream::ignore( char c )
{
    if ( full && c == buffer.get_kind() )
    {
        full = false;
    }
    else
    {
        full = false;
        char ch = 0;
        while ( cin >> ch )
            if ( ch == c )
                return;
    }
} 
