#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "linux_parser.h"
#include <numeric>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  const std::vector<int> cpu_times1 = LinuxParser::CpuUtilization();
   int idle_time1 = cpu_times1[3];
   int total_time1 = std::accumulate(cpu_times1.begin(), cpu_times1.end(), 0);
  sleep(1);
  const std::vector<int> cpu_times2 = LinuxParser::CpuUtilization();
  int idle_time2 = cpu_times2[3];
   int total_time2 = std::accumulate(cpu_times2.begin(), cpu_times2.end(), 0);
  const float idle_time_delta = (float)idle_time2 - (float)idle_time1;
  const float total_time_delta = (float)total_time2 - (float)total_time1;
  return (1.0 - idle_time_delta / total_time_delta);
}

