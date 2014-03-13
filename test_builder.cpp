#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

class Budowniczy
{
    public:
        Budowniczy();
        virtual ~Budowniczy();
        virtual void build_vector( int );
        virtual void build_p_int( int );
        virtual void build_n_int( int );

        virtual vector<int>& get_vector();

    protected:
        vector<int>* v;
};

Budowniczy::Budowniczy() : v( 0 )
{}

Budowniczy::~Budowniczy()
{
    delete v;
}

void Budowniczy::build_vector( int i )
{
    v = new vector<int> ( i );
}

void Budowniczy::build_p_int( int i )
{
    if( v == 0 )
        throw runtime_error( "v == 0" );

    for( vector<int>::size_type iter = 0; iter < v->size(); ++iter )
        if( ! (iter % 2) )
            ( *v )[ iter ] = i;
}

void Budowniczy::build_n_int( int i )
{
    if( v == 0 )
        throw runtime_error( "v == 0" );

    for( vector<int>::size_type iter = 0; iter < v->size(); ++iter )
        if( iter % 2 )
            ( *v )[ iter ] = i;
}

vector<int>& Budowniczy::get_vector()
{
    return *v;
}

class Budowniczy_pow2
        : public Budowniczy
{
    public:
        Budowniczy_pow2();
        virtual void build_p_int( int );
        virtual void build_n_int( int );

};

Budowniczy_pow2::Budowniczy_pow2() : Budowniczy()
{}

void Budowniczy_pow2::build_p_int( int i )
{
    if( v == 0 )
        throw runtime_error( "v == 0" );

    for( vector<int>::size_type iter = 0; iter < v->size(); ++iter )
        if( ! (iter % 2) )
            ( *v )[ iter ] = pow( 2, i );
}

void Budowniczy_pow2::build_n_int( int i )
{
    if( v == 0 )
        throw runtime_error( "v == 0" );

    for( vector<int>::size_type iter = 0; iter < v->size(); ++iter )
        if( iter % 2 )
            ( *v )[ iter ] = pow( 2, i );
}

class Kierownik
{
    public:
        Kierownik( Budowniczy& b ) : _bud( b ) {}
        void create_vector( int r, int p, int n )
        {
            _bud.build_vector( r );
            _bud.build_p_int( p );
            _bud.build_n_int( n );
        } 

    private:
        Budowniczy& _bud;
};

int main()
{
    Budowniczy* budowlaniec = new Budowniczy;
    Kierownik szef( *budowlaniec );

    try
    {
        szef.create_vector( 10, 2, 4 );
    }
    catch ( exception& e )
    {
        cerr << e.what();
    }

    copy( budowlaniec->get_vector().begin(),
          budowlaniec->get_vector().end(),
          ostream_iterator<int>( cout, ", " ));

    delete budowlaniec;
    cout << endl;

    budowlaniec = new Budowniczy_pow2;
    try
    {
        szef.create_vector( 10, 2, 4 );
    }
    catch ( exception& e )
    {
        cerr << e.what();
    }

    copy( budowlaniec->get_vector().begin(),
          budowlaniec->get_vector().end(),
          ostream_iterator<int>( cout, ", " ));

    delete budowlaniec;
}
