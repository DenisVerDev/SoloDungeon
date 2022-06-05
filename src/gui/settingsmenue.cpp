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
	this->slider_texture.loadFromFile(GameResources::gui_path + "slider_circle.png");

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

	// initializing video settings components
	this->vert_sync_text.setFont(GameResources::text_font);
	this->vert_sync_text.setCharacterSize(30);
	this->vert_sync_text.setFillColor(GameResources::text_color);
	this->vert_sync_text.setString("Vertical synchronization");

	this->vert_sync_switch = new GameSwitch();

	// initializing audio settings components
	this->sound_text.setFont(GameResources::text_font);
	this->sound_text.setCharacterSize(30);
	this->sound_text.setFillColor(GameResources::text_color);
	this->sound_text.setString("Sound volume");

	this->sound_slider = new GameSlider(0.f, 100.f, Settings::getSoundVolume());
	this->sound_slider->setTexture(this->slider_texture);

	this->music_text.setFont(GameResources::text_font);
	this->music_text.setCharacterSize(30);
	this->music_text.setFillColor(GameResources::text_color);
	this->music_text.setString("Music volume");

	this->music_slider = new GameSlider(0.f, 100.f, Settings::getMusicVolume());
	this->music_slider->setTexture(this->slider_texture);

	// initializing key/mouse settings components
	int actions_count = GameInput::key_actions_count + GameInput::mouse_actions_count;
	this->actions_text = new sf::Text[actions_count];

	for (int i = 0; i < actions_count; i++)
	{
		this->actions_text[i].setFont(GameResources::text_font);
		this->actions_text[i].setCharacterSize(30);
		this->actions_text[i].setFillColor(GameResources::text_color);
		this->actions_text[i].setString(GameInput::getActionString((PlayerAction)(i + 1)));
	}

	this->action_plates = new GamePlate[actions_count];
	for (int i = 0; i < actions_count; i++)
	{
		this->action_plates[i].setSize(sf::Vector2f(48.f, 48.f));
	}
	this->action_plates[0].setText("W");
	this->action_plates[1].setText("S");
	this->action_plates[2].setText("D");
	this->action_plates[3].setText("A");
	this->action_plates[4].setText("Esc");
	this->action_plates[5].setText("Btn1");

	this->warning_text.setFont(GameResources::text_font);
	this->warning_text.setCharacterSize(28);
	this->warning_text.setFillColor(GameResources::additional_color);
	this->warning_text.setString("This screen shows only standart input, you can change it in config file");

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

	// delete video settings components
	delete this->vert_sync_switch;
	this->vert_sync_switch = nullptr;

	// delete audio settings components
	delete this->sound_slider;
	this->sound_slider = nullptr;

	delete this->music_slider;
	this->music_slider = nullptr;

	// delete key/mouse settings
	delete[] this->actions_text;
	this->actions_text = nullptr;

	delete[] this->action_plates;
	this->action_plates = nullptr;

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
			this->vert_sync_switch->update(GameCycle::mouse_data);
			this->vert_sync_switch->clickHandle();
			break;

		case STab::Audio:
			this->sound_slider->update(GameCycle::mouse_data);
			this->music_slider->update(GameCycle::mouse_data);
			break;

		case STab::KeyMouse:
			// no logic needed
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
		GameCycle::addGameEvent(GameEvent::EndSM);
	}

	if (this->btn_standart->getIsClicked() && this->isEventSent == false)
	{
		Settings::setStandartSettings();
		this->setSettings();

		this->isEventSent = true;
		GameCycle::addGameEvent(GameEvent::SettingsUpdate);
	}

	if (this->btn_apply->getIsClicked() && this->isEventSent == false)
	{
		this->applySettings();

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
			target.draw(this->vert_sync_text);
			this->vert_sync_switch->draw(target);
			break;

		case STab::Audio:
			target.draw(this->sound_text);
			target.draw(this->music_text);
			this->sound_slider->draw(target);
			this->music_slider->draw(target);
			break;

		case STab::KeyMouse:
			target.draw(this->warning_text);
			int actions_count = GameInput::key_actions_count + GameInput::mouse_actions_count;
			for (int i = 0; i < actions_count; i++)
			{
				target.draw(this->actions_text[i]);
				this->action_plates[i].draw(target);
			}
			break;
	}
}

void SettingsMenue::applySettings()
{
	Settings::setVerticalSync(!(bool)this->vert_sync_switch->getState());

	Settings::setSoundVolume(this->sound_slider->getValue());
	Settings::setMusicVolume(this->music_slider->getValue());
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
	this->btn_apply->setPosition(sf::Vector2f(this->position.x + this->size.x - this->btn_apply->getSize().x, this->position.y + this->size.y - this->btn_apply->getSize().y));

	// set head line postion
	this->head_line.setPosition(sf::Vector2f(this->position.x, this->position.y + this->btn_video->getSize().x));

	// set video settings components position
	this->vert_sync_text.setPosition(this->position.x + 50, this->position.y + 150);
	
	this->vert_sync_switch->setPosition(dt::getCenteredPostion(sf::Vector2f(400, 80), this->vert_sync_switch->getSize(), sf::Vector2f(this->position.x + 400, this->position.y + 132)));

	// set audio settings components position
	this->sound_text.setPosition(this->position.x + 50, this->position.y + 150);
	this->music_text.setPosition(this->position.x + 50, this->position.y + 230);

	this->sound_slider->setPosition(dt::getCenteredPostion(sf::Vector2f(400, 80), this->sound_slider->getSize(), sf::Vector2f(this->position.x + 400, this->position.y + 132)));
	this->music_slider->setPosition(dt::getCenteredPostion(sf::Vector2f(400, 80), this->music_slider->getSize(), sf::Vector2f(this->position.x + 400, this->position.y + 212)));

	// set key/mouse settings components position
	this->warning_text.setPosition(this->position.x, this->position.y + 80.f);

	int actions_count = GameInput::key_actions_count + GameInput::mouse_actions_count;
	int pos_y = 180;
	for (int i = 0; i < actions_count; i++)
	{
		if (i <= actions_count / 2)
		{
			this->actions_text[i].setPosition(this->position.x + 50, this->position.y + pos_y);
			this->action_plates[i].setPosition(sf::Vector2f(this->position.x + 250, this->position.y + pos_y - 5.f));
			pos_y += 80;
		}
		
		if (i == actions_count / 2) pos_y = 180;
		
		if(i > actions_count / 2)
		{
			this->actions_text[i].setPosition(this->position.x + 430, this->position.y + pos_y);
			this->action_plates[i].setPosition(sf::Vector2f(this->position.x + 630, this->position.y + pos_y - 5.f));
			pos_y += 82;
		}
	}
}

void SettingsMenue::setSettings()
{
	// init video settings
	this->vert_sync_switch->setState((SwitchState)(!Settings::vertical_sync));

	// init audio settings
	this->sound_slider->setValue(Settings::getSoundVolume());
	this->music_slider->setValue(Settings::getMusicVolume());
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
