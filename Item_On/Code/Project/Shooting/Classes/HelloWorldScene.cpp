#include "header.h"

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	srand((int)time(NULL));
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	this->setTouchEnabled(true);
	this->scheduleUpdate();

	

	Life=3, SuAm=true, BombUse=false;
	Score=0, TickTime=0;
	BossComing=false;
	gop=1;
	MisCount=0;

	mvt=240;
	Count=0, bomb=2;
	
	ticktime=0;
	health_end=0.5;
	
	bul=false, Live=true;

	
	Em1y=660, Em2y=670, Em3y=650, BosY=900, BossLife=15000;
	rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
	Em1x=rd1;
	Em2x=rd2;
	Em3x=rd3;
	
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 , 615));
	CCMenuItemImage *BombBut = CCMenuItemImage::create("img/LP_01.png", "img/LP_02.png", this, menu_selector(HelloWorld::BombCheck));
	BombBut->setPosition(ccp(240, 200));

    CCMenu* pMenu = CCMenu::create(pCloseItem, BombBut, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 3);

	Heart3=CCSprite::create("img/Life.png");
	Heart3->setPosition(ccp(150,600));
	this->addChild(Heart3, 3);
	Heart2=CCSprite::create("img/Life.png");
	Heart2->setPosition(ccp(100,600));
	this->addChild(Heart2, 3);
	Heart1=CCSprite::create("img/Life.png");
	Heart1->setPosition(ccp(50,600));
	this->addChild(Heart1, 3);

	Bomb1=CCSprite::create("img/laser.png");
	Bomb1->setPosition(ccp(50,550));
	this->addChild(Bomb1, 3);
	Bomb2=CCSprite::create("img/laser.png");
	Bomb2->setPosition(ccp(100,550));
	this->addChild(Bomb2, 3);

	Lazer=CCSprite::create("img/laser_1.png");
	Lazer->setPosition(ccp(-1000,-1000));
	Lazer->setScale(1.5f);
	this->addChild(Lazer, 2);


	Char = CCSprite::create("img/char.png");
	Char->setPosition(ccp(230, 110));
	this->addChild(Char, 2);

	
	BossMonster = CCSprite::create("img/boss.png");
	BossMonster->setPosition(ccp(240, BosY));
	this->addChild(BossMonster, 2);
	

	CCSprite* TimeImg = CCSprite::create("img/Time.png");
	TimeImg->setPosition(ccp(230, 620));
	this->addChild(TimeImg, 3);
	CCSprite* ScoreImg = CCSprite::create("img/Score.png");
	ScoreImg->setPosition(ccp(330, 620));
	this->addChild(ScoreImg, 3);
	LabelScore = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
	LabelScore->setPosition(ccp(350,610));
	LabelScore->setString(CCString::createWithFormat("%d", Score)->m_sString.c_str());
	this->addChild(LabelScore, 3);
	LabelTime = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
	LabelTime->setPosition(ccp(250,610));
	LabelTime->setString(CCString::createWithFormat("%d", TickTime)->m_sString.c_str());
	this->addChild(LabelTime, 3);

	timer_gaze = CCSprite::create("img/xpbar_02.png");
	m_pHPProgress = CCProgressTimer::create(timer_gaze);
	m_pHPProgress->setPosition(ccp(250,600));
	m_pHPProgress->setScale(0.3f);
	m_pHPProgress->setPercentage(100);
	m_pHPProgress->setMidpoint(ccp(0, 0.5));    //끝 지점
	m_pHPProgress->setBarChangeRate(ccp(1, 0));
	m_pHPProgress->setType(kCCProgressTimerTypeBar);
	this->addChild(m_pHPProgress, 3);

	MapLoad();

	pBullet =  CCArray::create();	// pBullet 배열을 초기화.
	pBullet -> retain();			// retain 함수는 메모리가 해제되지 않게 설정함.
	
	
	BossMi =  CCArray::create();
	BossMi -> retain();	

	Enm1 =  CCArray::create();
	Enm1 -> retain();
	Enm2 =  CCArray::create();
	Enm2 -> retain();
	Enm3 =  CCArray::create();
	Enm3 -> retain();
	
	HItem =  CCArray::create();
	HItem -> retain();
	MItem =  CCArray::create();
	MItem -> retain();
	LItem =  CCArray::create();
	LItem -> retain();

	this->schedule(schedule_selector(HelloWorld::Bullet), 0.2f);
	this->schedule(schedule_selector(HelloWorld::TimeCheck), 0.1f);
	this->schedule(schedule_selector(HelloWorld::TimeCheck_), 1.0f);
    //this->schedule(schedule_selector(HelloWorld::BossEnemyCheck), 0.3f);

    return true;
}

