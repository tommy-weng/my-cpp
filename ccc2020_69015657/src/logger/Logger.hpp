#pragma once

#include <iostream>
#include <fstream>

using namespace std;

enum LogLevel
{
  DBG,
  INF,
  WRN,
  ERR,
  VIP
};

class Logger
{
public:
  Logger(std::ofstream& outstream, const char* logName = nullptr);
  ~Logger();

  inline void setLogLevel(LogLevel loglevel)
  {
    level = loglevel;
  }

  Logger& dbg();
  Logger& err();
  Logger& vip();

  template <typename T>
  Logger& operator << (T var);
  Logger& operator << (ostream& (*pf)(ostream&));
  Logger& operator << (const char* str);
private:
  LogLevel level;
  std::ofstream& out;
  char* log;
};

extern LogLevel logLevelConfig;

template <typename T>
Logger& Logger::operator << (T var)
{
  if (level >= logLevelConfig)
    out << var;
  return *this;
}

extern Logger lg;
