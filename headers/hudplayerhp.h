/*
 * hudplayerhp.h
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_HUDPLAYERHP_H_
#define SOURCE_HEADERS_HUDPLAYERHP_H_

#include "hudelement.h"

class HUDPlayerHp: public HUDElement{
public:

	HUDPlayerHp();

	HUDPlayerHp(Graphics &graphics);
	~HUDPlayerHp();

	void update(float elapsedTime);

	std::string getObjectType();

private:

	void setupAnimations();

};



#endif /* SOURCE_HEADERS_HUDPLAYERHP_H_ */
