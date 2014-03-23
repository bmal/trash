#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "boost/signal.hpp"
#include "boost/smart_ptr.hpp"

using namespace std;

class parking_lot_guard
{
   typedef boost::signal<void(const string&)> alarm_type;
   typedef alarm_type::slot_type slot_type;
   typedef vector<string> cars;
   typedef cars::iterator iterator;

   public:
      parking_lot_guard() : alarm_(new alarm_type), cars_(new cars)
      {}

      boost::signals::connection
         connect(const slot_type& slot)
      {
            return alarm_->connect(slot);
      }

      void operator() (bool is_entering, const string& car_id)
      {
         if(is_entering)
            enter(car_id);
         else
            leave(car_id);
      }

   private:
      boost::shared_ptr<alarm_type> alarm_;
      boost::shared_ptr<cars> cars_;

      void enter(const string& car_id)
      {
         cout << "parking_lot_guard::enter(" << car_id << ")\n";

         if(binary_search(cars_->begin(), cars_->end(), car_id))
            (*alarm_)(car_id);
         else
            cars_->insert(lower_bound(cars_->begin(), cars_->end(), car_id),
                  car_id);
      }

      void leave(const string& car_id)
      {
         cout << "parking_lot_guard::leave(" << car_id << ")\n";

         if(!binary_search(cars_->begin(), cars_->end(), car_id))
            (*alarm_)(car_id);
         else
            cars_->erase(
                  remove(cars_->begin(), cars_->end(), car_id),
                  cars_->end());
      }
};

class gate
{
   typedef boost::signal<void(bool, const string&)> signal_type;
   typedef signal_type::slot_type slot_type;
   public:
      boost::signals::connection
         connect(const slot_type& slot)
      {
            return enter_or_leave_.connect(slot);
      }

      void enter(const string& car_id)
      {
         enter_or_leave_(true, car_id);
      }

      void leave(const string& car_id)
      {
         enter_or_leave_(false, car_id);
      }

   private:
      signal_type enter_or_leave_;
};

class security_guard
{
   public:
      security_guard(const char* name) : name_(name)
      {}

      void stop_the_car() const
      {
         cout << "Stop! Stac, mowi funkcjonariusz " << name_ << endl;
      }

      void ignore() const
      {
         cout << "Nic nie widzialem!\n";
      }

      void operator() (const string& car_id) const
      {
         if(!car_id.find(string("DB")))
            stop_the_car();
         else
            ignore();
      }

   private:
      string name_;
};

int main()
{
   vector<security_guard> security_guards;
   security_guards.push_back("Daniel");
   security_guards.push_back("Wiktor");
   security_guards.push_back("Pawel");

   gate gate1;
   gate gate2;

   parking_lot_guard monitoring;

   gate1.connect(monitoring);
   gate2.connect(monitoring);

   for(vector<security_guard>::size_type i = 0;
         i < security_guards.size();
         ++i)
      monitoring.connect(security_guards[i]);

   gate1.enter("DB 1432");
   gate2.enter("PO 3421");
   gate2.enter("DA 6503");
   gate1.enter("PO 3421");

   gate2.leave("DB 1432");
   gate1.leave("DB 1432");
   gate1.leave("DA 6503");
}
