/*
 * backgroundsectorlibraryhandler.h
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_
#define SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_

#include "globals.h"
#include "animatedsprite.h"
#include <memory>
#include <vector>
#include "sectorbackground.h"

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
	W_BOT_TOP_VALUE = 1 << 3,			// 8 -- permite passagem entre bot e bot
	W_BOT_LEFT_VALUE = 1 << 4,			// 16 -- permite passagem entre bot e left
	W_BOT_RIGHT_VALUE = 1 << 5, 		// 32 -- permite passagem entre bot e right
	W_LEFT_TOP_VALUE = 1 << 6,			// 64 -- permite passagem entre left e top
	W_LEFT_BOT_VALUE = 1 << 7,			// 128 -- permite passagem entre left e bot
	W_LEFT_RIGHT_VALUE = 1 << 8,		// 256 -- permite passagem entre left e right
	W_RIGHT_TOP_VALUE = 1 << 9,			// 512 --  permite passagem entre right e top
	W_RIGHT_BOT_VALUE = 1 << 10,		// 1024 -- permite passagem entre right e bot
	W_RIGHT_LEFT_VALUE = 1 << 11,		// 2048 -- permite passagem entre right e left
};



constexpr SectorFlags W_TOP_BOT(W_TOP_BOT_VALUE);

constexpr SectorFlags W_TOP_LEFT(W_TOP_LEFT_VALUE);

constexpr SectorFlags W_TOP_RIGHT(W_TOP_RIGHT_VALUE);

constexpr SectorFlags W_BOT_TOP(W_BOT_TOP_VALUE);

constexpr SectorFlags W_BOT_LEFT(W_BOT_LEFT_VALUE);

constexpr SectorFlags W_BOT_RIGHT(W_BOT_RIGHT_VALUE);

constexpr SectorFlags W_LEFT_TOP(W_LEFT_TOP_VALUE);

constexpr SectorFlags W_LEFT_BOT(W_LEFT_BOT_VALUE);

constexpr SectorFlags W_LEFT_RIGHT(W_LEFT_RIGHT_VALUE);

constexpr SectorFlags W_RIGHT_TOP(W_RIGHT_TOP_VALUE);

constexpr SectorFlags W_RIGHT_BOT(W_RIGHT_BOT_VALUE);

constexpr SectorFlags W_RIGHT_LEFT(W_RIGHT_LEFT_VALUE);


/*
 * termino da declaração de SectorFlags
 */

struct MapObjectBlueprint{

	MapObjectType type;
	Vector2 positionOffsetOnSector;

	MapObjectBlueprint(MapObjectType type,	Vector2 position):
		type(type), positionOffsetOnSector(position)
	{}
};

struct BlockSector{

	std::vector<BlockType> sectorInfo;

	unsigned int sectorFlags;

	std::vector<MapObjectBlueprint> objectsToBuildVector;

	std::string backgroundPath;

	BlockSector(std::vector<BlockType> sectorInfo, unsigned int sectorFlags, std::string backgroundPath):
		sectorInfo(sectorInfo), sectorFlags(sectorFlags), backgroundPath(backgroundPath)
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
