/*
 * Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <iostream>
#include <array>

#include <SDL2/SDL_mixer.h>

/**
 * @brief The Audio class
 */
class Audio {
private:
    // A boolean to let us know if the audio is opened or not.
    bool m_audio_opened;
    //
    std::array<Mix_Chunk*, 3> m_effects;
    //
    std::array<Mix_Music*, 1> m_musics;

    // An array containing the path for each effect on the hard drive.
    std::array<std::string, 4> m_effects_paths;
    // An array containing the path for each music on the hard drive.
    std::array<std::string, 1> m_music_path;


private:
    void load_musics(); // loads all musics of the game.
    void load_effects(); // loads all the effects of the game.

public:
    /**
     * @brief The EffectType enum
     */
    enum class EffectType
    {
        hit_paddle,
        score_up,
        ball_speed
    };

    /**
     * @brief The Music enum
     */
    enum class Music
    {
        music_1
    };

public:
    Audio();
    ~Audio();

    bool is_open();

    void play_music(Music music_type, const int& loop_flag);
    void play_effect(EffectType effect_type);

    void show_audio_drivers();
};

#endif // AUDIO_HPP
