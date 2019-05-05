#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <chrono>

class stopwatch {
private:
    std::chrono::high_resolution_clock::time_point start;
public:
    stopwatch()
        : start(std::chrono::high_resolution_clock::now())
    {}

    long long elapsed_millis() {
        auto finish = std::chrono::high_resolution_clock::now();
        auto micros = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);
        return micros.count();
    }
};

#endif // _STOPWATCH_H