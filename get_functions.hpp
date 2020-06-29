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

string get_dist() {
  string data = search("/etc/os-release", "PRETTY_NAME");
  regex regexpquo("\"");
  data = regex_replace(data, regexpquo, "");
  regex regexp("PRETTY_NAME=");
  if (data == "") {
    return execute("uname -om");
  }
  return regex_replace(data, regexp, "");
}

// Not so efficient
string get_mem() {
  string total_mem_raw = search("/proc/meminfo", "MemTotal:");
  string sh_mem_raw = search("/proc/meminfo", "Shmem:");
  string mem_free_raw = search("/proc/meminfo", "MemFree:");
  string buffers_raw = search("/proc/meminfo", "Buffers:");
  string cached_raw = search("/proc/meminfo", "Cached:");
  string sreclaimable_raw = search("/proc/meminfo", "SReclaimable:");

  regex regexp("(\\D+)");
  int total_mem = stoi(regex_replace(total_mem_raw, regexp, "")) / 1024;
  int sh_mem = stoi(regex_replace(sh_mem_raw, regexp, "")) / 1024;
  int mem_free = stoi(regex_replace(mem_free_raw, regexp, "")) / 1024;
  int buffers = stoi(regex_replace(buffers_raw, regexp, "")) / 1024;
  int cached = stoi(regex_replace(cached_raw, regexp, "")) / 1024;
  int sreclaimable = stoi(regex_replace(sreclaimable_raw, regexp, "")) / 1024;

  // Source: https://github.com/KittyKatt/screenFetch/issues/386
  int used_mem =
      total_mem + sh_mem - mem_free - buffers - cached - sreclaimable;
  return to_string(used_mem) + "M/" + to_string(total_mem) + "M";
}
