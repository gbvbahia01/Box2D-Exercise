/*
 * Tower.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: guilhermebraga
 */

#include "Tower.h"

Tower::Tower(WorldContract * game, CCPoint position) : b2Sprite (game, kSpriteTower){
	_startPosition = position;
	_inPlay = true;
	_reloaded = 0;
}

Tower::~Tower() {
}

Tower* Tower::create(WorldContract * game, CCPoint position) {
	Tower * sprite = new Tower(game, position);
	if (sprite) {
        sprite->initTower();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Tower::initTower() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    _body = _game->getWorld()->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    this->initWithFile("tower.png");
    b2CircleShape  circle;
    circle.m_radius = getContentSize().width / 2 / PTM_RATIO_BOX2D;
    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.isSensor = true;
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(this);
    setSpritePosition(_startPosition);
}

void Tower::updateAngle (float dt, b2Sprite* target){
	float diffx = this->getPosition().x - target->getPosition().x;
	float diffy = this->getPosition().y - target->getPosition().y;
	float angle = atan2(diffy, diffx);
	_body->SetTransform(b2Vec2(this->getPosition().x/PTM_RATIO_BOX2D, this->getPosition().y/PTM_RATIO_BOX2D), angle);
	if(_reloaded > 0){
		_reloaded -= dt;
	}
}

Bullet* Tower::fire(){
	if(_reloaded <= 0){
		Bullet* bullet = Bullet::create(_game, this->getPosition());
		_reloaded = 5;
		return bullet;
	}else {
		return NULL;
	}
}
