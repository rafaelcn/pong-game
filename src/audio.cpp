#include "debug.hpp"
#include "audio.hpp"

Audio::Audio()
{
  m_music_path[0] = "res/sounds/musics/music_1.wav";

  // hit_paddle_effect
  m_effects_paths[0] = "res/sounds/effects/hit_paddle.wav";
  // score_up_effect
  m_effects_paths[1] = "res/sounds/effects/score_up.wav";
  // ball_speed_up
  m_effects_paths[2] = "res/sounds/effects/speed_up.wav";


  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
    Debug::log_err("failed to initialize the audio subsystem, reason ", Mix_GetError());

    show_audio_drivers();
	return;
  }
  
  Debug::log("audio subsystem initialized");
  m_audio_opened = true;
  
  load_musics();
  load_effects();
}

Audio::~Audio()
{
  if (m_audio_opened) {
    Mix_CloseAudio();
  }
}

void Audio::load_musics()
{
  m_musics[0] = Mix_LoadMUS(m_music_path[0].c_str());

  if (m_musics[0] == nullptr) {
    Debug::log_warn("failed to load music " + m_music_path[0], " reason ", Mix_GetError());
  }
}

void Audio::load_effects()
{
  for (unsigned int i = 0; i < m_effects.size(); i++) {
    m_effects[i] = Mix_LoadWAV(m_effects_paths[i].c_str());
    if (m_effects[i] == nullptr)  {
      Debug::log_warn("failed to load effect " + m_effects_paths[i], " reason ", Mix_GetError());
    }
  }
}

void Audio::play_effect(EffectType effect_type)
{
  Mix_Chunk* effect = nullptr;

  switch (effect_type) {
  case EffectType::hit_paddle:
    effect = m_effects[0];
    break;
  case EffectType::score_up:
    effect = m_effects[1];
    break;
  case EffectType::ball_speed:
    effect = m_effects[2];
    break;
  default:
    Debug::log_warn("invalid effect");
    break;
  }
  
  if (Mix_PlayChannel(-1, effect, 0) != -1) {
    //success
  } else {
    Debug::log_err("failed to play effect, reason: ", Mix_GetError());
  }
}

// Going to make an enum to be accepted as a flag.
void Audio::play_music(Music music_type, const int& loop_flag)
{
  Mix_Music* music = nullptr;

  switch (music_type) {
  case Music::music_1:
    music = m_musics[0];
    break;
  default:
    Debug::log_warn("");
    break;
  }

  if (Mix_PlayMusic(music, loop_flag) == -1) {
    Debug::log_err("failed to play music, reason ", Mix_GetError());
  }
}


bool Audio::is_open()
{
  return m_audio_opened;
}

void Audio::show_audio_drivers()
{
  for(int i = 0; i < 10; i++)
    std::cout << "available on index[" << i << "]: " <<  SDL_GetAudioDriver(i) << "\n";
}
