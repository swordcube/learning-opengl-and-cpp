#include "vortex/core/Engine.h"
#include "vortex/utilities/Tools.h"

using namespace vortex;

namespace vortex {
    Scene* Engine::currentScene;

    void Engine::init(Scene* initialScene) {
        // Initialize SDL :3
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *window = SDL_CreateWindow("Goodbye Atmosphere", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VORTEX_WINDOW_WIDTH, VORTEX_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

        int initialWindowWidth;
        int initialWindowHeight;
        SDL_GetWindowSize(window, &initialWindowWidth, &initialWindowHeight);

        AssetServer::init();
        RenderingServer::init(window);

        SDL_Event event;
        bool running = true;

        Uint64 curTime = SDL_GetPerformanceCounter();
        Uint64 lastTime = 0;
        double deltaTime = 0;

        currentScene = initialScene;
        currentScene->ready();

        while (running) {
            lastTime = curTime;
            curTime = SDL_GetPerformanceCounter();
            deltaTime = std::min((double)((curTime - lastTime) / (double)SDL_GetPerformanceFrequency()), 0.1);

            RenderingServer::clear();

            if(!Tools::isNull(currentScene)) {
                currentScene->update(deltaTime);
                currentScene->draw();
            }

            RenderingServer::present();

            while (SDL_PollEvent(&event) != 0) {
                switch (event.type) {
                    case SDL_WINDOWEVENT:
                        switch (event.window.event) {
                            case SDL_WINDOWEVENT_RESIZED:
                                {
                                double initialRatio = (double)initialWindowWidth / (double)initialWindowHeight;
                                double windowRatio = (double)event.window.data1 / (double)event.window.data2;

                                glm::vec4 coordSize = glm::vec4();
                                coordSize.w = (windowRatio > initialRatio) ? ((double)event.window.data2 * initialRatio) : (double)event.window.data1;
                                coordSize.z = (windowRatio < initialRatio) ? ((double)event.window.data1 / initialRatio) : (double)event.window.data2;
                                coordSize.x = ((double)event.window.data1 - coordSize.w) * 0.5;
                                coordSize.y = ((double)event.window.data2 - coordSize.z) * 0.5;

                                vortex::RenderingServer::setViewportCoords((int)coordSize.x, (int)coordSize.y, (int)coordSize.w, (int)coordSize.z);
                                }
                                break;

                            default:
                                break;
                        }
                        break;

                    case SDL_QUIT:
                        running = false;
                        break;

                    case SDL_KEYDOWN:
                        printf("THE KEY!!: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                        break;

                    default:
                        break;
                }
            }
        }
        
        vortex::RenderingServer::dispose();
        SDL_DestroyWindow(window);
    }

    Scene* Engine::getCurrentScene() {
        return currentScene;
    }

    void Engine::setCurrentScene(Scene* newScene) {
        if(!Tools::isNull(currentScene))
            delete currentScene;

        currentScene = newScene;
    }
}