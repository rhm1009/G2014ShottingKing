#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "header.h"
#include "cMonster.h"

class HelloWorld : public cocos2d::CCLayer
{
private:

public: //�⺻���� �͵�
    virtual bool init();  

	cocos2d::CCPoint			origin;					//�ڵ������� �ػ󵵰� �ٸ��⶧���� x�� y�� ���������ִ�. �װ��� �����ϱ� ���� ����.
	cocos2d::CCSize				visibleSize;			//width = ȭ���� ���� ����. height = ȭ���� ���� ����.

    static cocos2d::CCScene* scene();

	void onEnter();
	void onExit();
	
	CREATE_FUNC(HelloWorld);
	CCTransitionScene* createTransition(int nIndex, float t, CCScene* s);

public:	//���Ǵ� ������ ����
	float mvt, BulX, BulY, ticktime, health_end, mBG01_Y, mBG02_Y, mBGSpeed;
	int Count, Life, bomb, gop, MisCount, Score, TickTime, itemRan, IR;

	int Em1x, Em1y, Em2x, Em2y, Em3x, Em3y, BosY, rd1, rd2, rd3, br, BossLife;

	bool bul,  Live, BossComing, SuAm, BombUse;

public: //�̸� ȣ�����ִ� �̹���, �迭, ��Ʋ�� ��
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
	
public: //�Լ���
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

	void EnemySpawn(float dt);//������ ������ �Լ�
    void BossEnemyCheck(float dt);//������ ������ �Լ�
	void Boss(); //������ ������ �Լ�
	void SuperArmor(float dt); // �ǰݽ� �����ð� �����Լ�

	void BombCheck(CCObject* pSender);
	void LCount();

	void Check(); //�浹, �̻��� ���� �Ÿ� �� �������ִ� �Լ�


	virtual void update(float dt);
    
    
public: //����
	CocosDenshion::SimpleAudioEngine *BGM;
	CocosDenshion::SimpleAudioEngine *Click;
	CocosDenshion::SimpleAudioEngine *WN;
	CocosDenshion::SimpleAudioEngine *Hit;
	CocosDenshion::SimpleAudioEngine *MD;
	CocosDenshion::SimpleAudioEngine *Boshit;
};
#endif // __HELLOWORLD_SCENE_H__
