#pragma once
#include "utils.hpp"
#if defined(__x86_64__) || defined(__amd64__) || defined(_M_AMD64) ||          \
    defined(__i386__)
#include <cpuid.h>
#endif
#include <iostream>
#include <regex>
#include <sys/utsname.h>
using namespace std;

string get_cpu() {
#if defined(__x86_64__) || defined(__amd64__) || defined(_M_AMD64) ||          \
    defined(__i386__)
  char CPUBrandString[0x40];
  unsigned int CPUInfo[4] = {0, 0, 0, 0};

  __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
  unsigned int nExIds = CPUInfo[0];

  memset(CPUBrandString, 0, sizeof(CPUBrandString));

  for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
    __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

    if (i == 0x80000002)
      memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000003)
      memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000004)
      memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
  }
  regex eliminate_whitespace("\\s{2,}");
  return regex_replace(CPUBrandString, eliminate_whitespace, "");
#elif defined(__aarch64__) || defined(__arm__)
  string data = search("/proc/cpuinfo", "model name");
  regex regexp("[mM]odel\\sname\\s+:\\s+");
  // Android fallback
  if (data == "") {
    data = search("/proc/cpuinfo", "Hardware");
    regexp = regex("Hardware\\s+:\\s+");
  }
  return regex_replace(data, regexp, "");
#endif
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
  int total_mem = stoi(regex_replace(total_mem_raw, regexp, ""));
  int sh_mem = stoi(regex_replace(sh_mem_raw, regexp, ""));
  int mem_free = stoi(regex_replace(mem_free_raw, regexp, ""));
  int buffers = stoi(regex_replace(buffers_raw, regexp, ""));
  int cached = stoi(regex_replace(cached_raw, regexp, ""));
  int sreclaimable = stoi(regex_replace(sreclaimable_raw, regexp, ""));

  // Source: https://github.com/KittyKatt/screenFetch/issues/386
  int used_mem =
      total_mem + sh_mem - mem_free - buffers - cached - sreclaimable;
  return to_string(used_mem / 1024) + "M/" + to_string(total_mem / 1024) + "M";
}

string get_host() {
  struct utsname sys_data;
  uname(&sys_data);
  return sys_data.nodename;
}

string get_kernel() {
  struct utsname sys_data;
  uname(&sys_data);
  return sys_data.release;
}

string get_arch() {
  struct utsname sys_data;
  uname(&sys_data);
  return sys_data.machine;
}
