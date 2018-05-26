/*
 * backgroundsectorlibraryhandler.h
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_
#define SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_

#include "globals.h"
#include <vector>

/*
 * inicio da declaração de SectorFlags
 *
 *	um enum simples eh mais facil, mas queria fazer pelo menos 1 vez na minha vida como as boas práticas mandam
 *
 * vide C++ standart 17.5.2.1.3 Bitmask types
 */
enum SectorFlags: unsigned int{

	W_TOP_BOT_VALUE = 1 << 0, 			// 0  -- permite passagem entre top e bot
	W_TOP_LEFT_VALUE = 1 << 1,			// 2  -- permite passagem entre top e left
	W_TOP_RIGHT_VALUE = 1 << 2,			// 4  -- permite passagem entre top e right
	W_BOT_LEFT_VALUE = 1 << 3,			// 8  -- permite passagem entre bot e left
	w_BOT_RIGHT_VALUE = 1 << 4, 		// 16 -- permite passagem entre bot e right
	w_LEFT_RIGHT_VALUE = 1 << 5,		// 32 -- permite passagem entre left e right

};


// permite passagem entre top e bot
constexpr SectorFlags W_TOP_BOT(W_TOP_BOT_VALUE);

// permite passagem entre top e left
constexpr SectorFlags W_TOP_LEFT(W_TOP_LEFT_VALUE);

// permite passagem entre top e right
constexpr SectorFlags W_TOP_RIGHT(W_TOP_RIGHT_VALUE);

// permite passagem entre bot e left
constexpr SectorFlags W_BOT_LEFT(W_BOT_LEFT_VALUE);

// permite passagem entre bot e roght
constexpr SectorFlags W_BOT_RIGHT(w_BOT_RIGHT_VALUE);

// permite passagem entre left e right
constexpr SectorFlags W_LEFT_RIGHT(w_LEFT_RIGHT_VALUE);

/*
 * termino da declaração de SectorFlags
 */

struct BlockSector{

	std::vector<BlockType> sectorInfo;
	unsigned int sectorFlags;
	Vector2 start_finishPos;

	BlockSector(std::vector<BlockType> sectorInfo, unsigned int sectorFlags, Vector2 start_finishPos = Vector2(-1,-1)):
		sectorInfo(sectorInfo), sectorFlags(sectorFlags), start_finishPos(start_finishPos)
	{}
};

class BackgroundSectorLibraryHandler{
public:

	BackgroundSectorLibraryHandler();

	BlockSector getRandomFillerSector(unsigned int flags = 0);

	BlockSector getRandomStartSector(unsigned int flags = 0);

	BlockSector getRandomFinishSector(unsigned int flags = 0);

private:

	std::vector<BlockSector> _fillerSectorLibrary;

	std::vector<BlockSector> _startSectorLibrary;

	std::vector<BlockSector> _finishSectorLibrary;

};



#endif /* SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_ */
