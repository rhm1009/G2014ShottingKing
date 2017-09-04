#include "CMonster.h"

void CMonster::MonInit(CCNode *node)
{
    CBul = new CBullet();
    CBul->BulInit(node);

    srand((int)time(NULL));
    BosY=550, BossLife=100000;
    rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
    Score=0;
    ItemCount=0;
    BS=false;

    LabelScore = CCLabelAtlas::create(",-./0123456789","Img/score_number_18x26.png",18,26,',');
	LabelScore->setPosition(ccp(350,610));
	LabelScore->setString(CCString::createWithFormat("%d", Score)->m_sString.c_str());
	node->addChild(LabelScore, 3);

    timer_gaze = CCSprite::create("img/xpbar_02.png");
	m_pHPProgress = CCProgressTimer::create(timer_gaze);
	m_pHPProgress->setPosition(ccp(250,600));
	m_pHPProgress->setScale(0.3f);
	m_pHPProgress->setPercentage(100);
	m_pHPProgress->setMidpoint(ccp(0, 0.5));    //³¡ ÁöÁ¡
	m_pHPProgress->setBarChangeRate(ccp(1, 0));
	m_pHPProgress->setType(kCCProgressTimerTypeBar);
	node->addChild(m_pHPProgress, 3);

    int PlusX=0, PlusY=0;

    Boss = CCSprite::create("img/boss.png");
	Boss->setPosition(ccp(240, 900));
	node->addChild(Boss, 3);

    for(int i=0; i<7; i++)
    {
        Enemy1[i] = CCSprite::create("img/enemy1.png");
        Enemy1[i]->setPosition(ccp(100+PlusX,1000+PlusY));
        node->addChild(Enemy1[i], 2);

        Enemy2[i] = CCSprite::create("img/enemy2.png");
        Enemy2[i]->setPosition(ccp(400-PlusX,1000+PlusY));
        node->addChild(Enemy2[i], 2);

        Enemy3[i] = CCSprite::create("img/enemy3.png");
        Enemy3[i]->setPosition(ccp(250,1000+PlusY));
        node->addChild(Enemy3[i], 2);

        BossMis[i] = CCSprite::create("img/Bosmi.png");
        BossMis[i]->setPosition(ccp(100+PlusX,1000+PlusY));
        node->addChild(BossMis[i], 2);

        PlusX+=50;
        PlusY+=100;
    }
    
    for(int i=0; i<27; i++)
    {
        HealItem[i] = CCSprite::create("img/Item_heal.png");
        HealItem[i]->setPosition(ccp(500, 500));
        node->addChild(HealItem[i], 3);
    }
}

void CMonster::ScorePlus(CCNode *node)
{
    Score++;
    LabelScore->setString(CCString::createWithFormat("%d", Score)->m_sString.c_str());
}

void CMonster::BulletSpawn(CCNode *node, float XPos)
{
    CBul->BulSet(node, XPos);
}



void CMonster::EnemyBulCrs(CCNode *node)
{
    float mCurrPercentage = m_pHPProgress->getPercentage();
    rd1_ = rand()%1000+750;
    rd2_ = rand()%1000+750;
    rd3_ = rand()%1000+750;

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<7; j++)
        {
            int item=rand()%7;

            if(Enemy1[i]->boundingBox().intersectsRect(CBul->Bullet[j]->boundingBox()))
            {
                Enemy1[i]->setPosition(ccp(rd1,rd1_));
                MD->playEffect("Sound/mondie.wav");
                Blood(node, CBul->Bullet[j]->getPosition());
                Score+=50;
                m_pHPProgress->setPercentage(mCurrPercentage + 2);
                CBul->BulCrash(j);

                if(item==2)
                {
                    Item(CBul->Bullet[j]->getPosition());
                }
            }
            if(Enemy2[i]->boundingBox().intersectsRect(CBul->Bullet[j]->boundingBox()))
            {
                Enemy2[i]->setPosition(ccp(rd2,rd2_));
                MD->playEffect("Sound/mondie.wav");
                Blood(node, CBul->Bullet[j]->getPosition());
                Score+=50;
                m_pHPProgress->setPercentage(mCurrPercentage + 2);
                CBul->BulCrash(j);

                if(item==2)
                {
                    Item(CBul->Bullet[j]->getPosition());
                }
            }
            if(Enemy3[i]->boundingBox().intersectsRect(CBul->Bullet[j]->boundingBox()))
            {
                Enemy3[i]->setPosition(ccp(rd3,rd3_));
                MD->playEffect("Sound/mondie.wav");
                Blood(node, CBul->Bullet[j]->getPosition());
                Score+=50;
                m_pHPProgress->setPercentage(mCurrPercentage + 2);
                CBul->BulCrash(j);

                if(item==2)
                {
                    Item(CBul->Bullet[j]->getPosition());
                }
            }
            if(BossMis[i]->boundingBox().intersectsRect(CBul->Bullet[j]->boundingBox()))
            {
                //BossMis[i]->setPosition(ccp(rd1,700+(730-BossMis[i]->getPositionY() )));
                BANG(node, CBul->Bullet[j]->getPosition());
                Score+=50;
                m_pHPProgress->setPercentage(mCurrPercentage + 2);
                CBul->BulCrash(j);
            }
            if(Boss->boundingBox().intersectsRect(CBul->Bullet[j]->boundingBox()))
            {
                Score+=20;
                m_pHPProgress->setPercentage(mCurrPercentage + 2);
                BossLife-=1000;
                CBul->BulCrash(j);
            }
        }
    }
}

