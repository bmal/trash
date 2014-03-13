#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Elementy
{
    public:
        virtual void get() = 0;
        virtual ~Elementy() {}
};

class Wystroj
 : public Elementy
{
    public:
        virtual void get();
        void add( Elementy* );
        void remove( Elementy* );
        virtual ~Wystroj();
    private:
        vector< Elementy* > elem_list;
};

void Wystroj::get()
{
    for( vector< Elementy* >::iterator iter = elem_list.begin();
         iter < elem_list.end();
         ++iter )
        ( *iter )->get();
}

void Wystroj::add( Elementy* e )
{
    elem_list.push_back( e );
};

void Wystroj::remove( Elementy* e )
{
    vector< Elementy* >::iterator iter 
        = find( elem_list.begin(),
                elem_list.end(),
                e );
    if( iter != elem_list.end() )
    {
        delete e;
        elem_list.erase( iter );
    }
    else
    {
        cerr << "Brak elementu";
        abort();
    }
}

Wystroj::~Wystroj()
{
    for( vector< Elementy* >::iterator iter = elem_list.begin();
         iter < elem_list.end();
         ++iter )
        delete *iter;
}

class Dzbanek
 : public Elementy
{
    public:
        virtual void get() { cout << " Dzbanek "; }
};

class Obraz
 : public Elementy
{
    public:
        virtual void get() { cout << " Obraz "; }
};

int main()
{
    Wystroj w;
    w.add( new Dzbanek );
    w.add( new Obraz );
    Elementy* iter = new Dzbanek;
    w.get();
    w.add( iter );
    cout << endl;
    w.get();
    w.remove( iter );
    cout << endl;
    w.get();
    cout << endl;
    w.remove( 0 );
}
