#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

/**
 * @brief The Debug class is where debug functions are defined.
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

        int expanded[] = { (std::cout << args << "", 0)... };
        (void)expanded;

        std::cout << std::endl;
    }

    template<typename... Ts>
    static void logerr(Ts const&... args)
    {
        std::cout << "Debug::logerr: ";

        int expanded[] = { (std::cout << args, 0)... };
        (void)expanded;

        std::cout << std::endl;
    }
};
#endif // DEBUG_H
