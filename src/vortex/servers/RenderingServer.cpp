#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vortex/core/Engine.h"
#include "vortex/core/Shader.h"
#include "vortex/resources/Texture.h"
#include "vortex/servers/RenderingServer.h"

namespace vortex {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec4 data;\n"
        "uniform mat4 PROJECTION;\n"
        "uniform mat4 TRANSFORM;\n"
        "out vec2 UV;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = PROJECTION * TRANSFORM * vec4(data.x, data.y, 0.0, 1.0);\n"
        "   UV = data.zw;\n"
        "}\0";
    
    const char *fragmentShaderSource = "#version 330 core\n"
        "uniform sampler2D TEXTURE;\n"
        "uniform vec4 MODULATE;\n"
        "uniform bool ONLY_MODULATE;\n"
        "in vec2 UV;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   if (ONLY_MODULATE) {\n"
        "       FragColor = MODULATE;\n"
        "       return;\n"
        "   }\n"
        "   FragColor = texture(TEXTURE, UV) * MODULATE;\n"
        "}\0";

    glm::mat4 RenderingServer::projection;
    Shader* RenderingServer::defaultShader;
    SDL_Window* RenderingServer::window;
    Color* RenderingServer::clearColor;

    unsigned int RenderingServer::VAO;

    void RenderingServer::setViewportCoords(int x, int y, int w, int h) {
        glViewport(x, y, w, h);
    }

    void RenderingServer::setClearColor(float r, float g, float b, float a) {
        clearColor->r = r;
        clearColor->g = g;
        clearColor->b = b;
        clearColor->a = a;
    }

    void RenderingServer::init(SDL_Window* window) {
        RenderingServer::window = window;

        SDL_GLContext context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);
        SDL_GL_SetSwapInterval(0);

        // Initialize glad and gl Shit
        gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
        clearColor = new Color("#0000FF");

        const float vertices[16] = {
            // positions   // texture coords
            0.0f,  0.0f,   0.0f, 0.0f,   // top left
            0.0f,  1.0f,   0.0f, 1.0f,   // bottom left
            1.0f,  1.0f,   1.0f, 1.0f,   // bottom right
            1.0f,  0.0f,   1.0f, 0.0f    // top right 
        };
        unsigned int indices[] = {
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        projection = glm::ortho(0.0f, (float)VORTEX_WINDOW_WIDTH, (float)VORTEX_WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

        defaultShader = new Shader(fragmentShaderSource, vertexShaderSource);
        defaultShader->use();

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    /// @brief  pisses
    void RenderingServer::dispose() {}

    void RenderingServer::clear() {
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader->use();
        glBindVertexArray(RenderingServer::VAO);

        glm::mat4 trans = glm::mat4(1.0);
        trans = glm::scale(trans, glm::vec3(VORTEX_WINDOW_WIDTH, VORTEX_WINDOW_HEIGHT, 1.0));

        unsigned int transLoc = defaultShader->getUniformLoc("TRANSFORM");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

        unsigned int modLoc = defaultShader->getUniformLoc("MODULATE");
        glUniform4f(modLoc, clearColor->r, clearColor->g, clearColor->b, clearColor->a);

        unsigned int onlyModLoc = defaultShader->getUniformLoc("ONLY_MODULATE");
        glUniform1i(onlyModLoc, 1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUniform1i(onlyModLoc, 0);
    }

    void RenderingServer::present() {
        SDL_GL_SwapWindow(window);
    }
}