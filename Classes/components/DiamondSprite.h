#ifndef _DIAMONDSPRITE_H_
#define _DIAMONDSPRITE_H_

#include "common.h"

class DiamondSprite:public CCSprite,public CCTouchDelegate
{
public:
	int row;
	int col;
	int type;
public:
	static DiamondSprite *createDiamond(const char *frameName);
};

#endif //!_DIAMONDSPRITE_H_