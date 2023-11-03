// CharacterController.cpp

#include "CharacterController.h"



CharacterController::CharacterController(physx::PxControllerManager* manager, const physx::PxExtendedVec3& position, physx::PxReal height, physx::PxReal radius)
    : physx::PxCapsuleController(manager, position, radius, height / 2.0f) // Adjust the capsule dimensions as needed
{
    // Additional initialization code if necessary
}

CharacterController::~CharacterController() {
    // Cleanup code if needed
}

void CharacterController::moveForward(float distance) {
    // Implement the logic to move the character forward
    // Example: set the velocity
    physx::PxVec3 dir(0.0f, 0.0f, 1.0f); // Move forward in the z-axis
    physx::PxControllerState state;
    getState(state);
    move(dir * distance, 0.0f, 0.001f, state);
}

void CharacterController::jump() {
    // Implement the logic for the character to jump
    // Example: set the upward velocity
    physx::PxVec3 up(0.0f, 1.0f, 0.0f);
    physx::PxControllerState state;
    getState(state);
    move(up, 5.0f * state.deltaT, 0.001f, state);
}

void CharacterController::update(float deltaTime) {
    // Implement any additional update logic if needed
    // Example: apply gravity
    physx::PxVec3 gravity(0.0f, -9.81f, 0.0f);
    physx::PxControllerState state;
    getState(state);
    move(gravity * deltaTime, 0.0f, 0.001f, state);
}

void CharacterController::moveForward(float distance) {
    // Implement the logic to move the character forward
    // Example: set the velocity
    physx::PxVec3 dir(0.0f, 0.0f, 1.0f); // Move forward in the z-axis
    physx::PxControllerState state;
    getState(state);
    move(dir * distance, 0.0f, 0.001f, state);
}

void CharacterController::jump() {
    // Implement the logic for the character to jump
    // Example: set the upward velocity
    physx::PxVec3 up(0.0f, 1.0f, 0.0f);
    physx::PxControllerState state;
    getState(state);
    move(up, 5.0f * state.deltaT, 0.001f, state);
}

void CharacterController::update(float deltaTime) {
    // Implement any additional update logic if needed
    // Example: apply gravity
    physx::PxVec3 gravity(0.0f, -9.81f, 0.0f);
    physx::PxControllerState state;
    getState(state);
    move(gravity * deltaTime, 0.0f, 0.001f, state);
}

void CharacterController::onShapeHit(const physx::PxControllerShapeHit& hit) {
    // Handle shape hit event
}

void CharacterController::onControllerHit(const physx::PxControllersHit& hit) {
    // Handle controller hit event
}

void CharacterController::onObstacleHit(const physx::PxControllerObstacleHit& hit) {
    // Handle obstacle hit event
}

physx::PxControllerBehaviorFlags CharacterController::getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) {
    // Return desired behavior flags
    return physx::PxControllerBehaviorFlags();
}

physx::PxControllerBehaviorFlags CharacterController::getBehaviorFlags(const physx::PxController& controller) {
    // Return desired behavior flags
    return physx::PxControllerBehaviorFlags();
}

physx::PxControllerBehaviorFlags CharacterController::getBehaviorFlags(const physx::PxObstacle& obstacle) {
    // Return desired behavior flags
    return physx::PxControllerBehaviorFlags();
}

bool CharacterController::operator==(const CharacterController& other) const
{
    return false;
}