void HelloWorld::update(float dt)
{
	
	LabelScore->setString(CCString::createWithFormat("%d", Score)->m_sString.c_str());
	LabelTime->setString(CCString::createWithFormat("%d", TickTime)->m_sString.c_str());
	///////////////////////////////
	if(Count>=8)
		BossComing=true;
	
    
	if(BossComing==false)
        this->schedule(schedule_selector(HelloWorld::EnemySpawn), 0.4f);
	else if(BossComing==true)
		Boss();
		
    ///////////////////////////////
	if(SuAm==false)
		Char->setOpacity(255);
	else if(SuAm>=true)
	{
		this->schedule(schedule_selector(HelloWorld::SuperArmor), 5.0f);
		Char->setOpacity(120);
	}
	/////////////////////////////
	if(BombUse==true)
		LCount();
	else if(BombUse==false)
	{
		ticktime=0;
		gop=1;
		Lazer->setPosition(ccp(-1000,-1000));
	}
	/////////////////////////////
	Check();
	LifeC();
	
	if(BossLife<=0)
	{
		CCScene* pScene = CWinScene::scene();

		CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
	}
	
	///////////////////////////////
	

	mBG01_Y			-=	mBGSpeed*gop;	// 1프레임마다 mBGSpeed만큼 맵을 움직임.
	mBG02_Y			-=	mBGSpeed*gop;	
	if(abs(mBG01_Y) > 640)	// 만약 맵이 끝까지 움직였다면?
	{		
		// 맵의 위치를 초기화시켜주고, 오브젝트를 전부 없애주고 새로 생성함.
		Count++;
		mBG01_Y		=	0;
		mBG02_Y		=	640;
		return;			// 함수를 종료.
	}
	// 프레임마다 맵의 위치를 조정.
	MAP->setPositionY(origin.y + mBG01_Y);
	MAP_->setPositionY(origin.y + mBG02_Y);
	float mCurrPercentage = m_pHPProgress->getPercentage();
	if(mCurrPercentage<=1)
		HealthGaze();
}

void HelloWorld::TimeCheck(float dt)
{
	ticktime += 0.1;
}
void HelloWorld::TimeCheck_(float dt)
{
	TickTime+=1;
}

void HelloWorld::HealthGaze()
{
	Life--;
	m_pHPProgress->setPercentage(100.f);

    if(bomb<=0)
    {
        Bomb1=CCSprite::create("img/laser.png");
        Bomb1->setPosition(ccp(50,550));
        this->addChild(Bomb1, 3);
    }
    if(bomb<=1)
    {
        Bomb2=CCSprite::create("img/laser.png");
        Bomb2->setPosition(ccp(100,550));
        this->addChild(Bomb2, 3);
    }

	bomb=2;
	MisCount=0;
}

void HelloWorld::MapLoad()
{
	MAP	 = CCSprite::create("img/back/03.png");
	MAP_ = CCSprite::create("img/back/03.png");
	MAP  ->setAnchorPoint(ccp(0, 0));
	MAP_ ->setAnchorPoint(ccp(0, 0));
	mBG01_Y						=	0;
	mBG02_Y						=	640;
	mBGSpeed					=	1.0f*gop;		// 맵이 움직이는 속도
	MAP  ->setPosition(ccp( origin.x ,mBG01_Y));
	MAP_ ->setPosition(ccp(origin.x ,mBG02_Y ));
	this->addChild(MAP,0);
	this->addChild(MAP_,0);
}



