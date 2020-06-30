#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include "Cpp11-BlockingQueue.h"

//----< move constructor >---------------------------------------------

template<typename T>
BlockingQueue<T>::BlockingQueue(BlockingQueue<T>&& bq) // need to lock so can't initialize
{
  std::lock_guard<std::mutex> l(mtx_);
  q_ = bq.q_;
  while (bq.q_.size() > 0)  // clear bq
    bq.q_.pop();
  /* can't copy  or move mutex or condition variable, so use default members */
}
//----< move assignment >----------------------------------------------

template<typename T>
BlockingQueue<T>& BlockingQueue<T>::operator=(BlockingQueue<T>&& bq)
{
  if (this == &bq) return *this;
  std::lock_guard<std::mutex> l(mtx_);
  q_ = bq.q_;
  while (bq.q_.size() > 0)  // clear bq
    bq.q_.pop();
  /* can't move assign mutex or condition variable so use target's */
  return *this;
}
//----< remove element from front of queue >---------------------------

template<typename T>
T BlockingQueue<T>::deQ()
{
  std::unique_lock<std::mutex> l(mtx_);
  /* 
     This lock type is required for use with condition variables.
     The operating system needs to lock and unlock the mutex:
     - when wait is called, below, the OS suspends waiting thread
       and releases lock.
     - when notify is called in enQ() the OS relocks the mutex, 
       resumes the waiting thread and sets the condition variable to
       signaled state.
     std::lock_quard does not have public lock and unlock functions.
   */
  if(q_.size() > 0)
  {
    T temp = q_.front();
    q_.pop();
    return temp;
  }
  // may have spurious returns so loop on !condition

  while (q_.size() == 0)
    cv_.wait(l, [this] () { return q_.size() > 0; });
  T temp = q_.front();
  q_.pop();
  return temp;
}
//----< push element onto back of queue >------------------------------

template<typename T>
void BlockingQueue<T>::enQ(const T& t)
{
  {
    std::unique_lock<std::mutex> l(mtx_);
    q_.push(t);
  }
  cv_.notify_one();
}
//----< peek at next item to be popped >-------------------------------

template <typename T>
T& BlockingQueue<T>::front()
{
  std::lock_guard<std::mutex> l(mtx_);
  if(q_.size() > 0)
    return q_.front();
  throw std::exception();
}
//----< remove all elements from queue >-------------------------------

template <typename T>
void BlockingQueue<T>::clear()
{
  std::lock_guard<std::mutex> l(mtx_);
  while (q_.size() > 0)
    q_.pop();
}
//----< return number of elements in queue >---------------------------

template<typename T>
size_t BlockingQueue<T>::size()
{
  std::lock_guard<std::mutex> l(mtx_);
  return q_.size();
}



#ifdef TEST_BLOCKING_QUEUE

std::mutex ioLock;

void test(BlockingQueue<std::string>* pQ)
{
  std::string msg;
  do
  {
    msg = pQ->deQ();
    {
      std::lock_guard<std::mutex> l(ioLock);
      std::cout << "\n  thread deQed " << msg.c_str();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while(msg != "quit");
}

int main()
{
  std::cout << "\n  Demonstrating C++11 Blocking Queue";
  std::cout << "\n ====================================";

  BlockingQueue<std::string> q;
  std::thread t(test, &q);

  for(int i=0; i<15; ++i)
  {
    std::ostringstream temp;
    temp << i;
    std::string msg = std::string("msg#") + temp.str();
    {
      std::lock_guard<std::mutex> l(ioLock);
      std::cout << "\n   main enQing " << msg.c_str();
    }
    q.enQ(msg);
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
  }
  q.enQ("quit");
  t.join();

  std::cout << "\n";
  std::cout << "\n  Making move copy of BlockingQueue";
  std::cout << "\n -----------------------------------";

  std::string msg = "test";
  q.enQ(msg);
  std::cout << "\n  before move:";
  std::cout << "\n    q.size() = " << q.size();
  std::cout << "\n    q.front() = " << q.front();
  BlockingQueue<std::string> q2 = std::move(q);  // move assignment
  std::cout << "\n  after move:";
  std::cout << "\n    q2.size() = " << q2.size();
  std::cout << "\n    q.size() = " << q.size();
  std::cout << "\n    q2 element = " << q2.deQ() << "\n";

  std::cout << "\n  Move assigning state of BlockingQueue";
  std::cout << "\n ---------------------------------------";
  BlockingQueue<std::string> q3;
  q.enQ("test");
  std::cout << "\n  before move:";
  std::cout << "\n    q.size() = " << q.size();
  std::cout << "\n    q.front() = " << q.front();
  q3 = std::move(q);
  std::cout << "\n  after move:";
  std::cout << "\n    q.size() = " << q.size();
  std::cout << "\n    q3.size() = " << q3.size();
  std::cout << "\n    q3 element = " << q3.deQ() << "\n";

  std::cout << "\n\n";
}

#endif
