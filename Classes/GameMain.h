#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common.h"

class GameMain:public CCLayer
{
private:
    /* ��ʼ��UI���� */
    void initUI();
	/* ��ʼ����Ϸ */
	void newGameHandler(CCObject *pSender);
public:
    static CCScene *scene();
    virtual bool init();
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
