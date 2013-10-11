#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common.h"
#include "ProtocolAds.h"
#include "PluginManager.h"

using namespace cocos2d::plugin;
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
class MyAdsListener:public AdsListener
{
    virtual void onAdsResult(AdsResultCode code, const char* msg);
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points);
};
#endif
class GameMain:public CCLayer
{

private:
    ProtocolAds *m_pAds;
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    MyAdsListener *m_pAdsListener;
#endif
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
