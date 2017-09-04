#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CBullet : public CCNode
{
private:

public:
    void BulInit(CCNode* node);
    void BulSet(CCNode* node, float XPos);
    void BulAct(CCNode* node);
    void BulCrash(int j);

    CCSprite*	Bullet[7];
    CCSprite*	SubBullet1[7];
    CCSprite*	SubBullet2[7];
    CCSprite*	SubBullet3[7];
    CCSprite*	SubBullet4[7];

    int BulCount, MisCount;
};