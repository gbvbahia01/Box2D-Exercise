/*
 * Bullet.h
 *
 *  Created on: Nov 24, 2014
 *      Author: guilhermebraga
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "b2Sprite.h"
#include "WorldContract.h"

class Bullet: public b2Sprite {
public:
	 Bullet(WorldContract * game, CCPoint position);
	virtual ~Bullet();
	static Bullet* create(WorldContract * game, CCPoint position);
	virtual void update (float dt);
private:
	    void initBullet();
	    CCPoint _startPosition;
};

#endif /* BULLET_H_ */
