/**
 * Copyright 2014-2018 Rafael Campos Nunes.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain a
 * copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
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
     * @brief The EffectType enum. Each enum corresponds to an effect.
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
