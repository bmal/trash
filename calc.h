#ifndef CALC_H
#define CALC_H

#include "token_stream.h"
#include "token_stream.cpp"

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
        void clean_up_mess();
        Token_stream ts;
        static const char print = ';';
        static const char quit = 'q';
        static const char number = '8';
};

#endif
