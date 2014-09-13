#include <streambuf>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <functional>
#include <vector>
#include <iomanip>

using namespace std;

struct Flags
{
      enum options {bytes, lines, max_line_length, chars, words, num_of_flags};
      bitset<5> state;
};

int lines(const string& file_name)
{
   ifstream file(file_name);
   return count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(),
         '\n');
}

int chars(const string& file_name)
{
   ifstream file(file_name);
   return count_if(istreambuf_iterator<char>(file), istreambuf_iterator<char>(),
         [](const char) {return true;});
}

int words(const string& file_name)
{
   ifstream file(file_name);
   return count_if(istream_iterator<string>(file), istream_iterator<string>(),
         [](const string&) {return true;});
}

string::size_type max_line_length(const string& file_name)
{
   ifstream file(file_name);
   string::size_type max_size = 0;
   string line;

   while(getline(file, line))
      if(line.size() > max_size)
         max_size = line.size();

   return max_size;
}

int bytes(const string& file_name)
{
   return chars(file_name);
}

void set_options(const string& token, Flags& flag)
{
   for(string::size_type option_number = 1;
         option_number < token.size();
         ++option_number)
   {
      switch(token[option_number])
      {
         case 'b':
            flag.state.set(Flags::bytes);
            break;
         case 'l':
            flag.state.set(Flags::lines);
            break;
         case 'L':
            flag.state.set(Flags::max_line_length);
            break;
         case 'm':
            flag.state.set(Flags::chars);
            break;
         case 'w':
            flag.state.set(Flags::words);
            break;
         case 'h':
            cerr << "Opcje:\n"
               << "-b - bajty\n"
               << "-l - linie\n"
               << "-L - znaki w najdluzszej linii\n"
               << "-m - znaki\n"
               << "-w - slowa\n"
               << "-h - pomoc\n";
            exit(EXIT_SUCCESS);
         default:
            cerr << "wc: bledna opcja -- '"<< token[option_number] << "'\n"
               << "Napisz \"wc -h\" dla uzyskania informacji.\n";
            exit(EXIT_FAILURE);
      }
   }
}

int print_and_return(const string& file_name, function<int(const string&)> fun)
{
   int value = fun(file_name);
   cout << setw(4) << value << ' ';
   return value;
}

template<class Container>
void print_custom_and_sum(Container& counter, const Flags& flag, const string& file_name)
{
   if(flag.state[Flags::bytes])
      counter[Flags::bytes] += print_and_return(file_name, bytes);

   if(flag.state[Flags::lines])
      counter[Flags::lines] += print_and_return(file_name, lines);

   if(flag.state[Flags::max_line_length])
      counter[Flags::max_line_length] += print_and_return(file_name, max_line_length);

   if(flag.state[Flags::chars])
      counter[Flags::chars] += print_and_return(file_name, chars);

   if(flag.state[Flags::words])
      counter[Flags::words] += print_and_return(file_name, words);
}

template<class Container>
void print_default_and_sum(Container& counter, const Flags& flag, const string& file_name)
{
   counter[Flags::lines] += print_and_return(file_name, lines);
   counter[Flags::words] += print_and_return(file_name, words);
   counter[Flags::chars] += print_and_return(file_name, chars);
}

template<class Container>
void print_summary(const Container& counter, const Flags& flag)
{
   if(flag.state[Flags::bytes])
      cout << setw(4) << counter[Flags::bytes] << ' ';

   if(flag.state[Flags::lines])
      cout << setw(4) << counter[Flags::lines] << ' ';

   if(flag.state[Flags::max_line_length])
      cout << setw(4) << counter[Flags::max_line_length] << ' ';

   if(flag.state[Flags::chars])
      cout << setw(4) << counter[Flags::chars] << ' ';

   if(flag.state[Flags::words])
      cout << setw(4) << counter[Flags::words] << ' ';

   cout << "razem" << endl;
}

int main(int argc, char *argv[])
{
   const char option = '-';
   Flags flag;
   vector<int> counter(Flags::num_of_flags);
   int files_counter = 0;

   for(int i = 1; i < argc; ++i)
   {
      string token = argv[i];
      if(token[0] == option)
         set_options(token, flag);
      else
      {
         if(flag.state.any())
            print_custom_and_sum(counter, flag, token);
         else
            print_default_and_sum(counter, flag, token);

         cout << token << endl;
         ++files_counter;
      }
   }

   if(files_counter > 1)
      print_summary(counter, flag);
}
