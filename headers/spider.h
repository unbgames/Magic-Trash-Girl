/*
 * spider.h
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_SPIDER_H_
#define SOURCE_HEADERS_SPIDER_H_

#include "enemy.h"

class Spider:public Enemy{
public:

	Spider(Graphics &graphics, float posX, float posY);

	~Spider();

	void update(float elpasedTime);

	std::string getEnemyType();

	void setupAnimations();

private:


};

#endif /* SOURCE_HEADERS_SPIDER_H_ */
