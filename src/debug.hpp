/*
 * Game: Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

/**
 * @brief The Debug class is where debug functions are defined.
 */
class Debug {
public:
    /**
     * @brief log_file
     * @param filename
     * @param message
     * @return
     */
    static bool log_file(const std::string& filename,
                         const std::string& message);


    /**
     * @brief log
     * @param args
     */
    template<typename... Ts>
    static void log(const Ts&... args)
    {
        std::cout << "Debug::log: ";

        int expanded[] = { (std::cout << args << "", 0)... };
        (void)expanded;

        std::cout << std::endl;
    }

    /**
     * @brief log_warn
     * @param args
     */
    template<typename... Ts>
    static void log_warn(const Ts&... args)
    {
        std::cout << "Debug::log_warn: ";

        int expanded[] = { (std::cout << args, 0)... };
        (void)expanded;

        std::cout << std::endl;
    }

    /**
     * @brief log_err
     * @param args
     */
    template<typename... Ts>
    static void log_err(const Ts&... args)
    {
        std::cerr << "Debug::log_err: ";

        int expanded[] = { (std::cerr << args, 0)... };
        (void)expanded;

        std::cerr << std::endl;
    }
};
#endif // DEBUG_H
