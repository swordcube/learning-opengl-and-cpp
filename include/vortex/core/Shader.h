#pragma once

#include <stdio.h>
#include <glad/glad.h>

namespace vortex {
    class Shader {
        public:
            Shader(const char *fragmentSource, const char *vertexSource);
            ~Shader();

            void use();
            unsigned int getUniformLoc(const char* name);

            static Shader* loadFromFile(const char *fragmentPath, const char *vertexPath);
        private:
            static unsigned int program;
    };
}