/*
 * backgroundsectorhandler.h
 *
 *  Created on: May 24, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BACKGROUNDSECTORHANDLER_H_
#define SOURCE_HEADERS_BACKGROUNDSECTORHANDLER_H_

#include "globals.h"
#include <vector>

class BackgroundSectorHandler{
public:

	BackgroundSectorHandler();

	std::vector<BlockType> getRandomSector();

private:

	std::vector<std::vector<BlockType>> _sectorLibrary;

};



#endif /* SOURCE_HEADERS_BACKGROUNDSECTORHANDLER_H_ */
