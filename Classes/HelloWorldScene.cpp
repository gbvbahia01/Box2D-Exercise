#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene() {
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if ( !CCLayer::init() ){
        return false;
    }
    _pick = 0;
    _last = 0;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HelloWorld::pick), "PICK", NULL);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(ccp(_origin.x + visibleSize.width - pCloseItem->getContentSize().width/2, _origin.y + pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSprite* pSprite = CCSprite::create("bg.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + _origin.x, visibleSize.height/2 + _origin.y));
    //this->addChild(pSprite, -2);
    
    _picksLablel = CCLabelTTF::create("Hits:0", "fonts/arial.ttf", TITLE_FONT_SIZE);
    _picksLablel->setPosition(ccp(_origin.x + _screenSize.width * 0.10, _origin.y + _screenSize.height * 0.03));
	this->addChild(_picksLablel, -1);

	_lastLablel = CCLabelTTF::create("Last:0", "fonts/arial.ttf", TITLE_FONT_SIZE);
	_lastLablel->setPosition(ccp(_origin.x + _screenSize.width * 0.90, _origin.y + _screenSize.height * 0.03));
	this->addChild(_lastLablel, -1);

	_bullets = CCArray::createWithCapacity(20);	_bullets->retain();
	_bullets->retain();

    this->initPhysics();

    setTouchEnabled( true );
    scheduleUpdate();
    return true;
}


void HelloWorld::initPhysics() {
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.0f);
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    _collisionListener = new CollisionListener();
    _world->SetContactListener(_collisionListener);
    m_debugDraw = new GLESDebugDraw( PTM_RATIO_BOX2D );
    _world->SetDebugDraw(m_debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    m_debugDraw->SetFlags(flags);

    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;
    //Nuke boll
    b2Body * nuke;
	b2Sprite * pocketData;
	b2CircleShape circle;

	float startX = _screenSize.width * 0.5f;
	float startY = _screenSize.height * 0.925f;
	_ball = Ball::create(this, kSpriteNuke, ccp(startX, startY));
	addChild(_ball, 0);

	startX = _screenSize.width * 0.05f;
	startY = _screenSize.height * 0.5f;
	_tower = Tower::create(this, ccp(startX, startY));
	addChild(_tower, 0);

    //create area sides
    b2BodyDef tableBodyDef;
    tableBodyDef.position.Set(0, 0);
    b2Body* tableBody = _world->CreateBody(&tableBodyDef);
    b2EdgeShape tableBox;
    tableBox.Set(b2Vec2(_origin.x/PTM_RATIO_BOX2D, _origin.y + 1 / PTM_RATIO_BOX2D),
                      b2Vec2(_origin.x + _screenSize.width * 2 / PTM_RATIO_BOX2D, _origin.y + 1 / PTM_RATIO_BOX2D));
	tableBody->CreateFixture(&tableBox,0);
}

void HelloWorld::reset(){
	_last = _pick;
	_pick = -1;
	float startX = _screenSize.width * 0.5f;
	float startY = _screenSize.height * 0.925f;
	_ball->reset();
	_ball->setSpritePosition(ccp(startX, startY));
	pick(NULL);
	char szNameI[10] = { 0 };
	sprintf(szNameI, "Last:%i", _last);
	_lastLablel->setString(szNameI);
	CCLOG("The game was reseted!");
}

void HelloWorld::update(float dt) {
	 _world->Step(dt, 10, 10);
	 _ball->update(dt);
	 _tower->updateAngle(dt, _ball);
	 _tower->update(dt);
	 int bulletsCount = _bullets->count();
	 for(int b = 0; b < bulletsCount; b++){
		 Bullet* bullet = (Bullet*)_bullets->objectAtIndex(b);
		 bullet->update(dt);
	 }

	 Bullet* bulletFire = _tower->fire();
	 if(bulletFire != NULL){
		 _bullets->addObject(bulletFire);
		 CCPoint shootVector = ccpSub(_ball->getPosition(), _tower->getPosition());
		 float shootAngle = ccpToAngle(shootVector);
		 //CCPoint normalizedShootVector = ccpNormalize(shootVector);
		 //CCPoint overshotVector = ccpMult(normalizedShootVector, 420);
		 //CCPoint offscreenPoint = ccpAdd(bulletFire->getPosition(), overshotVector);
		 int power = 100;
		 float x1 =  cos(shootAngle);
		 float y1 =  sin(shootAngle);
		 b2Vec2 force = b2Vec2(x1* power,y1* power);
		 bulletFire->getBody()->ApplyLinearImpulse(force, bulletFire->getBody()->GetPosition());
		 addChild(bulletFire, -1);
	 }

	 float ballX = _ball->getPosition().x;
	 if((ballX < (_origin.x - _ball->getContentSize().width / 2))
			 ||(ballX > (_origin.x + _screenSize.width + _ball->getContentSize().width / 2))){
		 reset();
	 }
}

void HelloWorld::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    _world->DrawDebugData();
    kmGLPopMatrix();
}

void HelloWorld::pick(cocos2d::CCObject* obj){
	char szNameI[10] = { 0 };
	sprintf(szNameI, "Hits:%i", ++_pick);
	_picksLablel->setString(szNameI);
}

void HelloWorld::menuCloseCallback(CCObject* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
