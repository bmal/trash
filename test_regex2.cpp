#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"

using namespace std;

class print
{
   public:
      print( ofstream& strm ) : _strm( strm ), _ile(0) {}

      void operator() (boost::smatch what )
      {
         _strm << _ile << ' ' << what[1].str() << endl;
         ++_ile;
      }

   private:
      ofstream& _strm;
      int _ile;
};

class regex_callback
{
   public:
      regex_callback() : sum_( 0 ) {}

      void operator() ( boost::smatch what )
      {
         sum_ += boost::lexical_cast< int >( what[1].str() );
      }

      int get_sum()
      {
         return sum_;
      }

   private:
      int sum_;
};

int main()
{
   boost::regex reg1( "(new)|(delete)");
   boost::smatch match1;
   string tekst = "Kazdemu wuwolaniu new musi odpowiadac wywolanie delete" 
      "wywolanie samego new to jawny wyciek pamieci";
   int new_counter = 0;
   int delete_counter = 0;
   string::const_iterator beg = tekst.begin();
   string::const_iterator end = tekst.end();
   while( boost::regex_search( beg, end, match1, reg1 ))
   {
      match1[1].matched ? ++new_counter : ++delete_counter;
      beg = match1[0].second;
   }

   if( new_counter > delete_counter )
      cout << "Wiecej new (" << new_counter << ") niz delete (" << delete_counter << ")\n";
   else
      cout << "Mniej new (" << new_counter << ") niz delete (" << delete_counter << ")\n";
   
//-----------------------------------

   fstream plik( "stalin.txt" );
   stringstream ss;
   ss << plik.rdbuf();
   string pliczek = ss.str();
   boost::regex reg( "(stalin[a-z]*)", boost::regex::icase | boost::regex::perl );
   boost::smatch match;
   boost::sregex_iterator iter( pliczek.begin(), pliczek.end(), reg );
   boost::sregex_iterator end_;
   ofstream nowy("regex_test.txt");
   if( !nowy )
      throw runtime_error("blad pliku!");
   for_each( iter, end_, print(nowy));

   cout << "-----------------------------------\n";

   boost::regex reg2( "(\\d{1,}),?" );
   string test = "1,2,3,23,2,3,45,3,23324,5435";
   boost::sregex_iterator it( test.begin(), test.end(), reg2 );
   boost::sregex_iterator end__;
   regex_callback c;
   int sum = for_each( it, end__, c ).get_sum();
   cout << "suma: " << sum << endl;
}
