#include "DiamondSprite.h"

DiamondSprite *DiamondSprite::createDiamond(const char *frameName)
{
	DiamondSprite *ds = new DiamondSprite();
	if(ds&&ds->initWithSpriteFrameName(frameName)){
		ds->autorelease();
	}
	return ds;
}