#include "header.h"

CCScene* CMenuScene::scene()
{
    CCScene *scene = CCScene::create();
    CMenuScene *layer = CMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool CMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	BGM->playBackgroundMusic("Sound/BGM.mp3", true); 

	CCSprite* pSprite = CCSprite::create("img/mn_bg.png");
    pSprite->setPosition(ccp(240,320));
    this->addChild(pSprite, 0);

	CCMenuItemImage *Start = CCMenuItemImage::create("img/Start_0.png", "img/Start_1.png", this, menu_selector(CMenuScene::Start));
	Start->setPosition(ccp(240, 300));
    CCMenuItemImage *Quit = CCMenuItemImage::create("img/Quit_0.png", "img/Quit_1.png", this, menu_selector(CMenuScene::Quit));
	Quit->setPosition(ccp(240, 200));
    CCMenu* pMenu = CCMenu::create(Start, Quit, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    
    
    return true;
}


void CMenuScene::Start(CCObject* pSender)
{
	Click->playEffect("Sound/Click.wav");  

	CCScene* pScene = HelloWorld::scene();

	CCDirector::sharedDirector()->pushScene( createTransition(7, 1, pScene) );
}

void CMenuScene::Quit(CCObject* pSender)
{
	Click->playEffect("Sound/Click.wav");  
    CCDirector::sharedDirector()->end();
}

CCTransitionScene* CMenuScene::createTransition(int nIndex, float t, CCScene* s)
{
    CCDirector::sharedDirector()->setDepthTest(false);
    
    switch(nIndex)
    {
        case 7: return CCTransitionCrossFade::create(t, s);
            
        default: break;
    }
    
    return NULL;
}