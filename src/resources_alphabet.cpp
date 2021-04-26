#include "resources_alphabet.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
#include <sstream>

void ResourcesAlphabet::initialize()
{
    std::istringstream s = std::istringstream(exported);
    std::string line;

    // Read line by line
    char currentCharacter;
    while (std::getline(s, line))
    {
        if (line.length() <= 0) // Slipping empty line
        {
            continue;
        }
        else if (line.length() == 1) // Handling a new character
        {
            currentCharacter = line.at(0);
            cubesMap.emplace(currentCharacter, std::vector<glm::mat4>());
            spheresMap.emplace(currentCharacter, std::vector<glm::mat4>());
        }
        else // Add a new cube transform to the current character
        {
            std::istringstream l = std::istringstream(line);

            // Parse position, scale, rotation
            float px, py, pz, sx, sy, sz, rx, ry, rz;
            l >> px  >> py  >> pz >> sx  >> sy  >> sz  >> rx >> ry >> rz;

            // Combine position, scale, rotation into a transformation matrix
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(px, py, pz));
            transform *= glm::eulerAngleXZ(glm::radians(rx), glm::radians(rz)); // Y angle is always 0, therefore unused
            transform = glm::scale(transform, glm::vec3(sx, sy, sz));

            // Is a sphere if has no rotation and Y scale exceeds X scale
            if (rx == 0.0f && rz == 0.0f && sy > sx)
                spheresMap.find(currentCharacter)->second.push_back(transform);
            else
                cubesMap.find(currentCharacter)->second.push_back(transform);
        }
    }
}

const std::vector<glm::mat4>* ResourcesAlphabet::getCubes(char character)
{
    std::unordered_map<char, std::vector<glm::mat4>>::const_iterator iter = cubesMap.find(character);

    if (iter != cubesMap.end())
        return &(iter->second);
    else
        return nullptr;
}

const std::vector<glm::mat4>* ResourcesAlphabet::getSpheres(char character)
{
    std::unordered_map<char, std::vector<glm::mat4>>::const_iterator iter = spheresMap.find(character);

    if (iter != spheresMap.end())
        return &(iter->second);
    else
        return nullptr;
}

std::unordered_map<char, std::vector<glm::mat4>> ResourcesAlphabet::cubesMap;
std::unordered_map<char, std::vector<glm::mat4>> ResourcesAlphabet::spheresMap;

// Externally generated file, format:
// position (x, y, z), scale (x y z), rotate (x, y, z) 
const char* ResourcesAlphabet::exported = R""""(
0
0 0.125 0 1 0.25 0.25 0 0 0
0 2 0 1 0.25 0.25 0 0 0
-0.5 1.0625 0 0.25 1.875 0.25 0 0 0
0.5 1.0625 0 0.25 1.875 0.25 0 0 0

1
0 1 0 0.25 2 0.25 0 0 0

4
0.5 1 0 0.25 2 0.25 0 0 0
-0.5 1.5 0 0.25 1 0.25 0 0 0
0 1 0 1 0.25 0.25 0 0 0

7
0.5 1 0 0.25 2 0.25 0 0 0
0 2 0 1 0.25 0.25 0 0 0

A
0 1 0 1 0.25 0.25 0 0 0
0 2 0 1 0.25 0.25 0 0 0
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 1 0 0.25 2 0.25 0 0 0

B
0 1.125 0 1 0.25 0.25 0 0 0
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 0.625 0 0.25 0.75 0.25 0 0 0
-0.125 0.125 0 1 0.25 0.25 0 0 0
-0.125 2 0 1 0.25 0.25 0 0 0
0.5 1.5625 0 0.25 0.625 0.25 0 0 0

H
0 1 0 1 0.25 0.25 0 0 0
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 1 0 0.25 2 0.25 0 0 0

M
-0.251 1.549 0 0.9 0.25 0.25 0 0 301.5208
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 1 0 0.25 2 0.25 0 0 0
0.251 1.549 0 0.9 0.25 0.25 0 0 58.479

N
0.001 1.023 0 2 0.25 0.25 0 0 299.8
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 1 0 0.25 2 0.25 0 0 0

P
0 1 0 1 0.25 0.25 0 0 0
-0.5 1 0 0.25 2 0.25 0 0 0
0.5 1.5 0 0.25 1 0.25 0 0 0
0 2 0 1 0.25 0.25 0 0 0

V
-0.402 1 0 0.25 2 0.25 0 0 25
0.402 1 0 0.25 2 0.25 0 0 335
)"""";
