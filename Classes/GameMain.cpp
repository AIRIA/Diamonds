#include "GameMain.h"
#include "components\MenuWithLabel.h"
#include "scenes\PlayScene.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
void MyAdsListener::onAdsResult(AdsResultCode code, const char* msg)
{
    CCLog("OnAdsResult, code : %d, msg : %s", code, msg);
}

void MyAdsListener::onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points)
{
    CCLog("Player get points : %d", points);
    if (pAdsPlugin != NULL)
    {
        pAdsPlugin->spendPoints(points);
    }
}
#endif

//--------------------------------------------------
CCScene *GameMain::scene()
{

    CCScene *mainScene = CCScene::create();
    CCLayer *mainLayer = GameMain::create();
    mainScene->addChild(mainLayer);
    return mainScene;
}

bool GameMain::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        m_pAds = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
        m_pAdsListener = new MyAdsListener();
        TAdsDeveloperInfo devConfig;
        devConfig["AdmobID"] = "a15227e92acfd15";
        m_pAds->configDeveloperInfo(devConfig);
        m_pAds->setAdsListener(m_pAdsListener);
        m_pAds->setDebugMode(true);
        m_pAds->showAds(ProtocolAds::kBannerAd,0,ProtocolAds::kPosBottom);
        setKeypadEnabled(true);
#endif
        initUI();
        res = true;
    }
    while (0);
    return res;
}

void GameMain::initUI()
{
    //±³¾°Í¼Æ¬
    CCSprite *bgSpr = SPRITE(hdpi_title_bg1.jpg);
    bgSpr->setPosition(VisibleRect::center());
    addChild(bgSpr);
    //LOGO
    CCSprite *logoSpr = SPRITE(hdpi_logo.png);
    logoSpr->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-90));
    addChild(logoSpr);
    CCActionInterval *rotateLeft = CCRotateBy::create(3,5);
    CCActionInterval *rotateRight = CCRotateBy::create(3,-5);
    CCSequence *rotateSeq = CCSequence::create(rotateLeft,rotateLeft->reverse(),rotateRight,rotateRight->reverse(),NULL);
    logoSpr->runAction(CCRepeatForever::create(rotateSeq));
    //Menu
    MenuWithLabel *start = MenuWithLabel::createWithSpriteAndText(SPRITE(menu_normal.png),SPRITE(menu_pressed.png),"New Game",MenuWithLabel::left);
    MenuWithLabel *score = MenuWithLabel::createWithSpriteAndText(SPRITE(menu_normal.png),SPRITE(menu_pressed.png),"Scores",MenuWithLabel::right);
    MenuWithLabel *setting = MenuWithLabel::createWithSpriteAndText(SPRITE(menu_normal.png),SPRITE(menu_pressed.png),"Setting",MenuWithLabel::left);
    CCMenu *gameMenu = CCMenu::create(start,score,setting,NULL);
    gameMenu->alignItemsVerticallyWithPadding(15);
    addChild(gameMenu);
    start->setTarget(this,menu_selector(GameMain::newGameHandler));
}

void GameMain::newGameHandler(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(PlayScene::create());
}

void GameMain::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

