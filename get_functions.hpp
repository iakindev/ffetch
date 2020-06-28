#pragma once
#include "utils.hpp"
#include <regex>
using namespace std;

string get_cpu() {
  string data = search("/proc/cpuinfo", "model name");
  regex regexp("[mM]odel\\sname\\s+:\\s+");
  return regex_replace(data, regexp, "");
}