#include "CBullet.h"

void CBullet::BulInit(CCNode* node)
{
    BulCount=0;
    MisCount=0;

    for(int i=0; i<7; i++)
    {
        Bullet[i] = CCSprite::create("img/charmi.png");
        Bullet[i]->setPosition(ccp(1000,1000));
        node->addChild(Bullet[i], 2);
        
        SubBullet1[i] = CCSprite::create("img/charmi.png");
        SubBullet1[i]->setPosition(ccp(1000,1000));
        node->addChild(SubBullet1[i], 2);

        SubBullet2[i] = CCSprite::create("img/charmi.png");
        SubBullet2[i]->setPosition(ccp(1000,1000));
        node->addChild(SubBullet2[i], 2);

        SubBullet3[i] = CCSprite::create("img/charmi.png");
        SubBullet3[i]->setPosition(ccp(1000,1000));
        node->addChild(SubBullet3[i], 2);

        SubBullet4[i] = CCSprite::create("img/charmi.png");
        SubBullet4[i]->setPosition(ccp(1000,1000));
        node->addChild(SubBullet4[i], 2);
    }
}

void CBullet::BulSet(CCNode* node, float XPos)
{
    if(BulCount<7)
    {
        Bullet[BulCount]->setPosition(ccp(XPos, 150));

        if(MisCount >= 1)
        {
            SubBullet1[BulCount]->setPosition(ccp(XPos-20, 140));
        }
        if(MisCount >= 2)
        {
            SubBullet2[BulCount]->setPosition(ccp(XPos+20, 140));
        }
        if(MisCount >= 3)
        {
            SubBullet3[BulCount]->setPosition(ccp(XPos-40, 130));
        }
        if(MisCount >= 4)
        {
            SubBullet4[BulCount]->setPosition(ccp(XPos+40, 130));
        }
        
        BulCount++;
    }
    else if(BulCount==7)
    {
        BulCount=0;
        Bullet[BulCount]->setPosition(ccp(XPos, 150));

        if(MisCount >= 1)
        {
            SubBullet1[BulCount]->setPosition(ccp(XPos-20, 140));
        }
        if(MisCount >= 2)
        {
            SubBullet2[BulCount]->setPosition(ccp(XPos+20, 140));
        }
        if(MisCount >= 3)
        {
            SubBullet3[BulCount]->setPosition(ccp(XPos-40, 130));
        }
        if(MisCount >= 4)
        {
            SubBullet4[BulCount]->setPosition(ccp(XPos+40, 130));
        }

        BulCount++;
    }
}

void CBullet::BulAct(CCNode* node)
{
    for(int i=0; i<7; i++)
    {
        Bullet[i]->setPositionY(Bullet[i]->getPositionY()+10);
        
        if(MisCount >= 1)
        {
            SubBullet1[i]->setPosition(ccp(Bullet[i]->getPositionX()-20,Bullet[i]->getPositionY()));
        }
        if(MisCount >= 2)
        {
            SubBullet2[i]->setPosition(ccp(Bullet[i]->getPositionX()+20,Bullet[i]->getPositionY()));
        }
        if(MisCount >= 3)
        {
            SubBullet3[i]->setPosition(ccp(Bullet[i]->getPositionX()-40,Bullet[i]->getPositionY()-10));
        }
        if(MisCount >= 4)
        {
            SubBullet4[i]->setPosition(ccp(Bullet[i]->getPositionX()+40,Bullet[i]->getPositionY()-10));
        }

    }
}

void CBullet::BulCrash(int j)
{
    Bullet[j]->setPosition(ccp(1000, 1000));

    if(MisCount >= 1)
    {
        SubBullet1[j]->setPosition(ccp(1000, 1000));
    }
    if(MisCount >= 2)
    {
        SubBullet2[j]->setPosition(ccp(1000, 1000));
    }
    if(MisCount >= 3)
    {
        SubBullet3[j]->setPosition(ccp(1000, 1000));
    }
    if(MisCount >= 4)
    {
        SubBullet4[j]->setPosition(ccp(1000, 1000));
    }
}