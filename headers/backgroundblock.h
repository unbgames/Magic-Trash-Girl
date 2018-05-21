/*
 * backgroundblock.h
 *
 *  Created on: May 21, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_BACKGROUNDBLOCK_H_
#define SOURCE_HEADERS_BACKGROUNDBLOCK_H_

#include "animatedsprite.h"

class BackgroundBlock: public AnimatedSprite{
public:

	BackgroundBlock(Graphics &graphics, int indexX, int indexY, BlockType typeIn);
	~BackgroundBlock();

	void update(float elapsedTime);

	void setupAnimations();

	void takeDamage(float damage);

	BlockType getType();

private:

	float _hp;

	BlockType _type;

};



#endif /* SOURCE_HEADERS_BACKGROUNDBLOCK_H_ */
