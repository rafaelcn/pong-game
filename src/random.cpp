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

#include "random.hpp"

// Forward declaration to a static member.
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
