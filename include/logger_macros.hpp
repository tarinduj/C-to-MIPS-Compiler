#ifndef LOGGER_MACROS_HPP
#define LOGGER_MACROS_HPP

#include "rang.hpp"
#include <iostream>

#define LOG                                                                    \
  std::clog << rang::style::bold << rang::style::dim << rang::fg::gray         \
            << "[LOG]" << rang::style::reset << rang::style::dim               \
            << "[" __FILE__ << ":" << __func__ << ":" << __LINE__ << "] "      \
            << rang::style::reset
#define MSG                                                                    \
  std::clog << rang::style::bold << rang::fgB::blue << "[MSG]"                 \
            << rang::style::reset << rang::style::dim << "[" __FILE__ << ":"   \
            << __func__ << ":" << __LINE__ << "] " << rang::style::reset
#define ERR                                                                    \
  std::clog << rang::style::bold << rang::fgB::red << "[ERR]"                  \
            << rang::style::reset << rang::style::dim << "[" __FILE__ << ":"   \
            << __func__ << ":" << __LINE__ << "] " << rang::style::reset

#endif