#ifndef _DIAMONDSPRITE_H_
#define _DIAMONDSPRITE_H_

#include "common.h"


class DiamondSprite:public CCSprite,public CCTouchDelegate
{
public:
	int row;
	int col;
	int type;
	bool canBeRemove;
public:
	bool isContainPoint(CCTouch *pTouch);
	virtual void onEnter();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	DiamondSprite():canBeRemove(false){};
	static DiamondSprite *createDiamond(const char *frameName);
};

#endif //!_DIAMONDSPRITE_H_