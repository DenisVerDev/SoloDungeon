#pragma once
#include"GameButton.h"
#include"GameSwitch.h"
#include"GameSlider.h"
#include"../../headers/scenes/Scene.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	SettingsMenue class:
-------------------------------------------------------------------------------------------*/

class GameButton;
class GameSwitch;
class GameSlider;

enum class STab		// settings tab type
{
	Video,
	Audio,
	KeyMouse
};

class SettingsMenue : public Scene
{

private:

	//------MENUE COMPONENTS------

	GameButton* btn_video;			// button for video settings

	GameButton* btn_audio;			// button for audio settings

	GameButton* btn_keymouse;		// button for key/mouse settings

	sf::RectangleShape head_line;	// underlines buttons and whole settings menue

	GameButton* btn_back;			// back to the parent menue

	GameButton* btn_standart;		// set standart settings

	GameButton* btn_apply;			// apply settings button

	//------TEXTURES------

	sf::Texture video_texture;		// btn_video texture

	sf::Texture audio_texture;		// btn_audio texture

	sf::Texture keymouse_texture;	// btn_keymouse texture

	//------PRIVATE VARS------	

	STab tab_type;					// what tab is open

	sf::Vector2f position;			// settings menue position

	sf::Vector2f size;				// settings menue size

	//------PRIVATE METHODS------	

	// set check mode false to previous tab button
	void uncheckTabButton();

public:

	//------CONSTRUCTOR/DESTRUCTOR------

	// default constructor
	SettingsMenue();

	// destructor
	~SettingsMenue();

	//------METHODS------

	// settings menue logic
	virtual void logic();

	// handle tab buttons click event
	void tabClickHandle();

	// handle back, standart and apply buttons click event
	void btnClickHandle();

	// draw whole settings menue
	virtual void draw(sf::RenderTarget& target);

	// set settings menue position
	void setPosition(sf::Vector2f position);

	//------GETTERS------

	sf::Vector2f getPosition();

	sf::Vector2f getSize();
};