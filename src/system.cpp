#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Done by Lidia: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int> Pids=LinuxParser::Pids();
  processes_.clear();
  for (auto p:Pids){
    Process process(p);
    processes_.push_back(process);
}
  sort(processes_.begin(),processes_.end());
  return processes_;
}

// DONE by me: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  return LinuxParser::Kernel(); 
}

// Done by me: Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization(); }

// Done by me: Return the operating system name
std::string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem(); 
}

// Done by me: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  return LinuxParser::RunningProcesses(); 
}
// Done by me: Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses();
}

// Done by me: Return the number of seconds since the system started running
long int System::UpTime() { 
  return LinuxParser::UpTime(); 
}