#ifndef JOBCONTROLLER_H
#define JOBCONTROLLER_H

// STL
#include <list>

// PUT
#include <put/object.h>
#include <put/specialized/processevent.h>

class JobController : public Object
{
public:
  JobController (void) noexcept { }
  ~JobController(void) noexcept = default;

  void add(pid_t parent_pid, pid_t child_pid) noexcept;
  const std::list<std::pair<pid_t, pid_t>>& getPids(void) noexcept { return m_pids; }

  bool sendSignal(posix::Signal::EId signum) noexcept;

  signal<posix::error_t> exited; // exit signal with PID and process exit code
  signal<posix::Signal::EId> killed; // killed signal with PID and signal number
private:
  void remove(pid_t pid) noexcept;
  std::list<std::pair<pid_t, pid_t>> m_pids;
  std::list<ProcessEvent> m_procs;
};

#endif // JOBCONTROLLER_H
