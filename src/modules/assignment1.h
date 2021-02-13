#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../world.h"

class  Assignment1: public Module
{
public:

    void Startup(World& world) override
    {
        Module::Startup(world);
        const float scale = Resources::unitSize * 3.0f;
        const float interval = 10.0f;
        const float radius = Resources::unitSize * 64.0f;

        andrew   = new Node();
        mark     = new Node();
        nicholas = new Node();
        paul     = new Node();
        fifth    = new Node();

        a =  new NodeCharacter('A', Resources::basicShader, scale);
        a2 = new NodeCharacter('A', Resources::basicShader, scale);
        a3 = new NodeCharacter('A', Resources::basicShader, scale);
        b =  new NodeCharacter('B', Resources::basicShader, scale);
        h =  new NodeCharacter('H', Resources::basicShader, scale);
        n =  new NodeCharacter('N', Resources::basicShader, scale);
        m =  new NodeCharacter('M', Resources::basicShader, scale);
        p =  new NodeCharacter('P', Resources::basicShader, scale);
        p2 = new NodeCharacter('P', Resources::basicShader, scale);
        v =  new NodeCharacter('V', Resources::basicShader, scale);

        zero  = new NodeCharacter('0', Resources::basicShader, scale);
        zero2 = new NodeCharacter('0', Resources::basicShader, scale);
        zero3 = new NodeCharacter('0', Resources::basicShader, scale);
        one   = new NodeCharacter('1', Resources::basicShader, scale);
        one2  = new NodeCharacter('1', Resources::basicShader, scale);
        four  = new NodeCharacter('4', Resources::basicShader, scale);
        four2 = new NodeCharacter('4', Resources::basicShader, scale);
        four3 = new NodeCharacter('4', Resources::basicShader, scale);
        four4 = new NodeCharacter('4', Resources::basicShader, scale);
        seven = new NodeCharacter('7', Resources::basicShader, scale);

        andrew->addChild(*a);
        andrew->addChild(*h);
        andrew->addChild(*four);
        andrew->addChild(*one);
        
        mark->addChild(*m);
        mark->addChild(*b);
        mark->addChild(*four2);
        mark->addChild(*seven);
        
        nicholas->addChild(*n);
        nicholas->addChild(*a2);
        nicholas->addChild(*four3);
        nicholas->addChild(*zero);
        
        paul->addChild(*p);
        paul->addChild(*v);
        paul->addChild(*four4);
        paul->addChild(*one2);

        fifth->addChild(*a3);
        fifth->addChild(*p2);
        fifth->addChild(*zero2);
        fifth->addChild(*zero3);

        world.sceneGraph->addChild(*andrew);
        world.sceneGraph->addChild(*mark);
        world.sceneGraph->addChild(*nicholas);
        world.sceneGraph->addChild(*paul);
        world.sceneGraph->addChild(*fifth);

        placeName(*andrew,   interval, radius);
        placeName(*mark,     interval, radius);
        placeName(*nicholas, interval, radius);
        placeName(*paul,     interval, radius);
        placeName(*fifth,    interval, radius);

        andrew->transform   = glm::translate(glm::mat4(1.0f), getPosOnCircle(45.0f,  radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(45.0f - 90.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        mark->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(315.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(315.0f + 90.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        nicholas->transform = glm::translate(glm::mat4(1.0f), getPosOnCircle(135.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(135.0f + 90.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        paul->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(225.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(225.0f - 90.0f)  ,glm::vec3(0.0f, 1.0f, 0.0f));
        fifth->transform    = glm::mat4(1.0f)* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 getPosOnCircle(float degree, float radius) {
        float radians = glm::radians(degree);
        return glm::vec3(glm::cos(radians)*radius, 0.0f, glm::sin(radians)*radius);
    }

    void placeName(Node& root, float interval, float radius) {
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        float x = interval * -1.5f; 
        auto it = root.beginChildren();
        auto end = root.endChildren();

        for (; it != end; ++it)
        {
            Node& child = **it;
            child.transform = glm::translate(glm::mat4(1.0f), getPosOnCircle(x, radius) - glm::vec3(radius, 0.0f, 0.0f)) *
                    glm::rotate(glm::mat4(1.0f), glm::radians(-x - 90.f), up);
            x+= interval;
        }
}

    void Shutdown(World& world) override
    {
        selected = nullptr;
        delete andrew;
        delete mark;
        delete nicholas;
        delete paul;
        delete fifth;
    }

    void Update(World& world, float deltaSeconds) override
    {
        if (selected != nullptr) {


            if (scaleUp) {
                selected->scaleStep(deltaSeconds);
            }

            if (scaleDown) {
                selected->scaleStep(-deltaSeconds);
            }

            //TODO: if ikjl move object up / left / right / down

        }
    }


    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_Y) {
            scaleUp = false;
        }
        if (key == GLFW_KEY_I) {
            scaleDown = false;
        }
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        // model selection
        if (key == GLFW_KEY_1) {
            selected = andrew;
        }
        if (key == GLFW_KEY_2) {
            selected = mark;
        }
        if (key == GLFW_KEY_3) {
            selected = nicholas;
        }
        if (key == GLFW_KEY_4) {
            selected = paul;
        }
        if (key == GLFW_KEY_5) {
            selected = fifth;
        }

        // setup model scaling
        if (key == GLFW_KEY_Y) {
            scaleUp = true;
        }
        if (key == GLFW_KEY_I) {
            scaleDown = true;
        }

        // setup model manipulation mode: move vs rotate
        caps = !(mods & GLFW_MOD_SHIFT) != !(mods & GLFW_MOD_CAPS_LOCK); // bitwise xor didn't work here

        if (selected != nullptr && !caps) {
            if (key == GLFW_KEY_H) {
                selected->rotate(-5, selected->up());
            } else if (key == GLFW_KEY_K) {
                selected->rotate(5, selected->up());
            }
        }

        // Polygon mode
        if (selected != nullptr && (key == GLFW_KEY_P || key == GLFW_KEY_L || key == GLFW_KEY_T)) {
            RenderMode polygonMode;
            if (key == GLFW_KEY_P)
                polygonMode = RenderMode::Point;
            else if (key == GLFW_KEY_L)
                polygonMode = RenderMode::Line;
            else
                polygonMode = RenderMode::Triangle;

            auto it = selected->beginChildren();
            auto end = selected->endChildren();
            for (; it != end; ++it)
            {
                Node& child = **it;
                NodeCharacter* character = dynamic_cast<NodeCharacter*>(&child);
                if (character != nullptr)
                    character->renderMode = polygonMode;
            }
        }
    }

protected:
    bool scaleUp = false, scaleDown = false, rotate = false, caps = false;
    glm::vec2 modelMovement;
    Node* selected;

    Node *andrew, *mark, *nicholas, *paul, *fifth;

    NodeCharacter *a, *a2, *a3, *b, *h, *n, *m, *p, *p2, *v, *zero, *zero2, *zero3, *one, *one2, *four, *four2, *four3, *four4, *seven;
};