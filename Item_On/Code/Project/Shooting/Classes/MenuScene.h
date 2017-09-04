#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class CMenuScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	void Start(CCObject* pSender);
	void Quit(CCObject* pSender);
	CREATE_FUNC(CMenuScene);
	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);


	
	CocosDenshion::SimpleAudioEngine *BGM;
	CocosDenshion::SimpleAudioEngine *Click;
};
