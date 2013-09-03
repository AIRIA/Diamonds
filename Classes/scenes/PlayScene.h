#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "base/BaseScene.h"
#include "components/DiamondSprite.h"


class PlayScene:public BaseScene
{
public:
	vector<DiamondSprite*> waitRemove;
	static DiamondSprite *diamonds[D_ROW][D_COL];
	static DiamondSprite *rotateDiamonds[D_ROW][D_COL];
	static CCSpriteBatchNode *diamondBatch;
public:
	/* 根据一个钻石获取他周围可以消除的钻石 */
	vector<DiamondSprite*> getDiamonds(DiamondSprite *ds);
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
	/* 检测是不是有三个连着的 */
	void checkThree(DiamondSprite *source[D_ROW][D_COL]);
	/* 更改两个钻石在vector中的位置 */
	void changePosInVector();
	/* 移除钻石 */
	void removeDiamonds(vector<DiamondSprite*> dsVec);
	/* 填补空位 */
	void fillNewDiamonds();
	/************************************************************************/
	/*                 检测给定的表格数组中所有可以消除的钻石                 */
	/************************************************************************/
	vector<DiamondSprite*> checkAllCanbeRemove(DiamondSprite *source[D_ROW][D_COL]);
	/************************************************************************/
	/* 在填充了新的钻石后检查是否有可以消除的                                 */
	/************************************************************************/
	void checkFillDiamonds(CCObject *obj);
	/************************************************************************/
	/* 返回到主菜单                                                          */
	/************************************************************************/
	virtual void keyBackClicked();
public:
    virtual bool init();
	virtual void draw();
    CREATE_FUNC(PlayScene);
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);
};

#endif // !_PLAYSCENE_H_
