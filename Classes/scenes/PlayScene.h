#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base\BaseScene.h"

class PlayScene:public BaseScene
{
public:
	/* 创建随机顺序的钻石 */
	void createDiamonds();

public:
    virtual bool init();
    CREATE_FUNC(PlayScene);
};

#endif // !_PLAYSCENE_H_
