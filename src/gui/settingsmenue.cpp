#include"../../src/headers/gui/SettingsMenue.h"

//------Constructor/Destructor definition------

SettingsMenue::SettingsMenue()
{
	// settings menue will have constant size
	this->size.x = 800;
	this->size.y = 600;

	// set is event was sent
	this->isEventSent = false;

	// loading textures
	this->video_texture.loadFromFile(GameResources::gui_path + "video_settings.png");
	this->audio_texture.loadFromFile(GameResources::gui_path + "audio_settings.png");
	this->keymouse_texture.loadFromFile(GameResources::gui_path + "keymouse_settings.png");

	this->video_texture.setSmooth(true);
	this->audio_texture.setSmooth(true);
	this->keymouse_texture.setSmooth(true);

	// tab buttons initializing
	this->btn_video = new GameButton();
	this->btn_video->loadTexture(this->video_texture);
	sf::Vector2u texture_size = this->video_texture.getSize();
	this->btn_video->setSize(texture_size.x,texture_size.y);
	this->btn_video->setTextureScale(0.9f, 0.9f);

	this->btn_audio = new GameButton();
	this->btn_audio->loadTexture(this->audio_texture);
	texture_size = this->audio_texture.getSize();
	this->btn_audio->setSize(texture_size.x, texture_size.y);
	this->btn_audio->setTextureScale(0.8f, 0.8f);

	this->btn_keymouse = new GameButton();
	this->btn_keymouse->loadTexture(this->keymouse_texture);
	texture_size = this->keymouse_texture.getSize();
	this->btn_keymouse->setSize(texture_size.x, texture_size.y);
	this->btn_keymouse->setTextureScale(0.9f, 0.9f);

	// initializing head line
	this->head_line.setSize(sf::Vector2f(this->size.x,0.f));
	this->head_line.setOutlineThickness(0.5f);
	this->head_line.setOutlineColor(GameResources::additional_color);

	// initialize tab type
	this->tab_type = STab::Video;
	this->btn_video->setCheckMode(true);

	// initializing butons back and apply
	this->btn_back = new GameButton("Back");
	this->btn_back->setSize(80.f, 50.f);

	this->btn_apply = new GameButton("Apply settings");
	this->btn_apply->setSize(172.f, 36.f);

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

	delete this->btn_apply;
	this->btn_apply = nullptr;

	GameLog::log("Settins menue was destroyed!");
}

//------Methods definition------

void SettingsMenue::logic()
{
	sf::Vector2f mouse_pos(GameCycle::mouse_data.getPosition());

	// update tab button's
	this->btn_video->update(mouse_pos);
	this->btn_audio->update(mouse_pos);
	this->btn_keymouse->update(mouse_pos);

	// update back and apply buttons
	this->btn_back->update(mouse_pos);
	this->btn_apply->update(mouse_pos);

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

	if (this->btn_apply->getIsClicked() && this->isEventSent == false && Settings::getIsChanged() == true)
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

	// draw back and apply button
	this->btn_back->draw(target);
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

void SettingsMenue::resetEventSent()
{
	this->isEventSent = false;
}

void SettingsMenue::setPosition(sf::Vector2f position)
{
	this->position = position;

	// set tab buttons position
	this->btn_video->setPosition(this->position);
	this->btn_audio->setPosition(sf::Vector2f(this->btn_video->getPosition().x + this->btn_video->getWidth()+ 30, this->position.y));
	this->btn_keymouse->setPosition(sf::Vector2f(this->btn_audio->getPosition().x + this->btn_audio->getWidth() + 30, this->position.y));

	// set back and apply button's position
	this->btn_back->setPosition(sf::Vector2f(20, 10));
	sf::Vector2f apply_pos = dt::getCenteredPostion(this->size, sf::Vector2f(this->btn_apply->getWidth(), this->btn_apply->getHeight()), this->position);
	this->btn_apply->setPosition(sf::Vector2f(apply_pos.x,this->position.y + this->size.y - this->btn_apply->getHeight()));

	// set head line postion
	this->head_line.setPosition(sf::Vector2f(this->position.x, this->position.y + this->btn_video->getHeight()));
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
