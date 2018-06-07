/*
 * vaccumcleaner.h
 *
 *  Created on: Jun 6, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_VACUUMCLEANER_H_
#define SOURCE_HEADERS_VACUUMCLEANER_H_

#include "animatedsprite.h"
#include "player.h"

class VacuumCleaner: public AnimatedSprite{
public:

	VacuumCleaner();

	VacuumCleaner(Graphics &graphics, Player &player);
	~VacuumCleaner();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();

	void activateVacuum();
	void bubble();

	bool getFolowingPlayer();
	void toggleFolowingPlayer();

	void update(float elapsedTime);
	void draw(Graphics &graphics);

	std::string getObjectType();

	void setupAnimations();

private:

	bool _folowingPlayer;

	Player* _playerAssociated;

	Direction _facing;

	VacuumCone _vCone;




};


#endif /* SOURCE_HEADERS_VACUUMCLEANER_H_ */
