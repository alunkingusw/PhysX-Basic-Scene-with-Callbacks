#pragma once
#include "fmod.hpp";
class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool initialize();
    FMOD::Sound* loadSound(const char* filename);
    void playSound(FMOD::Sound* sound);

private:
    FMOD::System* system;
};
