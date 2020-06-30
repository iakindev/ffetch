#include "get_functions.hpp"
#include "utils.hpp"
#include <iomanip>
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

  cout << username << printRed("@") << hostname << endl;
  cout << setw(16) << left << printRed("dist", true) << dist << endl;
  cout << setw(16) << left << printRed("kernel", true) << kernel << endl;
  cout << setw(16) << left << printRed("cpu", true) << cpu << endl;
  cout << setw(16) << left << printRed("arch", true) << arch << endl;
  cout << setw(16) << left << printRed("uptime", true) << uptime << endl;
  cout << setw(16) << left << printRed("memory", true) << memory << endl;
  return 0;
}
