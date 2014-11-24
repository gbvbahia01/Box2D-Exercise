/*
 * Bullet.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: guilhermebraga
 */

#include "Bullet.h"

Bullet::Bullet(WorldContract * game, CCPoint position) : b2Sprite (game, kSpriteBullet){
	_startPosition = position;
	_inPlay = true;
}

Bullet::~Bullet() {
}

Bullet* Bullet::create(WorldContract * game, CCPoint position){
	Bullet * sprite = new Bullet(game, position);
		if (sprite) {
	        sprite->initBullet();
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return NULL;
}

void Bullet::update (float dt) {
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO_BOX2D);
        setPositionY(_body->GetPosition().y * PTM_RATIO_BOX2D);
    }
}

void Bullet::initBullet() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    _body = _game->getWorld()->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    _body->SetLinearDamping(1.2);
    _body->SetAngularDamping(0.8);
    this->initWithFile("bullet.png");
    b2CircleShape  circle;
    circle.m_radius = getContentSize().width / 2 / PTM_RATIO_BOX2D;
    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
	fixtureDef.density = 3;
	fixtureDef.restitution = 0.4;
	//add collision filters so only white ball can be hit by bullet
	fixtureDef.filter.categoryBits = 0x0010;
    _body->SetBullet(true);
    _body->CreateFixture(&fixtureDef);
    //store the b2Sprite as the body's userData
    _body->SetUserData(this);
    setSpritePosition(_startPosition);
}
