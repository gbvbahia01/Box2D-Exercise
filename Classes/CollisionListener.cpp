//
//  CollisionListener.cpp
//  MiniPool
//
//  Created by Roger Engelbert on 1/14/13.
//
//

#include "CollisionListener.h"
#include "SimpleAudioEngine.h"
#include "b2Sprite.h"

using namespace CocosDenshion;

void CollisionListener::BeginContact(b2Contact* contact) {
	//CCLOG("CollisionListener::BeginContact");
}
void CollisionListener::EndContact(b2Contact* contact){
	//CCLOG("CollisionListener::EndContact");
}

void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)  {
	b2Body * bodyA = contact->GetFixtureA()->GetBody();
	b2Body * bodyB = contact->GetFixtureB()->GetBody();

	b2Sprite * spriteA = (b2Sprite *) bodyA->GetUserData();
	b2Sprite * spriteB = (b2Sprite *) bodyB->GetUserData();

	 if (spriteA && spriteB) {
		 if((spriteB->getInPlay() && spriteA->getType() == kSpriteNuke && spriteB->getType() == kSpriteBullet)){
			 CCNotificationCenter::sharedNotificationCenter()->postNotification("PICK", NULL);
			 spriteB->setInPlay(false);
		 }else if(spriteA->getInPlay() && spriteA->getType() == kSpriteBullet && spriteB->getType() == kSpriteNuke){
			 CCNotificationCenter::sharedNotificationCenter()->postNotification("PICK", NULL);
			 spriteA->setInPlay(false);
		 }
	 }

	//CCLOG("CollisionListener::PreSolve");
}

void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	//CCLOG("CollisionListener::PostSolve");
}
