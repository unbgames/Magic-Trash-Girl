/*
 * globlas.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */
// Canais:

//Músicas:
// Menu:
// 0- Intro
// 1- Granola

// HUB
// 2- HUB

// FASE
// 3- Aventura Subterranea
// 4- Aventura Subterranea na água

// BOSS
// 5- BOSS INTRO
// 6- BOSS
// 7- VICTORY


//SFX:
// 16 - Aspirador On
// 17 - Aspirador Off
// 18 - Aspirador Loop

// 19 - Karen Andando
// 20 - Karen Dano
// 21 - Karen Mergulho		(a implementar)
// 22 - Karen Morreu
// 23 - Karen Pulo

// 24 - HUD click

//


#ifndef SOURCE_HEADERS_GLOBALS_H_
#define SOURCE_HEADERS_GLOBALS_H_

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_ttf.h>

#define CHUNKSIZE 256

namespace player_constants {
	const float WALK_SPEED = 0.4f;
	const float NORMAL_JUMP_SPEED = -0.8f;
	const float BUBLE_JUMP_SPEED = -1.2f;
	const float WATER_JUMP_SPEED =  -0.2f;
	const float FALL_ACELERATION = 0.002f;
	const float FALL_ACELERATION_IN_WATER = 0.0002f;
	const float MAX_FALL_SPEED_ON_WATER = 0.3f;
	const float MAX_FALL_SPEED = 1.2f;

	const float PLAYER_START_X = 130;
	const float PLAYER_START_Y = 72;

	const float PROJECTILE_SPEED = 0.8f;

	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGTH = 48;

	const int CONE_WIDTH = 32;
	const int CONE_HEIGTH = 32;

	const int INVULNERABILITY_TIME = 2000;
	const int INVULNERABILITY_BLINK_TIME = 100;
}

namespace vacuum_constants{
	const int VACUUM_WIDTH = 48;
	const int VACUUM_HEIGTH = 24;

	const float FLOAT_SPEED = 0.4f;
}

namespace globals{
	const int INITIAL_SCREEN_WIDTH = 1024;
	const int INITIAL_SCREEN_HEIGTH = 576;

	const std::string WINDOW_NAME = "Trash Girl";

	const float SMOOTH_CAMERA_VELOCITY = 0.3f;
	const float SMOOTH_CAMERA_TIMER_MAX = 200;

	const float FALL_ACELERATION = 0.002f;
	const float MAX_FALL_SPEED = 1.2f;
}

namespace background_blocks_constants {
	const int BLOCK_WIDTH = 64;
	const int BLOCK_HEIGTH = 64;

	const int INITIAL_NUMBER_BLOCKS_LINE = 34; //globals::SCREEN_WIDTH / BLOCK_WIDTH;
	const int INITIAL_NUMBER_BLOCKS_COLUMN = 34 ;//globals::SCREEN_HEIGTH / BLOCK_HEIGTH;

	const int NUMBER_BLOCKS_LINE_SECTORS = 16;
	const int NUMBER_BLOCKS_COLUMN_SECTORS = 16;

	const int NUMBER_SECTORS_LINE = 8;
	const int NUMBER_SECTORS_COLUMN = 8;

	const int BLOCK_BORDER_TOP_BOT_SIZE = BLOCK_WIDTH/4;
	const int BLOCK_BORDER_RIGHT_LEFT_SIZE = BLOCK_HEIGTH/4;
}

namespace enemy_constants {
	const int SOUNDMAXDIST = 512;

	const int SPYDER_WIDTH = 48;
	const int SPYDER_HEIGHT = 32;
	const int SPIDER_HP = 100;

	const int BOSS_WIDTH = 144;
	const int BOSS_HEIGHT = 144;
	const int BOSS_HP = 1000;
}

