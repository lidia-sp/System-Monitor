#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "linux_parser.h"

#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  //bool get_cpu_times(int &, int &);

  // TODO: Declare any necessary private members
 private:
};

#endif