void HelloWorld::Blood(const CCPoint Pos)
{
	CCSprite* piPang = CCSprite::create("img/eft/blood_01.png");
	piPang->setPosition(Pos);

	CCAnimation* bld = CCAnimation::create();
	bld->addSpriteFrameWithFileName("img/eft/blood_01.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_02.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_03.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_04.png");
	bld->setDelayPerUnit(0.1);
	bld->setRestoreOriginalFrame(true);

	CCAnimate* animate = CCAnimate::create(bld);
	CCCallFuncND* removeAction = CCCallFuncND::create(this, callfuncND_selector(CCNode::removeChild), animate);
	CCFiniteTimeAction* seq=CCSequence::create(animate, removeAction, NULL);

	this->addChild(piPang, 1);
	piPang->runAction(seq);


}
void HelloWorld::BANG(const CCPoint Pos)
{
	CCSprite* Bang = CCSprite::create("img/eft/blaze_01.png");
	Bang->setPosition(Pos);

	CCAnimation* blz = CCAnimation::create();
	blz->addSpriteFrameWithFileName("img/eft/blaze_01.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_02.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_03.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_04.png");
	blz->setDelayPerUnit(0.1);
	blz->setRestoreOriginalFrame(true);

	CCAnimate* animate = CCAnimate::create(blz);
	CCCallFuncND* removeAction = CCCallFuncND::create(this, callfuncND_selector(CCNode::removeChild), animate);
	CCFiniteTimeAction* seq_=CCSequence::create(animate, removeAction, NULL);

	this->addChild(Bang, 1);
	Bang->runAction(seq_);


}

void HelloWorld::SuperArmor(float dt)
{
	SuAm=false;
}

void HelloWorld::BombCheck(CCObject* pSender)
{
    if(BombUse==false)
    {
	    BombUse=true;
	    bomb--;
    }
}

void HelloWorld::LCount()
{
	if(bomb==1)
	{
		removeChild(Bomb2, false);
		gop=5;
		Lazer->setPosition(ccp(mvt,470));
	}
	if(bomb==0)
	{
		removeChild(Bomb1, false);
		gop=5;
		Lazer->setPosition(ccp(mvt,470));
	}
	if(ticktime>=3)
		BombUse=false;
}

void HelloWorld::Bullet(float dt)
{
	Score+=2;
	CCSprite* Charmis = CCSprite::create("img/Charmi.png");
	BulX =	mvt;// + (Char->getContentSize().width*3);
	BulY =	150 + 10;//(Char->getContentSize().height*2.1);
	Charmis->setPosition(ccp(BulX, BulY));
	this->addChild(Charmis);
	CCActionInterval* tempActBullet = CCMoveBy::create(1, ccp(0, visibleSize.height));
	Charmis->runAction(tempActBullet);
	pBullet->addObject(Charmis);
	
	if(MisCount>=1)
	{
		CCSprite* Charmis1 = CCSprite::create("img/Charmi.png");
		Charmis1->setPosition(ccp(BulX+20, BulY-10));
		this->addChild(Charmis1);
		CCActionInterval* tempActBullet = CCMoveBy::create(1, ccp(0, visibleSize.height));
		Charmis1->runAction(tempActBullet);
		pBullet->addObject(Charmis1);
	}
	if(MisCount>=2)
	{
		CCSprite* Charmis2 = CCSprite::create("img/Charmi.png");
		Charmis2->setPosition(ccp(BulX-20, BulY-10));
		this->addChild(Charmis2);
		CCActionInterval* tempActBullet = CCMoveBy::create(1, ccp(0, visibleSize.height));
		Charmis2->runAction(tempActBullet);
		pBullet->addObject(Charmis2);
	}
	if(MisCount>=3)
	{
		CCSprite* Charmis3 = CCSprite::create("img/Charmi.png");
		Charmis3->setPosition(ccp(BulX+40, BulY-20));
		this->addChild(Charmis3);
		CCActionInterval* tempActBullet = CCMoveBy::create(1, ccp(0, visibleSize.height));
		Charmis3->runAction(tempActBullet);
		pBullet->addObject(Charmis3);
	}
	if(MisCount>=4)
	{
		CCSprite* Charmis4 = CCSprite::create("img/Charmi.png");
		Charmis4->setPosition(ccp(BulX-40, BulY-20));
		this->addChild(Charmis4);
		CCActionInterval* tempActBullet = CCMoveBy::create(1, ccp(0, visibleSize.height));
		Charmis4->runAction(tempActBullet);
		pBullet->addObject(Charmis4);
	}
}

