// CharacterController.h

#pragma once

#include <characterkinematic/PxCapsuleController.h>
#include <characterkinematic/PxControllerManager.h>


class CharacterController : public physx::PxCapsuleControllerDesc, public physx::PxUserControllerHitReport, public physx::PxControllerBehaviorCallback {
public:
    CharacterController(physx::PxControllerManager* manager, const physx::PxExtendedVec3& position, physx::PxReal height = 1.0f, physx::PxReal radius = 0.5f);
    ~CharacterController();

    // Add any additional methods for controlling the character
    void moveForward(float distance);
    void jump();

    // Call this in the game loop to update the character's position
    void update(float deltaTime);

    // Implement pure virtual methods from PxUserControllerHitReport
    void onShapeHit(const physx::PxControllerShapeHit& hit) override;
    void onControllerHit(const physx::PxControllersHit& hit) override;
    void onObstacleHit(const physx::PxControllerObstacleHit& hit) override;

    // Implement pure virtual methods from PxControllerBehaviorCallback
    physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) override;
    physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxController& controller) override;
    physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxObstacle& obstacle) override;

    CharacterController() = default;
    bool operator==(const CharacterController& other) const;
};