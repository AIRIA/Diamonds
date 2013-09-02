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

#endif // !_COMMON_H_
