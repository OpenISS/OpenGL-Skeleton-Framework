#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "shader.h"

// Inspired by https://learnopengl.com/Model-Loading/Mesh

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

enum class DrawMode
{
    INDEXED,
    VERTEX
};

class Mesh
{
public:

    void createGPUBuffers()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        if(this->drawingMode == DrawMode::INDEXED)
            glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        if(this->drawingMode == DrawMode::INDEXED){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        //clear state
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
    }

    void draw()
    {
        glBindVertexArray(VAO);
        if(this->drawingMode == DrawMode::INDEXED)
            glDrawElements(this->polygonMode, indices.size(), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(this->polygonMode, 0, vertices.size());

        glBindVertexArray(0);
    }

    void setPolygonMode(GLenum mode) {
        this->polygonMode = mode;
    }

    void setDrawingMode(DrawMode mode) {
        this->drawingMode = mode;
    }

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

protected:
    GLenum polygonMode = GL_TRIANGLES;
    DrawMode drawingMode = DrawMode::VERTEX;
};