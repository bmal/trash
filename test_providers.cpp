#include <iostream>
#include <functional>
#include <future>  
#include <chrono> 
#include <thread>

int countdown (int from, int to) {
  for (int i=from; i!=to; --i) {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";
  return from-to;
}

void countdown_promise (int from, int to, std::promise<int>& pr) {
  for (int i=from; i!=to; --i) {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";
  pr.set_value(from-to);
}

int main ()
{
  //packaged_task
  std::packaged_task<int(int,int)> tsk (countdown);   
  std::future<int> ret = tsk.get_future();           
  std::thread th(std::move(tsk),10,0);   
  std::cout << "zzz...zzz...zzz\n";
  int value = ret.get();                 
  std::cout << "The countdown lasted for " << value << " seconds.\n";
  th.join();

  std::cout << "-------------------------------------\n";
  //async

  auto ret1 = std::async(std::launch::async, countdown, 10, 0);
  std::cout << "zzz...zzz...zzz\n";
  int value1 = ret1.get();                 
  std::cout << "The countdown lasted for " << value1 << " seconds.\n";

  std::cout << "-------------------------------------\n";
  //promise

  std::promise<int> pr;
  auto ret2 = pr.get_future();
  std::thread th2(countdown_promise, 10, 0, ref(pr));
  std::cout << "zzz...zzz...zzz\n";
  int value2 = ret2.get();                 
  std::cout << "The countdown lasted for " << value2 << " seconds.\n";
  th2.join();

  return 0;
}
