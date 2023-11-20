#include "SoundEventCallback.h"

// Custom collision callback class

    void SoundEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, 
        const physx::PxContactPair* pairs, physx::PxU32 nbPairs) {
        // Iterate through contact pairs
        
        for (physx::PxU32 i = 0; i < nbPairs; i++) {
            const physx::PxContactPair& cp = pairs[i];
            // Handle collision events as needed
            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
                std::cout << "Collision detected!" << std::endl;
            }
        }
    }

    void SoundEventCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) {
        
        for (physx::PxU32 i = 0; i < count; i++) {
            const physx::PxTriggerPair& triggerPair = pairs[i];
            if (triggerPair.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
                std::cout << "Trigger detected!" << std::endl;
            }
        }
    }

    void SoundEventCallback::onWake(physx::PxActor** actors, physx::PxU32 count) {
        for (physx::PxU32 i = 0; i < count; i++) {
            std::cout << "Actor woke up!" << std::endl;
        }
    }

    void SoundEventCallback::onSleep(physx::PxActor** actors, physx::PxU32 count) {
        for (physx::PxU32 i = 0; i < count; i++) {
            std::cout << "Actor went to sleep!" << std::endl;
        }
    }

    void SoundEventCallback::onAdvance(const physx::PxRigidBody* const* bodyBuffer, 
        const physx::PxTransform* poseBuffer, const physx::PxU32 count) {
        for (physx::PxU32 i = 0; i < count; i++) {
            const physx::PxRigidBody* body = bodyBuffer[i];
            const physx::PxTransform& pose = poseBuffer[i];
            std::cout << "Advanced state of Rigid Body!" << std::endl;
        }
    }

    void SoundEventCallback::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) {
        for (physx::PxU32 i = 0; i < count; i++) {
            const physx::PxConstraintInfo& constraintInfo = constraints[i];
            std::cout << "Constraint broken!" << std::endl;
        }
    }

    physx::PxFilterFlags boxCollisionFilterShader(
        physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, 
        physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, 
        physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
    {
       
        // let triggers through
        if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
        {
            pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
            return physx::PxFilterFlag::eDEFAULT;
        }
        // generate contacts for all that were not filtered above
        pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
        // trigger the contact callback for pairs (A,B) where
        // the filtermask of A contains the ID of B and vice versa.
        std::cout << "contact";
        if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
            pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

        return physx::PxFilterFlag::eDEFAULT;
    }

    void setupFiltering(physx::PxRigidActor* actor, physx::PxU32 filterGroup, physx::PxU32 filterMask)
    {
        physx::PxFilterData filterData;
        filterData.word0 = filterGroup; // word0 = own ID
        filterData.word1 = filterMask;  // word1 = ID mask to filter pairs that trigger a
        // contact callback (list multiple using |);
        const physx::PxU32 numShapes = actor->getNbShapes();

        // Allocate an array of PxShape* pointers.
        physx::PxShape** shapes = new physx::PxShape*[actor->getNbShapes()];
        // Get the shapes of the actor.
        actor->getShapes(shapes, actor->getNbShapes());

        // Set the simulation filter data for each shape.
        for (physx::PxU32 i = 0; i < actor->getNbShapes(); ++i)
        {
            shapes[i]->setSimulationFilterData(filterData);
        }

        // Free the array of PxShape* pointers.
        delete[] shapes;
    }
