/**
 * Copyright 2014 Rafael Campos Nunes.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain a
 * copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

/**
 * @brief The Debug class is where debug functions are defined, using the power
 * of variadic templates it .
 */
class Debug {
public:
    /**
     * @brief log The default log, it prints args on the stdout.
     * @param args The arguments to be printed on the terminal.
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
     * @brief log_warn The warning log, it prints out args on the stdout
     * which should be taken with care.
     * @param args The arguments to be printed on the terminal.
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
     * @brief log_err The error log, use this to print really bad things that
     * happened with something.
     * @param args The arguments to be printed on the terminal.
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
