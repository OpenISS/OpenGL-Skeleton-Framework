#include "buffer.h"

void Buffer::generate()
{
    glGenBuffers(1, &rendererID);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &rendererID);
}

void Buffer::bind() const
{
    glBindBuffer(bufferType, rendererID);
}

void Buffer::unbind() const
{
    glBindBuffer(bufferType, 0);
}




VertexBuffer::VertexBuffer(unsigned int size)
{
    generate();
    VertexBuffer::bind();
    glBufferData(bufferType, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    generate();
    VertexBuffer::bind();
    glBufferData(bufferType, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::setData(const void *data, unsigned int size) const
{
    VertexBuffer::bind();
    glBufferSubData(bufferType, 0, size, data);
}




IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count): count(count)
{
    // sizeof(unsigned int) == sizeof(GLuint);
    bufferType = GL_ELEMENT_ARRAY_BUFFER;

    generate();
    IndexBuffer::bind();
    glBufferData(bufferType, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}