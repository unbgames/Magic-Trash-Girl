/*
 * blockborder.h
 *
 *  Created on: May 31, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BLOCKBORDER_H_
#define SOURCE_HEADERS_BLOCKBORDER_H_

#include "animatedsprite.h"

class BackgroundBlock;

class BlockBorder: public AnimatedSprite{
public:

	BlockBorder(Graphics &graphics, BackgroundBlock blockAssociated);
	~BlockBorder();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

private:

	BackgroundBlock* _blockAssociated;

};



#endif /* SOURCE_HEADERS_BLOCKBORDER_H_ */
