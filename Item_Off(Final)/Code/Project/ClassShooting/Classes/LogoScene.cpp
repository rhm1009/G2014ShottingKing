#include "LogoScene.h"
USING_NS_CC;


CCScene* CLogoScene::scene()
{
    CCScene *scene = CCScene::create();
    CLogoScene *layer = CLogoScene::create();
    scene->addChild(layer);
    return scene;
}

bool CLogoScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* pSprite = CCSprite::create("img/KGLogo.png");

    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(pSprite, 0);

    this->scheduleUpdate();	
	this->schedule(schedule_selector(CLogoScene::LogoTime), 1.5f);
    
    return true;
}

void CLogoScene::LogoTime(float dt)
{
	CLogoScene::transScene();
	dt=0;
}

void CLogoScene::transScene()
{
	CCScene* pScene = CMenuScene::scene();
	CCDirector::sharedDirector()->pushScene( createTransition(18, 1, pScene) );

}


CCTransitionScene* CLogoScene::createTransition(int nIndex, float t, CCScene* s)
{
    CCDirector::sharedDirector()->setDepthTest(false);
    
    switch(nIndex)
    {
        case 18: return CCTransitionFade::create(t, s, ccWHITE);
        default: break;
    }
    
    return NULL;
}
