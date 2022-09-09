#include <iostream>
#include <string>

using std::string;
using std::to_string;

class Logger {
 public:
  void log(const string& message) { printf("%s\n", message.c_str()); }
};

static Logger gLogger;
