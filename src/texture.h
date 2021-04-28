#pragma once

#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include "light_data.h"

class Texture {

public:
    Texture(): width(0), height(0), numChannels(0), textureID(0) {}

    Texture(unsigned char* data, const int width, const int height, const int depth)
    : data(data), width(width), height(height), numChannels(depth), textureID(0)  {}

    explicit Texture(const std::string& path);

    explicit Texture(const std::string& path, unsigned int format);

    ~Texture() { clearTexture(); }

    void loadTexture(bool mipmaps = true);

    void useTexture(int slot = TEXTURE_SLOT_DIFFUSE) const;

    void clearTexture();

private:
    unsigned int textureID, format, type = GL_TEXTURE_2D;

    int width, height, numChannels;

    bool loaded = false;

    std::string pathToFile;

    unsigned char* data = nullptr;

    void loadFile(const std::string& filepath);
};