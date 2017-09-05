/* **************************** File ********************************/
/**
 * Copyright (c) 2012 Anton Feldmann
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:#
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * \file logger.hpp
 *
 * \brief describes a Logger interface
 *
 * \author Anton Feldmann
 * \date   5. Sep 2012
 *
 */

#pragma once

#include <string>
#include <stdio.h>
#include <stdint.h>

/****************************************************************
 * Macro declaration
 ****************************************************************/
#define PRINTDBG(MSG ...)           \
  Logger::getLogger(false).writeDBG(MSG);

#define PRINTIFO(MSG ...)           \
  Logger::getLogger(false).writeIFO(MSG);

#define PRINTERR(MSG ...)             \
  Logger::getLogger(false).writeERR(MSG);

#define TPRINTDBG(MSG ...)            \
  Logger::getLogger(true).writeDBG(MSG);

#define TPRINTIFO(MSG ...)           \
  Logger::getLogger(true).writeIFO(MSG);

#define TPRINTERR(MSG ...)            \
  Logger::getLogger(true).writeERR(MSG);

/****************************************************************
 *    Class declaration
 ****************************************************************/
/************************* Class ********************************/
/**
 * \brief cpp representation for logging
 *
 * \author Anton Feldmann
 * \date 5. Sep 2012
 */
class Logger{
private:
  explicit Logger(bool);
  Logger(void);
  Logger(Logger&);
  Logger& operator=(Logger const &log);
  void closeFile();
  
public:
  virtual ~Logger(void);
  
  static Logger& getLogger(bool terminal = false);
  
  const std::string& getLogFile() const { return fileName; };
  bool setLogFile(const std::string&);
  
  void writeDBG(const char*, ...);
  void writeIFO(const char*, ...);
  void writeERR(const char*, ...);
  
 public:
  static Logger* g_logger;
  
 private:
  FILE* p_outputFile;
  std::string fileName;
  pthread_mutex_t lock;
  bool terminalMSG;
};
