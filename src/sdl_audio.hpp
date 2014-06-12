#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <iostream>

class AudioWrapper
{
    //An little chunk(effect).
    Mix_Chunk* effect;
    //A music.
    Mix_Music* music;
    //A boolean to let us know if the audio is opened or not.
    bool audioOpened;

public:
    AudioWrapper(Mix_Chunk** effect, Mix_Music** music);
    ~AudioWrapper();

    bool loadMusic(const std::string& musicName);
    bool loadEffect(const std::string& effectName);

    void playMusic(const int& loopFlag);
    void playEffect();

    void showAudioDriversAvailable();

};

#endif // SDL_AUDIO_H
