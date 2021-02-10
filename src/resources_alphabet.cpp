#include "resources_alphabet.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>
#include <sstream>

void ResourcesAlphabet::initialize()
{
    std::istringstream s = std::istringstream(exported);
    std::string line;

    char currentCharacter;
    while (std::getline(s, line))
    {
        if (line.length() <= 0)
        {
            continue;
        }
        else if (line.length() == 1)
        {
            currentCharacter = line.at(0);
            cubesMap.emplace(currentCharacter, std::vector<glm::mat4>());
        }
        else
        {
            std::istringstream l = std::istringstream(line);

            float px, py, pz, sx, sy, sz, rx, ry, rz;
            l >> px  >> py  >> pz >> sx  >> sy  >> sz  >> rx >> ry >> rz;

            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(px, py, pz));
            transform *= glm::eulerAngleXZ(glm::radians(rx), glm::radians(rz)); // Y angle is always 0
            transform = glm::scale(transform, glm::vec3(sx, sy, sz));

            cubesMap.find(currentCharacter)->second.push_back(transform);
        }
    }
}

const std::vector<glm::mat4>* ResourcesAlphabet::getCubes(char character)
{
    std::unordered_map<char, std::vector<glm::mat4>>::const_iterator iter = cubesMap.find(character);

    if (iter != cubesMap.end())
    {
        return &(iter->second);
    }
    else
    {
        return NULL;
    }
}

std::unordered_map<char, std::vector<glm::mat4>> ResourcesAlphabet::cubesMap;
// position(x, y, z), transform (x y z), scale (x, y, z) 
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