void CMonster::Item(const CCPoint Pos)
{

    if(ItemCount<27)
    {
        HealItem[ItemCount]->setPosition(Pos);
        ItemCount++;
    }
    else if(ItemCount==27)
    {
        ItemCount=0;
        HealItem[ItemCount]->setPosition(Pos);
        ItemCount++;
    }
}

void CMonster::EnemyAct(CCNode *node)
{
    rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
    br = rand()%240+150;


    CBul->BulAct(node);

    for(int i=0; i<7; i++)
    {
        if(Enemy1[i]->getPositionY() > -30 && BS==false)
        {
            Enemy1[i]->setPositionY(Enemy1[i]->getPositionY()-7);
        }
        else if(Enemy1[i]->getPositionY() < -30)
        {
            Enemy1[i]->setPosition(ccp(rd1,700));
        }
        //////////////////////////////////////////////////////
        if(Enemy2[i]->getPositionY() > -30 && BS==false)
        {
            Enemy2[i]->setPositionX(Enemy2[i]->getPositionX()-1);
            Enemy2[i]->setPositionY(Enemy2[i]->getPositionY()-8);
        }
        else if(Enemy2[i]->getPositionY() < -30)
        {
            Enemy2[i]->setPosition(ccp(rd2,700));
        }
        //////////////////////////////////////////////////////
        if(Enemy3[i]->getPositionY() > -30 && BS==false)
        {
            Enemy3[i]->setPositionX(Enemy3[i]->getPositionX()+1);
            Enemy3[i]->setPositionY(Enemy3[i]->getPositionY()-9);
        }
        else if(Enemy3[i]->getPositionY() < -30)
        {
            Enemy3[i]->setPosition(ccp(rd3,700));
        }
        
        ///////////////////////////
        if(BS==true)
        {
            Enemy1[i]->setPosition(ccp(rd3,1900));
            Enemy2[i]->setPosition(ccp(rd3,1900));
            Enemy3[i]->setPosition(ccp(rd3,1900));
        }
        ////////////////////////////////////////////////////////////
        if(BossMis[i]->getPositionY() >= -30 && BS==true)
        {
            BossMis[i]->setPositionY(BossMis[i]->getPositionY()-8);
        }
        else if(BossMis[i]->getPositionY() <= -30)
        {
            BossMis[i]->setPosition(ccp(br,700));
        }
        


    }
    for(int i=0; i<27; i++)
    {
        ////////////////////////////item
        if(HealItem[i]->getPositionY() > -30)
        {
            HealItem[i]->setPositionY(HealItem[i]->getPositionY()-4);
        }
        else if(HealItem[i]->getPositionY() < -30)
        {
            HealItem[i]->setPosition(ccp(500,650));
        }
    }
}

void CMonster::BossAct(CCNode *node)
{
    if(BS==false)
    {
        BS=true;
    }
    if(Boss->getPositionY() > 450)
    {
        Boss->setPositionY(Boss->getPositionY()-3);
    }
}

