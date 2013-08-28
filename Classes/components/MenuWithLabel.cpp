#include "MenuWithLabel.h"

void MenuWithLabel::onEnter()
{
	CCMenuItemSprite::onEnter();
	CCSize size = getContentSize();
	if(pos==left){
		setPositionX(-size.width/2-100);
	}else{
		setPositionX(VisibleRect::left().x+size.width/2+100);
	}
	float y;
	y = this->getPositionY();
	CCActionInterval *easeAction = CCEaseBackOut::create(CCMoveTo::create(0.5f,ccp(0,y)));
	runAction(easeAction);
}

MenuWithLabel *MenuWithLabel::createWithSpriteAndText(CCSprite *normal,CCSprite *pressed,const char *text,INIT_POS pos)
{
	MenuWithLabel *mwl = new MenuWithLabel();
	if(mwl&&mwl->initWithNormalSprite(normal,pressed,NULL,NULL,NULL)){
		mwl->autorelease();
	}
	CCLabelTTF *menuName = CCLabelTTF::create(text,"fonts/TransformersSolid.ttf",24);
	CCSize size = normal->getContentSize();
	menuName->setPosition(ccp(size.width/2,size.height/2));
	mwl->addChild(menuName);
	mwl->pos = pos;
	return mwl;
}