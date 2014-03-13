#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "test_alloc.h"

using namespace std;

int main()
{
    vector< int, My_allocator< int > > v;
    v.push_back( 10 );
}
