#include <stdlib.h>
#include <math.h>
#include "calc.h"

using namespace std;

Calc::Calc()
    : ts( Token_stream() )
{
}

void Calc::run()
{
    while ( cin )
        try
        {
            cout << ">";
            Token t = ts.get();
            while (t.get_kind() == print )
                t = ts.get();
            if (t.get_kind() == quit )
                return;
            ts.putback( t );
            cout << "=" << expression() << '\n';
        }
    catch ( runtime_error & e )
    {
        cerr << e.what() << '\n';
        clean_up_mess();
    }
}

double Calc::expression()
{
    double left = term();
    Token t = ts.get();
    while ( true )
    {
        switch ( t.get_kind() )
        {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback( t );
                return left;
        }
    }
}

double Calc::term()
{
    double left = special();
    Token t = ts.get();
    while ( true )
    {
        switch ( t.get_kind() )
        {
            case '*':
                left *= special();
                t = ts.get();
                break;
            case '/':
                {
                    double d = special();
                    if ( d == 0 )
                        throw runtime_error( "Dzielenie przez 0" );
                    left /= d;
                    t = ts.get();
                    break;
                }
            case '%':
                {
                    double d = special();
                    int i1 = static_cast< int >( primary() );
                    if ( i1 != left )
                        throw runtime_error( "Lewy argument operatora % nie jest liczbą całkowitą\n" );
                    int i2 = static_cast< int >( d );
                    if ( i2 != d )
                        throw runtime_error( "Prawy argument operatora % nie jest liczbą całkowitą\n" );
                    left = i1 % i2;
                    t = ts.get();
                    break;
                }
            default:
                ts.putback( t );
                return left;
        }
    }
}

double Calc::special()
{
    double left = primary();
    Token t = ts.get();
    switch ( t.get_kind() )
    {
        case '!':
        {
            int i = static_cast< int >( left );
            if ( i != left )
                throw runtime_error( "Próba obliczenia silni z liczby zmiennoprzecinkowej\n" );
            if ( left > 0 )
            {
                int sum = 1;
                for ( int i = 1; i <= left; ++i )
                    sum *= i;
                return sum;
            }
            else if ( left == 0 )
                return 1;
            else
                throw runtime_error( "Silnia z ujemnej liczby\n" );
        }
        case '^':
        {
            double d = special();
            return pow( left, d );
        }
        default:
           ts.putback( t );
           return left;
    }
}

double Calc::primary()
{
    Token t = ts.get();
    switch ( t.get_kind() )
    {
        case '(':
            {
                double d = expression();
                t = ts.get();
                if ( t.get_kind() != ')' )
                    throw runtime_error( "Oczekiwano ')'\n" );
                return d;
            }
        case '{':
            {
                double d = expression();
                t = ts.get();
                if ( t.get_kind() != '}' )
                    throw runtime_error( "Oczekiwano '}'\n" );
                return d;
            }
        case number:
            return t.get_value();
        case '-':
            return - primary();
        case '+':
            return primary();
        default:
            throw runtime_error( "Oczekiwano czynnika\n" );
    }
}

void Calc::clean_up_mess()
{
    ts.ignore( print );
}
