#include "random_gen.h"

static std::random_device rnd_device;
static std::mt19937 generator(rnd_device());

int randomIntFromRange(int min, int max)
{
    std::uniform_int_distribution<> range(min, max);

    return range(generator);
}

float randomFloatFromRange(float min, float max)
{
    std::uniform_real_distribution<> range(min, max);

    return (float)range(generator);
}

bool tryEvent(float probability)
{
    std::uniform_real_distribution<> range(0.0, 1.0);

    return ((float)range(generator)) <= probability;
}
