#include <unistd.h>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"


using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process (int i):Pid_(i){
/*CpuUtilization_=CpuUtilization()
Command_=LinuxParser::Command(Pid_);*/
}
 
// Done by me: Return this process's ID
int Process::Pid () { 
  return Pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  std::ifstream file{ LinuxParser::kProcDirectory+ std::to_string(Pid_) + LinuxParser::kStatFilename};
  string line,utime;
  getline(file,line);
  std::istringstream linestream(line);
  float utime_f,stime,cutime,cstime,starttime,Hertz;
 
   for (int i=0;i<14;i++){
   linestream>>utime;
     } 
  linestream>>stime>>cutime>>cstime; //gives values until #17
  linestream>>starttime>>starttime>>starttime>>starttime>>starttime; 
  Hertz=sysconf(_SC_CLK_TCK);
  utime_f=std::stof(utime);
    return (utime_f+stime+cutime+cstime)/Hertz/(LinuxParser::UpTime()-starttime/Hertz); 
}

// Done by me: Return the command that generated this process
string Process::Command() { 
  return LinuxParser::Command(Pid_); }

// Done by me: Return this process's memory utilization
string Process::Ram() { 
  return LinuxParser::Ram(Pid_); }

// Done by me: Return the user (name) that generated this process
string Process::User() { 
  return LinuxParser::User(Pid_); }

// Done by me: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return LinuxParser::UpTime(Pid_); 
}

// Done by me: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return a.CpuUtilization()< CpuUtilization(); 
}