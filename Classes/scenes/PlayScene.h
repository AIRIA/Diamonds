#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base/BaseScene.h"
#include "components/DiamondSprite.h"


class PlayScene:public BaseScene
{
public:
	CCArray *diamonds;
public:
	/* ������ɵ���ʯ�б����ǲ����п�����������ʯ */
	void checkInitDiamonds();
	/* �������˳���8*8����ʯ */
	void createDiamonds();
public:
	PlayScene():diamonds(NULL){};
    virtual bool init();
	virtual void draw();
    CREATE_FUNC(PlayScene);
};

#endif // !_PLAYSCENE_H_
