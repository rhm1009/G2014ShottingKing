#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

class CWinScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(CWinScene);
	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);

	CocosDenshion::SimpleAudioEngine *BGM;
	CocosDenshion::SimpleAudioEngine *Click;
};
