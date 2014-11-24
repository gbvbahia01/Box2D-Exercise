//
//  Ball.h
//  MiniPool
//
//  Created by Roger Engelbert on 1/13/13.
//
//

#ifndef __MiniPool__Ball__
#define __MiniPool__Ball__


#include "b2Sprite.h"
#include "WorldContract.h"

class Ball : public b2Sprite {

public:
    CC_SYNTHESIZE(bool, _inPlay, InPlay);
    ~Ball();
    Ball(WorldContract * game, int type, CCPoint position);
    static Ball* create(WorldContract * game, int type, CCPoint position);
    virtual void reset(void);
    virtual void update (float dt);
private:
    void initBall();
    CCPoint _startPosition;
};

#endif /* defined(__MiniPool__Ball__) */
