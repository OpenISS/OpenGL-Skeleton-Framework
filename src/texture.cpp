#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

Texture::Texture(const std::string& path): Texture() {
    this->pathToFile = path;
}

Texture::Texture(const std::string& path, unsigned int format): Texture(path) {
    this->format = format;
}

void Texture::loadFile(const std::string& filepath) {
    if (pathToFile.empty()) {
        throw std::runtime_error("no file specified for texture!\n");
    }

    stbi_set_flip_vertically_on_load(1); // flip
    data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 0);

    if (!data) {
        throw std::runtime_error("Failed to load texture from file:" + filepath);
    }
}

void Texture::loadTexture(bool mipmaps) {
    if (!data) {
        loadFile(pathToFile);
    }

    glGenTextures(1, &textureID);
    glBindTexture(type, textureID);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // guess format based on available channels
    if (numChannels == 4)
        format = GL_RGBA;
    else if (numChannels == 3)
        format = GL_RGB;
    else if (numChannels == 1)
        format = GL_ALPHA;

    if (type == GL_TEXTURE_2D) {
        glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }

    if (mipmaps)
        glGenerateMipmap(type);

    glBindTexture(type, 0);

    if (data && !pathToFile.empty())
        stbi_image_free(data);

    loaded = true;
}

void Texture::useTexture(int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type, textureID);
}

void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
    data = nullptr;
    textureID = 0;
    width = 0;
    height = 0;
    numChannels = 0;
    pathToFile = "";
}

