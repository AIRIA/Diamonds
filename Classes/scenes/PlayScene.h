#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base/BaseScene.h"
#include "components/DiamondSprite.h"


class PlayScene:public BaseScene
{
public:
	CCArray *diamonds;
public:
	/* 检测生成的钻石列表中是不是有可以消除的钻石 */
	void checkInitDiamonds();
	/* 创建随机顺序的8*8的钻石 */
	void createDiamonds();
public:
	PlayScene():diamonds(NULL){};
    virtual bool init();
	virtual void draw();
    CREATE_FUNC(PlayScene);
};

#endif // !_PLAYSCENE_H_
