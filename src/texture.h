#pragma once

#include "thirdparty/stb/stb_image.h"

#include <GL/glew.h>
#include <stdexcept>
#include <string>

class Texture {

public:
    Texture(): width(0), height(0), channels(0), textureID(0) {}

    explicit Texture(std::string path, GLenum format = GL_RGBA): Texture() {
        this->pathToFile = path;
        this->format = format;
    }

    Texture(unsigned char* data, const int width, const int height, const int depth)
    : data(data), width(width), height(height), channels(depth), textureID(0)  {}

    void loadTexture();
    void useTexture();
    void clearTexture();

    ~Texture() { clearTexture(); }

private:
    GLuint textureID;
    GLenum type = GL_TEXTURE_2D;
    GLenum format = GL_RGBA;

    int width, height, channels;

    std::string pathToFile;
    unsigned char* data = nullptr;

    void loadFile(const std::string& filepath);
};