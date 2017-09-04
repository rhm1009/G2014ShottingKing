#pragma once

#include "cocos2d.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SimpleAudioEngine.h"
#include "WinScene.h"
#include "CBullet.h"

USING_NS_CC;

class CMonster : public CCNode
{
private:
    CBullet* CBul;

public:
    int BosY, rd1, rd2, rd3, br, BossLife, Score, rd1_, rd2_, rd3_, ItemCount;
    bool BS;

    CCLabelAtlas* LabelScore;

    CCProgressTimer *m_pHPProgress;
	CCSprite *timer_gaze;

    void MonInit(CCNode* node);
    void EnemyAct(CCNode* node);
    void BulletSpawn(CCNode* node, float XPos);
    void BossAct(CCNode* node);
    void EnemyCrash(CCNode *node, const CCRect rect);
    void LazerCrash(CCNode *node, const CCRect rect);
    void Blood(CCNode* node, const CCPoint Pos);
    void BANG(CCNode* node, const CCPoint Pos);
    void ScorePlus(CCNode* node);
    void EBC(CCNode *node);
    void EnemyBulCrs(CCNode *node);
    void Item(const CCPoint Pos);

    CCSprite*   Boss;
    CCSprite*	Enemy1[7];
    CCSprite*	Enemy2[7];
    CCSprite*	Enemy3[7];
    CCSprite*	BossMis[7];

    CCSprite*	HealItem[27];

    CocosDenshion::SimpleAudioEngine *Hit;
	CocosDenshion::SimpleAudioEngine *MD;
	CocosDenshion::SimpleAudioEngine *Boshit;
    
	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);
};