#include "random.hpp"

std::random_device Random::m_random_device;

float Random::get_real(float a, float b)
{
    std::mt19937 generator(m_random_device());
    std::uniform_real_distribution<> distribution(a, b);

    return distribution(generator);
}

int Random::get_int(int a, int b)
{
    std::mt19937 generator(m_random_device());
    std::uniform_int_distribution<> distribution(a, b);

    return distribution(generator);
}
