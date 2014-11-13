#ifndef SOUNDS_MANAGER_HPP
#define SOUNDS_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <SDL2/SDL_mixer.h>

namespace sounds {

class SoundsManager
{
  public:

    static void init(const std::string& musics_path, const std::string& sounds_path);
    static std::unique_ptr<SoundsManager>& instance() { return s_instance; }
    ~SoundsManager();

    static void playMusic(const std::string& music_path, int repeat = 0);
    static void pauseMusic();
    static void resumeMusic();
    static void setMusicVolume(short volume);

    static void playSound(const std::string& sound_path, int repeat = 0);
    static void setSoundVolume(short volume) { s_instance->m_sound_volume = volume; }

    static void clean();

  private:

    SoundsManager(const std::string& musics_path, const std::string& sounds_path);

    Mix_Music* getMusic(const std::string& music_path);
    Mix_Chunk* getSound(const std::string& sound_path);
    Mix_Music* loadMusic(const std::string& music_path);
    Mix_Chunk* loadSound(const std::string& sound_path);

  private:

    std::string m_musics_path;
    std::string m_sounds_path;

    std::map<std::string, Mix_Music*> m_musics;
    std::map<std::string, Mix_Chunk*> m_sounds;

    short m_sound_volume {50};

    static std::unique_ptr<SoundsManager> s_instance;
};

}

#endif // SOUNDS_MANAGER_HPP
