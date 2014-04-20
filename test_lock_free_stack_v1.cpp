#include <atomic>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>

template<typename T>
class lock_free_stack
{
   private:
      struct node
      {
         std::shared_ptr<T> data;
         node* next;

         node(const T& data_)
            : data(std::make_shared<T>(data_)), next(nullptr)
         {}
      };

      std::atomic<node*> head;
      std::atomic<unsigned> threads_in_pop;
      std::atomic<node*> to_be_deleted;

      static void delete_nodes(node* nodes)
      {
         std::cout << "CZYSZCZENIE\n";
         int i = 0;
         while(nodes)
         {
            std::cout << i++ << std::endl;
            node* next = nodes->next;
            delete nodes;
            nodes = next;
         }
      }

      void try_reclaim(node* old_head)
      {
         std::cout << threads_in_pop.load() << std::endl;
         if(threads_in_pop == 1)
         {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            if(!--threads_in_pop)
            {
               delete_nodes(nodes_to_delete);
            }
            else if(nodes_to_delete)
               chain_pending_nodes(nodes_to_delete);
            delete old_head;
         }
         else
         {
            chain_pending_node(old_head);
            --threads_in_pop;
         }
      }

      void chain_pending_nodes(node* first, node* last)
      {
         last->next = to_be_deleted;
         while(!to_be_deleted.compare_exchange_weak(last->next, first));
      }

      void chain_pending_nodes(node* nodes)
      {
         node* last = nodes;
         while(node* next = last->next)
            last = next;
         chain_pending_nodes(nodes, last);
      }

      void chain_pending_node(node* n)
      {
         chain_pending_nodes(n, n);
      }

   public:
      lock_free_stack()
         : head(nullptr), threads_in_pop(0), to_be_deleted(0)
      {}

      std::shared_ptr<T> pop()
      {
         ++threads_in_pop;
         node* old_head = head.load();
         while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
         std::shared_ptr<T> res;
         if(old_head)
            res.swap(old_head->data);
         try_reclaim(old_head);
         return res;
      }

      void push(const T& data)
      {
         node* const new_node = new node(data);
         new_node->next = head.load();
         while(!head.compare_exchange_weak(new_node->next, new_node));
      }
};

bool stop = 1;

void push(lock_free_stack<int>& s)
{
   for(int i = 0; i < 1000; ++i)
      s.push(i);
}

void pop(lock_free_stack<int>& s)
{
   while(stop);
   for(int i = 0; i < 250; ++i)
      s.pop();
}

int main()
{
   lock_free_stack<int> s;

   std::thread t_push(push, std::ref(s));
   std::thread t_pop1(pop, std::ref(s));
   std::thread t_pop2(pop, std::ref(s));
   std::thread t_pop3(pop, std::ref(s));
   std::thread t_pop4(pop, std::ref(s));

   t_push.join();

   stop = 0;

   t_pop1.join();
   t_pop2.join();
   t_pop3.join();
   t_pop4.join();
}
