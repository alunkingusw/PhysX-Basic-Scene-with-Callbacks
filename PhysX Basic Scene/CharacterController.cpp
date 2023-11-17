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
    //determine forward or backward based on the value
    int movement = 1;
    if (distance < 0) {
        movement = -1;
    }
    // Implement movement logic
    if (capsuleController) {
        // Get the current controller state
        physx::PxControllerState state;
        capsuleController->getState(state);

        // Get the controller's transform
        physx::PxTransform transform = capsuleController->getActor()->getGlobalPose();

        // Get the forward direction from the transform
        physx::PxVec3 forwardDir = transform.q.rotate(physx::PxVec3(0, 0, 1*movement));

        // Calculate the movement vector
        physx::PxVec3 movement = forwardDir * distance;

        // Move the controller
        physx::PxControllerFilters filters;
        capsuleController->move(movement, 0.0f, 0.001f, filters);

    }

}
void CharacterController::moveLeft(float distance) {
    // Implement movement logic
    //determine left or right based on the value
    int movement = 1;
    if (distance < 0) {
        movement = -1;
    }
    if (capsuleController) {
        
        // Get the current controller state
        physx::PxControllerState state;
        capsuleController->getState(state);

        // Get the controller's transform
        physx::PxTransform transform = capsuleController->getActor()->getGlobalPose();

        // Get the forward direction from the transform
        physx::PxVec3 forwardDir = transform.q.rotate(physx::PxVec3(movement*1, 0, 0));

        // Calculate the movement vector
        physx::PxVec3 movement = forwardDir * distance;

        // Move the controller
        physx::PxControllerFilters filters;
        capsuleController->move(movement, 0.0f, 0.001f, filters);

    }

}

void CharacterController::jump() {
    // Implement jump logic
    if (capsuleController) {
        // Get the current controller state
        physx::PxControllerState state;
        capsuleController->getState(state);

        // Set an upward velocity for jumping
        physx::PxVec3 up(0.0f, 1.0f, 0.0f);
        // Move the controller
        physx::PxControllerFilters filters;
        capsuleController->move(up, 0.0f, 0.001f, filters);
    }
}

void CharacterController::update(float deltaTime) {
    // Implement update logic
}

bool isKeyPressed(int key)
{
    return _kbhit() && _getch() == key;
}
