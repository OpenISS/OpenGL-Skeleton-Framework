#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

/**
 * Loads letter/digit cube transforms from an embedded text file.
 * 
 * This text file is currently exported through a Unity scene and script.
 */
class ResourcesAlphabet
{
public:

    static void initialize();

    /**
     * Returns the transformation matrices of the unit cubes composing the specified character.
     * Returns nullptr if the character isn't supported.
     */
    static const std::vector<glm::mat4>* getCubes(char character);

    /**
     * Returns the transformation matrices of the spheres composing the specified character.
     * Returns nullptr if the character isn't supported.
     */
    static const std::vector<glm::mat4>* getSpheres(char character);

protected:

    static std::unordered_map<char, std::vector<glm::mat4>> cubesMap;
    static std::unordered_map<char, std::vector<glm::mat4>> spheresMap;
    static const char* exported;
};
