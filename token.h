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
        char get_kind() { return kind; }
        double get_value() { return value; }

    private:
        char kind;
        double value;
};

#endif
