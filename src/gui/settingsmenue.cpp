#include"../../src/headers/gui/SettingsMenue.h"

//------Constructor/Destructor definition------

SettingsMenue::SettingsMenue() : Scene()
{
	// settings menue will have constant size
	this->size.x = 800;
	this->size.y = 600;

	// loading textures
	bool video_status = this->video_texture.loadFromFile(GameResources::gui_path + "video_settings.png");
	bool audio_status = this->audio_texture.loadFromFile(GameResources::gui_path + "audio_settings.png");
	bool keymouse_status = this->keymouse_texture.loadFromFile(GameResources::gui_path + "keymouse_settings.png");

	this->video_texture.setSmooth(true);
	this->audio_texture.setSmooth(true);
	this->keymouse_texture.setSmooth(true);

	// tab buttons initializing
	sf::Vector2u texture_size;

	this->btn_video = new GameButton();
	if (video_status == true)
	{
		this->btn_video->loadTexture(this->video_texture);
		texture_size = this->video_texture.getSize();
		this->btn_video->setSize(sf::Vector2f(texture_size.x, texture_size.y));
		this->btn_video->setTextureScale(0.9f, 0.9f);
	}
	else
	{
		this->btn_video->setText("Video");
		this->btn_video->setSize(sf::Vector2f(64.f, 64.f));
	}

	this->btn_audio = new GameButton();
	if (audio_status == true)
	{
		this->btn_audio->loadTexture(this->audio_texture);
		texture_size = this->audio_texture.getSize();
		this->btn_audio->setSize(sf::Vector2f(texture_size.x, texture_size.y));
		this->btn_audio->setTextureScale(0.8f, 0.8f);
	}
	else
	{
		this->btn_audio->setText("Audio");
		this->btn_audio->setSize(sf::Vector2f(64.f, 64.f));
	}

	this->btn_keymouse = new GameButton();
	if (keymouse_status == true)
	{
		this->btn_keymouse->loadTexture(this->keymouse_texture);
		texture_size = this->keymouse_texture.getSize();
		this->btn_keymouse->setSize(sf::Vector2f(texture_size.x, texture_size.y));
		this->btn_keymouse->setTextureScale(0.9f, 0.9f);
	}
	else
	{
		this->btn_keymouse->setText("Keys");
		this->btn_keymouse->setSize(sf::Vector2f(64.f, 64.f));
	}

	// initializing head line
	this->head_line.setSize(sf::Vector2f(this->size.x,0.f));
	this->head_line.setOutlineThickness(0.5f);
	this->head_line.setOutlineColor(GameResources::additional_color);

	// initialize tab type
	this->tab_type = STab::Video;
	this->btn_video->setCheckMode(true);

	// initializing butons back, standart and apply
	this->btn_back = new GameButton("Back");
	this->btn_back->setSize(sf::Vector2f(80.f, 50.f));

	this->btn_standart = new GameButton("Set standart settings");

	this->btn_apply = new GameButton("Apply settings");
	this->btn_apply->setSize(sf::Vector2f(172.f, 36.f));

	GameLog::log("Settings menue was initialized!");
}

SettingsMenue::~SettingsMenue()
{
	delete this->btn_video;
	this->btn_video = nullptr;

	delete this->btn_audio;
	this->btn_audio = nullptr;

	delete this->btn_keymouse;
	this->btn_keymouse = nullptr;

	delete this->btn_back;
	this->btn_back = nullptr;

	delete this->btn_standart;
	this->btn_standart = nullptr;

	delete this->btn_apply;
	this->btn_apply = nullptr;

	GameLog::log("Settings menue was destroyed!");
}

//------Methods definition------

