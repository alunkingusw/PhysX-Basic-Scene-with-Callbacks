#include <ctype.h>
#include <iostream>
#include "PxPhysicsAPI.h"
#include "SoundEventCallback.h"
#include <chrono>
#include <thread>
using namespace physx;

PxPvd* mPvd = NULL;

int main() {
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;

	PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);

	if (!mFoundation) {
		std::cerr << "Error creating PhysX foundation." << std::endl;
	}

	//set up the Pvd connection
	mPvd = PxCreatePvd(*mFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	//setup physics
	PxPhysics* physics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), true, mPvd);
	if (!physics) {
		std::cerr << "Error creating Physics object." << std::endl;
		mFoundation->release();
	}

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVE_ACTORS;

	//set up the default CPU dispatcher
	PxDefaultCpuDispatcher* cpuDispatcher = PxDefaultCpuDispatcherCreate(2); //2 threads
	sceneDesc.cpuDispatcher = cpuDispatcher;

	// Create collision callback instance
	SoundEventCallback collisionCallback;

	//set up a default filter shader
	sceneDesc.filterShader = &boxCollisionFilterShader;
	sceneDesc.simulationEventCallback = &collisionCallback;

	PxScene* scene = physics->createScene(sceneDesc);
	if (!scene) {
		std::cerr << "Error creating scene." << std::endl;
		physics->release();
		mFoundation->release();
		return 1;
	}
	//add Pvd flags
	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();
	if (pvdClient) {
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	//create ground plane
	PxMaterial* groundMaterial = physics->createMaterial(0.5f, 0.5f, 0.1f);
	PxTransform groundTransform = PxTransform(PxQuat(PxHalfPi, PxVec3(0, 0, 1)));
	PxRigidStatic* groundPlane = PxCreateStatic(*physics, groundTransform, PxPlaneGeometry(), *groundMaterial);
	//set the flags for collision callbacks between the floor and a box
	setupFiltering(groundPlane, FilterGroup::eFLOOR, FilterGroup::eBOX);
	scene->addActor(*groundPlane);


	//create stacked boxes
	PxMaterial* boxMaterial = physics->createMaterial(0.5f, 0.5f, 0.1f);
	float boxHalfExtent = 1.0f;
	float boxSpacing = 2.0f;

	for (int i = 0; i < 5; ++i) {
		PxTransform boxTransform(PxVec3(0.0f, i * (2 * boxHalfExtent + boxSpacing), 0.0f));
		PxBoxGeometry boxGeometry(PxVec3(boxHalfExtent, boxHalfExtent, boxHalfExtent));
		PxRigidDynamic* box = PxCreateDynamic(*physics, boxTransform, boxGeometry, *boxMaterial, 1.0f);
		// Set the flag for notification callback when sleeping and waking
		box->setActorFlag(PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
		//set the flags for collision callbacks between boxes
		setupFiltering(box, FilterGroup::eBOX, FilterGroup::eBOX);
		scene->addActor(*box);
	}

	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

	//create a simulation loop
	const float timeStep = 1.0f / 60.0f;
	while (true) {
		//simulate the scene
		scene->simulate(timeStep);
		scene->fetchResults(true);

		//add sleep to control the frame rate.
		// Calculate the time elapsed since the last frame
		std::chrono::duration<float> elapsedTime = 
			std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - lastFrameTime);

		// Sleep for the remaining time until the next frame
		if (elapsedTime.count() < timeStep) {
			std::this_thread::sleep_for(std::chrono::duration<float>(timeStep - elapsedTime.count()));
		}

		// Update the last frame time
		lastFrameTime = std::chrono::high_resolution_clock::now();
	}

	scene->release();
	physics->release();
	mFoundation->release();

	return 0;
}