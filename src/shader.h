#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

/**
 * Abstracts shader compilation, linking, and uniform updates.
 * 
 * Inspired by code from Lab from the labs.
 */
class Shader
{
public:

    void activate() const
    {
        glUseProgram(programID);
    }

    bool create(const std::string vertexSrc, const std::string fragmentSrc)
    {
        return create(vertexSrc.c_str(), fragmentSrc.c_str());
    }

    bool create(const char* vertexSrc, const char* fragmentSrc)
    {
        bool overallSuccess = true;

        // Vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderSource = vertexSrc;
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        // Fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSource = fragmentSrc;
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // Check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        // Link shaders
        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        programID = shaderProgram;

        return overallSuccess;
    }

    int getProgramID() const
    {
        return programID;
    }


    void setModelMatrix(const glm::mat4& mat) const
    {
        GLuint location = glGetUniformLocation(programID, "modelMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setViewProjectionMatrix(const glm::mat4& view, const glm::mat4& projection) const
    {
        setViewMatrix(view);
        setProjectionMatrix(projection);
    }

    void setViewMatrix(const glm::mat4& mat) const
    {
        GLuint location = glGetUniformLocation(programID, "viewMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setProjectionMatrix(const glm::mat4& mat) const
    {
        GLuint location = glGetUniformLocation(programID, "projectionMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setLightSpaceMatrix(const glm::mat4& mat) const
    {
        GLuint location = glGetUniformLocation(programID, "lightSpaceMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setColor(const glm::vec3& color) const
    {
        GLuint location = glGetUniformLocation(programID, "color");
        glUniform3fv(location, 1, glm::value_ptr(color));
    }

    void setTime(float time) const
    {
        GLuint location = glGetUniformLocation(programID, "time");
        glUniform1f(location, time);
    }

    void setCustomVector(const char* name, const glm::vec3& value) const
    {
        GLuint location = glGetUniformLocation(programID, name);
        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void setCustomFloat(const char* name, float value) const
    {
        GLuint location = glGetUniformLocation(programID, name);
        glUniform1f(location, value);
    }

    bool needsCamera = true;
    bool castsShadows = false;
    bool receivesShadows = false;

protected:

    int programID = -1;
};
