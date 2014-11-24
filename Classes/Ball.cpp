//
//  Ball.cpp
//  MiniPool
//
//  Created by Roger Engelbert on 1/13/13.
//
//

#include "Ball.h"

Ball::~Ball() {   
}

Ball::Ball (WorldContract * game, int type, CCPoint position) : b2Sprite (game, type) {
    _type = type;
    _startPosition = position;
    _inPlay = true;
}

Ball* Ball::create(WorldContract * game, int type, CCPoint position) {
    Ball * sprite = new Ball(game, type, position);
	if (sprite) {
        sprite->initBall();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Ball::initBall() {
    
    //create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    _body = _game->getWorld()->CreateBody(&bodyDef);
    //_body->SetSleepingAllowed(true);
    //_body->SetLinearDamping(1.2);
    //_body->SetAngularDamping(0.8);
    
    //this->initWithSpriteFrameName("nuke.png");
    this->initWithFile("nuke.png");
    //create circle shape
    b2CircleShape  circle;
    circle.m_radius = getContentSize().width / 2 / PTM_RATIO_BOX2D;
    
    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
	fixtureDef.density = 8;
	fixtureDef.restitution = 0.8;
	fixtureDef.friction = 0.5f;
	//add collision filters so only white ball can be hit by bullet
	fixtureDef.filter.categoryBits = 0x0010;
   // _body->SetBullet(true);
    
    _body->CreateFixture(&fixtureDef);
    //store the b2Sprite as the body's userData
    _body->SetUserData(this);
    
    setSpritePosition(_startPosition);
}

void Ball::reset() {
    if (_body) {
        _body->SetLinearVelocity(b2Vec2_zero);
        _body->SetAngularVelocity(0);
    }
    setSpritePosition(_startPosition);
    _inPlay = true;
    setVisible(true);
}

void Ball::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO_BOX2D);
        setPositionY(_body->GetPosition().y * PTM_RATIO_BOX2D);
    }
}
