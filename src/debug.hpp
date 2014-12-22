#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>


/**
 * @brief The Debug class
 */
class Debug {

public:
    /**
     * @brief logf
     * @param filename
     * @param message
     * @return
     */
    static bool logf(const std::string& filename, const std::string& message);


    template<typename... Ts>
    static void log(Ts const&... args)
    {
        std::cout << "Debug::log: ";

        int expanded[] = { (std::cout << args << std::endl, 0)... };
        (void)expanded;
    }

    template<typename... Ts>
    static void logerr(Ts const&... args)
    {
        std::cout << "Debug::logerr";

        int expanded[] = { (std::cout << args, 0)... };
        (void)expanded;
    }
private:
};
#endif // DEBUG_H
