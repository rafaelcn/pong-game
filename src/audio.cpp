#include <iostream>

#include <SDL2/SDL_mixer.h>

#include "debug.hpp"
#include "audio.hpp"

Audio::Audio(Mix_Chunk* effect, Mix_Music* music)
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        Debug::logerr("Audio system couldn't be initialized, check the logs.",
                      Mix_GetError());

        show_audio_drivers();
        m_audio_opened = false;
    }
    else {
        Debug::log("Audio system initialized.");

        m_pEffect        = effect;
        m_pMusic         = music;
        m_audio_opened   = true;
    }
}

Audio::~Audio()
{
    if(m_pEffect != nullptr && m_audio_opened)
        Mix_FreeChunk(this->m_pEffect);
    if(m_pMusic != nullptr && m_audio_opened)
        Mix_FreeMusic(this->m_pMusic);
    if(m_audio_opened)
        Mix_CloseAudio();
}

bool Audio::load_music(const std::string& music_name)
{
    if(m_audio_opened) {
        m_pMusic = Mix_LoadMUS(music_name.c_str());

        if(m_pMusic == nullptr) {
            Debug::logerr("Loading the music " + music_name + " has failed. :(",
                          Mix_GetError());
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

bool Audio::load_effect(const std::string& effect_name)
{
    if(m_audio_opened) {
        m_pEffect = Mix_LoadWAV(effect_name.c_str());

        if(m_pEffect == nullptr) {
            Debug::logerr("Loading the effect " + effect_name +
                          " has failed. :(",
                          Mix_GetError());
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

void Audio::play_effect()
{
    if(Mix_PlayChannel(-1, m_pEffect, 0) != -1) {
        //success
    }
    else {
        Debug::logerr("Cannot reproduce the effect. Due to: ", Mix_GetError());
    }
}

//going to make an enum to be accepted as a flag.
void Audio::play_music(const int& loop_flag)
{
    if(Mix_PlayMusic(m_pMusic, loop_flag) != -1) {
        //success
    }
    else {
        Debug::logerr("Cannot reproduce the music. Due to: ", Mix_GetError());
    }
}


bool Audio::is_open()
{
    return m_audio_opened;
}

void Audio::show_audio_drivers()
{
    std::cout << "A list of the audio drivers available:" << std::endl;

    for(int i = 0; i < 10; i++)
        std::cout << "Available on index[" << i << "]: "
                  <<  SDL_GetAudioDriver(i) << std::endl;

    std::cout << "\n" << std::endl;
}
