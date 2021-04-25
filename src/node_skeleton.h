#pragma once
#include <glm/gtx/quaternion.hpp>
#include "material.h"
#include "mesh.h"
#include "node_model.h"
#include "node_joint.h"
#include "node_bone.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

/**
 * Member of the scene graph, renders a spherical joint
 *
 * @see SceneGraph
 */
class NodeSkeleton : public NodeModel
{
public:
    NodeSkeleton(): NodeSkeleton(Resources::unshadedWhiteMaterial, Resources::litShader) {}

    NodeSkeleton(Material& material, Shader& shader)
    {
        this->boneMaterial = &material;
        this->jointMaterial = &material;
        setup();
    }

    NodeSkeleton(Material& boneMaterial, Material& jointMaterial, Shader& shader)
    {
        this->boneMaterial = &boneMaterial;
        this->jointMaterial = &jointMaterial;
        this->shader = &shader;
        setup();
    }

    void setup()
    {
        auto headPoint = glm::vec3(0.f, 3.3f, 0.f);
        auto neckPoint = glm::vec3(0.f, 2.9f, 0.f);
        auto torsoPoint = glm::vec3(0.f, 2.2f, 0.f);

        auto lShoulderPoint = glm::vec3(0.7f, 2.8f, 0.f);
        auto lelbowPoint = glm::vec3(lShoulderPoint.x + 0.3f, 2.25f, 0.f);
        auto lhipPoint = glm::vec3(lShoulderPoint.x - 0.1f, 1.6f, 0.f);
        auto lhandPoint = glm::vec3(lelbowPoint.x, 1.5f, 0.f);
        auto lkneePoint = glm::vec3(lhipPoint.x, 0.9f, 0.f);
        auto lfootPoint = glm::vec3(lhipPoint.x, 0.1f, 0.f);

        auto rShoulderPoint = glm::vec3(-lShoulderPoint.x, lShoulderPoint.y, lShoulderPoint.z);
        auto relbowPoint = glm::vec3(-lelbowPoint.x, lelbowPoint.y, lelbowPoint.z);
        auto rhandPoint = glm::vec3(-lhandPoint.x, lhandPoint.y, lhandPoint.z);
        auto rhipPoint = glm::vec3(-lhipPoint.x, lhipPoint.y, lhipPoint.z);
        auto rkneePoint = glm::vec3(-lkneePoint.x, lkneePoint.y, lkneePoint.z);
        auto rfootPoint = glm::vec3(-lfootPoint.x, lfootPoint.y, lfootPoint.z);


        head = new NodeJoint(*jointMaterial, *shader, headPoint, radius);
        neck = new NodeJoint(*jointMaterial, *shader, neckPoint, radius);
        torso = new NodeJoint(*jointMaterial, *shader, torsoPoint, radius);

        LShoulder = new NodeJoint(*jointMaterial, *shader, lShoulderPoint, radius);
        LElbow = new NodeJoint(*jointMaterial, *shader, lelbowPoint, radius);
        LHand = new NodeJoint(*jointMaterial, *shader, lhandPoint, radius);
        LHip = new NodeJoint(*jointMaterial, *shader, lhipPoint, radius);
        LKnee = new NodeJoint(*jointMaterial, *shader, lkneePoint, radius);
        LFoot = new NodeJoint(*jointMaterial, *shader, lfootPoint, radius);

        RShoulder = new NodeJoint(*jointMaterial, *shader, rShoulderPoint, radius);
        RElbow = new NodeJoint(*jointMaterial, *shader, relbowPoint, radius);
        RHand = new NodeJoint(*jointMaterial, *shader, rhandPoint, radius);
        RHip = new NodeJoint(*jointMaterial, *shader, rhipPoint, radius);
        RKnee = new NodeJoint(*jointMaterial, *shader, rkneePoint, radius);
        RFoot = new NodeJoint(*jointMaterial, *shader, rfootPoint, radius);

        // Link everything to local graph
        this->addChild(*head);
        this->addChild(*neck);
        this->addChild(*torso);

        this->addChild(*LShoulder);
        this->addChild(*LElbow);
        this->addChild(*LHand);
        this->addChild(*LHip);
        this->addChild(*LKnee);
        this->addChild(*LFoot);

        this->addChild(*RShoulder);
        this->addChild(*RElbow);
        this->addChild(*RHand);
        this->addChild(*RHip);
        this->addChild(*RKnee);
        this->addChild(*RFoot);

        auto boneSize = radius / 2;
        this->addChild(*new NodeBone(*boneMaterial, *shader, headPoint, neckPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, neckPoint, lShoulderPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, neckPoint, rShoulderPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, torsoPoint, lShoulderPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, torsoPoint, rShoulderPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, torsoPoint, lhipPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, torsoPoint, rhipPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, lhipPoint, rhipPoint, boneSize));

        this->addChild(*new NodeBone(*boneMaterial, *shader, lShoulderPoint, lelbowPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, lelbowPoint, lhandPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, lShoulderPoint, lhipPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, lhipPoint, lkneePoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, lkneePoint, lfootPoint, boneSize));

        this->addChild(*new NodeBone(*boneMaterial, *shader, rShoulderPoint, relbowPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, relbowPoint, rhandPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, rShoulderPoint, rhipPoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, rhipPoint, rkneePoint, boneSize));
        this->addChild(*new NodeBone(*boneMaterial, *shader, rkneePoint, rfootPoint, boneSize));
    }

    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) {}

    Material* boneMaterial = nullptr;
    Material* jointMaterial = nullptr;
    float radius = 0.5f;

    NodeJoint* head = nullptr;
    NodeJoint* neck = nullptr;
    NodeJoint* torso = nullptr;

    NodeJoint* LShoulder = nullptr;
    NodeJoint* LElbow = nullptr;
    NodeJoint* LHand = nullptr;
    NodeJoint* LHip = nullptr;
    NodeJoint* LKnee = nullptr;
    NodeJoint* LFoot = nullptr;

    NodeJoint* RShoulder = nullptr;
    NodeJoint* RElbow = nullptr;
    NodeJoint* RHand = nullptr;
    NodeJoint* RHip = nullptr;
    NodeJoint* RKnee = nullptr;
    NodeJoint* RFoot = nullptr;
};
