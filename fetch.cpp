#include <iostream>
using namespace std;

string execute(const string & mStr) {
  string result, file;
  FILE *pipe{popen(mStr.c_str(), "r")};
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    file = buffer;
    result += file.substr(0, file.size() - 1);
  }

  pclose(pipe);
  return result;
}

int main() {
  cout << execute("whoami") << "\033[31m@\033[0m" << execute("hostname") << endl;
  cout << "\033[31mkernel\033[0m " << execute("uname -r") << endl;
  cout << "\033[31mcpu\033[0m "
       << execute("lscpu | sed -nr '/Model name/ s/.*:\\s*(.*) @ .*/\\1/p'")
       << endl;
  cout << "\033[31marchitecture\033[0m " << execute("uname -m") << endl;
  cout << "\033[31muptime\033[0m " << execute("uptime -p") << endl;
  return 0;
}
