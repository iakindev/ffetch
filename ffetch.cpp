#include "ascii_art.hpp"
#include "get_functions.hpp"
#include "utils.hpp"
#include <iostream>
using namespace std;

int main() {
  string username = execute("whoami");
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

  // Initial ascii code, VERY unclean,
  // needs to be rewrited in more sane way
  for (int i = 0; i < (content_size > arch_linux.size() ? content_size
                                                        : arch_linux.size());
       i++) {
    cout << (arch_linux[i].size() == arch_linux[0].size()
                 ? arch_linux[i] + " "
                 : return_spaces(arch_linux[0].size() + 1))
         << content_arr[i] << endl;
  }

  return 0;
}
