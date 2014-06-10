#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

bool logw(const std::string& filename, const std::string& message);

template<typename T>
void log(const T& message)
{
    std::cout << "LOG: " << message << std::endl;
}

template<typename T>
void logerr(const T& message)
{
    std::cout << "LOG_ERR: " << message << std::endl;
}

#endif // DEBUG_H
