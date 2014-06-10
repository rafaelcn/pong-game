#include "debug.hpp"

#include <iostream>
#include <fstream>

bool logw(const std::string& filename, const std::string& message)
{
    std::ofstream file(filename);

    file << "--------- LOG ----------" << std::endl;

    file << message;

    file.close();

    return true; //wrote to the file successfully!
}
