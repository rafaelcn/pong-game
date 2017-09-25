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

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

/**
 * @brief The Random class is responsible to abstract methods in which the
 * programmer will use to obtain random numbers.
 */
class Random {
private:
    Random() {}
    ///
    static std::random_device m_random_device;
public:
    ~Random() {}

    /**
     * @brief Returns a real number between "a" and "b".
     * @param a the start interval value.
     * @param b the final interval value
     * @return a random float between the interval "a" and "b".
     */
    static float get_real(float a, float b);
    /**
     * @brief Returns an integer number between the interval
     * "a" and "b".
     * @param a the start interval value.
     * @param b the final interval value
     * @return a random int between the interval "a" and "b"
     */
    static int get_int(int a, int b);
};

#endif // RANDOM_HPP
