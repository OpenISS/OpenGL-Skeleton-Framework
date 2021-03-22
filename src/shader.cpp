#include "shader.h"

void Shader::load(const std::string &name, const std::string &location) {
    loadFrom(location + '/' + name);
}

void Shader::loadFrom(const std::string &location) {
    fromFiles(location + ".vert",  location + ".frag");
}

void Shader::fromFiles(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexCode = readFile(vertexLocation);
    std::string fragmentCode = readFile(fragmentLocation);

    create(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::fromFiles(const std::string& vertexLocation, const std::string& fragmentLocation)
{
    fromFiles(vertexLocation.c_str(), fragmentLocation.c_str());
}

std::string Shader::readFile(const char* fileLocation)
{
    std::string content;
    std::ifstream file(fileLocation);
    if (!file) {
        std::cerr << "ERROR::SHADER::LOADER::READ_FAILED: " << fileLocation << std::endl;
    }

    std::string line;
    while (!file.eof() && getline(file, line)) {
        content.append(line + '\n');
    }
    file.close();
    return content;
}

std::string Shader::readFile(const std::string& fileLocation)
{
    return readFile(fileLocation.c_str());
}

bool Shader::create(const char* vertexSrc, const char* fragmentSrc)
{
    int shaderProgram = glCreateProgram();

    if(!shaderProgram) {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATE_FAILED" << std::endl;
        return false;
    }

    int vertexShader = addShader(shaderProgram, vertexSrc, GL_VERTEX_SHADER);
    int fragmentShader = addShader(shaderProgram, fragmentSrc, GL_FRAGMENT_SHADER);

    if (vertexShader == -1 || fragmentShader == -1) {
        return false;
    }

    int success;
    char infoLog[1024];

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
        // return false;
    }

    // why delete?
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    programID = shaderProgram;

    return true;
}

bool Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    return create(vertexSrc.c_str(), fragmentSrc.c_str());
}

int Shader::addShader(int program, const char* code, GLenum type) {
    int shader = glCreateShader(type);

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    glAttachShader(program, shader);

    return shader;
}

void Shader::clear() {
    if (programID != -1) {
        glDeleteProgram(programID);
        programID = -1;
    }
}

void Shader::activate() const {
    glUseProgram(programID);
}

int Shader::getUniform(const char* name) const {
    return glGetUniformLocation(programID, name);
}

// Setters for various uniforms we use in our shaders

void Shader::setViewProjectionMatrix(const glm::mat4& view, const glm::mat4& projection) const
{
    setViewMatrix(view);
    setProjectionMatrix(projection);
}

void Shader::setModelMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniform("modelMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setViewMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniform("viewMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setProjectionMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniform("projectionMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setLightSpaceMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniform("lightSpaceMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setViewPosition(const glm::vec3& position) const
{
    glUniform3fv(getUniform("viewPosition"), 1, glm::value_ptr(position));
}

void Shader::setColor(const glm::vec3& color) const
{
    glUniform3fv(getUniform("ambientColor"), 1, glm::value_ptr(color));
}

void Shader::setUVScale(const glm::vec2& uvScale) const
{
    glUniform2fv(getUniform("uvScale"), 1, glm::value_ptr(uvScale));
}

void Shader::setTime(float time) const
{
    glUniform1f(getUniform("time"), time);
}

void Shader::setLight(const LightData& light) const
{
    setCustomVector("lightPosition", light.position);
    setCustomVector("lightAmbient", light.ambientColor * light.ambientIntensity);
    setCustomVector("lightDiffuse", light.diffuseColor * light.diffuseIntensity);
    setCustomVector("lightSpecular", light.specularColor * light.specularIntensity);
    setCustomFloat("lightConstantAttenuation", light.constantAttenuation);
    setCustomFloat("lightLinearAttenuation", light.linearAttenuation);
    setCustomFloat("lightQuadraticAttenuation", light.quadraticAttenuation);
}

void Shader::setMaterial(const Material& material) const
{
    setCustomVector("ambientColor", material.ambientColor * material.ambientIntensity);
    setCustomVector("diffuseColor", material.diffuseColor * material.diffuseIntensity);
    setCustomVector("specularColor", material.specularColor * material.specularIntensity);
    setCustomVector("uvScale", material.uvScale);
    setCustomFloat("shininess", material.shininess);
}

void Shader::setCustomVector(const char* name, const glm::vec3& value) const
{
    GLuint location = glGetUniformLocation(programID, name);
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setCustomVector(const char* name, const glm::vec2& value) const
{
    GLuint location = glGetUniformLocation(programID, name);
    glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::setCustomFloat(const char* name, float value) const
{
    GLuint location = glGetUniformLocation(programID, name);
    glUniform1f(location, value);
}

void Shader::setCustomInt(const char* name, int value) const
{
    GLuint location = glGetUniformLocation(programID, name);
    glUniform1i(location, value);
}

