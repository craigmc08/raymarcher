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

    Task() : my_id{id++} {}
    Task(int x, int y) : sx{x}, sy{y}, my_id{id++} {}

    bool get_next_task() {
        static std::mutex m;
        std::lock_guard<std::mutex> guard{m};

        int tileNumber = takenCount++;
        // All tiles are taken
        if (tileNumber > xTileCount * yTileCount) return false;

        sy = tileNumber / xTileCount;
        sx = tileNumber - sy * xTileCount; // Is this faster than remainder/mod method?
        return true;
    }

    void operator()() {
        bool done = false;
        int tasksCompleted = 0;
        do {
            if (!get_next_task()) {
                done = true;
                continue;
            }
            
            for(unsigned y = sy; y < sy + tileSize; y++) {
                if (y >= height) continue;
                for (unsigned x = sx; x < sx + tileSize; x++) {
                    if (x >= width) continue;
                    // Placeholder, need to get Trace() from scene
                    Vector luminance = Vector(1);
                    Vector color = luminance * 255;
                    int r = color.x > 255 ? 255 : (int)color.x;
                    int g = color.y > 255 ? 255 : (int)color.y;
                    int b = color.z > 255 ? 255 : (int)color.z;
                    int i = (y * width + x) * 3;
                    pixels[i] = r;
                    pixels[i+1] = g;
                    pixels[i+2] = b;
                }
            }
        } while (!done);

        threadsCompleted++;
    }

    static void setSceneSettings(int _tileSize, int _width, int _height, std::vector<int> _pixels) {
        tileSize = _tileSize;
        width = _width;
        height = _height;
        pixels = _pixels;
        xTileCount = width / tileSize + 1;
        yTileCount = height / tileSize + 1;
    }
};

#endif TASK_H_