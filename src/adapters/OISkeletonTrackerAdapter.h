#pragma once
#include <OpenISS.hpp>
#include <glm/glm.hpp>
#include "../node_skeleton.h"

using namespace openiss;

class OISkeletonTrackerAdapter
{
public:

    OISkeletonTrackerAdapter()
    {

    }

    void Setup(NodeSkeleton& skeleton, OISkeletonTracker& tracker, OITrackerFrame& trackerFrame, int userID = 0)
    {
        this->skeleton = &skeleton;
        this->tracker = &tracker;
        this->trackerFrame = &trackerFrame;
        this->userID = userID;
    }

    void Update(float deltaSeconds)
    {
        tracker->readFrame(trackerFrame);
        std::vector<std::shared_ptr<OIUserData>> users = trackerFrame->getUsers();

        const OIUserData& user = trackerFrame->getUserById(userID);
        OISkeleton* oiSkeleton = user.getSkeleton();

        skeleton->head->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_HEAD));
        skeleton->neck->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_NECK));
        skeleton->RShoulder->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_SHOULDER));
        skeleton->LShoulder->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_SHOULDER));
        skeleton->RElbow->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_ELBOW));
        skeleton->LElbow->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_ELBOW));
        skeleton->RHand->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_HAND));
        skeleton->LHand->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_HAND));
        skeleton->torso->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_TORSO));
        skeleton->RHip->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_HIP));
        skeleton->LHip->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_HIP));
        skeleton->RKnee->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_KNEE));
        skeleton->LKnee->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_KNEE));
        skeleton->RFoot->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_RIGHT_FOOT));
        skeleton->LFoot->setPoint(getAdapterJointPosition(*oiSkeleton, JointType::JOINT_LEFT_FOOT));

        skeleton->UpdatePositions();
    }

protected:

    glm::vec3 getAdapterJointPosition(OISkeleton& skeleton, JointType jointType) const 
    {
        std::shared_ptr<OISkeletonJoint> joint = skeleton.getJointByType(jointType);
        return glm::vec3(joint->x, joint->y, joint->z);
    }

    NodeSkeleton* skeleton = nullptr;
    OISkeletonTracker* tracker = nullptr;
    OITrackerFrame* trackerFrame = nullptr;
    int userID = 0;
};
