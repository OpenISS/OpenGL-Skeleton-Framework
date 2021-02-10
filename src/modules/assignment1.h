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

    virtual void Startup(World& world)
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

        auto* cube = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube->transform = glm::scale(cube->transform, glm::vec3(0.25f));

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

        world.sceneGraph->root.addChild(*andrew);
        world.sceneGraph->root.addChild(*mark);
        world.sceneGraph->root.addChild(*nicholas);
        world.sceneGraph->root.addChild(*paul);
        world.sceneGraph->root.addChild(*fifth);

        placeName(*andrew,   interval, radius);
        placeName(*mark,     interval, radius);
        placeName(*nicholas, interval, radius);
        placeName(*paul,     interval, radius);
        placeName(*fifth,    interval, radius);

        andrew->addChild(*cube);
        mark->addChild(*cube);
        nicholas->addChild(*cube);
        paul->addChild(*cube);

        andrew->transform   = glm::translate(glm::mat4(1.0f), getPosOnCircle(45.0f, radius))  * glm::rotate(glm::mat4(1.0f),  glm::radians(225.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        mark->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(315.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(315.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        nicholas->transform = glm::translate(glm::mat4(1.0f), getPosOnCircle(135.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(135.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
        paul->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(225.0f, radius)) * glm::rotate(glm::mat4(1.0f),  glm::radians(45.0f)  ,glm::vec3(0.0f, 1.0f, 0.0f));
        fifth->transform    = glm::translate(glm::mat4(1.0f), glm::vec3(radius, 0.0f, radius));
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
            child.transform = glm::translate(glm::mat4(1.0f), getPosOnCircle(x, radius) + glm::vec3(0.0f, 0.0f, radius)) *
                    glm::rotate(glm::mat4(1.0f), glm::radians(-x - 90.f), up);
            x+= interval;
        }
}

    virtual void Shutdown(World& world)
    {
        delete andrew;
        delete mark;
        delete nicholas;
        delete paul;
        delete fifth;
        delete a;
        delete a2;
        delete a3;
        delete b;
        delete h;
        delete n;
        delete m;
        delete p;
        delete p2;
        delete v;
        delete zero;
        delete zero2;
        delete zero3;
        delete one;
        delete one2;
        delete four;
        delete four2;
        delete four3;
        delete four4;
        delete seven;
    }

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);
    }

protected:
    Node* andrew;
    Node* mark;
    Node* nicholas;
    Node* paul;
    Node* fifth;

    NodeCharacter* a;
    NodeCharacter* a2;
    NodeCharacter* a3;
    NodeCharacter* b;
    NodeCharacter* h;
    NodeCharacter* n;
    NodeCharacter* m;
    NodeCharacter* p;
    NodeCharacter* p2;
    NodeCharacter* v;

    NodeCharacter* zero;
    NodeCharacter* zero2;
    NodeCharacter* zero3;
    NodeCharacter* one;
    NodeCharacter* one2;
    NodeCharacter* four;
    NodeCharacter* four2;
    NodeCharacter* four3;
    NodeCharacter* four4;
    NodeCharacter* seven;
};