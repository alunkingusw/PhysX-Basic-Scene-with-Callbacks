#pragma once

//add library for key listening
#include <conio.h>
#include "PxPhysicsAPI.h"
#include <iostream>;

////the following callback is referenced here: https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/CharacterControllers.html#hit-callback
//class CharacterControllerHitReport : public physx::PxUserControllerHitReport {
//public:
//    // Override the onShapeHit method
//    virtual void onShapeHit(const physx::PxControllerShapeHit& hit) override {
//        // Get the actor associated with the shape
//        physx::PxRigidActor* actor = hit.shape->getActor();
//        // Check if the actor is dynamic (movable)
//        if (actor->getType() == physx::PxActorType::eRIGID_DYNAMIC) {
//            // Cast to PxRigidDynamic to perform dynamic operations
//            physx::PxRigidDynamic* dynamicActor = static_cast<physx::PxRigidDynamic*>(actor);
//
//            // Example: Apply a force to move the dynamic actor
//            physx::PxVec3 force = physx::PxVec3(0.0f, 0.0f, 100.0f);
//            dynamicActor->addForce(force, physx::PxForceMode::eFORCE);
//            std::cout << "forcing!";
//        }
//    }
//    virtual void onControllerHit(const  physx::PxControllersHit& hit) override {};
//    virtual void onObstacleHit(const  physx::PxControllerObstacleHit& hit) override {};
//};

class CharacterController {
public:
    CharacterController(physx::PxControllerManager* manager, physx::PxScene* scene);
    ~CharacterController();

    void createCharacter(const physx::PxExtendedVec3& position, physx::PxMaterial* characterMaterial);
    void moveForward(float distance);
    void moveLeft(float distance);
    void jump();
    void update(float deltaTime);

private:
    physx::PxControllerManager* controllerManager;
    physx::PxScene* scene;
    physx::PxCapsuleController* capsuleController;
    // Create an instance of your hit report class
    //CharacterControllerHitReport* characterHitReport = nullptr;
};

bool isKeyPressed(int key);

