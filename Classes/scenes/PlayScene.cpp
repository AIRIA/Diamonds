#include "PlayScene.h"

using namespace std;
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
	srand(time(0));
	CCSpriteBatchNode *diamondBatch = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(hdpi_jewel1.png)->getTexture());
	addChild(diamondBatch);
	diamonds = CCArray::createWithCapacity(8);
	for(int i=0;i<8;i++){
		CCArray *col = CCArray::createWithCapacity(8);
		for(int j=0;j<8;j++){
			int feed = rand()%7+1;
			CCString *frameName = CCString::createWithFormat("hdpi_jewel%d.png",feed);
			DiamondSprite *diamond = DiamondSprite::createDiamond(frameName->getCString());
			diamond->type = feed;
			diamond->row = i;
			diamond->col = j;
			col->addObject(diamond);
			cout << feed << " ";
			diamond->setPosition(ccp(60*j+30,VisibleRect::leftTop().y-60*i-30));
			diamondBatch->addChild(diamond);
		}
		cout << endl;
		diamonds->addObject(col);
	}
}

