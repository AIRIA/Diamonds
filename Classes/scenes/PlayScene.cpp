#include "PlayScene.h"

using namespace std;



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
	checkThree(diamonds);
	setRotateDiamonds();
	CCLog("---------");
	checkThree(rotateDiamonds);
}

void PlayScene::createDiamonds()
{
    srand(time(0));
    CCSpriteBatchNode *diamondBatch = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(hdpi_jewel1.png)->getTexture());
    addChild(diamondBatch);
    for(int i=0; i<D_ROW; i++)
    {
        for(int j=0; j<D_COL; j++)
        {
            int feed = rand()%(D_TYPE-1)+1;
            CCString *frameName = CCString::createWithFormat("hdpi_jewel%d.png",feed);
            DiamondSprite *diamond = DiamondSprite::createDiamond(frameName->getCString());
            diamond->type = feed;
            diamond->row = i;
            diamond->col = j;
            diamonds[i][j] = diamond;
            diamond->setPosition(ccp(DIAMOND_WIDTH*(j+0.5),VisibleRect::leftTop().y-DIAMOND_HEIGHT*(i+0.5)));
            diamondBatch->addChild(diamond);
        }
    }
}

void PlayScene::setRotateDiamonds()
{
    for(int i=0; i<D_ROW; i++)
    {
        for(int j=0; j<D_COL; j++)
        {
            rotateDiamonds[i][j] = diamonds[D_ROW-j-1][D_COL-i-1];
        }
    }
}

void PlayScene::checkThree( DiamondSprite *source[D_ROW][D_COL] )
{
	srand(time(NULL));
	DiamondSprite **ds;
	ds = source[0];
	for(int i=0; i<D_ROW; i++)
	{
		int prevType = 0;
		int num = 1;
		for(int j=0; j<D_COL; j++)
		{
			if(checkIsVailible(*ds))
			{
				CCLog("is availible at row %d,col%d",(*ds)->row,(*ds)->col);
			}
			int currentType = (*ds)->type;
			//CCLog("diamond type %d",currentType);
			if(prevType==0)
			{
				prevType = currentType;
			}
			else if (prevType==currentType)
			{
				num++;
			}
			else
			{
				num = 1;
				prevType = currentType;
			}
			if(num==3){
				CCLog("find 3 diamonds at row %d",(*ds)->row);
				while(prevType==currentType){
					currentType = rand()%(D_TYPE-1)+1;
				}
			}
			ds++;
		}
	}
}

bool PlayScene::checkIsVailible( DiamondSprite *ds )
{
	int row = ds->row,col=ds->col,type = ds->type;
	int t1,t2;
	if(row>0&&row<(D_ROW-1)){//y direction
		t1 = diamonds[row-1][col]->type;
		t2 = diamonds[row+1][col]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}
	if(col>0&&col<(D_COL-1)){//x direction
		t1 = diamonds[row][col-1]->type;
		t2 = diamonds[row][col+1]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}
	if(row>1){//up
		t1 = diamonds[row-1][col]->type;
		t2 = diamonds[row-2][col]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}
	if(row<(D_ROW-2)){//down
		t1 = diamonds[row+1][col]->type;
		t2 = diamonds[row+2][col]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}
	
	if(col>1){//left
		t1 = diamonds[row][col-1]->type;
		t2 = diamonds[row][col-2]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}

	if(col<(D_COL-2)){//right
		t1 = diamonds[row][col+1]->type;
		t2 = diamonds[row][col+2]->type;
		if(t1==t2&&t1==type){
			return true;
		}
	}
	return false;
}



