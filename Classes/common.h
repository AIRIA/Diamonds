#ifndef _COMMON_H_
#define _COMMON_H_

#include "cocos2d.h"
#include "VisibleRect.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#define SPRITE_FRAME(url) CCSprite::createWithSpriteFrameName(#url)
#define SPRITE(imageName) CCSprite::create(#imageName)

#define D_ROW 8
#define D_COL 8
#define DIAMOND_WIDTH 60
#define DIAMOND_HEIGHT 60
#define D_TYPE 8
#define DOWN_TIME 0.1f
#define REMOVE_TIME 0.2f
#define CHANGE_TIME 0.2F

#endif // !_COMMON_H_
