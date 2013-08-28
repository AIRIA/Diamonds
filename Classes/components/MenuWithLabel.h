#ifndef _MENUWITHLABLE_H_
#define _MENUWITHLABLE_H_

#include "common.h"
/* �����ֵ�ͼƬ�˵� */
class MenuWithLabel:public CCMenuItemSprite
{
public:
	typedef enum{
		left,
		right
	} INIT_POS;

	INIT_POS pos;
public:
	virtual void onEnter();
	static MenuWithLabel *createWithSpriteAndText(CCSprite *normal,CCSprite *pressed,const char*,INIT_POS=left);
};

#endif // !_MENUWITHLABLE_H_
