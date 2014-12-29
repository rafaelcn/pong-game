#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <iostream>

#include <SDL2/SDL_mixer.h>

class Audio
{
private:
    // A little chunk(effect).
    Mix_Chunk* m_pEffect;
    // A music.
    Mix_Music* m_pMusic;
    // A boolean to let us know if the audio is opened or not.
    bool m_audio_opened;

public:
    Audio(Mix_Chunk* effect, Mix_Music* music);
    ~Audio();

    bool load_music(const std::string& music_name);
    bool load_effect(const std::string& effect_name);
    bool is_open();

    void play_music(const int& loop_flag);
    void play_effect();

    void show_audio_drivers();
};

#endif // AUDIO_HPP
