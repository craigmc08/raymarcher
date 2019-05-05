// https://bunjevac.net/2019/02/14/parallelizing-raytracer-in-a-weekend.html
// This whole task class (as well as most of the code/method for multi-threading)
// come from this article. Made some modifications, but it is almost the
// same.

#ifndef TASK_H_
#define TASK_H_

#include <vector>
#include <mutex>

#include "Vector.hpp"

struct Task {
    int sx = -1, sy = -1;
    int my_id;
    static int id;

    static std::vector<int> pixels;
    static int tileSize;
    static int xTileCount;
    static int yTileCount;
    static int width;
    static int height;

    static int takenCount;

    static int threadsCompleted;

    Task();
    Task(int x, int y);

    bool get_next_task();

    void operator()();

    static void setSceneSettings(int _tileSize, int _width, int _height, std::vector<int> _pixels);
};

#endif // TASK_H_