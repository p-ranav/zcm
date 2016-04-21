/*
 * Timer class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.21
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <set>
#include <cstdint>

class Timer
{
public:

  typedef uint64_t timer_id;
  typedef std::function<void()> handler_type;

  Timer()
    : nextId(1)
    , queue(comparator)
    , done(false)
  {
    ScopedLock lock(sync);
    worker = std::thread(std::bind(&Timer::threadStart, this));
  }

  ~Timer()
  {
    ScopedLock lock(sync);
    done = true;
    wakeUp.notify_all();
    lock.unlock();
    worker.join();
  }

  timer_id create(uint64_t msFromNow, uint64_t msPeriod,
				const std::function<void()> &handler)
  {
    return createImpl(Instance(0,
			       Clock::now() + Duration(msFromNow), Duration(msPeriod),
			       handler));
  }

  timer_id create(uint64_t msFromNow, uint64_t msPeriod,
				std::function<void()>&& handler)
  {
    return createImpl(Instance(0,
			       Clock::now() + Duration(msFromNow), Duration(msPeriod),
			       std::move(handler)));
  }

  bool destroy(timer_id id)
  {
    ScopedLock lock(sync);
    auto i = active.find(id);
    if (i == active.end())
      return false;
    else if (i->second.running)
      {
        // A callback is in progress for this Instance,
        // so flag it for deletion in the worker
        i->second.running = false;
      }
    else
      {
        queue.erase(std::ref(i->second));
        active.erase(i);
      }

    wakeUp.notify_all();
    return true;
  }


  bool exists(timer_id id)
  {
    ScopedLock lock(sync);
    return active.find(id) != active.end();
  }

  void threadStart()
  {
    ScopedLock lock(sync);

    while (!done)
      {
        if (queue.empty())
	  {
            // Wait (forever) for work
            wakeUp.wait(lock);
	  }
        else
	  {
            auto firstInstance = queue.begin();
            Instance& instance = *firstInstance;
            auto now = Clock::now();
            if (now >= instance.next)
	      {
                queue.erase(firstInstance);

                // Mark it as running to handle racing destroy
                instance.running = true;

                // Call the handler
                lock.unlock();
                instance.handler();
                lock.lock();

                if (done)
		  {
                    break;
		  }
                else if (!instance.running)
		  {
                    // Running was set to false, destroy was called
                    // for this Instance while the callback was in progress
                    // (this thread was not holding the lock during the callback)
                    active.erase(instance.id);
		  }
                else
		  {
                    instance.running = false;

                    // If it is periodic, schedule a new one
                    if (instance.period.count() > 0)
		      {
                        instance.next = instance.next + instance.period;
                        queue.insert(instance);
		      } else {
		      active.erase(instance.id);
                    }
		  }
	      } else {
	      // Wait until the timer is ready or a timer creation notifies
	      wakeUp.wait_until(lock, instance.next);
            }
	  }
      }
  }

private:
  std::mutex sync;
  typedef std::unique_lock<std::mutex> ScopedLock;

  std::condition_variable wakeUp;

  typedef std::chrono::steady_clock Clock;
  typedef std::chrono::time_point<Clock> Timestamp;
  typedef std::chrono::milliseconds Duration;

  struct Instance
  {
    Instance(timer_id id = 0)
      : id(id)
      , running(false)
    {
    }

    template<typename Tfunction>
    Instance(timer_id id, Timestamp next, Duration period, Tfunction&& handler) noexcept
      : id(id)
      , next(next)
      , period(period)
      , handler(std::forward<Tfunction>(handler))
      , running(false)
    {
    }

    Instance(Instance const& r) = delete;

    Instance(Instance&& r) noexcept
    : id(r.id)
      , next(r.next)
      , period(r.period)
      , handler(std::move(r.handler))
      , running(r.running)
    {
    }

    Instance& operator=(Instance const& r) = delete;

    Instance& operator=(Instance&& r)
    {
      if (this != &r)
	{
	  id = r.id;
	  next = r.next;
	  period = r.period;
	  handler = std::move(r.handler);
	  running = r.running;
	}
      return *this;
    }

    timer_id id;
    Timestamp next;
    Duration period;
    handler_type handler;
    bool running;
  };

  typedef std::unordered_map<timer_id, Instance> InstanceMap;
  timer_id nextId;
  InstanceMap active;

  // Comparison functor to sort the timer "queue" by Instance::next
  struct NextActiveComparator
  {
    bool operator()(const Instance &a, const Instance &b) const
    {
      return a.next < b.next;
    }
  };
  NextActiveComparator comparator;

  // Queue is a set of references to Instance objects, sorted by next
  typedef std::reference_wrapper<Instance> QueueValue;
  typedef std::multiset<QueueValue, NextActiveComparator> Queue;
  Queue queue;

  // Thread and exit flag
  std::thread worker;
  bool done;

  timer_id createImpl(Instance&& item)
  {
    ScopedLock lock(sync);
    item.id = nextId++;
    auto iter = active.emplace(item.id, std::move(item));
    queue.insert(iter.first->second);
    wakeUp.notify_all();
    return item.id;
  }

};

#endif // TIMER_HPP
