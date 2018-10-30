#ifndef EXITPENDING_H
#define EXITPENDING_H

// STL
#include <set>
#include <list>
#include <string>

// PDTK
#include <object.h>
#include <specialized/TimerEvent.h>


// helpers
template<typename T> constexpr microseconds_t seconds(T count) { return 1000000 * count; }


class EventPending : public Object
{
public:
  EventPending(void) noexcept;
  virtual ~EventPending(void) noexcept = default;

  bool setTimeout(microseconds_t timeout) noexcept;

  signal<> event_timeout;
  signal<> event_trigger;
protected:
  virtual bool activateTrigger(void) noexcept = 0;
private:
  void timerExpired(void) noexcept;
  TimerEvent m_timer;
  microseconds_t m_timeout_count;
  microseconds_t m_max_timeout_count;
};


class ExitPending : public EventPending
{
public:
  ExitPending (void) noexcept = default;
  ~ExitPending(void) noexcept = default;

  void setPids(const std::list<std::pair<pid_t, pid_t>>& pids) noexcept
    { m_services.clear(); m_pids = pids; }

  void setServices(const std::list<std::string>& services) noexcept
    { m_pids.clear(); m_services = services; }

private:
  bool activateTrigger(void) noexcept;
  std::list<std::pair<pid_t, pid_t>> m_pids;
  std::list<std::string> m_services;
};


class StartPending : public EventPending
{
public:
  StartPending (void) noexcept = default;
  ~StartPending(void) noexcept = default;

  void setServices(const std::list<std::string>& services) noexcept
    { m_services = services; }

private:
  bool activateTrigger(void) noexcept;
  std::list<std::string> m_services;
};



#endif // EXITPENDING_H