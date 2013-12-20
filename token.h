#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

class Token
{
    public:
        Token( char k ) : kind( k ), value( 0 ) {}
        Token( char k, double v ) : kind( k ), value( v ) {}
        Token( char k, string s ) : kind( k ), name( s ) {}
        char get_kind() { return kind; }
        double get_value() { return value; }
        string get_name() { return name; }

    private:
        char kind;
        double value;
        string name;
};

#endif
