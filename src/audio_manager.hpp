#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <iostream>

class AudioManager
{
    //An little chunk(effect).
    Mix_Chunk* effect;
    //A music.
    Mix_Music* music;
    //A boolean to let us know if the audio is opened or not.
    bool audio_opened;

public:
    AudioManager(Mix_Chunk** effect, Mix_Music** music);
    ~AudioManager();

    bool load_music(const std::string& musicName);
    bool load_effect(const std::string& effectName);
    bool isOpen();

    void playMusic(const int& loopFlag);
    void playEffect();

    void show_audio_drivers();

};

#endif // SDL_AUDIO_H
