#include "HelloWorldScene.h"

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

    CMon = new CMonster();
    CMon->MonInit(this);
    
    GameEnd=false, RC=false; //GameEnd=������ ���� ���� O/X, RC=RemoveChild
    WinCheck=false, LoseCheck=false;

	Life=3, SuAm=true, BombUse=false; //Life=���� ��� ����, SuAm=��������, BombUse=���� �ʻ�� ��뿩�� ����
	TickTime=0; // �ð��� ���ִ� ���� (1�ʾ�)
	BossComing=false; // ��ó�� ������ �ִ�or����
	gop=1; // ���� �ӵ�
	MisCount=0;

	mvt=240; // ĳ���� �̹����� y��ǥ
	Count=0, bomb=2; // Count=������ ���� ����, bomb=�ʻ�� ���� ����
	
	ticktime=0; // �ð��� ���ִ� ���� (0.1�ʾ�)
	health_end=0.5; // ü�°������� ������ ��
	
	bul=false, Live=true; 
	CrsCheck=true;

	Em1y=660, Em2y=670, Em3y=650, BosY=900, BossLife=15000; //Em1y=�� 1�� y��ǥ, Em2y=�� 2�� y��ǥ, ... , BosY=������ y��ǥ, BossLife=������ ü��

	rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
	Em1x=rd1;
	Em2x=rd2;
	Em3x=rd3;
	
	CCMenuItemImage *BombBut = CCMenuItemImage::create("img/LP_01.png", "img/LP_02.png", this, menu_selector(HelloWorld::BombCheck));
	BombBut->setPosition(ccp(240, 200));

    CCMenu* pMenu = CCMenu::create(BombBut, NULL);
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
	this->addChild(Char, 3);

	
	BossMonster = CCSprite::create("img/boss.png");
	BossMonster->setPosition(ccp(240, BosY));
	this->addChild(BossMonster, 2);
	

	CCSprite* TimeImg = CCSprite::create("img/Time.png");
	TimeImg->setPosition(ccp(230, 620));
	this->addChild(TimeImg, 3);
	CCSprite* ScoreImg = CCSprite::create("img/Score.png");
	ScoreImg->setPosition(ccp(330, 620));
	this->addChild(ScoreImg, 3);
	
	LabelTime = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
	LabelTime->setPosition(ccp(250,610));
	LabelTime->setString(CCString::createWithFormat("%d", TickTime)->m_sString.c_str());
	this->addChild(LabelTime, 3);

	MapLoad();

	this->schedule(schedule_selector(HelloWorld::Bullet), 0.2f);
	this->schedule(schedule_selector(HelloWorld::TimeCheck), 0.1f);
	this->schedule(schedule_selector(HelloWorld::TimeCheck_), 1.0f);
    //this->schedule(schedule_selector(HelloWorld::BossEnemyCheck), 0.3f);

    return true;
}

