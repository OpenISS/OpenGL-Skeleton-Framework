#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "mesh.h"

class LoaderOBJ
{
public:

    enum class Status
    {
        FILESYSTEM_ERROR,
        FORMAT_ERROR,
        SUCCESS
    };

    Status getStatus() { return status; }

    void loadFile(Mesh& destination, const std::string& relativeFilepath)
    {
        status = Status::SUCCESS;
        destination.vertices.clear();
        destination.indices.clear();
        destination.setDrawingMode(DrawMode::INDEXED);
        clear();

        std::ifstream file(relativeFilepath);
        if (!file)
        {
            status = Status::FILESYSTEM_ERROR;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (!parseLine(destination, line))
                break;
        }

        clear();
    }

    void loadText(Mesh& destination, const std::string& text)
    {
        status = Status::SUCCESS;
        destination.vertices.clear();
        destination.indices.clear();
        destination.setDrawingMode(DrawMode::INDEXED);
        clear();

        std::istringstream s = std::istringstream(text);
        std::string line;
        while (std::getline(s, line))
        {
            if (!parseLine(destination, line))
                break;
        }

        clear();
    }

protected:

    typedef std::tuple<unsigned int, unsigned int, unsigned int> VertexID;

    bool parseLine(Mesh& destination, const std::string& line)
    {
        if (line.size() < 2) // Empty line
            return true;

        const char firstChar = line.at(0);
        const char secondChar = line.at(1);

        if (firstChar == '#') // Comment
        {
            return true;
        }
        else if (firstChar == 'v' && secondChar == 'n') // Normal
        {
            std::istringstream l = std::istringstream(line.substr(2));

            float vx, vy, vz;
            l >> vx  >> vy  >> vz;

            normals.push_back(glm::vec3(vx, vy, vz));
        }
        else if (firstChar == 'v' && secondChar == 't') // UV
        {
            std::istringstream l = std::istringstream(line.substr(2));

            float vx, vy;
            l >> vx  >> vy;

            uvs.push_back(glm::vec2(vx, vy));
        }
        else if (firstChar == 'v') // Position
        {
            std::istringstream l = std::istringstream(line.substr(1));

            float vx, vy, vz;
            l >> vx  >> vy  >> vz;

            positions.push_back(glm::vec3(vx, vy, vz));
        }
        else if (firstChar == 'f') // Face
        {
            int positionIndex[3] = {0, 0, 0};
            int normalIndex[3] = {0, 0, 0};
            int uvIndex[3] = {0, 0, 0};
            bool normal = true;
            bool uv = true;

            // Position, UV, Normal
            int matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &positionIndex[0], &uvIndex[0], &normalIndex[0], &positionIndex[1], &uvIndex[1], &normalIndex[1], &positionIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9)
            {
                // Position, Normal
                matches = sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &positionIndex[0], &normalIndex[0], &positionIndex[1], &normalIndex[1], &positionIndex[2], &normalIndex[2]);
                if (matches != 6)
                {
                    // Position, UV
                    matches = sscanf(line.c_str(), "f %d/%d %d/%d %d/%d", &positionIndex[0], &uvIndex[0], &positionIndex[1], &uvIndex[1], &positionIndex[2], &uvIndex[2]);
                    if (matches != 6)
                    {
                        // Position
                        matches = sscanf(line.c_str(), "f %d %d %d", &positionIndex[0], &positionIndex[1], &positionIndex[2]);
                        if (matches != 3)
                        {
                            status = Status::FORMAT_ERROR;
                            return false;
                        }
                        normal = false;
                        uv = false;
                    }
                    else
                    {
                        normal = false;
                    }
                }
                else
                {
                    uv = false;
                }
            }

            positionIndex[0] = interpretIndex(positionIndex[0]);
            positionIndex[1] = interpretIndex(positionIndex[1]);
            positionIndex[2] = interpretIndex(positionIndex[2]);
            if (normal)
            {
                normalIndex[0] = interpretIndex(normalIndex[0]);
                normalIndex[1] = interpretIndex(normalIndex[1]);
                normalIndex[2] = interpretIndex(normalIndex[2]);
            }
            if (uv)
            {
                uvIndex[0] = interpretIndex(uvIndex[0]);
                uvIndex[1] = interpretIndex(uvIndex[1]);
                uvIndex[2] = interpretIndex(uvIndex[2]);
            }

            VertexID vertex1ID = VertexID(positionIndex[0], normalIndex[0], uvIndex[0]);
            VertexID vertex2ID = VertexID(positionIndex[1], normalIndex[1], uvIndex[1]);
            VertexID vertex3ID = VertexID(positionIndex[2], normalIndex[2], uvIndex[2]);

            unsigned int vertex1Index;
            unsigned int vertex2Index;
            unsigned int vertex3Index;

            auto v1 = vertexMap.find(vertex1ID);
            if (v1 == vertexMap.end())
            {
                Vertex v;
                v.position = positions[positionIndex[0]];
                v.color = glm::vec3(1.0f);
                if (normal)
                    v.normal = normals[normalIndex[0]];
                else
                    v.normal = glm::vec3(0.0f);
                if (uv)
                    v.uv = uvs[normalIndex[0]];
                else
                    v.uv = glm::vec2(0.0f);
                destination.vertices.push_back(v);
                vertex1Index = destination.vertices.size() - 1;
                vertexMap.emplace(vertex1ID, vertex1Index);
            }
            else
            {
                vertex1Index = (*v1).second;
            }

            auto v2 = vertexMap.find(vertex2ID);
            if (v2 == vertexMap.end())
            {
                Vertex v;
                v.position = positions[positionIndex[1]];
                v.color = glm::vec3(1.0f);
                if (normal)
                    v.normal = normals[normalIndex[1]];
                else
                    v.normal = glm::vec3(0.0f);
                if (uv)
                    v.uv = uvs[normalIndex[1]];
                else
                    v.uv = glm::vec2(0.0f);
                destination.vertices.push_back(v);
                vertex2Index = destination.vertices.size() - 1;
                vertexMap.emplace(vertex2ID, vertex2Index);
            }
            else
            {
                vertex2Index = (*v2).second;
            }

            auto v3 = vertexMap.find(vertex3ID);
            if (v3 == vertexMap.end())
            {
                Vertex v;
                v.position = positions[positionIndex[2]];
                v.color = glm::vec3(1.0f);
                if (normal)
                    v.normal = normals[normalIndex[2]];
                else
                    v.normal = glm::vec3(0.0f);
                if (uv)
                    v.uv = uvs[normalIndex[2]];
                else
                    v.uv = glm::vec2(0.0f);
                destination.vertices.push_back(v);
                vertex3Index = destination.vertices.size() - 1;
                vertexMap.emplace(vertex3ID, vertex3Index);
            }
            else
            {
                vertex3Index = (*v3).second;
            }

            destination.indices.push_back(vertex1Index);
            destination.indices.push_back(vertex2Index);
            destination.indices.push_back(vertex3Index);
        }

        return true;
    }

    unsigned int interpretIndex(int index)
    {
        return index - 1;
    }

    void clear()
    {
        positions.clear();
        normals.clear();
        uvs.clear();
        vertexMap.clear();
    }

    Status status;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::map<VertexID, unsigned int> vertexMap;
};
