#include "util.hpp"

float min(float l, float r) { return l < r ? l : r; }
float max(float l, float r) { return l > r ? l : r; }
float random() { return (float)rand() / RAND_MAX; }

std::default_random_engine randomGenerator;