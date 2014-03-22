#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include "boost/bind.hpp"
#include "boost/smart_ptr.hpp"

using namespace std;

class status
{
   public:
      status(const char* s) : _name(s), _ok(true) { cout << "Konstruktor\n"; }
      status( const status& other ) : _name(other._name), _ok(other._ok)
      {
         cout << "Konst kop\n";
      }

      status& operator=( const status& other )
      {
         cout << "oper =\n";
         _name = other._name;
         _ok = other._ok;
         return *this;
      }

      bool is_ok() { return _ok; }
      void break_it() { _ok = false; }
      void report()
      {
         if(_ok)
            cout << _name << " jest sprawny\n";
         else
            cout << _name << " nie jest sprawny\n";
      }

   private:
      string _name;
      bool _ok;
};

template<typename T>
void print( const T& obj )
{
   cout << obj << ", ";
}

int main()
{
   vector<status> v;
   v.push_back("kosiarka"); 
   v.push_back("telefon");
   v.push_back("zmywarka");
   v.push_back("laptop");

   v[1].break_it();

   cout << "---------------------------------\n";

   for_each(v.begin(), v.end(), boost::bind(&status::report, _1));
   cout << endl << endl;

   vector<boost::shared_ptr<status> > v1;
   v1.push_back(boost::shared_ptr<status>(new status("kosiarka"))); 
   v1.push_back(boost::shared_ptr<status>(new status("telefon")));
   v1.push_back(boost::shared_ptr<status>(new status("zmywarka")));
   v1.push_back(boost::shared_ptr<status>(new status("laptop")));

   v1[1]->break_it();

   for_each(v1.begin(), v1.end(), boost::bind(&status::report, _1));

   cout << "\n---------------------------------------\n\n";

   vector<int> v2;
   for(int i = 0; i < 10; ++i)
      v2.push_back(i);

   vector<int> v3;
   remove_copy_if(v2.begin(), v2.end(), back_inserter(v3), 
             boost::bind(logical_or<bool>(), 
                         boost::bind(less<int>(), _1, 3),
                         boost::bind(greater<int>(), _1, 7)));

   copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, ", "));

   cout << "\n---------------------------------------\n\n";

   map<int, string> m;
   m[1] = "jeden";
   m[2] = "dwa";
   m[3] = "trzy";
   m[4] = "cztery";

   for_each(m.begin(), m.end(), boost::bind(&print<string>, boost::bind(&map<int, string>::value_type::second, _1)));
}
