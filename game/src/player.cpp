/*
 * player.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#include "player.h"
#include "graphics.h"
#include <iostream>
#include "game.h"
#include "playerprojectile.h"
#include "config.h"

int Player::playercount = 0;

Player::Player(){ // @suppress("Class members should be properly initialized")

}

Player::Player(Graphics &graphics, float posX, float posY):
		AnimatedSprite(graphics, ASSETS_PATH("/playerchanged.png"), 0, 0, player_constants::PLAYER_WIDTH, player_constants::PLAYER_HEIGTH, posX, posY, 300),
		_facing(RIGHT),
		_idleFacing(RIGHT),
		_isAirborne(false),
		_isSwiming(false),
		_startJump(false),
		_invulnerable(false),
		_invulnerableTimer(0),
		_invulnerableBlinkTimer(0),
		_hp(4){

		playercount++;

		// Karen
		sAndando 	= new Sound (sound_paths::K_ANDANDO, (unsigned int) 19);
		sDano 		= new Sound (sound_paths::K_DANO, (unsigned int) 20);
		sMergulho 	= new Sound (sound_paths::K_MERGULHO, (unsigned int) 21);
		sMorreu 	= new Sound (sound_paths::K_MORREU, (unsigned int) 22);
		sPulo		= new Sound (sound_paths::K_PULO, (unsigned int) 23);


		if (sAndando == nullptr) 		printf ("Não foi possível carregar o som em %s\n", sound_paths::K_ANDANDO.c_str());
		if (sDano== nullptr) 			printf ("Não foi possível carregar o som em %s\n", sound_paths::K_DANO.c_str());
		if (sMergulho== nullptr) 		printf ("Não foi possível carregar o som em %s\n", sound_paths::K_MERGULHO.c_str());
		if (sMorreu == nullptr) 		printf ("Não foi possível carregar o som em %s\n", sound_paths::K_MORREU.c_str());
		if (sPulo== nullptr) 			printf ("Não foi possível carregar o som em %s\n", sound_paths::K_PULO.c_str());

		//std::cout << playercount << std::endl;

		this->setupAnimations();
		this->playAnimation("IdleRight");
}


Player::~Player(){

}

void Player::animationDone(std::string currentAnimation){

}

void Player::setupAnimations(){
	this->addAnimation(8, 0, 0, "IdleRight", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(8, 0, 0, "IdleLeft", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(5, 0, player_constants::PLAYER_HEIGTH, "MoveRight", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(5, 0, player_constants::PLAYER_HEIGTH, "MoveLeft", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(8, 0, 0, "LookUp", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(8, 0, 0, "LookDown", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(3, 0, player_constants::PLAYER_HEIGTH*2, "Jump", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(5, player_constants::PLAYER_WIDTH*3, player_constants::PLAYER_HEIGTH*2, "FallingRight", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(5, player_constants::PLAYER_WIDTH*3, player_constants::PLAYER_HEIGTH*2, "FallingLeft", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(5, 0, player_constants::PLAYER_HEIGTH, "SwimRight", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0));
	this->addAnimation(5, 0, player_constants::PLAYER_HEIGTH, "SwimLeft", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(8, 0, 0, "SwimUp", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0),ExVariables(270, nullptr, SDL_FLIP_NONE));
	this->addAnimation(8, 0, 0, "SwimDown", player_constants::PLAYER_WIDTH,player_constants::PLAYER_HEIGTH, Vector2 (0,0), ExVariables(90, nullptr, SDL_FLIP_NONE));

}

void Player::moveLeft(){
		if (!this->_isAirborne && !this->_isSwiming && !sAndando->IsPlaying()) sAndando->Play(1);
		this->_facing = LEFT;
		this->_idleFacing = LEFT;
		this->_dx = -player_constants::WALK_SPEED;
		if(this->_isSwiming){
			this->playAnimation("SwimLeft");
		}else{
			this->playAnimation("MoveLeft");
		}
}

void Player::moveRight(){
		if (!this->_isAirborne && !this->_isSwiming && !sAndando->IsPlaying()) sAndando->Play(1);
		this->_facing = RIGHT;
		this->_idleFacing = RIGHT;
		this->_dx = player_constants::WALK_SPEED;
		if(this->_isSwiming){
			this->playAnimation("SwimRight");
		}else{
			this->playAnimation("MoveRight");
		}
}

void Player::stopMoving(){
		sAndando->Stop();
		this->_dx = 0.0f;
		if((this->_facing == UP) || (this->_facing == DOWN)){
			this->_facing = this->_idleFacing;
		}
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::jump(){
	if(!this->_isAirborne){
		sPulo->Play(1);
		//this->playAnimation("Jump", true);

		if(this->_isSwiming){
			this->_dy = player_constants::WATER_JUMP_SPEED;
			return;
		}

		Vector2 auxCheckBuble[2];

		auxCheckBuble[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
		auxCheckBuble[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

		if(((Game::getInstance().getBlockType(auxCheckBuble[0].x, auxCheckBuble[0].y)) == BUBLE) || ((Game::getInstance().getBlockType(auxCheckBuble[1].x, auxCheckBuble[1].y)) == BUBLE)){
			this->_dy = player_constants::BUBLE_JUMP_SPEED;
		//	std::cout << "BUBLE JUMP" << std::endl;
		}else{
			this->_dy = player_constants::NORMAL_JUMP_SPEED;
		}

	}
}

void Player::lookUp(){

		if(!this->_isSwiming){
			this->_dx = 0.0f;
		}

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = UP;
		this->playAnimation("LookUp");
}

void Player::lookDown(){

		if(!this->_isSwiming){
			this->_dx = 0.0f;
		}

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = DOWN;
		this->playAnimation("LookDown");
}

void Player::takeContextAction(std::string objectType){

}


void Player::update(float elapsedTime){


//	std::cout << "Player update, hp : " << this->_hp << "    invulnerable flag: " << this->_invulnerable << "  instance: " << this << std::endl;

	if(this->_invulnerable){
		this->_invulnerableTimer += elapsedTime;
		this->_invulnerableBlinkTimer += elapsedTime;
		if(this->_invulnerableBlinkTimer >= player_constants::INVULNERABILITY_BLINK_TIME){
			this->setVisible(!this->getVisible());
			this->_invulnerableBlinkTimer = 0;
		}
		if(this->_invulnerableTimer >= player_constants::INVULNERABILITY_TIME){
			this->_invulnerableTimer = 0;
			this->_invulnerable = false;
			this->_invulnerableBlinkTimer = 0;
			this->setVisible(true);
		}
	}

	if(this->_isAirborne){

	//	if(this->_currentAnimation != "Jump"){
				if(this->_facing == RIGHT){
					this->playAnimation("FallingRight");
				}else if(this->_facing == LEFT){
					this->playAnimation("FallingLeft");
				}


		//}

		this->_dy += player_constants::FALL_ACELERATION * elapsedTime;
		this->_dy = std::min(this->_dy , player_constants::MAX_FALL_SPEED);
	}

	/*
	 * check de estado de airborne
	 */

	Vector2 auxCheckAirborne[2];

	auxCheckAirborne[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
	auxCheckAirborne[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

	if(((Game::getInstance().getBlockType(auxCheckAirborne[0].x, auxCheckAirborne[0].y)) == NONE) && ((Game::getInstance().getBlockType(auxCheckAirborne[1].x, auxCheckAirborne[1].y)) == NONE)){
		this->_isAirborne = true;
	}

	/*
	 * check de estado de swiming
	 */

	Vector2 auxCheckSwiming[2];

	auxCheckSwiming[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
	auxCheckSwiming[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

	if(((Game::getInstance().getBlockType(auxCheckSwiming[0].x, auxCheckSwiming[0].y)) == WATER) && ((Game::getInstance().getBlockType(auxCheckSwiming[1].x, auxCheckSwiming[1].y)) == WATER)){
		if(!this->_isSwiming){
			this->_isSwiming = true;
			this->_isAirborne = false;

			if(this->_dy < 0){
				this->_dy = std::max(this->_dy , -player_constants::MAX_FALL_SPEED_ON_WATER);
			}else if(this->_dy > 0){
				this->_dy = std::min(this->_dy , player_constants::MAX_FALL_SPEED_ON_WATER);
			}
		}

		this->_dy += (player_constants::FALL_ACELERATION_IN_WATER) * elapsedTime;

	}else{
		if(this->_isSwiming && (this->_isAirborne == true)){
			this->_dy = player_constants::NORMAL_JUMP_SPEED;
		}
		this->_isSwiming = false;
	}

	this->_checkBackgroundColision(elapsedTime);

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	this->_correctionBackgroundColision();

	/*
	 * update da camera
	 */
	if(this->_graphicsAssociated->camera.folowPlayer){
		this->_graphicsAssociated->camera.smoothSetX(this->_x + this->_w/2 - this->_graphicsAssociated->windowWidth/2);
		this->_graphicsAssociated->camera.smoothSetY(this->_y + this->_h/2 - this->_graphicsAssociated->windowHeight/2);
	}

	AnimatedSprite::update(elapsedTime);
}

void Player::_checkBackgroundColision(float elapsedTime){

	/*
	 * check de colision
	 */

	int pixelsToCheckVertical = (int)(this->_y + (this->_dy * elapsedTime)) - (int)this->_y ;
	int pixelsToCheckHorizontal = (int)(this->_x + (this->_dx * elapsedTime)) - (int)this->_x ;

	Vector2 auxCheckColision[4];

	float fauxX = 0;
	int auxY = 0;
	int auxX = 0;
	float auxXncI = 0;
	bool foundVerticalColision = false;
	bool foundHorizontalColision = false;
	if(!(pixelsToCheckVertical < 1)){
		auxXncI = (float)pixelsToCheckHorizontal/(float)std::abs(pixelsToCheckVertical);
	}

	if(pixelsToCheckVertical != 0 && pixelsToCheckHorizontal != 0){
		for(int j = 1; j <= std::abs(pixelsToCheckVertical) ;j++){

			fauxX += auxXncI;
			auxY = (pixelsToCheckVertical > 0) ? j : j*-1;
			auxX = (int)fauxX;

			auxCheckColision[0] = Vector2((int)(((this->_x-1 + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y -1 + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[1] = Vector2((int)(((this->_x + this->_w + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y - 1 + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[2] = Vector2((int)(((this->_x-1 + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[3] = Vector2((int)((this->_x + this->_w + auxX)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h + auxY)/background_blocks_constants::BLOCK_HEIGTH));

			/*
			 * 0 = top left
			 * 1 = top right
			 * 2 = bot left
			 * 3 = bot right
			 */

			/*
			 * check de colision com movimento horizontal;
			 */

			if((this->_dx > 0)
				&& ((((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != WATER)) || (((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != NONE)))){
				foundHorizontalColision = true;

				fauxX -= auxXncI;
				auxX = (int)fauxX;

				this->_x += auxX;
			}
			if((this->_dx < 0)
				&& ((((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != WATER)) || (((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != NONE)))){
				foundHorizontalColision = true;

				fauxX -= auxXncI;
				auxX = (int)fauxX;

				this->_x += auxX;
			}
			if((this->_dy > 0)
				&& ((((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != WATER)) || (((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != NONE)))){
				foundVerticalColision = true;

				this->_y += auxY - 1;
			}
			if((this->_dy < 0)
				&& ((((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != WATER)) || (((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != NONE)))){
				foundVerticalColision = true;

				this->_y += auxY + 1;
			}
			if(foundHorizontalColision || foundVerticalColision){
				break;
			}
		}

	}

	/*
	 * check de colision para a direita
	 */

	if(pixelsToCheckHorizontal > 0){
			for(int i = 1; i <= pixelsToCheckHorizontal ; i++){

				Vector2 auxCheckRightColision[2];

				auxCheckRightColision[0] = Vector2((int)(((this->_x + this->_w - 1 + i)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
				auxCheckRightColision[1] = Vector2((int)((this->_x + this->_w - 1 + i)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y)/background_blocks_constants::BLOCK_HEIGTH));

				if((((Game::getInstance().getBlockType(auxCheckRightColision[0].x, auxCheckRightColision[0].y)) != NONE) && (Game::getInstance().getBlockType(auxCheckRightColision[0].x, auxCheckRightColision[0].y)) != WATER)
					|| (((Game::getInstance().getBlockType(auxCheckRightColision[1].x, auxCheckRightColision[1].y)) != NONE) && (Game::getInstance().getBlockType(auxCheckRightColision[1].x, auxCheckRightColision[1].y)) != WATER)){
				this->_x += i - 1;
					this->_dx = 0;
					break;

				}
			}
		}

	/*
	 * check de colision para a esquerda
	 */

	if(pixelsToCheckHorizontal < 0){
		for(int i = -1; i >= pixelsToCheckHorizontal ; i--){

			Vector2 auxCheckLeftColision[2];

			auxCheckLeftColision[0] = Vector2((int)(((this->_x + i)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckLeftColision[1] = Vector2((int)((this->_x + i)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y)/background_blocks_constants::BLOCK_HEIGTH));

			if((((Game::getInstance().getBlockType(auxCheckLeftColision[0].x, auxCheckLeftColision[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckLeftColision[0].x, auxCheckLeftColision[0].y)) != WATER))
					|| (((Game::getInstance().getBlockType(auxCheckLeftColision[1].x, auxCheckLeftColision[1].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckLeftColision[1].x, auxCheckLeftColision[1].y)) != NONE))){
				this->_x += i + 1;
				this->_dx = 0;
				break;
			}
		}
	}

	/*
	 * check de colision para cima
	 */

	if(pixelsToCheckVertical < 0){
		for(int i = -1; i >= pixelsToCheckVertical ; i--){

			Vector2 auxCheckUpColision[2];

			auxCheckUpColision[0] = Vector2((int)(((this->_x)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + i)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckUpColision[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y + i)/background_blocks_constants::BLOCK_HEIGTH));

			if((((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != WATER))
			|| (((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != NONE))){

				this->_y += i + 1;
				this->_dy = 0;
				break;
			}
		}
	}

	/*
	 * check de colision para baixo
	 */

	if(pixelsToCheckVertical > 0){
		for(int i = 1; i <= pixelsToCheckVertical ; i++){

			Vector2 auxCheckUpColision[2];

			auxCheckUpColision[0] = Vector2((int)(((this->_x)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + this->_h + i)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckUpColision[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y + this->_h + i)/background_blocks_constants::BLOCK_HEIGTH));

			if((((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != WATER))
			|| (((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != WATER) && ((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != NONE))){

				this->_isAirborne = false;
				this->_y += i;
				this->_dy = 0;
				break;

			}
		}
	}
}

void Player::_correctionBackgroundColision(){

	/*
	 * corre��o caso haja colis�o;
	 */

	bool noColision = true;
	int framesInColision = 0;
	bool checkAirborne = false;

	do{
		noColision = true;
		Vector2 auxColision[4];

		/*
		 * 0 = top left
		 * 1 = top right
		 * 2 = bot left
		 * 3 = bot right
		 */

		auxColision[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[1] = Vector2((int)(((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[2] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[3] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));

		bool colisionArray[4] = {false,false,false,false};

		for(int i = 0; i < 4; i++){
			if(((Game::getInstance().getBlockType(auxColision[i].x, auxColision[i].y)) != NONE) && ((Game::getInstance().getBlockType(auxColision[i].x, auxColision[i].y)) != WATER)){

				colisionArray[i] = true;

			}
			bool correctTop = false;
			bool correctBot = false;
			bool correctRight = false;
			bool correctLeft = false;

			//essas corre�oes n�o sao perfeitas, arrumar depois

			if(colisionArray[0]){ //top left colision
				//std::cout << "0 correction" << std::endl;
				noColision = false;
				correctTop = true;
				correctLeft = true;
			}
			if(colisionArray[1]){ //top right colision
				//std::cout << "1 correction" << std::endl;
				noColision = false;
				correctTop = true;
				correctRight = true;
			}
			if(colisionArray[2]){ //bot left colision
				//std::cout << "2 correction" << std::endl;
				noColision = false;
				correctBot = true;
				correctLeft = true;
			}
			if(colisionArray[3]){ //bot right colision
				//std::cout << "3 correction" << std::endl;
				noColision = false;
				correctBot = true;
				correctRight = true;
			}

			if(correctTop){ //top
				std::cout << "top correction" << std::endl;
				noColision = false;
				this->_y ++;
			}
			if(correctBot){ //bot
				std::cout << "bot correction" << std::endl;
				checkAirborne = true;
				noColision = false;
				this->_y --;
			}
			if(correctLeft){ //left
				std::cout << "left correction" << std::endl;
				noColision = false;
				this->_x ++;
			}
			if(correctRight){ //right
				std::cout << "right correction" << std::endl;
				noColision = false;
				this->_x --;
			}

		}

		if(!noColision){
			framesInColision++;
		}else{
			framesInColision = 0;
			if(checkAirborne){
				this->_isAirborne = false;
			}
		}
	}while(!noColision && framesInColision < 1000);

	if(framesInColision >= 1000){
		std::cout << "game deu crash, player nao conseguiu achar local sem colisao em 1000 tentativas";
		Game::getInstance().requestQuit();
		return;
	}

	/*
	 * termino da corre��o
	 */
}


void Player::setPosition(float x, float y){

	this->_x = x;
	this->_y = y;

	if(this->_graphicsAssociated->camera.folowPlayer){
		this->_graphicsAssociated->camera.hardSetX(this->_x + this->_w/2 - this->_graphicsAssociated->windowWidth/2);
		this->_graphicsAssociated->camera.hardSetY(this->_y + this->_h/2 - this->_graphicsAssociated->windowHeight/2);
	}

}

void Player::draw(Graphics &graphics){
	AnimatedSprite::draw(graphics);
}

void Player::setTimeForFrames(double newTime){
	this->_timeToUpdate = newTime;
}
double Player::getTimeForFrames(){
	return this->_timeToUpdate;
}

std::string Player::getObjectType(){
	return "Player";
}

Direction Player::getFacing(){
	return this->_facing;
}

bool Player::getIsSwiming(){
	return this->_isSwiming;
}

void Player::resolveColision(std::string objectType){

	if(objectType == "Enemy"){
		if(this->_invulnerable == false){
			sDano->Play(1);
			this->_invulnerable = true;
			this->setVisible(false);
			this->_hp --;
			if (this->_hp ==0) sMorreu->Play(1);
//			std::cout << "Player resolve colision, hp : " << this->_hp << "    invulnerable flag: " << this->_invulnerable << "  instance: " << this << std::endl;
		}
	}

}

int Player::getHp(){
	return this->_hp;
}

void Player::setHp(int hp){
	this->_hp = hp;
}
