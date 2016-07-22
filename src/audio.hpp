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
 * @brief The Audio class is a wrapper to the sdl-mixer system and also
 * offers an API to load an play music/effects on the game.
 */
class Audio {
private:
    // A boolean to let us know if the audio is opened or not.
    bool m_audio_opened;
    // Array of game effects
    std::array<Mix_Chunk*, 3> m_effects;
    // Array of the game music
    std::array<Mix_Music*, 1> m_musics;

    // An array containing the path for each effect on the hard drive.
    std::array<std::string, 4> m_effects_paths;
    // An array containing the path for each music on the hard drive.
    std::array<std::string, 1> m_music_path;


private:
    /**
     * @brief Loads all musics of the game.
     */
    void load_musics();

    /**
     * @brief Loads all the effects of the game.
     */
    void load_effects();

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

    /**
     * @brief is_open
     * @return
     */
    bool is_open();

    /**
     * @brief play_music
     * @param music_type
     * @param loop_flag
     */
    void play_music(Music music_type, const int& loop_flag);

    /**
     * @brief play_effect Play any effect of the EffectType enum
     * @param effect_type An enum which describes which effects are available.
     */
    void play_effect(EffectType effect_type);

    /**
     * @brief show_audio_drivers Lists all the audio drivers available.
     */
    void show_audio_drivers();
};

#endif // AUDIO_HPP
