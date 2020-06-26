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
  cout << execute("whoami") << "@" << execute("hostname") << endl;
  cout << "kernel " << execute("uname -r") << endl;
  cout << "cpu "
       << execute("lscpu | sed -nr '/Model name/ s/.*:\\s*(.*) @ .*/\\1/p'")
       << endl;
  cout << "architecture " << execute("uname -m") << endl;
  cout << "uptime " << execute("uptime -p") << endl;
  return 0;
}
