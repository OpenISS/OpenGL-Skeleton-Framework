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
    Mesh() {
        VAO = 0, VBO = 0, EBO = 0;
    }

    void setBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices = {}, bool uploadToGPU = true)
    {
        if (indices.size() > 0)
            drawingMode = DrawMode::INDEXED;
        else
            drawingMode = DrawMode::VERTEX;

        this->vertices = vertices;
        this->indices = indices;

        if (uploadToGPU)
            uploadBuffersToGPU();
    }

    ~Mesh() {
        clearBuffers();
    }

    void uploadBuffersToGPU()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        if (this->drawingMode == DrawMode::INDEXED)
            glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        if (this->drawingMode == DrawMode::INDEXED) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
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
        if (this->drawingMode == DrawMode::INDEXED)
            glDrawElements(this->polygonMode, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(this->polygonMode, 0, static_cast<GLsizei>(vertices.size()));

        glBindVertexArray(0);
    }

    void clearBuffers() {
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
            EBO = 0;
        }
        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
    }

    void setPolygonMode(GLenum mode) {
        this->polygonMode = mode;
    }

    void setDrawingMode(DrawMode mode) {
        this->drawingMode = mode;
    }

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;

protected:
    GLenum polygonMode = GL_TRIANGLES;
    DrawMode drawingMode = DrawMode::VERTEX;
};