void CMonster::EnemyCrash(CCNode* node, const CCRect rect)
{
    rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;
    rd1_ = rand()%1000+750;
	rd2_ = rand()%1000+750;
	rd3_ = rand()%1000+750;

    EnemyBulCrs(node);
    
    float mCurrPercentage = m_pHPProgress->getPercentage();

    for(int i=0; i<7; i++)
    {
        if(Enemy1[i]->boundingBox().intersectsRect(rect))
        {
            Enemy1[i]->setPosition(ccp(rd1,rd1_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Enemy2[i]->boundingBox().intersectsRect(rect))
        {
            Enemy2[i]->setPosition(ccp(rd2,rd2_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Enemy3[i]->boundingBox().intersectsRect(rect))
        {
            Enemy3[i]->setPosition(ccp(rd3,rd3_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(BossMis[i]->boundingBox().intersectsRect(rect))
        {
            //BossMis[i]->setPosition(ccp(rd3,700+(730-BossMis[i]->getPositionY() )));
            Score+=25;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Boss->boundingBox().intersectsRect(rect))
        {
            Score+=50;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
            BossLife-=10;

            if(BossLife<=0)
            {
                //CCScene* pScene = CWinScene::scene();
                //CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
            }
        }
        ///////////////////////
    }
}
void CMonster::LazerCrash(CCNode* node, const CCRect rect)
{
    rd1 = rand()%460+21;
	rd2 = rand()%460+21;
	rd3 = rand()%460+21;

    rd1_ = rand()%1000+750;
	rd2_ = rand()%1000+750;
	rd3_ = rand()%1000+750;
    
    float mCurrPercentage = m_pHPProgress->getPercentage();

    EnemyBulCrs(node);

    for(int i=0; i<7; i++)
    {
        if(Enemy1[i]->boundingBox().intersectsRect(rect))
        {
            Enemy1[i]->setPosition(ccp(rd1,rd1_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Enemy2[i]->boundingBox().intersectsRect(rect))
        {
            Enemy2[i]->setPosition(ccp(rd2,rd2_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Enemy3[i]->boundingBox().intersectsRect(rect))
        {
            Enemy3[i]->setPosition(ccp(rd3,rd3_));
            MD->playEffect("Sound/mondie.wav");
            Score+=100;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(BossMis[i]->boundingBox().intersectsRect(rect))
        {
            BossMis[i]->setPosition(ccp(rd3,700+(730-BossMis[i]->getPositionY() )));
            BANG(node, BossMis[i]->getPosition());
            Score+=25;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
        }
        if(Boss->boundingBox().intersectsRect(rect))
        {
            Score+=5;
            m_pHPProgress->setPercentage(mCurrPercentage + 2);
            BossLife--;

            if(BossLife<=0)
            {
                //CCScene* pScene = CWinScene::scene();
                //CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
            }
        }
        ///////////////////////
    }
}

void CMonster::Blood(CCNode *node, const CCPoint Pos)
{
	CCSprite* piPang = CCSprite::create("img/eft/blood_01.png");
	piPang->setPosition(Pos);

	CCAnimation* bld = CCAnimation::create();
	bld->addSpriteFrameWithFileName("img/eft/blood_01.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_02.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_03.png");
	bld->addSpriteFrameWithFileName("img/eft/blood_04.png");
	bld->setDelayPerUnit(0.05);
	bld->setRestoreOriginalFrame(true);

	CCAnimate* animate = CCAnimate::create(bld);
	CCCallFuncND* removeAction = CCCallFuncND::create(node, callfuncND_selector(CCNode::removeChild), animate);
	CCFiniteTimeAction* seq=CCSequence::create(animate, removeAction, NULL);

	node->addChild(piPang, 1);
	piPang->runAction(seq);


}

void CMonster::BANG(CCNode *node, const CCPoint Pos)
{
	CCSprite* Bang = CCSprite::create("img/eft/blaze_01.png");
	Bang->setPosition(Pos);

	CCAnimation* blz = CCAnimation::create();
	blz->addSpriteFrameWithFileName("img/eft/blaze_01.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_02.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_03.png");
	blz->addSpriteFrameWithFileName("img/eft/blaze_04.png");
	blz->setDelayPerUnit(0.05);
	blz->setRestoreOriginalFrame(true);

	CCAnimate* animate = CCAnimate::create(blz);
	CCCallFuncND* removeAction = CCCallFuncND::create(this, callfuncND_selector(CCNode::removeChild), animate);
	CCFiniteTimeAction* seq_=CCSequence::create(animate, removeAction, NULL);

	this->addChild(Bang, 1);
	Bang->runAction(seq_);


}

CCTransitionScene* CMonster::createTransition(int nIndex, float t, CCScene* s)
{
    CCDirector::sharedDirector()->setDepthTest(false);
    
    switch(nIndex)
    {
        case 7: return CCTransitionCrossFade::create(t, s);
            
        default: break;
    }
    
    return NULL;
}