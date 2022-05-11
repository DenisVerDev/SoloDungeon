#pragma once
#include"../headers/render/GameRender.h"
#include"../headers/scenes/MenueScene.h"
#include"../headers/tools/MouseData.h"

/*-------------------------------------------------------------------------------------------
	GameCycle class:
	- main core of the game
	- render, update and work with files are separated in different threads
	[TODO]:1
	- every thread's lifespan should be based on the game state except gamelog thread
	[TODO]:2
	- update audio settings
-------------------------------------------------------------------------------------------*/

class GameRender;
class GameScene;
class MenueScene;

/* game events are handling in the main thread, so they can access every component of the game cycle
   * list is not finished
*/
enum class GameEvent
{
	SettingsUpdate,	// update render and audio settings
	SetMainMenue,	// set MainMenue game state
	SetLoading,		// set Loading game state
	SetGameplay,	// set Gameplay game state
	SetPause,		// set Pause game state
	Quit			// quit from game
};

/* almost each game state has it's own game scene and render
   * list is not finished
*/
enum class GameState
{
	MainMenue,
	Loading,
	Gameplay,
	Pause,
	Kill	// quit game, stop all threads
};

class GameCycle
{

private:

	static GameState gstate;			// current game state

	static std::vector<GameEvent> game_events; // game events

	//------PRIVATE VARS------	

	sf::Event system_event;				// system window event

	GameRender* grender;				// renders everything on screen

	MenueScene* mscene;					// Main menue scene

	sf::Thread gamelog_thread;			// gamelog thread

public:

	static MouseData mouse_data;		// current mouse data

	static bool running;				// if game is running

	//------CONSTRUCTOR/DESTRUCTOR------	

	// public constructor
	GameCycle();

	// destructor => frees all memory
	~GameCycle();

	//------METHODS------	

	// start game cycle
	void start();

	// handle window's system events
	void handleSystemEvents();		

	// handle game events
	void handleGameEvents();

	// add game event to the queue
	static void addGameEvent(GameEvent game_event);

	// free memory from game scene
	void destroyGameScene(GameScene*& scene);

	// end game process and all threads
	void kill();

	//------GETTERS------	
	
	// get current game state
	static GameState getCurrentState();
};