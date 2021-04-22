#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../world.h"

#include "OpenISS.hpp"

#include <iostream>

using namespace openiss;

class TestOpenISS : public Module
{
public:

    MODULE_CONSTRUCTOR(TestOpenISS)

    void Startup(World& world) override
    {
        g_oOpenISS = new OpenISS(NULL_DEVICE);

        OIStatus l_tRetVal = g_oOpenISS->init();

        if(l_tRetVal != OIStatus::STATUS_OK)
        {
            std::cerr
                    << "Failed to init OpenISS..."
                    << "(" << static_cast<int>(l_tRetVal) << ")"
                    << std::endl;

            exit(EXIT_FAILURE);
        }

        l_tRetVal = g_oOpenISS->enableDepth();

        // ... check l_tRetVal

        l_tRetVal = g_oOpenISS->enableRGB();

        // ... check l_tRetVal

        std::cout << "OpenISS: enabled depth and RGB streams..." << std::endl;

        g_oDevice = g_oOpenISS->getDevice().get();

        OIFrame* l_opFrame = g_oDevice->readFrame(DEPTH_STREAM);

        if(l_opFrame == nullptr)
        {
            // ...
            std::cerr << "OpenISS: null depth frame..." << std::endl;
        }
        else
        {
            std::cout << "OpenISS: acquired depth frame..." << std::endl;
        }

        l_opFrame = g_oDevice->readFrame(COLOR_STREAM);

        if(l_opFrame == nullptr)
        {
            // ...
            std::cerr << "OpenISS: null color frame..." << std::endl;
        }
        else
        {
            std::cout << "OpenISS: acquired color frame..." << std::endl;
        }

        // ...
        // put you code here
        // ...
        // TODO

    }

    void Shutdown(World &world) override
    {
        delete g_oOpenISS;

        std::cout << "OpenISS example terminating..." << std::endl;
    }

protected:

// Context
    OpenISS* g_oOpenISS = nullptr;

// Current device
    OIDevice* g_oDevice = nullptr;

};
