/*
 * backgroundsectorhandler.cpp
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#include <backgroundsectorlibraryhandler.h>

BackgroundSectorLibraryHandler::BackgroundSectorLibraryHandler(){

	std::vector<BlockType> aux;
	unsigned int auxFlags;

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(i == 0 || i == background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS - 1){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	auxFlags = (W_LEFT_RIGHT | W_RIGHT_LEFT);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(j == 0 || j == background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS-1){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	auxFlags = (W_TOP_BOT | W_BOT_TOP);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(i == j){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	auxFlags = (W_TOP_RIGHT | W_BOT_LEFT | W_RIGHT_TOP | W_LEFT_BOT);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(i + j == background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS-1){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	auxFlags = (W_TOP_LEFT | W_BOT_RIGHT | W_LEFT_TOP | W_RIGHT_BOT);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){

			if((i%2 == 0) && (j%2 == 0)){
				aux.push_back(BREAKABLE);
			}else{
				aux.push_back(NONE);
			}
		}
	}

	auxFlags = (0);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){

			if(j == 0 || j == background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS-1){
				aux.push_back(UNBREAKABLE);
			}else if(i == 0){
				aux.push_back(NONE);
			}else if(i == background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS - 1){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(WATER);
			}
		}
	}

	auxFlags = (0);

	this->_fillerSectorLibrary.push_back(BlockSector(aux, auxFlags));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(i == 4 || j == 5){
				aux.push_back(NONE);
			}else{
				aux.push_back(BREAKABLE);
			}
		}
	}

	auxFlags = (-1);

	this->_startSectorLibrary.push_back(BlockSector(aux, auxFlags, Vector2(4*background_blocks_constants::BLOCK_HEIGTH, 4*background_blocks_constants::BLOCK_WIDTH)));

	aux.clear();

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			if(i == 4 && j == 4){
				aux.push_back(NONE);
			}else if(i == 5 && j == 4){
				aux.push_back(UNBREAKABLE);
			}else{
				aux.push_back(BREAKABLE);
			}
		}
	}

	auxFlags = (-1);

	this->_finishSectorLibrary.push_back(BlockSector(aux, auxFlags, Vector2(4*64, 4*64)));

	this->_finishSectorLibrary.back().objectsToBuildVector.push_back(MapObjectBlueprint(PORTAL_TO_NEXT_RANDOM_LEVEL, Vector2(4*64, 4*64)));

}

BlockSector BackgroundSectorLibraryHandler::getRandomFillerSector(unsigned int flags){

	int randomIndex = rand() % this->_fillerSectorLibrary.size();

	for(int i = randomIndex ; i < (int)this->_fillerSectorLibrary.size() ; i ++){
		if((this->_fillerSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_fillerSectorLibrary[i];
		}
	}
	for(int i = randomIndex-1 ; i >= 0 ; i --){
		if((this->_fillerSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_fillerSectorLibrary[i];
		}
	}

	std::cout << "error nenhum setor com as configuraçoes encontradas, colocando setor nulo no local" << std::endl;

	std::vector<BlockType> aux;

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			aux.push_back(NONE);
		}
	}

	return BlockSector(aux, 0);
}

BlockSector BackgroundSectorLibraryHandler::getRandomStartSector(unsigned int flags){

	int randomIndex = rand() % this->_startSectorLibrary.size();

	for(int i = randomIndex ; i < (int)this->_startSectorLibrary.size() ; i ++){
		if((this->_startSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_startSectorLibrary[i];
		}
	}
	for(int i = randomIndex-1 ; i >= 0 ; i --){
		if((this->_startSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_startSectorLibrary[i];
		}
	}

	std::cout << "error nenhum setor com as configuraçoes encontradas, colocando setor nulo no local" << std::endl;

	std::vector<BlockType> aux;

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			aux.push_back(NONE);
		}
	}

	return BlockSector(aux, 0, Vector2(background_blocks_constants::BLOCK_WIDTH,background_blocks_constants::BLOCK_HEIGTH));
}

BlockSector BackgroundSectorLibraryHandler::getRandomFinishSector(unsigned int flags){

	int randomIndex = rand() % this->_finishSectorLibrary.size();

	for(int i = randomIndex ; i < (int)this->_finishSectorLibrary.size() ; i ++){
		if((this->_finishSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_finishSectorLibrary[i];
		}
	}
	for(int i = randomIndex-1 ; i >= 0 ; i --){
		if((this->_finishSectorLibrary[i].sectorFlags & flags) == flags){
			return this->_finishSectorLibrary[i];
		}
	}

	std::cout << "error nenhum setor com as configuraçoes encontradas, colocando setor nulo no local" << std::endl;

	std::vector<BlockType> aux;

	for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; i++){
		for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; j ++){
			aux.push_back(NONE);
		}
	}

	return BlockSector(aux, 0, Vector2(background_blocks_constants::BLOCK_WIDTH,background_blocks_constants::BLOCK_HEIGTH));
}

/*
 * inicio da implementação dos operadores de SectorFlags
 *
 * vide C++ standart 17.5.2.1.3 Bitmask types
 */

constexpr SectorFlags operator&(SectorFlags X, SectorFlags Y) {
    return static_cast<SectorFlags>(
        static_cast<unsigned int>(X) & static_cast<unsigned int>(Y));
}

constexpr SectorFlags operator|(SectorFlags X, SectorFlags Y) {
    return static_cast<SectorFlags>(
        static_cast<unsigned int>(X) | static_cast<unsigned int>(Y));
}

constexpr SectorFlags operator^(SectorFlags X, SectorFlags Y) {
    return static_cast<SectorFlags>(
        static_cast<unsigned int>(X) ^ static_cast<unsigned int>(Y));
}

constexpr SectorFlags operator~(SectorFlags X) {
    return static_cast<SectorFlags>(~(static_cast<unsigned int>(X)));
}

SectorFlags& operator&=(SectorFlags& X, SectorFlags Y) {
    X = X & Y; return X;
}

SectorFlags& operator|=(SectorFlags& X, SectorFlags Y) {
    X = X | Y; return X;
}

SectorFlags& operator^=(SectorFlags& X, SectorFlags Y) {
    X = X ^ Y; return X;
}
/*
 * termino da implementação dos operadores de SectorFlags
 *
 */
