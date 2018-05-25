/*
 * backgroundsectorhandler.cpp
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#include "BackgroundSectorHandler.h"
#include <ctime>

BackgroundSectorHandler::BackgroundSectorHandler(){

	srand(time(NULL));

	std::vector<BlockType> aux;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j ++){
			if(i == 0 || i == 7 || j == 0 || j == 7){
				aux.push_back(BREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	this->_sectorLibrary.push_back(aux);

	aux.clear();

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j ++){
			if(i == 0 || i == 7 || j == 0 || j == 7){
				aux.push_back(NONE);
			}else{
				aux.push_back(BREAKABLE);
			}
		}
	}

	this->_sectorLibrary.push_back(aux);

	aux.clear();

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j ++){
			if(i == 0 || i == 7 || j == 0 || j == 7){
				aux.push_back(BREAKABLE);
			}else{
				aux.push_back(UNBREAKABLE);
			}
		}
	}

	this->_sectorLibrary.push_back(aux);

}

std::vector<BlockType> BackgroundSectorHandler::getRandomSector(){

	int randomIndex = rand() % this->_sectorLibrary.size();

	return this->_sectorLibrary[randomIndex];
}
