#include "cMonster.h"

/*
bool Monster::EnemyInit()
{
	
	srand((int)time(NULL));

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	Em1y=660, Em2y=670, Em3y=650, BosY=900, BossLife=15000;
	Count=0;
	rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
	Em1x=rd1;
	Em2x=rd2;
	Em3x=rd3;

	BossMi =  CCArray::create();
	BossMi -> retain();	

	Enm1 =  CCArray::create();
	Enm1 -> retain();
	Enm2 =  CCArray::create();
	Enm2 -> retain();
	Enm3 =  CCArray::create();
	Enm3 -> retain();

	BossMonster = CCSprite::create("img/boss.png");
	BossMonster->setPosition(ccp(240, BosY));
	this->addChild(BossMonster, 2);
	
}

void Monster::EnemySpawn(float dt)
{
	rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
	////////////////////////
	
	CCSprite* Enmy1 = CCSprite::create("img/enemy1.png");
	Enmy1->setPosition(ccp(rd1,Em1y));
	this->addChild(Enmy1, 2);

	CCActionInterval* move1=CCMoveBy::create(2, ccp(0, -visibleSize.height-100));
	Enmy1->runAction(move1);

	Enm1->addObject( Enmy1 );
	///////////////////////////
	CCSprite* Enmy2 = CCSprite::create("img/enemy2.png");
	Enmy2->setPosition(ccp(rd2,Em2y));
	this->addChild(Enmy2, 2);

	CCActionInterval* move2=CCMoveBy::create(2, ccp(visibleSize.width/3, -visibleSize.height-100));
	Enmy2->runAction(move2);


	Enm2->addObject( Enmy2 );
	///////////////////////////
	CCSprite* Enmy3 = CCSprite::create("img/enemy3.png");
	Enmy3->setPosition(ccp(rd3,Em3y));
	this->addChild(Enmy3, 2);

	CCActionInterval* move3=CCMoveBy::create(2, ccp(-visibleSize.width/2, -visibleSize.height-100));
	Enmy3->runAction(move3);


	Enm3->addObject( Enmy3 );
	/////////////////////
	if(Count>=8)
	{
		br = rand()%200+150;
		
		CCSprite* Bosmi = CCSprite::create("img/Bosmi.png");
		Bosmi->setPosition(ccp(br, BosY));
		this->addChild(Bosmi, 2);
		CCActionInterval* BMmove = CCMoveBy::create(4, ccp(0, -visibleSize.height));
		Bosmi->runAction(BMmove);
		BossMi->addObject(Bosmi);
	}
}
*/