enum Direction{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum BlockType{
	NONE,
	BREAKABLE,
	UNBREAKABLE,
	BUBLE,
	WATER,
	OUTOFBONDS
};

enum MapObjectType{
	PLAYER_START_POSITION, 		// 0
	PORTAL_TO_NEXT_RANDOM_LEVEL,// 1
	RAT, 					// 2

};

struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y):
		x(x), y(y)
	{}
	Vector2 zero(){
		return Vector2(0, 0);
	}
};

struct ExVariables{
	double angle;
	SDL_Point* centerOfRotation;
	SDL_RendererFlip flipFlag;

	ExVariables() :
		angle(0),
		centerOfRotation(nullptr),
		flipFlag(SDL_FLIP_NONE)
	{}

	ExVariables(double angleIn, SDL_Point* centerIn, SDL_RendererFlip flipIn) :
		angle(angleIn),
		centerOfRotation(centerIn),
		flipFlag(flipIn)
	{}

};

enum xbox360GamepadMaping{
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	directionalUp = 11,
	directionalDown = 12,
	directionalRight = 14,
	directionalLeft = 13,
	start = 6
};

namespace music_paths{
	const std::string MUSICA = "assets/MUSICA/";

	const std::string MENU 			= MUSICA + "0_menu/";
	const std::string MENU_INTRO 	= MENU + "1_intro.wav";
	const std::string MENU_GRANOLA 	= MENU + "2_granola.wav";

	const std::string HUB_PATH 		= MUSICA + "1_hub/";
	const std::string HUB 			= HUB_PATH + "hub.wav";

	const std::string FASE 			= MUSICA + "2_fase/";
	const std::string AVSUB 		= FASE + "avsub.wav";
	const std::string AVSUB_W 		= FASE + "avsub_w.wav";

	const std::string BOSS_PATH 	= MUSICA +"3_boss/";
	const std::string BOSS_INTRO 	= BOSS_PATH + "boss_intro.wav";
	const std::string BOSS 			= BOSS_PATH + "boss.wav";
	const std::string VICTORY	 	= BOSS_PATH + "victory_theme.wav";
}

namespace sound_paths{
	const std::string SFX 		= "assets/SFX/";
	const std::string PORTA 	= SFX + "porta.wav";

	const std::string ASPIRADOR	= SFX + "Aspirador/";
	const std::string A_ON		= ASPIRADOR + "on.wav";
	const std::string A_OFF		= ASPIRADOR + "off.wav";
	const std::string A_LOOP	= ASPIRADOR + "loop.wav";

	const std::string HUD_PATH	= SFX + "HUD/";
	const std::string HUD		= HUD_PATH + "clique.wav";

	const std::string KAREN		= SFX + "Karen/";
	const std::string K_ANDANDO = KAREN + "andando.wav";
	const std::string K_DANO 	= KAREN + "dano.wav";
	const std::string K_MERGULHO= KAREN + "mergulho.wav";
	const std::string K_MORREU	= KAREN + "morreu.wav";
	const std::string K_PULO	= KAREN + "pulo.wav";

	const std::string MOSCA		= SFX + "Mosca/";

	const std::string RATO_PATH	= SFX + "Rato/";
	const std::string RATO		= RATO_PATH + "rato.wav";
	const std::string RATO_MORTE= RATO_PATH + "rato_morte.wav";



}

namespace sound_constants{
	const int MAXSOUNDVOLUME = 128;
}

enum FadeTypes{
	LINEAR,
	SQUARE,
	EXPONENTIAL,
	INVERSESQUARE,			// A/((R+B)^2);
};

namespace music_constants{
	const FadeTypes STDFADE = SQUARE;

	const float EXP_CONST = 1000;

	const float MAXDEPTH	 = 128; 	// profundidade a partir da qual a musica n�o muda mais
	const float MAXVOLUME	 = 128;
	const float MINVOLUME	 = 0.99; 	// n�o podemos dividir por 0 n�o � mesmo?
}

#endif /* SOURCE_HEADERS_GLOBALS_H_ */
