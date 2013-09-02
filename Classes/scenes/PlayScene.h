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
	vector<DiamondSprite*> waitRemove;
	DiamondSprite *diamonds[D_ROW][D_COL];
	DiamondSprite *rotateDiamonds[D_ROW][D_COL];
public:
	/* ����һ����ʯ��ȡ����Χ������������ʯ */
	vector<DiamondSprite*> getDiamonds(DiamondSprite *ds);
	void changePosHandler();
	/* ���һ����ʯ�ǲ��ǿ��Ա�ɾ�� */
	bool checkIsVailible(DiamondSprite *ds);
	/* ������ɵ���ʯ�б����ǲ����п�����������ʯ */
	void checkInitDiamonds();
	/* �������˳���8*8����ʯ */
	void createDiamonds();
	/* ��ת���� */
	void setRotateDiamonds();
	/* ��ⱦʯ����λ�ú� �ǲ��ǿ��Ա�ɾ�� */
	void checkCanbeDes(CCObject *obj);
	void checkThree(DiamondSprite *source[D_ROW][D_COL]);
	/* ����������ʯ��vector�е�λ�� */
	void changePosInVector();
	/* �Ƴ���ʯ */
	void removeDiamonds(vector<DiamondSprite*> dsVec);
	
public:
    virtual bool init();
	virtual void draw();
    CREATE_FUNC(PlayScene);
	virtual void onEnter();
	virtual void onExit();
};

#endif // !_PLAYSCENE_H_
