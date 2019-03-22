#ifndef LOGGER_MACROS_HPP
#define LOGGER_MACROS_HPP

#include "rang.hpp"
#include <iostream>


#ifndef NOFILEANDLINE
#define FILEANDLINE << "[" __FILE__ << ":" << __func__ << ":" << __LINE__ << "] "
#else 
#define FILEANDLINE << " "
#endif


#define LOG                                                                    \
  std::clog << rang::style::bold << rang::style::dim << rang::fg::gray         \
            << "[LOG]" << rang::style::reset << rang::style::dim               \
            FILEANDLINE      \
            << rang::style::reset
#define MSG                                                                    \
  std::clog << rang::style::bold << rang::fgB::blue << "[MSG]"                 \
            << rang::style::reset << rang::style::dim \
            FILEANDLINE << rang::style::reset
#define ERR                                                                    \
  std::clog << rang::style::bold << rang::fgB::red << "[ERR]"                  \
            << rang::style::reset << rang::style::dim \
            FILEANDLINE << rang::style::reset

#define CONTEXTLOG                                             \
  std::clog << rang::style::bold << rang::style::dim << rang::fgB::magenta << "[CON]"                  \
            << rang::style::reset << rang::style::dim \
            FILEANDLINE << rang::style::reset



#endif