#pragma once

#include <iostream>
#include "PxPhysicsAPI.h"

class SoundEventCallback : public physx::PxSimulationEventCallback{
public:

    virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
    virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
    virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override;
    virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
    virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override;
    virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
    
};
physx::PxFilterFlags boxCollisionFilterShader(
    physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
    physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
    physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);

void setupFiltering(physx::PxRigidActor* actor, physx::PxU32 filterGroup, physx::PxU32 filterMask);

struct FilterGroup
{
    enum Enum
    {
        eBOX = (1 << 0),
        eFLOOR = (1 << 1),
    };
};