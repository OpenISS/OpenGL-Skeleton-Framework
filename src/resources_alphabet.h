#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class ResourcesAlphabet
{
public:

    static void initialize();

    static const std::vector<glm::mat4>* getCubes(char character);

protected:

    static std::unordered_map<char, std::vector<glm::mat4>> cubesMap;
    static const char* exported;
};
