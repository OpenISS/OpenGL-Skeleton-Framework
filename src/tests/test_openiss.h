#pragma once
#include <iostream>
#include <OpenISS.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../node_joint.h"
#include "../node_bone.h"
#include "../resources.h"
#include "../world.h"

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

        if(l_opFrame == nullptr) {
            std::cerr << "OpenISS: null depth frame..." << std::endl;
        } else {
            std::cout << "OpenISS: acquired depth frame..." << std::endl;
        }

        l_opFrame = g_oDevice->readFrame(COLOR_STREAM);

        if(l_opFrame == nullptr) {
            std::cerr << "OpenISS: null color frame..." << std::endl;
        } else {
            std::cout << "OpenISS: acquired color frame..." << std::endl;
        }

        // ...
        // put you code here
        // ...
        // TODO

        localRoot = new Node;
        world.sceneGraph->addChild(*localRoot);

        setEnabled(enabled);
    }

    void Shutdown(World &world) override
    {
        world.sceneGraph->removeChild(*localRoot);
        delete localRoot; // Recursively deletes all its children

        std::cout << "OpenISS example terminating..." << std::endl;
        delete g_oOpenISS;
    }


    void setEnabled(bool enabled) override
    {
        this->enabled = enabled;
        localRoot->visible = enabled;
    }

protected:

    Node* localRoot = nullptr;

// Context
    OpenISS* g_oOpenISS = nullptr;

// Current device
    OIDevice* g_oDevice = nullptr;

};
