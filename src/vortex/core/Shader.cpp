#include "vortex/core/Shader.h"
#include "vortex/core/FileSystem.h"
#include "vortex/servers/RenderingServer.h"
#include "glm/gtc/type_ptr.hpp"
#include <stdlib.h>

namespace vortex {
    unsigned int Shader::program;

    Shader::Shader(const char *fragmentSource, const char *vertexSource) {
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("Shader Vertex Compilation Failed :( - %s\n", infoLog);
        }

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("Shader Fragment Compilation Failed :( - %s\n", infoLog);
        }

        program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            printf("Shader Link Failed :( - %s\n", infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(program);
        glUniformMatrix4fv(getUniformLoc("PROJECTION"), 1, GL_FALSE, glm::value_ptr(vortex::RenderingServer::projection));
    }

    Shader::~Shader() {
        glDeleteProgram(program);
    }

    void Shader::use() {
        glUseProgram(program);
    }

    unsigned int Shader::getUniformLoc(const char* name) {
        return glGetUniformLocation(program, name);
    }

    Shader* Shader::loadFromFile(const char *fragmentPath, const char *vertexPath) {
        char *_fragment_source = FileSystem::getFileContents(fragmentPath);
        char *_vertex_source = FileSystem::getFileContents(vertexPath);

        Shader *_return_shader = new Shader(_fragment_source, _vertex_source);
        
        free(_fragment_source);
        free(_vertex_source);

        return _return_shader;   
    }
}