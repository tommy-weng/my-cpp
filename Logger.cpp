#include <iostream>

using namespace std;

class Logger
{
public:
  Logger(bool flag, ostream& outstream):isOpen(flag), out(outstream){};
  template <typename T>
  Logger& operator << (T var);
  Logger& operator << (ostream& (*pf)(ostream&));
  Logger& operator << (const char* str);
private:
  bool isOpen;
  ostream& out;
};

template <typename T>
Logger& Logger::operator << (T var)
{
  if (isOpen)
    out << var;
  return *this;
}
  
Logger& Logger::operator << (ostream& (*pf)(ostream&))
{
  if (isOpen)
    out << pf;
  return *this;
}

Logger& Logger::operator << (const char* str)
{
  if (isOpen)
    out << str << "string";
  return *this;
}

int main()
{
  Logger lg(true, cout);
  
  lg << "hell" <<  1 << endl;
  return 1;
}
