#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "vortex/core/Shader.h"
#include "vortex/resources/Texture.h"
#include "vortex/utilities/Color.h"

namespace vortex {
    class RenderingServer {
        public:
            // note to self: this removes constructor
            RenderingServer() = delete;

            static void init(SDL_Window* window);
            static void dispose();

            static void clear();
            static void present();

            static void setViewportCoords(int x, int y, int w, int h);
            static void setClearColor(float r, float g, float b, float a);

            static glm::mat4 projection;
            static Shader* defaultShader;
            static unsigned int VAO;
        
        private:
            static Color* clearColor;
            static SDL_Window* window;
    };
}