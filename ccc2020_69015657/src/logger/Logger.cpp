#include "Logger.hpp"

LogLevel logLevelConfig = VIP;

const char* logName = "/tmp/ccc2020.log";

std::ofstream out;
Logger lg(out);

void openLog()
{
  out.open(logName, std::ios::app);
}

void closeLog()
{
  out.close();
}

Logger::Logger(std::ofstream& outstream, const char* log)
:level(DBG),
out(outstream)
{
  if (nullptr == log)
  {
    log = logName;
  }
  out.open(log, std::ios::app);
}
Logger::~Logger()
{
  out.close();
}
Logger& Logger::operator << (ostream& (*pf)(ostream&))
{
  if (level >= logLevelConfig)
    out << pf;
  return *this;
}

Logger& Logger::operator << (const char* str)
{
  if (level >= logLevelConfig)
    out << str;
  return *this;
}

static void printTime(Logger& log)
{
  time_t now = time(NULL);
  tm*  ltm = localtime(&now);
  log << "time=" << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << ",";
}

Logger& Logger::dbg()
{
  this->setLogLevel(DBG);
  printTime(*this);
  *this << "DBG,";
  return *this;
}

Logger& Logger::err()
{
  this->setLogLevel(ERR);
  printTime(*this);
  *this << "ERR,";
  return *this;
}

Logger& Logger::vip()
{
  this->setLogLevel(VIP);
  printTime(*this);
  *this << "VIP,";
  return *this;
}
