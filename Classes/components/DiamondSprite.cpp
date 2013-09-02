#include "DiamondSprite.h"
#include "base/ShareVars.h"
#include "scenes/PlayScene.h"

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
	scheduleUpdate();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

void DiamondSprite::changePosition()
{
	if(fstDiamond&&secDiamond)
	{
		touchEnable = false;
		fstDiamond->setZOrder(1);
		secDiamond->setZOrder(2);
		CCPoint p1 = fstDiamond->getPosition();
		CCPoint p2 = secDiamond->getPosition();
		CCActionInterval *m1 = CCMoveTo::create(0.3f,p1);
		CCActionInterval *m2 = CCMoveTo::create(0.3f,p2);
		CCCallFunc *moveCompFunc = CCCallFunc::create(fstDiamond,callfunc_selector(DiamondSprite::changePostionHandler));
		CCSequence *moveSeq = CCSequence::create(m1,moveCompFunc,NULL);
		fstDiamond->runAction(m2);
		secDiamond->runAction(moveSeq);
	}
}

void DiamondSprite::changePostionHandler()
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(CHECK_CANBE_REMOVE);
}

bool DiamondSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(touchEnable&&isContainPoint(pTouch)){
		if(fstDiamond==NULL){
			fstDiamond = this;
		}else if(secDiamond==NULL){
			secDiamond = this;
			changePosition();
		}else{
			fstDiamond = this;
			secDiamond = NULL;
		}
	}
	return true;
}

void DiamondSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if(touchEnable&&isContainPoint(pTouch)){
		if(fstDiamond==NULL){
			fstDiamond = this;
		}else if(fstDiamond!=this&&secDiamond==NULL){
			secDiamond = this;
			changePosition();
		}else{
			fstDiamond = this;
			secDiamond = NULL;
		}
	}
}

void DiamondSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

bool DiamondSprite::isContainPoint( CCTouch *touch )
{
	CCPoint arPoint = getAnchorPointInPoints();
	CCPoint point = convertTouchToNodeSpaceAR(touch);
	CCSize spriteSize = getContentSize();
	CCRect spriteRect = CCRectMake(-arPoint.x,-arPoint.y,spriteSize.width,spriteSize.height);
	return spriteRect.containsPoint(point);
}

void DiamondSprite::update( float delta )
{
	if(row<D_ROW){
		DiamondSprite *blowDiamond = PlayScene::diamonds[row+1][col];
		if(isMoving==false&&blowDiamond==NULL){
			isMoving = true;
			CCLog("row %d,col %d",row+1,col);
			CCActionInterval *moveDown = CCMoveTo::create(0.3f,ccp(getPositionX(),getPositionY()-DIAMOND_HEIGHT));
			CCCallFunc *resetCallFunc = CCCallFunc::create(this,callfunc_selector(DiamondSprite::updatePosition));
			runAction(CCSequence::create(moveDown,resetCallFunc,NULL));
			
		}
	}
}

void DiamondSprite::updatePosition()
{
	this->row = this->row+1;
	isMoving = false;
	//PlayScene::diamonds[row][col] = this;
}
