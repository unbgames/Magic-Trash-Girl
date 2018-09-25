/*
 * game.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GAME_H_
#define SOURCE_HEADERS_GAME_H_

#include <backgroundsectorlibraryhandler.h>
#include <keyboardinput.h>
#include <vacuumcleaner.h>
#include "animatedsprite.h"
#include <vector>
#include "player.h"
#include "menubackground.h"
#include <memory>
#include "backgroundblock.h"
#include "gamepadinput.h"
#include <stack>
#include "menu.h"
#include "hudelement.h"
#include "textcaches.h"
#include "Musics.h"
#include "fullmapbackground.h"

class Graphics;

class Game{
public:

	Game();

	~Game();

	static Game& getInstance();

	void addNewSpriteToDraw(AnimatedSprite* sprite);

	void setupBackgroundBlocks(Graphics &graphics, int columns, int lines);

	void damageBlock(int indexX, int indexY, float damage);

	BlockType getBlockType(int indexX, int indexY);

	void setBlockType(int indexX, int indexY, BlockType type);

	void setupBlockBorder(int x, int y);

	void redoBlockBorder(int x, int y);

	void redoAdjacentsBlocksBorders(int x, int y);

	void requestQuit();

	void setupBathroomMap();

	void setupRoomMap();

	void setupTutorialMap();

	void createNewPseudoRandomBlocksVector(int sectorsByLine, int sectorsByColumn);

	int getCurrentNumberBlocksLine();

	int getCurrentNumberBlocksColumn();

	void setMenuToReplaceInStack(Menu* menuToReplaceInStack);

	void buildMapObjectBlueprint(MapObjectBlueprint blueprint, Vector2 sectorPosition);

	void checkColisionFullMap();

	float getPlayerVaccumDps();

	void CheckMenuIntro();
	void FadeOutMenuMusic();
	void initMusic();
private:

	static Game* _instance;

	void gameLoop();

	void draw(Graphics &graphics);

	void update(float elapsedtime);

	std::vector<std::shared_ptr<AnimatedSprite>> _spritesToDraw;

	std::vector<std::shared_ptr<HUDElement>> _hudElements;

	std::vector<SectorBackground> _sectorsBackgrounds;

	Player _player;
	std::shared_ptr<AnimatedSprite> _sharedPtrPlayer;

	VacuumCleaner _vaccumcleaner;
	std::shared_ptr<AnimatedSprite> _sharedPtrVaccumCleaner;
	std::shared_ptr<AnimatedSprite> _sharedPtrVaccumCone;


	KeyboardInput _keyboardInput;

	GamepadInput _gamepadInputPlayer1;

	GamepadInput _gamepadInputPlayer2;

	std::vector<BackgroundBlock> _backgroundBlocks;

	int _mapWidth, _mapHeight;

	int _numberBlocksLine, _numberBlocksColumn;

	bool _quitFlag;

	BackgroundSectorLibraryHandler _backgroundSectorHandler;

	Graphics* _graphicsAssociated;

	std::stack<std::shared_ptr<Menu>> _menuStack;

	Menu* _menuToReplaceInStack;

	bool _showFpsFlag;
	int _fps;

	bool _vSyncFlag;
	float _minFrameTime;

	TextCaches _textCaches;

	Musics musics;
	Musics sounds;

	FullMapBackground _mapBackground;
	bool _mapBackgroundFlag;

	bool _hubFlag;

};



#endif /* SOURCE_HEADERS_GAME_H_ */
