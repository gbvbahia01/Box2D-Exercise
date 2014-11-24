/*
 * WordContract.h
 *
 *  Created on: Nov 23, 2014
 *      Author: guilhermebraga
 */

#ifndef WORLDCONTRACT_H_
#define WORLDCONTRACT_H_

#define PTM_RATIO_BOX2D 32
#include "Box2D.h"

class WorldContract {
public:
	CC_SYNTHESIZE(b2World *, _world, World);
};


#endif /* WORLDCONTRACT_H_ */
