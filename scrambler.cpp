#include <iostream>
#include <iterator>
#include <vector>
#include <memory>
#include <random>

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>


template<bool control_characters>
class Scrambler
{
   public:
      void set_random_number(int number)
      {
         random_number_ = number;
      }

      void set_password(const std::string& password)
      {
         int new_password = 0;
         for(int elem : password)
            new_password += elem;
         new_password %= last_char;
         if(new_password < first_char)
            new_password += first_char;
         password_ = new_password;
      }

      std::vector<char> encrypt(const std::vector<char>& message) const
      {
         std::default_random_engine dre(random_number_);
         std::uniform_int_distribution<int> shifts_generator(
               lower_bound, upper_bound);

         std::vector<char> result;
         for(int elem : message)
         {
            int shift = shifts_generator(dre);
            if((password_ ^ elem) + shift > last_char)
               result.push_back(first_char + ((password_ ^ elem) + shift)%last_char);
            else
               result.push_back((password_ ^ elem) + shift);
         }
         return result;
      }

      std::vector<char> decrypt(const std::vector<char>& code) const
      {
         std::default_random_engine dre(random_number_);
         std::uniform_int_distribution<int> shifts_generator(
               lower_bound, upper_bound);

         const auto size = code.size();

         std::vector<int> shifts;
         for(unsigned i = 0; i < size; ++i)
            shifts.push_back(shifts_generator(dre));

         std::vector<char> result;
         for(unsigned i = 0; i < size; ++i)
         {
            if(static_cast<int>(code[i]) - shifts[i] < first_char)
               result.push_back(password_ ^ (last_char + (static_cast<int>(code[i]) - shifts[i] - first_char)));
            else
               result.push_back(password_ ^ (code[i] - shifts[i]));
         }
         return result;
      }

   private:
      std::vector<char> message_;
      int random_number_ {0};
      int password_ {0};

      const int lower_bound {0};
      const int upper_bound {90};
      const int first_char
      {
         boost::mpl::if_<
            boost::mpl::bool_<control_characters>, 
            boost::mpl::int_<0>, 
            boost::mpl::int_<32>
         >::type::value
      };
      const int last_char {127};
};

int main()
{
   std::cout << "Wpisz wiadomosc (enter -> ctrl-D):\n\t>> ";
   std::vector<char> message(
         std::istreambuf_iterator<char>(std::cin),
         std::istreambuf_iterator<char>());
   message.pop_back();

   int random_number;
   std::cout << "Wpisz losowa liczbe:\n\t>> ";
   std::cin >> random_number;

   std::string password;
   std::cout << "Wpisz haslo:\n\t>> ";
   std::cin >> password;

   Scrambler<false> scrambler;
   scrambler.set_random_number(random_number);
   scrambler.set_password(password);

   auto result = scrambler.encrypt(message);
   auto original = scrambler.decrypt(result);

   for(auto elem : result)
      std::cout << elem;
   std::cout << std::endl;
   for(auto elem : original)
      std::cout << elem;
}
