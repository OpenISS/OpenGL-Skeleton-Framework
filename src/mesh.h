#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "shader.h"

// Inspired by https://learnopengl.com/Model-Loading/Mesh

/// Represents a single vertex and all its attributes
struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;
};

/// Type of drawing to use to draw a mesh
enum class DrawMode
{
    /// Uses an index buffer to re-use vertices, for glDrawElements
    INDEXED,

    /// Doesn't use an index buffer, each triangle specified by 3 unique vertices, for glDrawArrays
    VERTEX
};

/**
 * Abstracts mesh GPU buffer construction, uploading, and rendering.
 */
class Mesh
{
public:

    Mesh()
    {
        VAO = 0, VBO = 0, EBO = 0;
    }

    /// Automatically destroys GPU buffers
    ~Mesh()
    {
        deleteGPUBuffers();
    }

    /**
     * Convenient setup function. Automatically deduces drawing mode (DrawMode::INDEXED if indices is empty).
     * 
     * @param vertices List of vertices.
     * @param indices List of indices (leave empty if unused).
     * @param uploadToGPU Calls uploadBuffersToGPU if true
     * @see DrawMode
     * @see uploadBuffersToGPU()
     */
    void setBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices = {}, bool uploadToGPU = true)
    {
        // Automatically deduce drawing mode
        if (indices.size() > 0)
            drawingMode = DrawMode::INDEXED;
        else
            drawingMode = DrawMode::VERTEX;

        this->vertices = vertices;
        this->indices = indices;

        if (uploadToGPU)
            uploadBuffersToGPU();
    }

    /// Uploads the contents of vertices and indices buffers from CPU to GPU
    void uploadBuffersToGPU()
    {
        // Create buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        if (this->drawingMode == DrawMode::INDEXED)
            glGenBuffers(1, &EBO);

        // Set VAO
        glBindVertexArray(VAO);

        // Upload vertices
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        if (this->drawingMode == DrawMode::INDEXED)
        {
            // Upload indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }

        // Set position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
        glEnableVertexAttribArray(0);

        // Set color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // Set normal attribute
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);

        // Set uv attribute
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(3);

        // Clear state
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

    void deleteGPUBuffers()
    {
        if (EBO != 0)
        {
            glDeleteBuffers(1, &EBO);
            EBO = 0;
        }

        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }

        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
    }

    /// To specify triangle (default), line, point, etc
    void setPolygonMode(GLenum mode)
    {
        this->polygonMode = mode;
    }

    /// @see DrawMode
    void setDrawingMode(DrawMode mode)
    {
        this->drawingMode = mode;
    }

    /**
     * Raw vector of vertices to be consumed by uploadBuffersToGPU.
     */
    std::vector<Vertex> vertices;

    /**
     * Raw vector of indices to be consumed by uploadBuffersToGPU.
     * 
     * Should be empty when not using indexed drawing.
     */
    std::vector<unsigned int> indices;

protected:

    GLuint VAO, VBO, EBO;
    GLenum polygonMode = GL_TRIANGLES;
    DrawMode drawingMode = DrawMode::VERTEX;
};
