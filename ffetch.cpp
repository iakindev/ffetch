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

  // Initial ascii code, VERY unclean,
  // needs to be rewrited in more sane way
  int count_to =
      content_size > arch_linux.size() ? content_size : arch_linux.size();
  // figure out whic os's art will be used here
  vector<string> ascii_art = arch_linux;
  for (int i = 0; i < count_to; i++) {
    cout << (ascii_art[i].size() == ascii_art[0].size()
                 ? ascii_art[i] + " "
                 : return_spaces(ascii_art[0].size() + 1))
         << content_arr[i] << endl;
  }
  return 0;
}
