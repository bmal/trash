#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "boost/smart_ptr.hpp"
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/lambda/if.hpp"
#include "boost/lambda/loops.hpp"
#include "boost/lambda/switch.hpp"
#include "boost/lambda/construct.hpp"
#include "boost/lambda/casts.hpp"
#include "boost/lambda/exceptions.hpp"
#include "boost/lambda/algorithm.hpp"
#include "boost/lambda/numeric.hpp"

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

class mem
{
   public:
      mem& operator= (const string& s)
      {
         _v.push_back(s);
         return *this;
      }
      void print()
      {
         copy(_v.begin(), _v.end(), ostream_iterator<string>(cout, ", "));
      }
   private:
      vector<string> _v;
};

int main()
{
   using namespace boost::lambda;
   vector<status> v;
   v.push_back("kosiarka"); 
   v.push_back("telefon");
   v.push_back("zmywarka");
   v.push_back("laptop");

   v[1].break_it();

   cout << "---------------------------------\n";

   for_each(v.begin(), v.end(), bind(&status::report, _1));
   cout << endl << endl;

   vector<boost::shared_ptr<status> > v1;
   v1.push_back(boost::shared_ptr<status>(new status("kosiarka"))); 
   v1.push_back(boost::shared_ptr<status>(new status("telefon")));
   v1.push_back(boost::shared_ptr<status>(new status("zmywarka")));
   v1.push_back(boost::shared_ptr<status>(new status("laptop")));

   v1[1]->break_it();

   for_each(v1.begin(), v1.end(), bind(&status::report, *_1));

   cout << "\n---------------------------------------\n\n";

   vector<int> v2;
   for(int i = 0; i < 10; ++i)
      v2.push_back(i);

   vector<int> v3;
   remove_copy_if(v2.begin(), v2.end(), back_inserter(v3), _1 < 3 || _1 > 7);

   copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, ", "));

   cout << "\n---------------------------------------\n\n";

   map<int, string> m;
   m[1] = "jeden";
   m[2] = "dwa";
   m[3] = "trzy";
   m[4] = "cztery";

   for_each(m.begin(), m.end(), cout << bind(&map<int, string>::value_type::second, _1) << constant(", "));
   cout << endl;

   constant_type<string>::type pause(constant(string(", ")));
   for_each(m.begin(), m.end(), cout << bind(&map<int, string>::value_type::second, _1) << pause);
   cout << endl;

   mem r;
   var_type<mem>::type remember(var(r));
   for_each(m.begin(), m.end(), remember = bind<string>(&map<int, string>::value_type::second, _1));
   r.print();
   
   cout << "\n----------------------------------------\n\n";

   vector<int> v4;
   for(int i = 0; i < 10; ++i)
      v4.push_back(i);

   transform(v4.begin(), v4.end(), ostream_iterator<int>(cout, ", "), _1 * 10);
   
   cout << "\n----------------------------------------\n\n";

   for_each(v4.begin(), v4.end(), if_then_else(_1 < 5, cout << constant("mniejsze niz 5\n"), cout << constant("wieksze niz 5\n")));
   cout << endl;
   for_each(v4.begin(), v4.end(), if_(_1 < 5)[cout << constant("mniejsze niz 5\n")].else_[cout << constant("wieksze niz 5\n")]);
   cout << endl;

   for_each(v4.begin(), v4.end(), switch_statement(_1,
            case_statement<0>
              (cout << constant("mamy 0\n")),
            case_statement<5>
              (cout << constant("mamy 5\n")),
            default_statement
              (cout << constant("cos innego ") << _1 << '\n')));
   cout << endl <<endl;

   for_each(v4.begin(), v4.end(), 
         while_loop(_1 > 0, (cout << constant("zmniejszamy!(") 
               << ll_static_cast<char>(_1 + 40) << constant(")\n"), --_1))); //or do_while_loop

   cout << "\n----------------------------------------\n\n";

   map<string, boost::shared_ptr<int> > m1;
   typedef boost::shared_ptr<int> sptr;
   m1["pierwszy"] = sptr(new int(10));
   m1["drugi"];
   m1["trzeci"] = sptr(new int(5));

   for_each(m1.begin(), m1.end(), if_then_else(!bind(&map<string, sptr>::value_type::second, _1),
                                               (bind(&map<string, sptr>::value_type::second, _1) = 
                                               bind(constructor<sptr>(), bind(new_ptr<int>())),
                                                   cout << constant("Utworzono wskaznik dla: ") <<
                                                   bind(&map<string, sptr>::value_type::first, _1) <<
                                                   constant(" o wartosci ")) << constant("\n"),
                                              cout << constant("Posiada juz wskaznik\n")));

   for_each(m1.begin(), m1.end(), if_then_else(!bind(&map<string, sptr>::value_type::second, _1),
                                                 throw_exception(bind(constructor<runtime_error>(), constant("pusty wskaznik"))),
                                              cout << constant("Ehh! Posiada juz wskaznik\n")));

}
