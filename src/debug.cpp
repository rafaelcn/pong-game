#include "debug.hpp"

#include <iostream>
#include <fstream>

static bool logf(const std::string& filename, const std::string& message)
{
    std::ofstream file(filename);

    file << "PongGame log file" << std::endl;

    file << message;

    file.close();

    return true; //wrote to the file successfully!
}
