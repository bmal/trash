#ifndef CALC_H
#define CALC_H

#include "token_stream.h"
#include "token_stream.cpp"
#include <map>

class Calc
{
    public:
        Calc();
        void run();

    private:
        double expression();
        double term();
        double special();
        double primary();
        double statement();
        double declaration();
        void clean_up_mess();
        bool is_declared( string );
        double define_name( string, double );
        double get_value( string );
        void set_value( string, double );
        Token_stream ts;
        static const char print = ';';
        static const char quit = 'q';
        static const char number = '8';
        static const char name = 'n';
        static const char let = 'l';
        map< string, double > var_table;
};

#endif
