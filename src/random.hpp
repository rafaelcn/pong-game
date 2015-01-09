#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random {
private:

public:
    Random();
    ~Random();

    // returns a float random number between an interval of a to b.
    static float get_rand_number(float a, float b);
};

#endif // RANDOM_HPP
