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
            while ( t.get_kind() == print )
                t = ts.get();
            if ( t.get_kind() == quit )
                return;
            ts.putback( t );
            cout << "=" << statement() << '\n';
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
        case square_root:
            {
                double d = primary();
                if ( d < 0 )
                    throw runtime_error( "Pierwiastek z liczyb ujemnej" );
                return sqrt( d );
            }
        case number:
            return t.get_value();
        case '-':
            return - primary();
        case '+':
            return primary();
        default:
            if ( var_table.count( t.get_name() ) > 0 )
                return get_value( t.get_name() );
            else
            throw runtime_error( "Oczekiwano czynnika\n" );
    }
}

double Calc::statement()
{
    Token t = ts.get();
    switch ( t.get_kind() )
    {
        case let:
            return declaration();
        case set:
            return assign();
        default:
            ts.putback( t );
            return expression();
    }
}

double Calc::declaration()
{
    Token t = ts.get();
    if ( t.get_kind() != name )
        throw runtime_error( "Oczekiwano nazwy w deklaracji" );
    string var_name  = t.get_name();

    Token t2 = ts.get();
    if ( t2.get_kind() != '=' )
        throw runtime_error( "Brak znaku '=' w deklaracji zmiennej " );

    double d = expression();
    define_name( var_name, d );
    return d;
}

double Calc::assign()
{
    Token t = ts.get();
    if ( t.get_kind() != name )
        throw runtime_error( "Oczekiwano nazwy" );
    string var_name = t.get_name();

    if ( ! is_declared( var_name ) )
        throw runtime_error( "Nie można przypisać wartości niezadeklarowanej zmiennej" );

    Token t2 = ts.get();
    if ( t2.get_kind() != '=' )
        throw runtime_error( "Brak znaku '=' w przypisaniu wartości zmiennej" );

    double d = expression();
    set_value( var_name, d );
    return d;
}

void Calc::clean_up_mess()
{
    ts.ignore( print );
}

bool Calc::is_declared( string s )
{
    if ( var_table.count( s ) > 0 )
        return true;
    else
        return false;
}

double Calc::define_name( string s, double d )
{
    if ( is_declared( s ) )
        throw runtime_error( "Podwójna deklaracja" );
    set_value( s, d );
    return d;
}

double Calc::get_value( string s )
{
    map< string, double >::iterator iter = var_table.find( s );
    return iter->second;
}

void Calc::set_value( string s, double d )
{
    var_table[ s ] = d;
}
