#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../module.h"
#include "../node_letter.h"
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
        const float interval = Resources::unitSize * 6.0f;

        andrew   = new Node();
        mark     = new Node();
        nicholas = new Node();
        paul     = new Node();

        a =  new NodeLetter('A', Resources::basicShader, scale);
        a2 = new NodeLetter('A', Resources::basicShader, scale);
        b =  new NodeLetter('B', Resources::basicShader, scale);
        h =  new NodeLetter('H', Resources::basicShader, scale);
        n =  new NodeLetter('N', Resources::basicShader, scale);
        m =  new NodeLetter('M', Resources::basicShader, scale);
        p =  new NodeLetter('P', Resources::basicShader, scale);
        v =  new NodeLetter('V', Resources::basicShader, scale);

        zero  = new NodeLetter('0', Resources::basicShader, scale);
        one   = new NodeLetter('1', Resources::basicShader, scale);
        one2  = new NodeLetter('1', Resources::basicShader, scale);
        four  = new NodeLetter('4', Resources::basicShader, scale);
        four2 = new NodeLetter('4', Resources::basicShader, scale);
        four3 = new NodeLetter('4', Resources::basicShader, scale);
        four4 = new NodeLetter('4', Resources::basicShader, scale);
        seven = new NodeLetter('7', Resources::basicShader, scale);

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

        world.sceneGraph->root.addChild(*andrew);
        world.sceneGraph->root.addChild(*mark);
        world.sceneGraph->root.addChild(*nicholas);
        world.sceneGraph->root.addChild(*paul);
        
        placeName(*andrew,   interval);
        placeName(*mark,     interval);
        placeName(*nicholas, interval);
        placeName(*paul,     interval);
    }

    void placeName(Node& root, float interval) {
        float x = interval * -1.5f;
        auto it = root.beginChildren();
        auto end = root.endChildren();

        for (; it != end; ++it)
        {
            Node& child = **it;
            child.transform = glm::translate(glm::mat4(1.0f), glm::vec3(x , 0.0f,  0.0f));
            x+= interval;
        }
    }

    virtual void Shutdown(World& world)
    {
        delete andrew;
        delete mark;
        delete nicholas;
        delete paul;
        delete a;
        delete a2;
        delete b;
        delete h;
        delete n;
        delete m;
        delete p;
        delete v;
        delete zero;
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

    NodeLetter* a;
    NodeLetter* a2;
    NodeLetter* b;
    NodeLetter* h;
    NodeLetter* n;
    NodeLetter* m;
    NodeLetter* p;
    NodeLetter* v;

    NodeLetter* zero;
    NodeLetter* one;
    NodeLetter* one2;
    NodeLetter* four;
    NodeLetter* four2;
    NodeLetter* four3;
    NodeLetter* four4;
    NodeLetter* seven;
};