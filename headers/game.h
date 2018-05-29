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
#include "animatedsprite.h"
#include <vector>
#include "player.h"
#include "menubackground.h"
#include <memory>
#include "backgroundblock.h"
#include "gamepadinput.h"
#include <stack>
#include "menu.h"


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

	void requestQuit();

	void createNewPseudoRandomBlocksVector(int sectorsByLine, int sectorsByColumn);

	int getCurrentNumberBlocksLine();

	int getCurrentNumberBlocksColumn();

	int setMenuToReplaceInStack();

private:

	static Game* _instance;

	void gameLoop();

	void draw(Graphics &graphics);

	void update(float elapsedtime);

	std::vector<std::unique_ptr<AnimatedSprite>> _spritesToDraw;

	Player _player;

	KeyboardInput _keyboardInput;

	GamepadInput _gamepadInput;

	std::vector<BackgroundBlock> _backgroundBlocks;

	int _numberBlocksLine, _numberBlocksColumn;

	bool _quitFlag;

	BackgroundSectorLibraryHandler _backgroundSectorHandler;

	Graphics* _graphicsAssociated;

	std::stack<std::unique_ptr<Menu>> _menuStack;

	Menu* _menuToReplaceInStack;

};



#endif /* SOURCE_HEADERS_GAME_H_ */