void HelloWorld::update(float dt)
{
    if(GameEnd==false)
    {
        LabelTime->setString(CCString::createWithFormat("%d", TickTime)->m_sString.c_str());
        ///////////////////////////////
        if(Count>=3)
            CMon->BossAct(this);

        CMon->EnemyAct(this);


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
        
        float mCurrPercentage = CMon->m_pHPProgress->getPercentage();
        if(mCurrPercentage<=1)
            HealthGaze();

        
    }
    else
    {
        this->removeChild(Char, false);
        this->removeChild(Bomb1, false);
        this->removeChild(Bomb2, false);
        this->removeChild(CMon->m_pHPProgress, false);
        this->removeChild(CMon->Boss, false);

    }
    if(CMon->BossLife<=0)
    {
        

        WinCheck=true;
        GameEnd=true;

        if(RC==false)
        {
            WinResult = CCSprite::create("img/WinResult.png");
            WinResult->setPosition(ccp(visibleSize.width/2 + 
                origin.x, visibleSize.height/2 + origin.y));
            this->addChild(WinResult, 5);
            RC=true;

            ResultTime = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
            ResultTime->setPosition(ccp(385,425));
            ResultTime->setString(CCString::createWithFormat("%d", TickTime)->m_sString.c_str());
            this->addChild(ResultTime, 6);

            Result1 = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
            Result1->setPosition(ccp(215,362));
            Result1->setString(CCString::createWithFormat("%d", CMon->Score)->m_sString.c_str());
            this->addChild(Result1, 6);
            
            Result2 = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
            Result2->setPosition(ccp(215,318));
            Result2->setString(CCString::createWithFormat("%d", 100000-TickTime*100)->m_sString.c_str());
            this->addChild(Result2, 6);

            Result3 = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
            Result3->setPosition(ccp(215,260));
            Result3->setString(CCString::createWithFormat("%d", CMon->Score+(100000-TickTime*100))->m_sString.c_str());
            this->addChild(Result3, 6);

            CCMenuItemImage *MenuBtn = CCMenuItemImage::create("img/Go_Main_0.png", "img/Go_Main_1.png",
                this, menu_selector(HelloWorld::menuCloseCallback));
            MenuBtn->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-150));

            CCMenu* pMenu = CCMenu::create(MenuBtn, NULL);
            pMenu->setPosition(CCPointZero);
            this->addChild(pMenu, 6);
        }
    }
    if(Life<=0)
    {
        LoseCheck=true;
        if(RC==false)
        {
            LoseResult = CCSprite::create("img/LoseResult.png");
            LoseResult->setPosition(ccp(visibleSize.width/2 + 
                origin.x, visibleSize.height/2 + origin.y));
            this->addChild(LoseResult, 5);

            CCMenuItemImage *MenuBtn = CCMenuItemImage::create("img/Go_Main_0.png", "img/Go_Main_1.png",
                this, menu_selector(HelloWorld::menuCloseCallback));
            MenuBtn->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

            CCMenuItemImage *ReplayBtn = CCMenuItemImage::create("img/Replay_0.png", "img/Replay_1.png",
                this, menu_selector(HelloWorld::ReplayBtnClick));
            ReplayBtn->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-100));

            CCMenu* pMenu = CCMenu::create(MenuBtn, ReplayBtn, NULL);
            pMenu->setPosition(CCPointZero);
            this->addChild(pMenu, 6);

            RC=true;
        }
    }

    mBG01_Y			-=	mBGSpeed*gop;	// 1�����Ӹ��� mBGSpeed��ŭ ���� ������
    mBG02_Y			-=	mBGSpeed*gop;	
    if(abs(mBG01_Y) > 640)	// ���� ���� ������ �������ٸ�
    {		
        // ���� ��ġ�� �ʱ�ȭ�����ְ�, ������Ʈ�� ���� �����ְ� ���� ������
        Count++;
        mBG01_Y		=	0;
        mBG02_Y		=	640;
        return;			// �Լ��� ����
    }
    // �����Ӹ��� ���� ��ġ�� ����
    MAP->setPositionY(origin.y + mBG01_Y);
    MAP_->setPositionY(origin.y + mBG02_Y);



}

void HelloWorld::TimeCheck(float dt)
{
    if(GameEnd==false)
    {
        ticktime += 0.1;
        CMon->ScorePlus(this);
        float mCurrPercentage = CMon->m_pHPProgress->getPercentage();
        CMon->m_pHPProgress->setPercentage(mCurrPercentage - 0.5);
    }
}

void HelloWorld::TimeCheck_(float dt)
{
    if(GameEnd==false)
	    TickTime+=1;
}

void HelloWorld::HealthGaze()
{
	Life--;
	CMon->m_pHPProgress->setPercentage(100.f);

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
	mBGSpeed					=	1.0f*gop;		// ���� �����̴� �ӵ�
	MAP  ->setPosition(ccp( origin.x ,mBG01_Y));
	MAP_ ->setPosition(ccp(origin.x ,mBG02_Y ));
	this->addChild(MAP,0);
	this->addChild(MAP_,0);
}

