#ifndef PROCESS_H
#define PROCESS_H
#include "linux_parser.h"
#include <fstream>
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process (int);
  int Pid ();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int Pid_;
 /* std::string User_;
  std::string Command_;
  float CpuUtilization_;
  srd::string Ram_;
  long int UpTime_;*/
};

#endif