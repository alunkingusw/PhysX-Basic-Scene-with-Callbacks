#include "SoundManager.h";




SoundManager::SoundManager() : system(nullptr) {}

SoundManager::~SoundManager() {
    if (system) {
        system->release();
    }
}

bool SoundManager::initialize() {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        // Handle error
        return false;
    }

    result = SoundManager::system->init(32, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK) {
        // Handle error
        return false;
    }

    return true;
}

FMOD::Sound* SoundManager::loadSound(const char* filename) {
    FMOD::Sound* sound;
    FMOD_RESULT result = system->createSound(filename, FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        // Handle error
        return nullptr;
    }

    return sound;
}

void SoundManager::playSound(FMOD::Sound* sound) {
    if (sound) {
        FMOD::Channel* channel;
        system->playSound(sound, 0, false, &channel);
    }
}
