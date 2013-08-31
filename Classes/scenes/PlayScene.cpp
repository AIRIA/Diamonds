#include "PlayScene.h"

using namespace std;

#define ROW 8
#define COL 8
#define DIAMOND_WIDTH 60
#define DIAMOND_HEIGHT 60

bool PlayScene::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!BaseScene::init());
		//加载纹理
        frameCache->addSpriteFramesWithFile("textures/diamond.plist");
        CCSprite *bgSpr = SPRITE(hdpi_bground1.jpg);
        bgSpr->setPosition(VisibleRect::center());
        addChild(bgSpr);
		res = true;
		createDiamonds();
		checkInitDiamonds();
    }
    while (0);
    return res;
}

void PlayScene::draw()
{
	//在这里绘制网格
}

void PlayScene::checkInitDiamonds()
{
	CCObject *oneRow = NULL;
	CCARRAY_FOREACH(diamonds,oneRow)
	{
		CCArray *ds = (CCArray*)oneRow;
		CCObject *diamond;
		//相同钻石挨着的个数
		int num=1;
		int prevType=0;
		CCARRAY_FOREACH(ds,diamond)
		{
			DiamondSprite *diamondSpr = (DiamondSprite*)diamond;
			//CCLog("row %d",diamondSpr->row);
			if(prevType==0){
				prevType = diamondSpr->type;
			}else if(prevType==diamondSpr->type){
				num++;
			}else{
				num = 1;
				prevType = diamondSpr->type;
			}
			if(num==3){
				CCLog("find 3diamond  at row %d",diamondSpr->row);
				srand(time(NULL));
				int newType = prevType;
				while(newType==prevType){
					newType = rand()%(COL-1)+1;
				}
				prevType=newType;
				num = 1;
			}
		}
	}
}

void PlayScene::createDiamonds()
{
	srand(time(0));
	CCSpriteBatchNode *diamondBatch = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(hdpi_jewel1.png)->getTexture());
	addChild(diamondBatch);
	diamonds = CCArray::createWithCapacity(ROW);
	for(int i=0;i<ROW;i++){
		CCArray *col = CCArray::createWithCapacity(COL);
		for(int j=0;j<COL;j++){
			int feed = rand()%(COL-1)+1;
			CCString *frameName = CCString::createWithFormat("hdpi_jewel%d.png",feed);
			DiamondSprite *diamond = DiamondSprite::createDiamond(frameName->getCString());
			diamond->type = feed;
			diamond->row = i;
			diamond->col = j;
			col->addObject(diamond);
			cout << feed << " ";
			diamond->setPosition(ccp(DIAMOND_WIDTH*(j+0.5),VisibleRect::leftTop().y-DIAMOND_HEIGHT*(i+0.5)));
			diamondBatch->addChild(diamond);
		}
		cout << endl;
		diamonds->addObject(col);
	}
}

