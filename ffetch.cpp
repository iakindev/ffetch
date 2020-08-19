#include "ascii_art.hpp"
#include "get_functions.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
  string username = get_username();
  string hostname = get_host();
  string dist = get_dist();
  string kernel = get_kernel();
  string cpu = get_cpu();
  string arch = get_arch();
  string uptime = get_uptime();
  string memory = get_mem();

  string content_arr[7] = {
      username + printRed("@") + hostname, printRed("dist", true) + dist,
      printRed("kernel", true) + kernel,   printRed("cpu", true) + cpu,
      printRed("arch", true) + arch,       printRed("uptime", true) + uptime,
      printRed("memory", true) + memory};
  unsigned int content_size = sizeof(content_arr) / sizeof(content_arr[0]);

  vector<string> ascii_art;

  switch (str2int(dist.c_str())) {
  case str2int("Arch Linux"):
    ascii_art = arch_linux;
    break;
  default:
    ascii_art = {};
    break;
  }

  for (unsigned int i = 0; i < content_size; i++) {
    if (i < ascii_art.size()) {
      cout << ascii_art[i] + " " << content_arr[i] << endl;
    } else {
      cout << content_arr[i] << endl;
    }
  }

  return 0;
}
