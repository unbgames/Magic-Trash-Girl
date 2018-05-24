/*
 * backgroundsectorhandler.cpp
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#include "BackgroundSectorHandler.h"

BackgroundSectorHandler::BackgroundSectorHandler(){
	std::vector<BlockType> aux;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j ++){
			if(i == 0 || i == 7 || j == 0 || j == 8){
				aux.push_back(BREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	this->_sectorLibrary.push_back(aux);
}

std::vector<BlockType> BackgroundSectorHandler::getRandomSector(){
	/*
	 * joguei uma moeda, cara era 0, coroa era 1, deu cara, função devidamente randomica
	 */
	return this->_sectorLibrary[0];
}
