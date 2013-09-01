#include "DiamondSprite.h"
#include "base/ShareVars.h"

DiamondSprite *DiamondSprite::createDiamond(const char *frameName)
{
	DiamondSprite *ds = new DiamondSprite();
	if(ds&&ds->initWithSpriteFrameName(frameName)){
		ds->autorelease();
	}
	return ds;
}

void DiamondSprite::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

bool DiamondSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(isContainPoint(pTouch)){
		this->setOpacity(128);
		if(fstDiamond==NULL){
			fstDiamond = this;
		}else if(secDiamond==NULL){

		}
	}
	return true;
}

void DiamondSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if(isContainPoint(pTouch)){
		this->setOpacity(128);
	}
}

void DiamondSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("Ended");
}

bool DiamondSprite::isContainPoint( CCTouch *touch )
{
	CCPoint arPoint = getAnchorPointInPoints();
	CCPoint point = convertTouchToNodeSpaceAR(touch);
	CCSize spriteSize = getContentSize();
	CCRect spriteRect = CCRectMake(-arPoint.x,-arPoint.y,spriteSize.width,spriteSize.height);
	return spriteRect.containsPoint(point);
}
