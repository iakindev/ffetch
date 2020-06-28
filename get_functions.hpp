#pragma once
#include "utils.hpp"
#include <regex>
using namespace std;

string get_cpu() {
  string data = search("/proc/cpuinfo", "model name");
  regex regexp("[mM]odel\\sname\\s+:\\s+");
  // Android fallback
  if (data == "") {
    data = search("/proc/cpuinfo", "Hardware");
    regexp = regex("Hardware\\s+:\\s+");
  }
  return regex_replace(data, regexp, "");
}