#include "sounds_manager.hpp"

#include "utils/logging/easylogging++.h"

namespace sounds {

SoundsManager::SoundsManager(const std::string& musics_path, const std::string& sounds_path)
  : m_musics_path(musics_path)
  , m_sounds_path(sounds_path)
{}

SoundsManager::~SoundsManager()
{
  for( auto music : m_musics )
    Mix_FreeMusic( music.second );
  m_musics.clear();

  for( auto sound : m_sounds )
    Mix_FreeChunk( sound.second );
  m_sounds.clear();
}

void SoundsManager::playMusic(const std::string& music_path, int repeat)
{
  Mix_PlayMusic( getMusic(music_path), repeat );
}

void SoundsManager::setMusicVolume(short volume)
{
  Mix_VolumeMusic(volume);
}

void SoundsManager::playSound(const std::string& sound_path, int repeat)
{
  // We need to specify the sound volume each time we play it
  auto sound = getSound(sound_path);
  Mix_VolumeChunk(sound, m_sound_volume);
  Mix_PlayChannel( -1, sound, repeat );
}

void SoundsManager::pauseMusic()
{
  Mix_PauseMusic();
}

void SoundsManager::resumeMusic()
{
  Mix_ResumeMusic();
}

Mix_Music* SoundsManager::getMusic(const std::string &music_path)
{
  auto found = m_musics.find(music_path);
  if(found != m_musics.end())
    return found->second;

  // Image not yet loaded
  return loadMusic(music_path);
}

Mix_Chunk* SoundsManager::getSound(const std::string &sound_path)
{
  auto found = m_sounds.find(sound_path);
  if(found != m_sounds.end())
    return found->second;

  // Image not yet loaded
  return loadSound(sound_path);
}

Mix_Music* SoundsManager::loadMusic(const std::string& path)
{
  // Load
  const std::string full_path = m_musics_path + path;
  Mix_Music* music = Mix_LoadMUS( full_path.c_str() );
  if( !music )
  {
    LOG(ERROR) << "Unable to load music " << full_path.c_str() << "! Mixer Error: " << Mix_GetError();
    return nullptr;
  }

  // Save texture in cache
  m_musics[path] = music;

  return music;
}

Mix_Chunk* SoundsManager::loadSound(const std::string& path)
{
  // Load
  const std::string full_path = m_sounds_path + path;
  Mix_Chunk* sound = Mix_LoadWAV( full_path.c_str() );
  if( !sound )
  {
    LOG(ERROR) << "Unable to load sound " << full_path.c_str() << "! Mixer Error: " << Mix_GetError();
    return nullptr;
  }

  // Save texture in cache
  m_sounds[path] = sound;

  return sound;
}

}
