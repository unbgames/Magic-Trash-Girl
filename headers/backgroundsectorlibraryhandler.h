/*
 * backgroundsectorhandler.h
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_
#define SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_

#include "globals.h"
#include <vector>

class BackgroundSectorLibraryHandler{
public:

	BackgroundSectorLibraryHandler();

	std::vector<BlockType> getRandomSector();

private:

	std::vector<std::vector<BlockType>> _sectorLibrary;

};



#endif /* SOURCE_HEADERS_BACKGROUNDSECTORLIBRARYHANDLER_H_ */
