#pragma once
#include"GameButton.h"
#include"GameSwitch.h"
#include"GameSlider.h"
#include"GamePlate.h"
#include"../../headers/scenes/Scene.h"
#include"../../headers/tools/GameInput.h"
#include"SFML/Graphics.hpp"

/*-------------------------------------------------------------------------------------------
	SettingsMenue class:
	- simple menue where player can change game's settings
-------------------------------------------------------------------------------------------*/

class GameButton;
class GameSwitch;
class GameSlider;
class GamePlate;

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

	//------VIDEO SETTINGS COMPONENTS------

	sf::Text vert_sync_text;		// vertical sync text

	GameSwitch* vert_sync_switch;	// vertical sync switch

	//------AUDIO SETTINGS COMPONENTS------

	sf::Text sound_text;			// sound volume text

	GameSlider* sound_slider;		// sound volume slider

	sf::Text music_text;			// music volume text

	GameSlider* music_slider;		// music volume slider

	//------KEY/MOUSE SETTINGS COMPONENTS------

	sf::Text* actions_text;			// actions text

	GamePlate* action_plates;		// plates with key/mouse buttons

	sf::Text warning_text;			// warning text

	//------TEXTURES------

	sf::Texture video_texture;		// btn_video texture

	sf::Texture audio_texture;		// btn_audio texture

	sf::Texture keymouse_texture;	// btn_keymouse texture

	sf::Texture slider_texture;		// slider circle texture(anti alising alternative)

	//------PRIVATE VARS------	

	STab tab_type;					// what tab is open

	sf::Vector2f position;			// settings menue position

	sf::Vector2f size;				// settings menue size

	//------PRIVATE METHODS------	

	// set check mode false to previous tab button
	void uncheckTabButton();

	// handle tab buttons click event
	void tabClickHandle();

	// handle back, standart and apply buttons click event
	void btnClickHandle();

	// get settigs from gui and apply it
	void applySettings();

public:

	//------CONSTRUCTOR/DESTRUCTOR------

	// default constructor
	SettingsMenue();

	// destructor
	~SettingsMenue();

	//------METHODS------

	// settings menue logic
	virtual void logic();

	// draw whole settings menue
	virtual void draw(sf::RenderTarget& target);

	// set settings menue position
	void setPosition(sf::Vector2f position);

	// set everything according to settings
	void setSettings();

	//------GETTERS------

	sf::Vector2f getPosition();

	sf::Vector2f getSize();
};