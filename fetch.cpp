#include "get_functions.hpp"
#include "utils.hpp"

#include <iomanip>
#include <iostream>
#include <regex>
using namespace std;

int main() {
  string username = execute("whoami");
  string hostname = execute("hostname");
  string dist = get_dist();
  string kernel = execute("uname -r");
  string cpu = get_cpu();
  string arch = execute("uname -m");
  string uptime = execute("uptime -p");
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
