#include "CharacterController.h"

CharacterController::CharacterController(physx::PxControllerManager* manager, physx::PxScene* scene)
    : controllerManager(manager), scene(scene), capsuleController(nullptr) {
}

CharacterController::~CharacterController() {
    if (capsuleController) {
        capsuleController->release();
    }
}

void CharacterController::createCharacter(const physx::PxExtendedVec3& position, physx::PxMaterial* characterMaterial) {
    // Create capsule controller
    physx::PxCapsuleControllerDesc desc;
    desc.setToDefault();
    desc.radius = 0.5f;
    desc.height = 2.0f;
    desc.upDirection = physx::PxVec3(0, 1, 0);
    desc.position = position;
    desc.material = characterMaterial;
    capsuleController = static_cast<physx::PxCapsuleController*>(controllerManager->createController(desc));

    // Add the actor to the scene
    //scene->addActor(*capsuleController->getActor());
}

void CharacterController::moveForward(float distance) {
    // Implement movement logic

}

void CharacterController::jump() {
    // Implement jump logic
}

void CharacterController::update(float deltaTime) {
    // Implement update logic
}
