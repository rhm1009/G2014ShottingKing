#include "Unit.h"

#define UNIT_NORMAL			"UnitStateNormal"
#define UNIT_HIGHLIGHTED	"UnitstateHighlighted"
#define DEFAULT_BARSIZE		180

//Unit* Unit::createSolider(const char *pszFileName)
//{
//    Unit *pobSprite = new Unit();
//    if (pobSprite && pobSprite->initWithFile(pszFileName))
//    {
//        pobSprite->autorelease();
//        return pobSprite;
//    }
//    CC_SAFE_DELETE(pobSprite);
//    return NULL;
//}
Unit::Unit()
{
}

Unit::~Unit()
{

}
bool Unit::unitInit()
{
	if(this)
	{
		CCLog("this had alloced");
		state = UnitStateStop;
		maxHP = hp = 100;
		power = 0;
		hpBarBase_X = 140;
		needsRender = true;
		unitSelectedState = UnitStateNormal;
		_actionCache = NULL;

		baseHPBar = CCSprite::create("Unit/hp_bar.png");
		baseHPBar->setPosition(ccp(this->boundingBox().size.width/2, this->boundingBox().size.height+20));
		//baseHPBar->setScaleX(1.5);
		//baseHPBar->setScaleX(Unit::setSizeXByScale(hpBarBase_X , baseHPBar->boundingBox().size.width));
		baseHPBar->setColor(ccc3(0,0,0));
		this->addChild(baseHPBar);

		hpBar = CCSprite::create("Unit/hp_bar.png");
		hpBar->setAnchorPoint(ccp(0.0,0.0));
		hpBar->setPosition(ccp(0,0));
		//hpBar->setScaleX(1.5);
		//hpBar->setScaleX(Unit::setSizeXByScale(hpBarBase_X, baseHPBar->boundingBox().size.width));
		baseHPBar->addChild(hpBar);

		CCLog("base:%f bar:%f", baseHPBar->getScale(), hpBar->getScale());
		

		//this->schedule(schedule_selector());
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	Unit::getAtkUpInfo()
{
	return atkUpInfo;
}

int	Unit::getHlthUpInfo()
{
	return hlthUpInfo;
}

float Unit::getHP()
{
	return hp;
}

float Unit::getMaxHp()
{
	return maxHP;
}

float Unit::getPower()
{
	return power;
}

int	Unit::getState()
{
	return state;
}

bool Unit::isNeedsRender()
{
	return needsRender;
}

bool Unit::isFirstUnit()
{
	return _isFirstUnit;
}

int Unit::getUnitType()
{
	return charType;
}

int Unit::getUnitSelectedState()
{
	return unitSelectedState;
}

CCAction* Unit::getActionCache()
{
	return _actionCache;
}

//float Unit::getSpeed()
//{
//	return speed;
//}
//
//CCPoint Unit::getDestination()
//{
//	return destination;
//}

//CCArray* Unit::getCrashedObjects()
//{
	//return crashedObj;
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Unit::setAtkUpInfo(int _atkInfo)
{
	atkUpInfo = _atkInfo;
}

void Unit::setHlthUpInfo(int _hlthInfo)
{
	hlthUpInfo = _hlthInfo;
}

void Unit::setHP(float _hp)
{
	hp = _hp;
	setHPBar(hp,getMaxHp());
}

void Unit::setMaxHP(float _maxHP)
{
	maxHP = _maxHP;
}

void Unit::setPower(float _power)
{
	power = _power;
}

void Unit::setState(int _state)
{
	state = _state;

}

void Unit::setNeedsRender(bool _isNeedToRender)
{
	needsRender = _isNeedToRender;
}

void Unit::setFirstUnit(bool _firstUnit)
{
	_isFirstUnit = _firstUnit;
}

void Unit::setUnitType(int _type)
{
	charType = _type;
}

void Unit::setUnitSelectedState(int _unitSelectedState)
{
	unitSelectedState = _unitSelectedState;
	unitStateChanged();
}

void Unit::setActionCache(CCAction* action)
{
	_actionCache = action;
}

void Unit::setHPBar(float currentHP, float maxHP)
{
	//hpBar->setScaleX(setSizeXByScale(currentHP*baseHPBar->boundingBox().size.width/maxHP,hpBar->boundingBox().size.width));
	hpBar->setScaleX(currentHP*1/maxHP);
	CCLog("hpBarScale:%f hpBarWidth:%f",hpBar->getScaleX(), hpBar->boundingBox().size.width);
}

void Unit::setHPBarVisible(bool visible)
{
	baseHPBar->setVisible(visible);
	hpBar->setVisible(visible);
}

void Unit::setHPToMax()
{
	hp = maxHP;
}

//void Unit::setSpeed(float _speed)
//{
//	speed = _speed;
//}
//
//void Unit::setDestination(CCPoint dest)
//{
//	destination = dest;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Unit::unitStateChanged()
{
	switch(getUnitSelectedState())
	{
	case UnitStateNormal:
		unitNormal();
		break;
	case UnitStateHighlighted:
		unitHighlighted();
		break;
	default:
		break;
	}
}

void Unit::unitNormal()
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(UNIT_NORMAL, this);
}

void Unit::unitHighlighted()
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(UNIT_HIGHLIGHTED, this);
}

//void Unit::unitRun()
//{
//	float dest = (destination.x - this->boundingBox().origin.x) / speed;
//}

float Unit::setSizeXByScale(float size, float targetSpriteWidth)
{
	return size / targetSpriteWidth;
}

void Unit::setSizeX(float size)
{
	this->setScale(Unit::setSizeXByScale(size, this->boundingBox().size.width));
}