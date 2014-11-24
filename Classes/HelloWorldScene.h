#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "WorldContract.h"
#include "CollisionListener.h"
#include "GLES-Render.h"
#include "b2Sprite.h"
#include "AppMacros.h"
#include "Ball.h"
#include "Tower.h"
#include "Bullet.h"
#include "Box2D.h"

#define SHOT_POWER 6.0

class HelloWorld : public cocos2d::CCLayer, WorldContract{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void initPhysics();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void draw();
    void update(float dt);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void pick(cocos2d::CCObject* obj);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
    int _pick;
    int _last;
    Ball * _ball;
    Tower * _tower;
    CCSize _screenSize;
    CCPoint _origin;
    GLESDebugDraw * m_debugDraw;
    b2ContactListener * _collisionListener;
    CCLabelTTF* _picksLablel;
    CCLabelTTF* _lastLablel;
    CCArray* _bullets;

    void reset();
};

#endif // __HELLOWORLD_SCENE_H__
