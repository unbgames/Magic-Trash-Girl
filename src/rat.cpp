/*
 * rat.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#include <rat.h>
#include "game.h"

Rat::Rat(Graphics &graphics, float posX, float posY):
				Enemy(graphics, "assets/rat.png", enemy_constants::RAT_WIDTH, enemy_constants::RAT_HEIGHT, posX, posY, 300, enemy_constants::RAT_HP),
				_stuckInBubble(false),
				_storedDxBubble(0),
				_storedDyBubble(0),
				_bubbleTimer(0),
				_storedDxColision(0),
				_storedDyColision(0),
				_takingDamageFromPlayerVaccum(false),
				_isAirborne(false),
				_facing(RIGHT)
				{
				this->setupAnimations();
				this->playAnimation("IDLE");
				//tirar esse set, esta aqui somente pra testes
				this->_dx = -0.1f;
}

Rat::~Rat(){

}

void Rat::update(float elapsedTime){

	bool changeDirections = false;

	if(this->_takingDamageFromPlayerVaccum){
		this->_hp -= (elapsedTime/1000) * Game::getInstance().getPlayerVaccumDps();
		this->_takingDamageFromPlayerVaccum = false;
	}

	if(this->_stuckInBubble){
		_bubbleTimer += elapsedTime;
		if(_bubbleTimer > 3000){
			this->freeFromBubble();
		}
	}else{

		if(this->_isAirborne){
			this->_dy += globals::FALL_ACELERATION * elapsedTime;
			this->_dy = std::min(this->_dy , globals::MAX_FALL_SPEED);
		}

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
						this->_storedDxColision = _dx;
						this->_dx = 0;
						changeDirections = true;
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
					this->_storedDxColision = _dx;
					this->_dx = 0;
					changeDirections = true;
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

		this->_x += this->_dx * elapsedTime;
		this->_y += this->_dy * elapsedTime;

		/*
		 * correção caso haja colisão;
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

				//essas correçoes não sao perfeitas, arrumar depois

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
					//std::cout << "rat top correction" << std::endl;
					noColision = false;
					this->_y ++;
				}
				if(correctBot){ //bot
					//std::cout << "rat bot correction" << std::endl;
					checkAirborne = true;
					noColision = false;
					this->_y --;
				}
				if(correctLeft){ //left
					//std::cout << "rat left correction" << std::endl;
					noColision = false;
					this->_x ++;
				}
				if(correctRight){ //right
					//std::cout << "rat right correction" << std::endl;
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
			this->setToBeDeleted(true);
			return;
		}

		/*
		 * termino da correção
		 */
	}

	if(this->_hp < 0){
		this->setToBeDeleted(true);
	}

	if(this->_dx > 0){
		this->_facing = RIGHT;
		this->playAnimation("MovingRight");
	}else if(this->_dx < 0){
		this->_facing = LEFT;
		this->playAnimation("MovingLeft");
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

	if(((Game::getInstance().getBlockType(auxCheckAirborne[0].x, auxCheckAirborne[0].y)) == NONE) && ((Game::getInstance().getBlockType(auxCheckAirborne[1].x, auxCheckAirborne[1].y)) != NONE)){
		if(this->_dx < 0){
			this->_dx = this->_dx * -1;
		}
	}

	if(((Game::getInstance().getBlockType(auxCheckAirborne[0].x, auxCheckAirborne[0].y)) != NONE) && ((Game::getInstance().getBlockType(auxCheckAirborne[1].x, auxCheckAirborne[1].y)) == NONE)){
		if(this->_dx > 0){
			this->_dx = this->_dx * -1;
		}
	}


	if(changeDirections){
		if(this->_storedDxColision < 0){
			this->_dx = this->_storedDxColision * -1;
		}else if(this->_storedDxColision > 0){
			this->_dx = this->_storedDxColision * -1;
		}
		this->_storedDxColision = 0;
	}

	AnimatedSprite::update(elapsedTime);
}

std::string Rat::getEnemyType(){
	return "Rat";
}

void Rat::resolveColision(std::string objectType){

	if(objectType == "PlayerProjectile"){
		this->encaseInBubble();
	}else if(objectType == "VacuumCone"){
		if(this->_stuckInBubble){
			this->_takingDamageFromPlayerVaccum = true;
		}
	}

}

void Rat::encaseInBubble(){
	if(!this->_stuckInBubble){
		this->_storedDxBubble = this->_dx;
		this->_storedDyBubble = this->_dy;
		this->_dx = 0;
		this->_dy = 0;
		this->_stuckInBubble = true;
		if(this->_facing == RIGHT){
			this->playAnimation("StuckInBubbleRight");
		}
		if(this->_facing == LEFT){
			this->playAnimation("StuckInBubbleLeft");
		}
	}
}

void Rat::freeFromBubble(){
	this->_dx = this->_storedDxBubble;
	this->_dy = this->_storedDyBubble;
	this->_storedDxBubble = 0;
	this->_storedDyBubble = 0;
	this->_stuckInBubble = false;
	this->playAnimation("IDLE");
	this->_bubbleTimer = 0;
}

void Rat::setupAnimations(){

	this->addAnimation(1, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(1, 0, this->_h, "StuckInBubbleRight", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(1, 0, this->_h, "StuckInBubbleLeft", this->_w, this->_h, Vector2(0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(1, 0, 0, "MovingRight", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(1, 0, 0, "MovingLeft", this->_w, this->_h, Vector2(0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));

}
