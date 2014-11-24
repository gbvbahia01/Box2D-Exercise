/*
 * Tower.h
 *
 *  Created on: Nov 24, 2014
 *      Author: guilhermebraga
 */

#ifndef TOWER_H_
#define TOWER_H_

#include "b2Sprite.h"
#include "Bullet.h"
#include "WorldContract.h"

class Tower: public b2Sprite {
public:
	Tower(WorldContract * game, CCPoint position);
	virtual ~Tower();
	CC_SYNTHESIZE(bool, _inPlay, InPlay);
    static Tower* create(WorldContract * game, CCPoint position);
    void updateAngle(float dt, b2Sprite* target);
    Bullet* fire();
private:
    void initTower();
    CCPoint _startPosition;
    float _reloaded;
};

#endif /* TOWER_H_ */
