#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base/BaseScene.h"
#include "components/DiamondSprite.h"

#define D_ROW 8
#define D_COL 8
#define DIAMOND_WIDTH 60
#define DIAMOND_HEIGHT 60
#define D_TYPE 8

class PlayScene:public BaseScene
{
public:
	DiamondSprite *diamonds[D_ROW][D_COL];
	DiamondSprite *rotateDiamonds[D_ROW][D_COL];
public:
	void changePosHandler();
	/* 检测一个宝石是不是可以被删除 */
	bool checkIsVailible(DiamondSprite *ds);
	/* 检测生成的钻石列表中是不是有可以消除的钻石 */
	void checkInitDiamonds();
	/* 创建随机顺序的8*8的钻石 */
	void createDiamonds();
	/* 旋转数组 */
	void setRotateDiamonds();
	/* 检测宝石交换位置后 是不是可以被删除 */
	void checkCanbeDes(CCObject *obj);
	void checkThree(DiamondSprite *source[D_ROW][D_COL]);
public:
    virtual bool init();
	virtual void draw();
    CREATE_FUNC(PlayScene);
	virtual void onEnter();
	virtual void onExit();
};

#endif // !_PLAYSCENE_H_
