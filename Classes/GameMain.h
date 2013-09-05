#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common.h"
#include "ProtocolAds.h"
#include "PluginManager.h"

using namespace cocos2d::plugin;

class MyAdsListener:public AdsListener
{
	virtual void onAdsResult(AdsResultCode code, const char* msg);
	virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points);
};

class GameMain:public CCLayer
{

private:
	ProtocolAds *m_pAds;
	MyAdsListener *m_pAdsListener;
private:
    /* 初始化UI界面 */
    void initUI();
	/* 开始新游戏 */
	void newGameHandler(CCObject *pSender);
	/************************************************************************/
	/* 按返回键退出游戏                                                      */
	/************************************************************************/
	virtual void keyBackClicked();
public:
    static CCScene *scene();
    virtual bool init();
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
