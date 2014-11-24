//
//  b2Sprite.h
//  MiniPool
//
//  Created by Roger Engelbert on 1/13/13.
//
//

#ifndef __MiniPool__b2Sprite__
#define __MiniPool__b2Sprite__

#include "cocos2d.h"
#include "Box2D.h"
#include "WorldContract.h"

class HelloWorld;

enum {
    kSpriteNuke,
    kSpriteTower,
    kSpriteBullet,
};

using namespace cocos2d;

class b2Sprite : public CCSprite {
    
public:
    
    b2Sprite (WorldContract * game, int type);
    CC_SYNTHESIZE(bool, _inPlay, InPlay);
    CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(WorldContract *, _game, Game);
    CC_SYNTHESIZE(int, _type, Type);
    
    virtual void setSpritePosition (CCPoint position);
    virtual void update(float dt);
    virtual void hide(void);
    virtual void reset(void);
    /*
     * get squared magnitude of sprite's vector
     */
    virtual float mag();
};


#endif /* defined(__MiniPool__b2Sprite__) */
