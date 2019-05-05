#include "Task.hpp"

Task::Task() {
    my_id = id++;
}
Task::Task(int x, int y) {
    sx = x;
    sy = y;
    my_id = id++;
}

bool Task::get_next_task() {
    static std::mutex m;
        std::lock_guard<std::mutex> guard{m};

        int tileNumber = takenCount++;
        // All tiles are taken
        if (tileNumber > xTileCount * yTileCount) return false;

        sy = tileNumber / xTileCount;
        sx = tileNumber - sy * xTileCount; // Is this faster than remainder/mod method?
        return true;
}

void Task::operator()() {
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

void Task::setSceneSettings(int _tileSize, int _width, int _height, std::vector<int> _pixels) {
    tileSize = _tileSize;
    width = _width;
    height = _height;
    pixels = _pixels;
    xTileCount = width / tileSize + 1;
    yTileCount = height / tileSize + 1;
}

int Task::id = 0;
std::vector<int> Task::pixels{0};
int Task::tileSize = 1;
int Task::xTileCount = 1;
int Task::yTileCount = 1;
int Task::width = 1;
int Task::height = 1;
int Task::takenCount = 0;
int Task::threadsCompleted = 0;