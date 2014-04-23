#include <memory>
#include <mutex>

//#include <thread>
//#include <iostream>
//#include <chrono>
//#include "test_threadsafe_queue.hpp"
//#include <stack>
//#include <queue>

template<typename T>
class threadsafe_stack
{
   private:
      struct node
      {
         std::shared_ptr<T> data;
         std::unique_ptr<node> next;
      };

      std::mutex head_mutex;
      std::unique_ptr<node> head;

   public:
      threadsafe_stack()
         : head(new node)
      {}

      threadsafe_stack(const threadsafe_stack& other) = delete;
      threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

      std::shared_ptr<T> pop();
      void push(T new_value);
};

template<typename T>
void threadsafe_stack<T>::push(T new_value)
{
   std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
   std::unique_ptr<node> new_node(new node);
   std::lock_guard<std::mutex> lk(head_mutex);
   head->data = new_data;
   new_node->next = std::move(head);
   head = std::move(new_node);
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop()
{
   std::unique_ptr<node> res;
   std::lock_guard<std::mutex> lk(head_mutex);

   if(!head->next)
      return std::shared_ptr<T>();

   res = std::move(head->next);
   head->next = std::move(res->next);
   return res->data;
}

/*
int start = 0;

void fill_s(threadsafe_stack<int>& s)
{
   for(int i = 0; i < 100000; ++i)
      s.push(i);
}

void pop_s(threadsafe_stack<int>& s)
{
   while(!start);
   for(int i = 0; i < 25000; ++i)
      s.pop();
      //std::cout << *s.pop() << ' ' << std::this_thread::get_id() << std::endl;
}

void fill_q(threadsafe_queue<int>& s)
{
   for(int i = 0; i < 100000; ++i)
      s.push(i);
}

void pop_q(threadsafe_queue<int>& s)
{
   while(!start);
   for(int i = 0; i < 25000; ++i)
      s.try_pop();
//std::cout << *s.pop() << ' ' << std::this_thread::get_id() << std::endl;
}

int main()
{
   threadsafe_queue<int> q;
   std::thread tf2(fill_q, std::ref(q));
   tf2.join();
   std::thread tp3(pop_q, std::ref(q));
   std::thread tp4(pop_q, std::ref(q));
   std::thread tp5(pop_q, std::ref(q));
   std::thread tp6(pop_q, std::ref(q));
   auto q_start = std::chrono::steady_clock::now();
   start = true;
   tp3.join();
   tp4.join();
   tp5.join();
   tp6.join();
   auto q_end = std::chrono::steady_clock::now();

   threadsafe_stack<int> s;
   std::thread tf(fill_s, std::ref(s));
   tf.join();
   std::thread tp1(pop_s, std::ref(s));
   std::thread tp2(pop_s, std::ref(s));
   std::thread tp7(pop_s, std::ref(s));
   std::thread tp8(pop_s, std::ref(s));
   start = true;
   auto s_start = std::chrono::steady_clock::now();
   tp1.join();
   tp2.join();
   tp7.join();
   tp8.join();
   auto s_end = std::chrono::steady_clock::now();
   start = false;

   std::cout << "Czas dla stosu: " << 
      std::chrono::duration_cast<std::chrono::milliseconds>(s_end - s_start).count() << std::endl;
   std::cout << "Czas dla kolejki: " << 
      std::chrono::duration_cast<std::chrono::milliseconds>(q_end - q_start).count() << std::endl;

   std::cout << "Dla 1 watku: \n";
   std::queue<int> q_std;
   for(int i = 0; i < 100000; ++i)
      q_std.push(i);
   std::stack<int> s_std;
   for(int i = 0; i < 100000; ++i)
      s_std.push(i);
   s_start = std::chrono::steady_clock::now();
   for(int i = 0; i < 100000; ++i)
      s_std.pop();
   s_end = std::chrono::steady_clock::now();
   q_start = std::chrono::steady_clock::now();
   for(int i = 0; i < 100000; ++i)
      q_std.pop();
   q_end = std::chrono::steady_clock::now();

   std::cout << "Czas dla stosu: " << 
      std::chrono::duration_cast<std::chrono::milliseconds>(s_end - s_start).count() << std::endl;
   std::cout << "Czas dla kolejki: " << 
      std::chrono::duration_cast<std::chrono::milliseconds>(q_end - q_start).count() << std::endl;
}
*/
