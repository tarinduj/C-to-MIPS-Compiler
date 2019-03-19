#ifndef LOGGER_MACROS_HPP
#define LOGGER_MACROS_HPP

#include <iostream>

#define LOG std::clog << "[LOG][" __FILE__ << ":" << __LINE__ << "] "
#define MSG std::clog << "[MSG][" __FILE__ << ":" << __LINE__ << "] "
#define ERR std::clog << "[ERR][" __FILE__ << ":" << __LINE__ << "] "

#endif