void HelloWorld::SuperArmor(float dt) //���� ������ ��, 5�� �Ŀ� �������¸� Ǭ��.
{
	SuAm=false;
}

void HelloWorld::BombCheck(CCObject* pSender)
{
    if(BombUse==false && bomb>0)
    {
	    BombUse=true;
	    bomb--;
    }
}

void HelloWorld::LCount()
{
    if(GameEnd==false)
    {
        if(bomb==1)
        {
            removeChild(Bomb2, false);
            gop=4;
            Lazer->setPosition(ccp(mvt,400));
        }
        if(bomb==0)
        {
            removeChild(Bomb1, false);
            gop=4;
            Lazer->setPosition(ccp(mvt,400));
        }
        if(ticktime>=3)
            BombUse=false;
    }
}

void HelloWorld::Bullet(float dt)
{
    if(GameEnd==false)
        CMon->BulletSpawn(this, mvt);
}

void HelloWorld::LifeC() // ��� ���� �����Լ�
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

		GameEnd=true;
        //CCScene* pScene = CLoseScene::scene();

		//CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
	}
}

void HelloWorld::Check()
{
	CCObject* obj = NULL;
	
    float mCurrPercentage = CMon->m_pHPProgress->getPercentage();

    //CMon->EBC(this);

    CMon->LazerCrash(this , Lazer->boundingBox());

    if(SuAm==false)
    {
        rd1 = rand()%460+21;
        rd2 = rand()%460+21;
        rd3 = rand()%460+21;

        for(int i=0; i<7; i++)
        {
            if(CMon->Enemy1[i]->boundingBox().intersectsRect(Char->boundingBox()))
            {
                CMon->Enemy1[i]->setPosition(ccp(rd1,700+(730-CMon->Enemy1[i]->getPositionY() )));
                CMon->m_pHPProgress->setPercentage(mCurrPercentage - 50);
                Hit->playEffect("Sound/hit.wav"); 
                SuAm=true;
            }
            if(CMon->Enemy2[i]->boundingBox().intersectsRect(Char->boundingBox()))
            {
                CMon->Enemy2[i]->setPosition(ccp(rd2,700+(730-CMon->Enemy2[i]->getPositionY() )));
                CMon->m_pHPProgress->setPercentage(mCurrPercentage - 50);
                Hit->playEffect("Sound/hit.wav"); 
                SuAm=true;
            }
            if(CMon->Enemy3[i]->boundingBox().intersectsRect(Char->boundingBox()))
            {
                CMon->Enemy3[i]->setPosition(ccp(rd3,700+(730-CMon->Enemy3[i]->getPositionY() )));
                CMon->m_pHPProgress->setPercentage(mCurrPercentage - 50);
                Hit->playEffect("Sound/hit.wav"); 
                SuAm=true;
            }
            if(CMon->HealItem[i]->boundingBox().intersectsRect(Char->boundingBox()))
            {
                CMon->HealItem[i]->setPosition(ccp(1000,700));
                CMon->m_pHPProgress->setPercentage(mCurrPercentage + 50);
            }
            if(CMon->BossMis[i]->boundingBox().intersectsRect(Char->boundingBox()))
            {
                CMon->BossMis[i]->setPosition(ccp(rd3,700+(730-CMon->BossMis[i]->getPositionY() )));
                CMon->m_pHPProgress->setPercentage(mCurrPercentage - 60);
                Hit->playEffect("Sound/hit.wav"); 
                SuAm=true;
            }
        }
    }
    else if(SuAm==true)
    {

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
    if(GameEnd==false){
        CCPoint touchPoint = pTouch->getLocation();

        mvt=touchPoint.x;

        if(mvt<=10)
            mvt=11;
        else if(mvt>=470)
            mvt=469;

        Char->setPositionX(mvt);

        return true;
    }
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent* event)
{
    if(GameEnd==false){
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

void HelloWorld::ReplayBtnClick(CCObject* pSender)
{
	Click->playEffect("Sound/Click.wav");  

	CCScene* pScene = HelloWorld::scene();

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