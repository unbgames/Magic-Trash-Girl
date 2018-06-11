/*
 * hudplayerhp.h
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_HUDPLAYERHP_H_
#define SOURCE_HEADERS_HUDPLAYERHP_H_

#include "hudelement.h"
#include "player.h"

class HUDPlayerHp: public HUDElement{
public:

	HUDPlayerHp();

	HUDPlayerHp(Graphics &graphics, Player* associatedPlayer);
	~HUDPlayerHp();

	void update(float elapsedTime);

	std::string getObjectType();

private:

	void setupAnimations();

	Player* _associatedPlayer;

};



#endif /* SOURCE_HEADERS_HUDPLAYERHP_H_ */
