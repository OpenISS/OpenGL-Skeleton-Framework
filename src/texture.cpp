#include "texture.h"

void Texture::loadFile(const std::string& filepath) {
    if (pathToFile.empty()) {
        throw std::runtime_error("no file specified for texture!\n");
    }

    data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

    if (!data) {
        throw std::runtime_error("Failed to load texture from file: %s\n");
    }
}

void Texture::loadTexture() {
    if (!data) {
        loadFile(pathToFile);
    }

    glGenTextures(1, &textureID);
    glBindTexture(type, textureID);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (type == GL_TEXTURE_2D) {
        glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }

    glGenerateMipmap(type);
    glBindTexture(type, 0);

    stbi_image_free(data);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(type, textureID);
}

void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    channels = 0;
    pathToFile = "";
}

