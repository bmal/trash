#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <iostream>
#include <stdexcept>
#include "token.h"

class Token_stream
{
    public:
        Token_stream();                 // Tworzy obiekt klasy Token_stream, który wczytuje dane ze strumienia cin
        Token get();                    // Tworzy token
        void putback( Token );          // Zwraca token
        void ignore( char );            // Odrzuca znaki do i włącznie z c

    private:
        bool full;                      // Czy w buforze jest token?
        Token buffer;                   // Przechowuje zwrócony przez putback() token
        static const char quit = 'q';
        static const char print = ';';
        static const char number = '8';
};

#endif
