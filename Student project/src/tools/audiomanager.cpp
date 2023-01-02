#include"../../src/headers/tools/AudioManager.h"

sf::Music* AudioManager::ambience_music = nullptr;

sf::SoundBuffer* AudioManager::sword_hit = nullptr;
sf::SoundBuffer* AudioManager::entity_hitted = nullptr;
sf::SoundBuffer* AudioManager::game_win = nullptr;
sf::SoundBuffer* AudioManager::game_lose = nullptr;

std::vector<sf::Sound*> AudioManager::sounds;

float AudioManager::music_volume;
float AudioManager::sound_volume;

void AudioManager::playMusic()
{
	AudioManager::ambience_music->play();
}

void AudioManager::stopMusic()
{
	AudioManager::ambience_music->stop();
}

void AudioManager::updateSettings(float music_volume, float sound_volume)
{
	AudioManager::music_volume = music_volume;
	AudioManager::sound_volume = sound_volume;

	// update music volume
	AudioManager::ambience_music->setVolume(AudioManager::music_volume);

	// update sounds volume
	for (auto s : AudioManager::sounds)
	{
		s->setVolume(AudioManager::sound_volume);
	}
}

void AudioManager::initSound(sf::Sound& sound, SFXType type)
{
	switch (type)
	{
		case SFXType::SwordHit:
			sound.setBuffer(*AudioManager::sword_hit);
			sound.setVolume(AudioManager::sound_volume*0.4f);
			break;

		case SFXType::EntityHitted:
			sound.setBuffer(*AudioManager::entity_hitted);
			sound.setVolume(AudioManager::sound_volume*0.22f);
			break;

		case SFXType::GameWin:
			sound.setBuffer(*AudioManager::game_win);
			sound.setVolume(AudioManager::sound_volume);
			break;

		case SFXType::GameLose:
			sound.setBuffer(*AudioManager::game_lose);
			sound.setVolume(AudioManager::sound_volume);
			break;
	}

	AudioManager::sounds.push_back(&sound);
}

bool AudioManager::loadAudio(std::string path)
{
	AudioManager::ambience_music = new sf::Music();
	bool music = AudioManager::ambience_music->openFromFile(path + "ambience_music.wav");
	AudioManager::ambience_music->setLoop(true);

	AudioManager::sword_hit = new sf::SoundBuffer();
	bool sfx_sword = AudioManager::sword_hit->loadFromFile(path + "sword_hit.wav");

	AudioManager::entity_hitted = new sf::SoundBuffer();
	bool sfx_entity = AudioManager::entity_hitted->loadFromFile(path + "entity_hitted.wav");

	AudioManager::game_win = new sf::SoundBuffer();
	bool sfx_win = AudioManager::game_win->loadFromFile(path + "game_win.wav");

	AudioManager::game_lose = new sf::SoundBuffer();
	bool sfx_lose = AudioManager::game_lose->loadFromFile(path + "game_lose.wav");

	if (music == sfx_sword == sfx_entity == sfx_win == sfx_lose == true) return true;
	else return false;
}

void AudioManager::free()
{
	for (auto s : AudioManager::sounds)
	{
		s = nullptr;
	}
	AudioManager::sounds.clear();

	delete AudioManager::ambience_music;
	AudioManager::ambience_music = nullptr;

	delete AudioManager::sword_hit;
	AudioManager::sword_hit = nullptr;

	delete AudioManager::entity_hitted;
	AudioManager::entity_hitted = nullptr;

	delete AudioManager::game_win;
	AudioManager::game_win = nullptr;

	delete AudioManager::game_lose;
	AudioManager::game_lose = nullptr;
}
