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
     * @brief get_real returns a real number between "a" and "b"
     * @param a the
     * @param b
     * @return
     */
    float get_real(float a, float b);
    /**
     * @brief get_int
     * @param a
     * @param b
     * @return
     */
    int get_int(float a, float b);
};

#endif // RANDOM_HPP
