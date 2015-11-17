/*
 * Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Random {
private:
    std::random_device m_random_device;
public:
    Random();
    ~Random();

    /**
     * @brief Returns a real number between "a" and "b".
     * @param a the start interval value.
     * @param b the final interval value
     * @return a random float between the interval "a" and "b".
     */
    float get_real(float a, float b);
    /**
     * @brief Returns an integer number between the interval 
     * "a" and "b".
     * @param a the start interval value.
     * @param b the final interval value
     * @return a random int between the interval "a" and "b"
     */
    int get_int(int a, int b);
};

#endif // RANDOM_HPP
