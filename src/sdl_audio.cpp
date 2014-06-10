#include "sdl_audio.h"
#include "debug.hpp"

#include <SDL2/SDL_mixer.h>
#include <iostream>

AudioWrapper::AudioWrapper(Mix_Chunk** effect, Mix_Music** music)
{
    if(*effect == NULL || *music == NULL)
        logerr("The music of the effect passed is null!");
    else
    {
        //I think that I'll move that to the sdl_openAudio();
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
        {
            logerr("Could not initialize the audio dude :(");
            logerr(Mix_GetError());
        }
        else
        {
            log("SDL_Audio initialized perfectly :)");

            this->effect    = *effect;
            this->music     = *music;
        }
    }
}

AudioWrapper::~AudioWrapper()
{
    Mix_FreeChunk(this->effect);
    //Mix_FreeMusic(this->music);
    Mix_CloseAudio();
}

bool AudioWrapper::loadMusic(const std::string& musicName)
{
    this->music = Mix_LoadMUS(musicName.c_str());

    if(this->music == NULL)
    {
        logerr("Loading the music " + musicName + " has failed. :(");
        logerr(Mix_GetError());
        return false;
    }
    else
        return true;
}

bool AudioWrapper::loadEffect(const std::string& effectName)
{
    this->effect = Mix_LoadWAV(effectName.c_str());

    if(this->effect == NULL)
    {
        logerr("Loading the effect " + effectName + " has failed. :(");
        logerr(Mix_GetError());
        return false;
    }
    else
        return true;
}

void AudioWrapper::playEffect()
{
    if(Mix_PlayChannel(-1, this->effect, 0) != -1)
    {
        //success
    }
    else
    {
        logerr("Cannot reproduce the effect.");
        logerr(Mix_GetError());
    }
}

//going to make an enum to be accepted as a flag.
void AudioWrapper::playMusic(const int& loopFlag)
{
    if(Mix_PlayMusic(this->music, loopFlag) != -1)
    {
        //success
    }
    else
    {
        logerr("Cannot reproduce the music.");
        logerr(Mix_GetError());
    }
}
