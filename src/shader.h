#pragma once

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

/**
 * Abstracts shader compilation, linking, and uniform updates.
 * 
 * Inspired by code from Lab from the labs.
 */
class Shader
{
public:

    ~Shader() { clear(); }

    void load(const std::string& name, const std::string& location = "shaders");

    void loadFrom(const std::string& location);

    void fromFiles(const std::string& vertexLocation, const std::string& fragmentLocation);
    void fromFiles(const char* vertexLocation, const char* fragmentLocation);

    static std::string readFile(const std::string& fileLocation);
    static std::string readFile(const char* fileLocation);

    bool create(const std::string& vertexSrc, const std::string& fragmentSrc);
    bool create(const char* vertexSrc, const char* fragmentSrc);

    void clear();

    void activate() const;

    int getUniform(const char* name) const;

    void setModelMatrix(const glm::mat4& mat) const;

    void setViewProjectionMatrix(const glm::mat4& view, const glm::mat4& projection) const;

    void setViewMatrix(const glm::mat4& mat) const;

    void setProjectionMatrix(const glm::mat4& mat) const;

    void setLightSpaceMatrix(const glm::mat4& mat) const;

    void setColor(const glm::vec3& color) const;

    void setTime(float time) const;

    void setCustomVector(const char* name, const glm::vec3& value) const;

    void setCustomFloat(const char* name, float value) const;

    void setCustomInt(const char* name, int value) const;

    bool needsCamera = true;
    bool castsShadows = false;
    bool receivesShadows = false;

protected:
    static int addShader(int program, const char* code, GLenum type);

    int programID = -1;
};
