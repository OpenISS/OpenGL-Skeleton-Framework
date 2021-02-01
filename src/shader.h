#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

// Inspired by code from Lab

class Shader
{
public:

    void activate()
    {
        glUseProgram(programID);
    }

    bool create(const std::string vertexSrc, const std::string fragmentSrc)
    {
        create(vertexSrc.c_str(), fragmentSrc.c_str());
    }

    bool create(const char* vertexSrc, const char* fragmentSrc)
    {
        bool overallSuccess = true;

        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderSource = vertexSrc;
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSource = fragmentSrc;
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        // link shaders
        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            overallSuccess = false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        programID = shaderProgram;

        return overallSuccess;
    }

    int getProgramID()
    {
        return programID;
    }


    void setModelMatrix(glm::mat4& mat)
    {
        GLuint location = glGetUniformLocation(programID, "modelMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setViewMatrix(glm::mat4& mat)
    {
        GLuint location = glGetUniformLocation(programID, "viewMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setProjectionMatrix(glm::mat4& mat)
    {
        GLuint location = glGetUniformLocation(programID, "projectionMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

    void setColor(glm::vec3& color)
    {
        GLuint location = glGetUniformLocation(programID, "color");
        glUniform3fv(location, 1, glm::value_ptr(color));
    }

protected:

    int programID = -1;
};
