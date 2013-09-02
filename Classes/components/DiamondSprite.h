#ifndef _DIAMONDSPRITE_H_
#define _DIAMONDSPRITE_H_

#include "common.h"

class DiamondSprite:public CCSprite,public CCTouchDelegate
{
private:
	bool isMoving;
public:
    int row;
    int col;
    int type;
    bool canBeRemove;
public:
    static DiamondSprite *createDiamond(const char *frameName);
	void updatePosition();
    /* �����Ѿ�ѡ�е�������ʯ��λ�� */
    static void changePosition();
    void changePostionHandler();
	virtual void update(float delta);
    bool isContainPoint(CCTouch *pTouch);
    virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    DiamondSprite():isMoving(false),canBeRemove(false) {};
};

#endif //!_DIAMONDSPRITE_H_