#ifndef __SLOGGER_HPP__
#define __SLOGGER_HPP__

#include <string>
#include <memory>
#include <mutex>

using namespace std;

namespace log{

  class Sys_Logger{
  public:
    virtual ~Sys_Logger();
    static Sys_Logger& GetInstance(string *name, int facility);

    void info(string *text);
    void err(string *text);
    void alert(string *text);
    void crit(string *text);
    void warning(string *text);
    void notice(string *text);
    void debug(string *text);

  private:
    static unique_ptr<Sys_Logger> m_instance;
    static once_flag m_onceFlag;
    Sys_Logger(string *name, int facility);
    Sys_Logger(const Sys_Logger& src) = delete;
    Sys_Logger& operator=(const Sys_Logger& rhs) = delete;

  private:
    mutex mu_safe;
  };

}

#endif
