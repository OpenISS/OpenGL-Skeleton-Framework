#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
        destination.setDrawingMode(DrawMode::VERTEX);

        std::ifstream file(relativeFilepath);
        if (!file)
        {
            status = Status::FILESYSTEM_ERROR;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            parseLine(destination, line);
        }

        if (destination.indices.size() > 0)
            destination.setDrawingMode(DrawMode::INDEXED);
    }

    void loadText(Mesh& destination, const std::string& text)
    {
        status = Status::SUCCESS;
        destination.vertices.clear();
        destination.indices.clear();
        destination.setDrawingMode(DrawMode::VERTEX);

        std::istringstream s = std::istringstream(text);
        std::string line;
        while (std::getline(s, line))
        {
            parseLine(destination, line);
        }

        if (destination.indices.size() > 0)
            destination.setDrawingMode(DrawMode::INDEXED);
    }

protected:

    void parseLine(Mesh& destination, const std::string& line)
    {
        if (line.size() == 0) // Empty line
            return;

        const char firstChar = line.at(0);

        if (firstChar == '#') // Comment
        {
            return;
        }
        else if (firstChar == 'v') // Vertex
        {
            std::istringstream l = std::istringstream(line.substr(1));

            float vx, vy, vz;
            l >> vx  >> vy  >> vz;

            destination.vertices.push_back({glm::vec3(vx, vy, vz), glm::vec3(1.0f)});
        }
        else if (firstChar == 'f') // Face
        {
            std::istringstream l = std::istringstream(line.substr(1));

            int v1, v2, v3;
            l >> v1 >> v2 >> v3;

            destination.indices.push_back(interpretVertexIndex(destination, v1));
            destination.indices.push_back(interpretVertexIndex(destination, v2));
            destination.indices.push_back(interpretVertexIndex(destination, v3));
        }
    }

    int interpretVertexIndex(const Mesh& destination, int index)
    {
        if (index > 0)
            return index - 1;
        else
            return destination.vertices.size() - index;
    }

    Status status;
};
