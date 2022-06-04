#pragma once
#include"SFML/Audio.hpp"

enum class SFXType
{
	SwordHit,
	EntityHitted,
	GameWin,
	GameLose
};

class AudioManager
{
private:

	static sf::Music* ambience_music;			// background-fight music

	static sf::SoundBuffer* sword_hit;			// sword hit sfx
	static sf::SoundBuffer* entity_hitted;		// entity got hit sfx
	static sf::SoundBuffer* game_win;			// game win sfx
	static sf::SoundBuffer* game_lose;			// game lose sfx

	static std::vector<sf::Sound*> sounds;		// vector of pointers to work with all game sounds

	static float music_volume;
	static float sound_volume;

	// private constructor => static class
	AudioManager();

public:

	// play ambient background music
	static void playMusic();

	// stop ambient background music
	static void stopMusic();

	// update audio settings
	static void updateSettings(float music_volume, float sound_volume);

	// init sound with buffer
	static void initSound(sf::Sound& sound, SFXType type);

	// load all game audio
	static bool loadAudio(std::string path);

	// free memory
	static void free();
};