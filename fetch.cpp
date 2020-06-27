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

string printRed(string text, bool space = false) {
  return "\033[31m" + text + "\033[0m" + (space == true ? " " : "");
}

int main() {
  cout << execute("whoami") << printRed("@") << execute("hostname") << endl;
  cout << printRed("kernel", true) << execute("uname -r") << endl;
  cout << printRed("cpu", true)
       << execute("lscpu | sed -nr '/Model name/ s/.*:\\s*(.*) @ .*/\\1/p'")
       << endl;
  cout << printRed("architecture", true) << execute("uname -m") << endl;
  cout << printRed("uptime", true) << execute("uptime -p") << endl;
  return 0;
}
