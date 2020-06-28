#pragma once
#include <fstream>
#include <iostream>
using namespace std;

string search(string file_path, string search_for) {
  string line;
  bool found = false;

  ifstream file;
  file.open(file_path);
  if (file.is_open()) {
    unsigned int line_num = 0;
    while (getline(file, line) && !found) {
      line_num++;
      if (line.find(search_for, 0) != string::npos) {
        found = true;
        file.close();
        break;
      }
    }
    if (file.is_open())
      file.close();
  }
  return line;
}

string execute(const string &mStr) {
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