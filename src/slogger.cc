extern "C" {
# include <syslog.h>
}

#include <slogger/slogger.hpp>

using namespace log;

unique_ptr<Sys_Logger> Sys_Logger::m_instance;

once_flag Sys_Logger::m_onceFlag;

Sys_Logger::Sys_Logger(string *name, int facility){
  openlog(name->c_str(), LOG_CONS | LOG_PID | LOG_NDELAY, facility);
}

void Sys_Logger::warning(string *text){
  syslog (LOG_WARNING, "%s",text->c_str());
}

void Sys_Logger::debug(string *text){
  syslog (LOG_DEBUG,"%s" ,text->c_str());
}

void Sys_Logger::notice(string *text){
  syslog (LOG_NOTICE, "%s", text->c_str());
}

void Sys_Logger::crit(string *text)
{
  syslog (LOG_CRIT, "%s",text->c_str());
}

void Sys_Logger::alert(string *text)
{
  syslog (LOG_ALERT, "%s",text->c_str());
}

void Sys_Logger::err(string *text)
{
  syslog (LOG_ERR, "%s", text->c_str());
}

void Sys_Logger::info(string *text)
{
  syslog (LOG_INFO, "%s",text->c_str());
}

Sys_Logger::~Sys_Logger()
{
  closelog();
}

Sys_Logger& Sys_Logger::GetInstance(string *name, int facility)
{
    std::call_once(m_onceFlag,
                   [=] { m_instance.reset(new Sys_Logger(name,facility)); });
    return *m_instance.get();
}
