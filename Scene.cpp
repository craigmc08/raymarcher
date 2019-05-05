#include "Scene.hpp"

void Scene::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Scene::setSamples(int samples) {
    this->samples = samples;
}

void Scene::SetCamera(Camera* camera) {
    camera->setSceneSettings(width, height);
    this->camera = camera;
}
void Scene::SetSun(Vector direction, Vector color) {
    sunDirection = direction.normalized();
    sunColor = color;
}
void Scene::AddObject(SceneObject* object) {
    objects.push_back(object);
}

std::vector<int> Scene::Render() {
    std::vector<int> pixels(width * height * 3);

    const unsigned n_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads{n_threads};

    // 32 is magic render tile size. Should expose this as a setting
    Task::setSceneSettings(32, width, height, pixels);
    for (auto &t : threads) t = std::thread{Task()};

    while (Task::threadsCompleted != n_threads) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto &t : threads) t.join();

    return pixels;
}

void Scene::RenderToFile(const char* filename) {
    FILE* fp;
    if (fopen_s(&fp, filename, "wb") != 0) {
        printf("Failed to open file %s", filename);
    }

    // Write PPM file header
    fprintf(fp, "P6 %d %d 255\n", width, height);

    auto pixels = Render();

    // Write image pixels to file
    for (int i = 0; i < width * height * 3; i++) {
        fprintf(fp, "%c", pixels[i]);
    }

    fclose(fp);
}