#include "sdl_audio.hpp"
#include "debug.hpp"

#include <SDL2/SDL_mixer.h>
#include <iostream>

AudioWrapper::AudioWrapper(Mix_Chunk** effect, Mix_Music** music)
{
    /* There's no problem if the *music or the *effect be NULL, actually we have
     * to initialize the variables effect and music with NULL on main, otherwise
     * it will be initialize with trash from the memory. We load  the  music and
     * effect on this class, due that the *music and *effect should be NULL.
     */
    //if(*effect == NULL || *music == NULL)
    //    logerr("The music or the effect passed is null!");
    //else
    //{
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
        {
            logerr("Could not initialize the audio dude :(");
            logerr(Mix_GetError());
            showAudioDriversAvailable();
            this->audioOpened = false;
        }
        else
        {
            log("SDL_Audio initialized perfectly :)");
            showAudioDriversAvailable();
            this->effect        = *effect;
            this->music         = *music;
            this->audioOpened   = true;
        }
    //}
}

AudioWrapper::~AudioWrapper()
{
    if(this->effect != NULL && this->audioOpened)
        Mix_FreeChunk(this->effect);
    if(this->music != NULL && this->audioOpened)
        Mix_FreeMusic(this->music);
    if(this->audioOpened)
        Mix_CloseAudio();
}

bool AudioWrapper::loadMusic(const std::string& musicName)
{
    if(audioOpened)
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
    else
    {
        return false;
    }
}

bool AudioWrapper::loadEffect(const std::string& effectName)
{
    if(audioOpened)
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
    else
    {
        return false;
    }
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


void AudioWrapper::showAudioDriversAvailable()
{
    std::cout << "A list of the audio drivers available:" << std::endl;

    for(int i = 0; i < 10; i++)
        std::cout << "Available on index[" << i << "]: "
                  <<  SDL_GetAudioDriver(i) << std::endl;
}
