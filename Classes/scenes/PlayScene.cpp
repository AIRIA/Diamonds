#include "PlayScene.h"

bool PlayScene::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!BaseScene::init());
		//¼ÓÔØÎÆÀí
        frameCache->addSpriteFramesWithFile("textures/diamond.plist");
        CCSprite *bgSpr = SPRITE(hdpi_bground1.jpg);
        bgSpr->setPosition(VisibleRect::center());
        addChild(bgSpr);
		res = true;
		createDiamonds();
    }
    while (0);
    return res;
}

void PlayScene::createDiamonds()
{
	
}

