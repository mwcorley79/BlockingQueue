#ifndef CPP11_BLOCKINGQUEUE_H
#define CPP11_BLOCKINGQUEUE_H
///////////////////////////////////////////////////////////////
// Cpp11-BlockingQueue.h - Thread-safe Blocking Queue        //
// ver 1.3                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2015 //
///////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one thread-safe class: BlockingQueue<T>.
 * Its purpose is to support sending messages between threads.
 * It is implemented using C++11 threading constructs including 
 * std::condition_variable and std::mutex.  The underlying storage
 * is provided by the non-thread-safe std::queue<T>.
 *
 * Required Files:
 * ---------------
 * Cpp11-BlockingQueue.h
 *
 * 
 * Build Process:
 * --------------
 * Windows (Visual Studio): devenv Cpp11-BlockingQueue.sln /rebuild debug
 * Linux (gnu C++): g++ -o BlockingQueueTest -DTEST_BLOCKING_QUEUE Cpp11-BlockingQueue.cpp -lpthread
 *
 * Run Command:
 * -----------
 * Linux ./BlockingQueueTest
 *  
 *
 * Maintenance History:
 * --------------------
 * ver 1.3 : 04 Mar 2016
 * - changed behavior of front() to throw exception
 *   on empty queue.
 * - added comment about std::unique_lock in deQ()
 * ver 1.2 : 27 Feb 2016
 * - added front();
 * - added move ctor and move assignment
 * - deleted copy ctor and copy assignment
 * ver 1.1 : 26 Jan 2015
 * - added copy constructor and assignment operator
 * ver 1.0 : 03 Mar 2014
 * - first release
 *
 */

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

template <typename T>
class BlockingQueue {
public:
  BlockingQueue() {}
  BlockingQueue(BlockingQueue<T>&& bq);
  BlockingQueue<T>& operator=(BlockingQueue<T>&& bq);
  BlockingQueue(const BlockingQueue<T>&) = delete;
  BlockingQueue<T>& operator=(const BlockingQueue<T>&) = delete;
  T deQ();
  void enQ(const T& t);
  T& front();
  void clear();
  size_t size();
private:
  std::queue<T> q_;
  std::mutex mtx_;
  std::condition_variable cv_;
};


#endif
