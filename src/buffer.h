#pragma once

#include <GL/glew.h>

class Buffer {
public:
    Buffer() = default;
    ~Buffer();

    virtual void bind() const;

    virtual void unbind() const;

protected:
    void generate();

    unsigned int rendererID = 0, bufferType = GL_ARRAY_BUFFER;
};

class VertexBuffer : public Buffer {
public:
    VertexBuffer() = default;

    VertexBuffer(unsigned int size);

    VertexBuffer(const void* data, unsigned int size);

    void setData(const void *data, unsigned int size) const;

};

class IndexBuffer : public Buffer {
public:

    IndexBuffer(const unsigned int* data, unsigned int size);

protected:
    unsigned int count = 0;
};
