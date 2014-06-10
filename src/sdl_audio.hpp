#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <iostream>

class AudioWrapper
{
    Mix_Chunk* effect;

    Mix_Music* music;

public:
    AudioWrapper(Mix_Chunk** effect, Mix_Music** music);
    ~AudioWrapper();

    bool loadMusic(const std::string& musicName);
    bool loadEffect(const std::string& effectName);

    void playMusic(const int& loopFlag);
    void playEffect();

};

#endif // SDL_AUDIO_H
