//C++
#include <iostream>

// SDL2
#include <SDL2/SDL_mixer.h>


// Pong Game
#include "audio_manager.hpp"
#include "debug.hpp"

AudioManager::AudioManager(Mix_Chunk** effect, Mix_Music** music)
{
    /* There's no problem if the *music or the *effect be NULL, actually we have
     * to initialize the variables effect and music with NULL on main, otherwise
     * it will be initialize with trash from the memory. We load  the  music and
     * effect on this class, due that the *music and *effect should be NULL.
     */
    //if(*effect == NULL || *music == NULL)
    //    Debug::logerr("The music or the effect passed is null!");
    //else
    //{
        // Bug detected on Xubuntu
        Debug::log(effect);
        Debug::log(music);

        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
        {
            Debug::logerr("Audio system couldn't be initialized, check the \
                          logs.");
            Debug::logerr(Mix_GetError());
            show_audio_drivers();
            this->audio_opened = false;
        }
        else
        {
            Debug::log("Audio system initialized.");

            this->effect        = *effect;
            this->music         = *music;
            this->audio_opened   = true;
        }
    //}
}

AudioManager::~AudioManager()
{
    if(this->effect != NULL && this->audio_opened)
        Mix_FreeChunk(this->effect);
    if(this->music != NULL && this->audio_opened)
        Mix_FreeMusic(this->music);
    if(this->audio_opened)
        Mix_CloseAudio();
}

bool AudioManager::load_music(const std::string& musicName)
{
    if(audio_opened)
    {
        this->music = Mix_LoadMUS(musicName.c_str());

        if(this->music == NULL)
        {
            Debug::logerr("Loading the music " + musicName + " has failed. :(");
            Debug::logerr(Mix_GetError());
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

bool AudioManager::load_effect(const std::string& effectName)
{
    if(audio_opened)
    {
        this->effect = Mix_LoadWAV(effectName.c_str());

        if(this->effect == NULL)
        {
            Debug::logerr("Loading the effect " + effectName + " has failed. :(");
            Debug::logerr(Mix_GetError());
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

void AudioManager::playEffect()
{
    if(Mix_PlayChannel(-1, this->effect, 0) != -1)
    {
        //success
    }
    else
    {
        Debug::logerr("Cannot reproduce the effect.");
        Debug::logerr(Mix_GetError());
    }
}

//going to make an enum to be accepted as a flag.
void AudioManager::playMusic(const int& loopFlag)
{
    if(Mix_PlayMusic(this->music, loopFlag) != -1)
    {
        //success
    }
    else
    {
        Debug::logerr("Cannot reproduce the music.");
        Debug::logerr(Mix_GetError());
    }
}


bool AudioManager::isOpen()
{
    return this->audio_opened;
}

void AudioManager::show_audio_drivers()
{
    std::cout << "A list of the audio drivers available:" << std::endl;

    for(int i = 0; i < 10; i++)
        std::cout << "Available on index[" << i << "]: "
                  <<  SDL_GetAudioDriver(i) << std::endl;

    std::cout << "\n" << std::endl;
}
