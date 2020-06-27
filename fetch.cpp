#include <iostream>
#include <iomanip>
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
  string username = execute("whoami");
  string hostname = execute("hostname");
  string dist     = execute("( lsb_release -ds || cat /etc/*release || uname -om ) 2>/dev/null | head -n1 | tr -d '\"'");
  string kernel   = execute("uname -r");
  string cpu      = execute("lscpu | sed -nr '/Model name/ s/.*:\\s*(.*) @ .*/\\1/p'");
  string arch     = execute("uname -m");
  string uptime   = execute("uptime -p");
  string memory   = execute("free -m  | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3") + "M/" + execute("free -m  | grep ^Mem | tr -s ' ' | cut -d ' ' -f 2") + "M";

  cout << username << printRed("@")                          << hostname << endl;
  cout << setw(16) << left << printRed("dist", true)         << dist     << endl;
  cout << setw(16) << left << printRed("kernel", true)       << kernel   << endl;
  cout << setw(16) << left << printRed("cpu", true)          << cpu      << endl;
  cout << setw(16) << left << printRed("arch", true)         << arch     << endl;
  cout << setw(16) << left << printRed("uptime", true)       << uptime   << endl;
  cout << setw(16) << left << printRed("memory", true)       << memory   << endl;
  return 0;
}
