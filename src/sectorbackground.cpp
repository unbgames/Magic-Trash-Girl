/*
 * sectorbackground.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#include "sectorbackground.h"

SectorBackground::SectorBackground(){

}

SectorBackground::SectorBackground(Graphics &graphics, std::string filepath, float posX, float posY):
		AnimatedSprite(graphics, filepath, 0, 0, background_blocks_constants::BLOCK_WIDTH * background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS, background_blocks_constants::BLOCK_HEIGTH * background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS, posX, posY, 300)
		{

		this->setupAnimations();
		this->playAnimation("IDLE");

}

SectorBackground::~SectorBackground(){

}

void SectorBackground::setupAnimations(){

	this->addAnimation(1, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));

}

std::string SectorBackground::getObjectType(){
	return "SectorBackground";
}