void HelloWorld::LifeC()
{
	if(Life==2)
	{
		removeChild(Heart3, false);
	}
	if(Life==1)
	{	
		removeChild(Heart2, false);
	}
	if(Life<=0)
	{
		removeChild(Heart1, false);

		CCScene* pScene = CLoseScene::scene();

		CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
	}
}
void HelloWorld::BossEnemyCheck(float dt)
{/*
    if(BossComing==false)
        EnemySpawn();
    else if(BossComing==true)
    {}*/
}

void HelloWorld::EnemySpawn(float dt)
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

void HelloWorld::Boss()
{
	if(Count==6)
	{
		WN->playEffect("Sound/warning.wav"); 
	}
	if(Count>=8)
	{
		if(BosY>=550)
			BosY-=2;

		BossMonster->setPositionY(BosY);
		/////////////////////////
		
		
		
	}
}

void HelloWorld::ItemSpawn(const CCPoint Pos)
{
	IR = rand()%6+1;

	if(IR==1 || IR==2)
	{
		CCSprite* Item_heal = CCSprite::create("img/Item_heal.png");
		Item_heal->setPosition(Pos);
		this->addChild(Item_heal, 2);
		CCActionInterval* TM1=CCMoveBy::create(5, ccp(0, -visibleSize.height-100));
		Item_heal->runAction(TM1);
		HItem->addObject( Item_heal );
	}
	else if(IR==3)
	{
		CCSprite* Item_mis = CCSprite::create("img/Item_mis.png");
		Item_mis->setPosition(Pos);
		this->addChild(Item_mis, 2);
		CCActionInterval* TM2=CCMoveBy::create(5, ccp(0, -visibleSize.height-100));
		Item_mis->runAction(TM2);
		MItem->addObject( Item_mis );
	}
	else if(IR==4 || IR==5 || IR==6)
	{
		CCSprite* Item_life = CCSprite::create("img/Item_super.png");
		Item_life->setPosition(Pos);
		this->addChild(Item_life, 2);
		CCActionInterval* TM3=CCMoveBy::create(5, ccp(0, -visibleSize.height-100));
		Item_life->runAction(TM3);
		LItem->addObject( Item_life );
	}
}


