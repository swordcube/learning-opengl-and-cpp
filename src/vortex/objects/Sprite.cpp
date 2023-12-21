#include <stdio.h>
#include <iostream>

#include "vortex/objects/Sprite.h"
#include "vortex/servers/RenderingServer.h"
#include "vortex/utilities/Tools.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace vortex;

namespace vortex {
    Sprite::Sprite() {
        Object();
        origin = glm::dvec2(0.0, 0.0);
        scale = glm::dvec2(1.0, 1.0);
    }

    Sprite::~Sprite() {
        texture->unreference();
        Object::~Object();
    }

    Texture* Sprite::getTexture() {
        return texture;
    }

    Shader* Sprite::getShader() {
        return (shader != NULL) ? shader : RenderingServer::defaultShader;
    }

    void Sprite::setTexture(Texture* newTexture) {
        if(texture == newTexture)
            return;
        
        if(!Tools::isNull(newTexture))
            newTexture->reference();
        
        if(!Tools::isNull(texture))
            texture->unreference();

        texture = newTexture;
    }

    void Sprite::update(double delta) {}
    void Sprite::draw() {
        Shader* drawShader = getShader();

        drawShader->use();
        glBindVertexArray(RenderingServer::VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getID());

        glm::mat4 trans = glm::mat4(1.0);
        glm::dvec2 size = glm::dvec2(texture->width * scale.x, texture->height * scale.y);

        trans = glm::translate(trans, glm::vec3(position + (-origin * size), 0.0));
        if (angle != 0.0) {
            trans = glm::translate(trans, glm::vec3(origin.x * size.x, origin.y * size.y, 0.0f));
            trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)); 
            trans = glm::translate(trans, glm::vec3(-origin.x * size.x, -origin.y * size.y, 0.0f));
        }
        trans = glm::scale(trans, glm::vec3(size, 1.0));

        glm::vec4 modulate = glm::vec4(1.0);

        unsigned int transLoc = drawShader->getUniformLoc("TRANSFORM");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

        unsigned int modLoc = drawShader->getUniformLoc("MODULATE");
        glUniform4fv(modLoc, 1, glm::value_ptr(modulate));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}