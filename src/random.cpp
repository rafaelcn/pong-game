#include "random.hpp"

Random::Random()
{
}

Random::~Random()
{
}


float Random::get_real(float a, float b)
{
    std::mt19937 generator(m_random_device());
    std::uniform_real_distribution<float> distribution(a, b);

    return distribution(generator);
}

int Random::get_int(float a, float b)
{
    std::mt19937 generator(m_random_device());
    std::uniform_int_distribution<> distribution(a, b);

    return distribution(generator);
}
