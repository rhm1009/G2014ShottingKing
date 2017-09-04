#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

USING_NS_CC;

/*
State Type

"STOP"
"RUN"
"BATTLE"

*/

enum UnitState
{
	UnitStateStop = 0,
	UnitStateRun = 1,
	UnitStateBattle = 2,
	UnitStateIdle = 3,
	UnitStateDie = 4,
	UnitStateTowerBattle = 5,
	UnitStateTempCollision = 6
};

enum UnitSelectedState
{
	UnitStateNormal,
	UnitStateHighlighted,
	UnitStateSelectingMod,
};

class Unit : public CCSprite
{
	
	float			hp;		// default is 100
	float			maxHP;	// default is 100
	float			power;	// default is 0

	int				atkUpInfo;
	int				hlthUpInfo;

	//float			speed;
	//CCPoint			destination;

	int				state;
	bool			needsRender;

	bool			_isFirstUnit;

	int				charType;
	int				unitSelectedState;
	
	CCAction*		_actionCache;

	float			hpBarBase_X;
	CCSprite*		baseHPBar;
	CCSprite*		hpBar;
private: // Private Func


public:
	Unit();
	~Unit();
	virtual	bool	unitInit();

public:
	int				getAtkUpInfo();
	int				getHlthUpInfo();

	float			getHP();
	float			getMaxHp();
	float			getPower();

	int				getState();
	bool			isNeedsRender();

	bool			isFirstUnit();

	int				getUnitType();
	int				getUnitSelectedState();

	CCAction*		getActionCache();

	//float			getSpeed();
	//CCPoint			getDestination();

public:
	void			setAtkUpInfo(int _atkInfo);
	void			setHlthUpInfo(int _hlthInfo);

	void			setHP(float _hp);
	void			setMaxHP(float _maxHP);
	void			setPower(float _power);

	void			setState(int _state);
	void			setNeedsRender(bool _isNeedToRender);

	void			setFirstUnit(bool _firstUnit);
	
	void			setUnitType(int _type);
	void			setUnitSelectedState(int _unitSelectedState);

	void			setActionCache(CCAction* action);

	void			setHPBar(float currentHP, float maxHP);
	void			setHPBarVisible(bool visible);

	//void			setSpeed(float _speed);
	//void			setDestination(CCPoint dest);

public: // Public Functions
	void			setHPToMax();
	
	void			unitStateChanged();
	
	void			unitNormal();		// notificate "UnitStateNormal"
	void			unitHighlighted();	// notificate "UnitstateHighlighted"
	
	void			unitRun();

	void			setSizeX(float size);

public: // Static Functions
	static float	setSizeXByScale(float size, float targetSpriteWidth); // return Scale Size
public: 
	
};

#endif