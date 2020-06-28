#pragma once
#include "utils.hpp"
#include <iostream>
#include <regex>
using namespace std;

string get_cpu() {
  string data = search("/proc/cpuinfo", "model name");
  regex regexp("[mM]odel\\sname\\s+:\\s+");
  // Android fallback
  if (data == "") {
    cout << "hai";
    data = search("/proc/cpuinfo", "Hardware");
    regex regexp("Hardware\\s+:\\s+");
  }
  return regex_replace(data, regexp, "");
}