#include "GameMain.h"
#include "components\MenuWithLabel.h"
#include "scenes\PlayScene.h"

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

