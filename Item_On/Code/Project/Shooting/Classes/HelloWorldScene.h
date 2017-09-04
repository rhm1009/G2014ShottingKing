#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "header.h"
#include "cMonster.h"

class HelloWorld : public cocos2d::CCLayer
{
private:

public: //기본적인 것들
    virtual bool init();  

	cocos2d::CCPoint			origin;					//핸드폰마다 해상도가 다르기때문에 x와 y가 숨겨질수있다. 그것을 보정하기 위한 변수.
	cocos2d::CCSize				visibleSize;			//width = 화면의 가로 길이. height = 화면의 세로 길이.

    static cocos2d::CCScene* scene();

	void onEnter();
	void onExit();
	
	CREATE_FUNC(HelloWorld);
	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);

public:	//사용되는 변수들 모음
	float mvt, BulX, BulY, ticktime, health_end, mBG01_Y, mBG02_Y, mBGSpeed;
	int Count, Life, bomb, gop, MisCount, Score, TickTime, itemRan, IR;

	int Em1x, Em1y, Em2x, Em2y, Em3x, Em3y, BosY, rd1, rd2, rd3, br, BossLife;

	bool bul,  Live, BossComing, SuAm, BombUse;

public: //미리 호출해주는 이미지, 배열, 아틀라스 등
	CCLabelAtlas* LabelScore;
	CCLabelAtlas* LabelTime;

	cocos2d::CCSprite*	MAP;
	cocos2d::CCSprite*	MAP_;

	CCProgressTimer *m_pHPProgress;
	CCSprite *timer_gaze;

	
	cocos2d::CCArray*	Enm1;
	cocos2d::CCArray*	Enm2;
	cocos2d::CCArray*	Enm3;
	cocos2d::CCArray*	BossMi;

	cocos2d::CCSprite*	BossMonster;
	
	cocos2d::CCArray*	pBullet;
	cocos2d::CCArray*	HItem;
	cocos2d::CCArray*	MItem;
	cocos2d::CCArray*	LItem;

	cocos2d::CCSprite*	Char;
	cocos2d::CCSprite*	Lazer;
	

	cocos2d::CCSprite*	Heart1;
	cocos2d::CCSprite*	Heart2;
	cocos2d::CCSprite*	Heart3;

	cocos2d::CCSprite*	Bomb1;
	cocos2d::CCSprite*	Bomb2;
	
public: //함수들
	void TimeCheck(float dt);
	void TimeCheck_(float dt);
    
    void menuCloseCallback(CCObject* pSender);
	
	virtual bool ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(CCTouch *pTouch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(CCTouch *pTouch, cocos2d::CCEvent* event);

	void MapLoad();

	void Bullet(float dt);

	void LifeC();
	void HealthGaze();

	void ItemSpawn(const CCPoint Pos);
	void Blood(const CCPoint Pos);
	void BANG(const CCPoint Pos);

	void EnemySpawn(float dt);//적유닛 나오는 함수
    void BossEnemyCheck(float dt);//적유닛 나오는 함수
	void Boss(); //보스몹 나오는 함수
	void SuperArmor(float dt); // 피격시 일정시간 무적함수

	void BombCheck(CCObject* pSender);
	void LCount();

	void Check(); //충돌, 미사일 나간 거리 등 측정해주는 함수


	virtual void update(float dt);
    
    
public: //사운드
	CocosDenshion::SimpleAudioEngine *BGM;
	CocosDenshion::SimpleAudioEngine *Click;
	CocosDenshion::SimpleAudioEngine *WN;
	CocosDenshion::SimpleAudioEngine *Hit;
	CocosDenshion::SimpleAudioEngine *MD;
	CocosDenshion::SimpleAudioEngine *Boshit;
};
#endif // __HELLOWORLD_SCENE_H__
