#pragma once

#include "header.h"

class CLogoScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CLogoScene);

    void LogoTime(float dt);
	void transScene();

	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);
};
