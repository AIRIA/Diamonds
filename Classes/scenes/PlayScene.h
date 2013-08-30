#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base/BaseScene.h"
#include "components/DiamondSprite.h"


class PlayScene:public BaseScene
{
public:
	CCArray *diamonds;
public:
	
	/* 创建随机顺序的8*8的钻石 */
	void createDiamonds();
public:
	PlayScene():diamonds(NULL){};
    virtual bool init();
    CREATE_FUNC(PlayScene);
};

#endif // !_PLAYSCENE_H_
