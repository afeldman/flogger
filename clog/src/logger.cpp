/******************************************************************************
 * Include Files
 *******************************************************************************/
#ifdef _DEBUG
#include <cassert>
#endif

#include <stdarg.h>
#include <sys/time.h>

#include <clogg/logger.hpp>

#define DEBUGCOLOR "\033[00;32m"/*Debug Color green*/
#define ERRORCOLOR  "\033[00;31m"/*ERROR Color red*/
#define INFOCOLOR  "\033[00;34m"/*INFO Color blue*/
#define RESETCOLOR "\033[00m" /*RESET*/

/* static Logger */
Logger* Logger::g_logger = 0;

Logger&
Logger::getLogger(bool with_terminal){
  if(!g_logger) {
    g_logger = new Logger(with_terminal);
  }
  return *g_logger;
};


Logger::Logger(bool with_terminal)
    :p_outputFile(NULL),
     fileName("") {
  this->terminalMSG = with_terminal;
};

Logger::~Logger() {
  this->closeFile();
};

bool
Logger::setLogFile(const std::string& logfilename) {
  this->closeFile();
  
#ifdef _DEBUG
  assert(p_outputFile);
#endif
  
  if (not logfilename.empty()) {
    this->p_outputFile = fopen(logfilename.c_str(), "a");
    if (p_outputFile) {
      this->fileName = logfilename;
    } else {
      return false;
    }
  }
  
  return true;
};

void
Logger::closeFile()
{
#ifdef _DEBUG
  assert(this->p_outputFile);
#endif
  if (this->p_outputFile){
    fclose( this->p_outputFile );
    this->p_outputFile   = NULL;
    this->fileName = "";
  }
};

void
Logger::writeDBG(const char* m_format, ...){
  va_list args;
  va_start(args, m_format);
  
  if (terminalMSG) {
    printf(DEBUGCOLOR "\nDEBUG: ");
    vprintf(m_format, args);
    printf(RESETCOLOR);
    fflush(stdout);
  } else {
#ifdef _DEBUG
    assert(this->p_outputFile);
#endif
    if (p_outputFile) {
      char buffer_m[2048];
      time_t currentTime = time (NULL);
      timeval tv;
      
      gettimeofday(&tv,NULL);
      strftime(buffer_m, 2048, "%Y/%m/%d %T:", localtime(&currentTime));
      
      fprintf(this->p_outputFile, "\n%s.%06d: DEBUG: ", buffer_m, (int32_t) tv.tv_sec);
      vfprintf(this->p_outputFile, m_format, args);
    }
  }
  va_end(args);
};

void
Logger::writeIFO(const char* m_format, ...){
  va_list args;
  va_start(args, m_format);
  
  if (terminalMSG) {
    printf(INFOCOLOR "\nINFO: ");
    vprintf(m_format, args);
    printf(RESETCOLOR);
    fflush(stdout);
  } else {
#ifdef _DEBUG
    assert(this->p_outputFile);
#endif
    if (p_outputFile) {
      char buffer_m[2048];
      time_t currentTime = time (NULL);
      timeval tv;
      
      gettimeofday(&tv,NULL);
      strftime(buffer_m, 2048, "%Y/%m/%d %T:", localtime(&currentTime));
      
      fprintf(this->p_outputFile, "\n%s.%06d: INFO: ", buffer_m, (int32_t) tv.tv_sec);
      vfprintf(this->p_outputFile, m_format, args);
    }
  }
  va_end(args);
  
};

void
Logger::writeERR(const char* m_format, ...){
  va_list args;
  va_start(args, m_format);

  if (terminalMSG) {
    printf(ERRORCOLOR "\nERROR: ");
    vprintf(m_format, args);
    printf(RESETCOLOR);
    fflush(stdout);
  } else {
#ifdef _DEBUG
    assert(this->p_outputFile);
#endif
    if (p_outputFile) {
      char buffer_m[2048];
      time_t currentTime = time (NULL);
      timeval tv;

      gettimeofday(&tv,NULL);
      strftime(buffer_m, 2048, "%Y/%m/%d %T:", localtime(&currentTime));

      fprintf(this->p_outputFile, "\n%s.%06d: ERROR: ", buffer_m, (int32_t) tv.tv_sec);
      vfprintf(this->p_outputFile, m_format, args);
    }
  }
  va_end(args);
};