void HelloWorld::Check()
{
	CCObject* obj = NULL;
	
	float mCurrPercentage = m_pHPProgress->getPercentage();

	CCARRAY_FOREACH(Enm1, obj)
	{
		CCSprite* Emy1 = (CCSprite*)obj;
		if(Emy1->getPositionY() < -30)
		{
			removeChild(Emy1, false);
			Enm1->removeObject(Emy1);
			continue;
		}
		CCARRAY_FOREACH(pBullet, obj)
		{
			CCSprite* CharMis = (CCSprite*) obj;
			if(CharMis->getPositionY() > 640)
			{
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				continue;
			}
			if(CharMis->boundingBox().intersectsRect(Emy1->boundingBox() ))
			{
				Blood(Emy1->getPosition());
				itemRan = rand()%20;
				if(itemRan==5)
					ItemSpawn(Emy1->getPosition());
				Emy1->setPositionY(-1000);
				MD->playEffect("Sound/mondie.wav"); 
				//float mCurrPercentage = m_pHPProgress->getPercentage();
				m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
				removeChild(Emy1, false);
				Enm1->removeObject(Emy1);
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);

				Score+=100;
			}
			if(CharMis->boundingBox().intersectsRect(BossMonster->boundingBox() ))
			{
				Boshit->playEffect("Sound/boshit.wav"); 
				m_pHPProgress->setPercentage(mCurrPercentage + 0.5);
				BossLife-=8;
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
			}
		}
		if(SuAm==false)
		{
			if(Char != NULL)
			{
				if(Char->boundingBox().intersectsRect(Emy1->boundingBox()))
				{
					Blood(Emy1->getPosition() );
					Hit->playEffect("Sound/hit.wav"); 
					removeChild(Emy1, false);
					Enm1->removeObject(Emy1);
					//float mCurrPercentage = m_pHPProgress->getPercentage();
					m_pHPProgress->setPercentage(mCurrPercentage - 50);
					SuAm=true;
				}
			}
		}
		if(Lazer->boundingBox().intersectsRect(Emy1->boundingBox()))
		{
			Blood(Emy1->getPosition());
			itemRan = rand()%20;
			if(itemRan==5)
				ItemSpawn(Emy1->getPosition());
			Emy1->setPositionY(-1000);
			MD->playEffect("Sound/mondie.wav"); 
			m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
			removeChild(Emy1, false);
			Enm1->removeObject(Emy1);
			Score+=100;
		}
		if(Lazer->boundingBox().intersectsRect(BossMonster->boundingBox()))
		{
			Boshit->playEffect("Sound/boshit.wav"); 
			m_pHPProgress->setPercentage(mCurrPercentage + 0.5);
			BossLife-=10;
			Score+=50;
		}

	}
	CCARRAY_FOREACH(Enm2, obj)
	{
		CCSprite* Emy2 = (CCSprite*)obj;
		if(Emy2->getPositionY() < -30)
		{
			removeChild(Emy2, false);
			Enm2->removeObject(Emy2);
			continue;
		}
		CCARRAY_FOREACH(pBullet, obj)
		{
			CCSprite* CharMis = (CCSprite*) obj;
			if(CharMis->getPositionY() > 640)
			{
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				continue;
			}
			if(CharMis->boundingBox().intersectsRect(Emy2->boundingBox() ))
			{
				Blood(Emy2->getPosition() );
				itemRan = rand()%20;
				if(itemRan==5)
					ItemSpawn(Emy2->getPosition());
				Emy2->setPositionY(-1000);
				MD->playEffect("Sound/mondie.wav"); 
				//float mCurrPercentage = m_pHPProgress->getPercentage();
				m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
				removeChild(Emy2, false);
				Enm2->removeObject(Emy2);
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				Score+=100;
			}
		}
		if(SuAm==false)
		{
			if(Char != NULL)
			{
				if(Char->boundingBox().intersectsRect(Emy2->boundingBox()))
				{
					Blood(Emy2->getPosition() );

					Hit->playEffect("Sound/hit.wav"); 
					removeChild(Emy2, false);
					Enm2->removeObject(Emy2);
					//float mCurrPercentage = m_pHPProgress->getPercentage();
					m_pHPProgress->setPercentage(mCurrPercentage - 50);
					SuAm=true;
				}
			}
		}
		if(Lazer->boundingBox().intersectsRect(Emy2->boundingBox()))
		{
			Blood(Emy2->getPosition());
			itemRan = rand()%20;
			if(itemRan==5)
				ItemSpawn(Emy2->getPosition());
			Emy2->setPositionY(-1000);
			MD->playEffect("Sound/mondie.wav"); 
			m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
			removeChild(Emy2, false);
			Enm2->removeObject(Emy2);
			Score+=100;
		}
	}
	CCARRAY_FOREACH(Enm3, obj)
	{
		CCSprite* Emy3 = (CCSprite*)obj;
		if(Emy3->getPositionY() < -30)
		{
			removeChild(Emy3, false);
			Enm3->removeObject(Emy3);
			continue;
		}
		CCARRAY_FOREACH(pBullet, obj)
		{
			CCSprite* CharMis = (CCSprite*) obj;
			if(CharMis->getPositionY() > 640)
			{
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				continue;
			}
			if(CharMis->boundingBox().intersectsRect(Emy3->boundingBox() ))
			{
				Blood(Emy3->getPosition() );
				itemRan = rand()%20;
				if(itemRan==5)
					ItemSpawn(Emy3->getPosition());
				Emy3->setPositionY(-1000);
				MD->playEffect("Sound/mondie.wav"); 
				//float mCurrPercentage = m_pHPProgress->getPercentage();
				m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
				removeChild(Emy3, false);
				Enm3->removeObject(Emy3);
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				Score+=100;
			}
		}
		if(SuAm==false)
		{
			if(Char != NULL)
			{
				if(Char->boundingBox().intersectsRect(Emy3->boundingBox()))
				{
					Blood(Emy3->getPosition() );

					Hit->playEffect("Sound/hit.wav"); 
					removeChild(Emy3, false);
					Enm3->removeObject(Emy3);
					//float mCurrPercentage = m_pHPProgress->getPercentage();
					m_pHPProgress->setPercentage(mCurrPercentage - 50);
					SuAm=true;
				}
			}
		}
		if(Lazer->boundingBox().intersectsRect(Emy3->boundingBox()))
		{
			Blood(Emy3->getPosition());
			itemRan = rand()%20;
			if(itemRan==5)
				ItemSpawn(Emy3->getPosition());
			Emy3->setPositionY(-1000);
			MD->playEffect("Sound/mondie.wav"); 
			m_pHPProgress->setPercentage(mCurrPercentage + 0.25);
			removeChild(Emy3, false);
			Enm3->removeObject(Emy3);
			Score+=100;
		}
	}

	
	
	CCARRAY_FOREACH(BossMi, obj)
	{
		CCSprite* BoM= (CCSprite*)obj;
		if(BoM->getPositionY() < -30)
		{
			removeChild(BoM, false);
			BossMi->removeObject(BoM);
			continue;
		}
		CCARRAY_FOREACH(pBullet, obj)
		{
			CCSprite* CharMis = (CCSprite*) obj;
			if(CharMis->getPositionY() > 640)
			{
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
				continue;
			}
			if(CharMis->boundingBox().intersectsRect(BoM->boundingBox() ))
			{
				BANG(BoM->getPosition());
				BoM->setPositionY(-1000);
				removeChild(BoM, false);
				BossMi->removeObject(BoM);
				removeChild(CharMis, false);
				pBullet->removeObject(CharMis);
			}
		}
		if(SuAm==false)
		{
			if(Char != NULL)
			{
				if(Char->boundingBox().intersectsRect(BoM->boundingBox()))
				{
					BANG(BoM->getPosition());
					Hit->playEffect("Sound/hit.wav"); 
					removeChild(BoM, false);
					BossMi->removeObject(BoM);
					m_pHPProgress->setPercentage(mCurrPercentage - 60);
					SuAm=true;
				}
			}
		}
		if(Lazer->boundingBox().intersectsRect(BoM->boundingBox()))
		{
			BANG(BoM->getPosition());
			BoM->setPositionY(-1000);
			removeChild(BoM, false);
			Enm3->removeObject(BoM);
		}
	}
	

	


	CCARRAY_FOREACH(HItem, obj)
	{
		CCSprite* HT = (CCSprite*)obj;
		if(HT->getPositionY() < -30)
		{
			removeChild(HT, false);
			HItem->removeObject(HT);
			continue;
		}
		if(Char->boundingBox().intersectsRect(HT->boundingBox()))
		{
			removeChild(HT, false);
			HItem->removeObject(HT);
			m_pHPProgress->setPercentage(100);
		}
	}
	CCARRAY_FOREACH(MItem, obj)
	{
		CCSprite* MT = (CCSprite*)obj;
		if(MT->getPositionY() < -30)
		{
			removeChild(MT, false);
			HItem->removeObject(MT);
			continue;
		}
		if(Char->boundingBox().intersectsRect(MT->boundingBox()))
		{
			removeChild(MT, false);
			MItem->removeObject(MT);
			MisCount++;
            if(MisCount>=5)
                Score+=1000;
		}
	}
	CCARRAY_FOREACH(LItem, obj)
	{
		CCSprite* LT = (CCSprite*)obj;
		if(LT->getPositionY() < -30)
		{
			removeChild(LT, false);
			HItem->removeObject(LT);
			continue;
		}
		if(Char->boundingBox().intersectsRect(LT->boundingBox()))
		{
			removeChild(LT, false);
			LItem->removeObject(LT);
			SuAm=true;
		}
	}
	



}


void HelloWorld::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
	CCLayer::onEnter();
}

void HelloWorld::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent* event)
{
    CCPoint touchPoint = pTouch->getLocation();

	mvt=touchPoint.x;

	if(mvt<=10)
		mvt=11;
	else if(mvt>=470)
		mvt=469;

	Char->setPositionX(mvt);

	return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent* event)
{
    CCPoint touchPoint = pTouch->getLocation();
	mvt=touchPoint.x;

	if(mvt<=10)
		mvt=11;
	else if(mvt>=470)
		mvt=469;

	Char->setPositionX(mvt);
	
	if(BombUse==true)
	{
		Lazer->setPosition(ccp(mvt,120));
	}
	
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent* event)
{
    CCPoint touchPoint = pTouch->getLocation();
}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	Click->playEffect("Sound/Click.wav");  

	CCScene* pScene = CMenuScene::scene();

	CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
}

CCTransitionScene* HelloWorld::createTransition(int nIndex, float t, CCScene* s)
{
    CCDirector::sharedDirector()->setDepthTest(false);
    
    switch(nIndex)
    {
        case 7: return CCTransitionCrossFade::create(t, s);
            
        default: break;
    }
    
    return NULL;
}