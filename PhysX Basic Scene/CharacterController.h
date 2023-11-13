#pragma once

#include "PxPhysicsAPI.h"

class CharacterController {
public:
    CharacterController(physx::PxControllerManager* manager, physx::PxScene* scene);
    ~CharacterController();

    void createCharacter(const physx::PxExtendedVec3& position, physx::PxMaterial* characterMaterial);
    void moveForward(float distance);
    void jump();
    void update(float deltaTime);

private:
    physx::PxControllerManager* controllerManager;
    physx::PxScene* scene;
    physx::PxCapsuleController* capsuleController;
};
