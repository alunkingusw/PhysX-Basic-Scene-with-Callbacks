#pragma once

//add library for key listening
#include <conio.h>
#include "PxPhysicsAPI.h"
#include <iostream>;
#include "Windows.h"

class CharacterController {
public:
    CharacterController(physx::PxControllerManager* manager, physx::PxScene* scene);
    ~CharacterController();

    void createCharacter(const physx::PxExtendedVec3& position, physx::PxMaterial* characterMaterial);
    void moveForward(float distance);
    void moveLeft(float distance);
    void jump();
    void update();

private:
    physx::PxControllerManager* controllerManager;
    physx::PxScene* scene;
    physx::PxCapsuleController* capsuleController;
};