void SettingsMenue::logic()
{
	// update tab button's
	this->btn_video->update(GameCycle::mouse_data);
	this->btn_audio->update(GameCycle::mouse_data);
	this->btn_keymouse->update(GameCycle::mouse_data);

	// update back, standart and apply buttons
	this->btn_back->update(GameCycle::mouse_data);
	this->btn_standart->update(GameCycle::mouse_data);
	this->btn_apply->update(GameCycle::mouse_data);

	// handle generic buttons click event
	this->btnClickHandle();
	this->tabClickHandle();

	// update different tabs
	switch (this->tab_type)
	{
		case STab::Video:
			break;

		case STab::Audio:
			break;

		case STab::KeyMouse:
			break;
	}

}

void SettingsMenue::tabClickHandle()
{
	// handle tab buttons click event

	if (this->btn_video->getIsClicked() && this->isEventSent == false && this->tab_type != STab::Video)
	{
		uncheckTabButton();
		this->tab_type = STab::Video;
		this->btn_video->setCheckMode(true);
	}

	if (this->btn_audio->getIsClicked() && this->isEventSent == false && this->tab_type != STab::Audio)
	{
		uncheckTabButton();
		this->tab_type = STab::Audio;
		this->btn_audio->setCheckMode(true);
	}

	if (this->btn_keymouse->getIsClicked() && this->isEventSent == false && this->tab_type != STab::KeyMouse)
	{
		uncheckTabButton();
		this->tab_type = STab::KeyMouse;
		this->btn_keymouse->setCheckMode(true);
	}
}

void SettingsMenue::btnClickHandle()
{
	// handle buttons back and apply click event
	if (this->btn_back->getIsClicked() && this->isEventSent == false)
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::EndPause);
	}

	if (this->btn_standart->getIsClicked() && this->isEventSent == false)
	{
		Settings::setStandartSettings();

		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::SettingsUpdate);
	}

	if (this->btn_apply->getIsClicked() && this->isEventSent == false)
	{
		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::SettingsUpdate);
	}
}

void SettingsMenue::uncheckTabButton()
{
	switch (this->tab_type)
	{
		case STab::Video:
			this->btn_video->setCheckMode(false);
			break;

		case STab::Audio:
			this->btn_audio->setCheckMode(false);
			break;

		case STab::KeyMouse:
			this->btn_keymouse->setCheckMode(false);
			break;
	}
}

void SettingsMenue::draw(sf::RenderTarget& target)
{
	// draw tab buttons
	this->btn_video->draw(target);
	this->btn_audio->draw(target);
	this->btn_keymouse->draw(target);

	// draw back, standart and apply button
	this->btn_back->draw(target);
	this->btn_standart->draw(target);
	this->btn_apply->draw(target);

	//draw head line
	target.draw(this->head_line);

	// draw different tabs
	switch (this->tab_type)
	{
	case STab::Video:
		break;

	case STab::Audio:
		break;

	case STab::KeyMouse:
		break;
	}
}

void SettingsMenue::setPosition(sf::Vector2f position)
{
	this->position = position;

	// set tab buttons position
	this->btn_video->setPosition(this->position);
	this->btn_audio->setPosition(sf::Vector2f(this->btn_video->getPosition().x + this->btn_video->getSize().x + 30, this->position.y));
	this->btn_keymouse->setPosition(sf::Vector2f(this->btn_audio->getPosition().x + this->btn_audio->getSize().x + 30, this->position.y));

	// set back and apply button's position
	this->btn_back->setPosition(sf::Vector2f(20, 10));
	this->btn_standart->setPosition(sf::Vector2f(this->position.x,this->position.y + this->size.y - this->btn_standart->getSize().y));
	this->btn_apply->setPosition(sf::Vector2f(this->position.x + this->size.x - this->btn_standart->getSize().x, this->position.y + this->size.y - this->btn_apply->getSize().y));

	// set head line postion
	this->head_line.setPosition(sf::Vector2f(this->position.x, this->position.y + this->btn_video->getSize().x));
}

//------Getters definition------

sf::Vector2f SettingsMenue::getPosition()
{
	return this->position;
}

sf::Vector2f SettingsMenue::getSize()
{
	return this->size;
}
