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
    int program = glCreateProgram();

    if(!program) {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATE_FAILED" << std::endl;
        return false;
    }

    int vs = compileShader(vertexSrc, GL_VERTEX_SHADER);
    int fs = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

    if (vs == -1 || fs == -1) {
        return false;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    char infoLog[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        // std::cerr << "ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
        // return false;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    programID = program;

    return true;
}

bool Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    return create(vertexSrc.c_str(), fragmentSrc.c_str());
}

int Shader::compileShader(const char* code, unsigned int type) {
    int shader = glCreateShader(type);

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*) alloca(length * sizeof(char)); // allocates to stack not heap
        glGetShaderInfoLog(shader, length, &length, infoLog);
        std::cerr << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return -1;
    }

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

/**
 * Gets uniform location from openGL shader or throws a warning
 * could be improved with a cache (simple hashmap) but we use const everywhere so its painful
 *
 * @param name of uniform attribute
 * @return int location
 */
int Shader::getUniformLocation(const char* name) const
{
    int location = glGetUniformLocation(programID, name);

    //if (location == -1)
    //    std::cout << "WARNING::SHADER::UNIFORM_MISSING: " << name << std::endl;

    return location;
}

// Setters for various uniforms we use in our shaders

void Shader::setViewProjectionMatrix(const glm::mat4& view, const glm::mat4& projection) const
{
    setViewMatrix(view);
    setProjectionMatrix(projection);
}

void Shader::setModelMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation("modelMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setViewMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation("viewMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setProjectionMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation("projectionMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setLightSpaceMatrix(const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setViewPosition(const glm::vec3& position) const
{
    glUniform3fv(getUniformLocation("viewPosition"), 1, glm::value_ptr(position));
}

void Shader::setColor(const glm::vec3& color) const
{
    glUniform3fv(getUniformLocation("ambientColor"), 1, glm::value_ptr(color));
}

void Shader::setUVScale(const glm::vec2& uvScale) const
{
    glUniform2fv(getUniformLocation("uvScale"), 1, glm::value_ptr(uvScale));
}

void Shader::setTime(float time) const
{
    glUniform1f(getUniformLocation("time"), time);
}

void Shader::setLight(int index, const LightData& light) const
{
    const char* base = "lights";
    setCustomVector(getIndexedName(index, base, "position").c_str(), light.position);
    setCustomVector(getIndexedName(index, base, "direction").c_str(), glm::normalize(light.direction));
    setCustomVector(getIndexedName(index, base, "ambient").c_str(), light.ambientColor * light.ambientIntensity);
    setCustomVector(getIndexedName(index, base, "diffuse").c_str(), light.diffuseColor * light.diffuseIntensity);
    setCustomVector(getIndexedName(index, base, "specular").c_str(), light.specularColor * light.specularIntensity);
    setCustomFloat(getIndexedName(index, base, "cutOff").c_str(), glm::cos(glm::radians(light.angle * 0.5f * 0.8f)));
    setCustomFloat(getIndexedName(index, base, "outerCutOff").c_str(), glm::cos(glm::radians(light.angle * 0.5f)));
    setCustomFloat(getIndexedName(index, base, "constantAttenuation").c_str(), light.constantAttenuation);
    setCustomFloat(getIndexedName(index, base, "linearAttenuation").c_str(), light.linearAttenuation);
    setCustomFloat(getIndexedName(index, base, "quadraticAttenuation").c_str(), light.quadraticAttenuation);

    int shadowParams = light.shadowsEnabled ? 1 : 0;
    setCustomInt(getIndexedName(index, base, "shadowMapParams").c_str(), shadowParams);
    setCustomFloat(getIndexedName(index, base, "shadowsBias").c_str(), light.shadowsBias);
    setCustomMatrix(getIndexedName(index, base, "shadowsMatrix").c_str(), light.shadowsMatrix);
}

void Shader::setMaterial(const Material& material) const
{
    setCustomVector("ambientColor", material.ambientColor * material.ambientIntensity);
    setCustomVector("diffuseColor", material.diffuseColor * material.diffuseIntensity);
    setCustomVector("specularColor", material.specularColor * material.specularIntensity);
    setCustomVector("uvScale", material.uvScale);
    setCustomFloat("shininess", material.shininess);
}

void Shader::setCustomMatrix(const char* name, const glm::mat4& value) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setCustomVector(const char* name, const glm::vec3& value) const
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setCustomVector(const char* name, const glm::vec2& value) const
{
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setCustomFloat(const char* name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setCustomInt(const char* name, int value) const
{
    glUniform1i(getUniformLocation(name), value);
}

std::string Shader::getIndexedName(int index, const char* base, const char* property) const
{
    if (property == nullptr)
        return std::string(base) + "[" + std::to_string(index) + "]";
    else
        return std::string(base) + "[" + std::to_string(index) + "]." + std::string(property);
}

