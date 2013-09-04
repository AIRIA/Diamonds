#include "PlayScene.h"
#include "base/ShareVars.h"
#include "GameMain.h"

using namespace std;

DiamondSprite *PlayScene::diamonds[D_ROW][D_COL] = {};
DiamondSprite *PlayScene::rotateDiamonds[D_ROW][D_COL] = {};
CCSpriteBatchNode *PlayScene::diamondBatch = NULL;

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
    diamondBatch = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(hdpi_jewel1.png)->getTexture());
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
            if(num==3)
            {
                CCLog("find 3 diamonds at row %d",(*ds)->row);
                while(prevType==currentType)
                {
                    while(checkIsVailible(*ds))
                    {
                        currentType = rand()%(D_TYPE-1)+1;
                        (*ds)->type = currentType;
                    }
                    CCString *frameName = CCString::createWithFormat("hdpi_jewel%d.png",currentType);
                    (*ds)->setDisplayFrame(frameCache->spriteFrameByName(frameName->getCString()));
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
    if(row>0&&row<(D_ROW-1)) //y direction
    {
        t1 = diamonds[row-1][col]->type;
        t2 = diamonds[row+1][col]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }
    if(col>0&&col<(D_COL-1)) //x direction
    {
        t1 = diamonds[row][col-1]->type;
        t2 = diamonds[row][col+1]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }
    if(row>1) //up
    {
        t1 = diamonds[row-1][col]->type;
        t2 = diamonds[row-2][col]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }
    if(row<(D_ROW-2)) //down
    {
        t1 = diamonds[row+1][col]->type;
        t2 = diamonds[row+2][col]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }

    if(col>1) //left
    {
        t1 = diamonds[row][col-1]->type;
        t2 = diamonds[row][col-2]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }

    if(col<(D_COL-2)) //right
    {
        t1 = diamonds[row][col+1]->type;
        t2 = diamonds[row][col+2]->type;
        if(t1==t2&&t1==type)
        {
            return true;
        }
    }
    return false;
}

void PlayScene::checkCanbeDes(CCObject *obj)
{
    vector<DiamondSprite*> temp;
    //记录下来两个钻石的原始 所在的行列数据
    changePosInVector();
    bool res = false;
	vector<DiamondSprite*> r1 = getDiamonds(fstDiamond);
	vector<DiamondSprite*> r2 = getDiamonds(secDiamond);
	waitRemove.insert(waitRemove.begin(),r1.begin(),r1.end());
	waitRemove.insert(waitRemove.begin(),r2.begin(),r2.end());
	removeDiamonds(waitRemove);
	
    if(r1.size()!=0||r2.size()!=0)
    {
		touchEnable = true;
    }
    else
    {
		changePosInVector();
        touchEnable = false;
        int fstOrder = fstDiamond->getZOrder();
        int secOrder = secDiamond->getZOrder();
		CCPoint p1 = ccp((secDiamond->col+0.5)*DIAMOND_WIDTH,VisibleRect::top().y-(secDiamond->row+0.5)*DIAMOND_HEIGHT);
		CCPoint p2 = ccp((fstDiamond->col+0.5)*DIAMOND_WIDTH,VisibleRect::top().y-(fstDiamond->row+0.5)*DIAMOND_HEIGHT);
        fstDiamond->getParent()->reorderChild(fstDiamond,secOrder);
        secDiamond->getParent()->reorderChild(secDiamond,fstOrder);
        CCActionInterval *m1 = CCMoveTo::create(CHANGE_TIME,p1);
        CCActionInterval *m2 = CCMoveTo::create(CHANGE_TIME,p2);
        CCCallFunc *moveCompFunc = CCCallFunc::create(this,callfunc_selector(PlayScene::changePosHandler));
        CCSequence *moveSeq = CCSequence::create(m1,moveCompFunc,NULL);
        fstDiamond->runAction(m2);
        secDiamond->runAction(moveSeq);
        secDiamond = fstDiamond = NULL;
    }
}

void PlayScene::onEnter()
{
    BaseScene::onEnter();
	scheduleUpdate();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(PlayScene::checkCanbeDes),CHECK_CANBE_REMOVE,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(PlayScene::checkFillDiamonds),CHECK_ALL_CANBE_REMOVE,NULL);
} 

void PlayScene::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CHECK_CANBE_REMOVE);
    BaseScene::onExit();
}

void PlayScene::changePosHandler()
{
    touchEnable = true;
}

vector<DiamondSprite*> PlayScene::getDiamonds( DiamondSprite *targetDS )
{
    vector<DiamondSprite*> diamondVec;
    //两个方向 row col
    int row = targetDS->row;
    DiamondSprite *ds;
    int prevType=0,currentType=0,num=1;
    vector<DiamondSprite*> tempRow;
    for(int i=0; i<D_COL; i++)
    {
        ds = diamonds[row][i];
		if(ds==NULL)
			continue;
        currentType = ds->type;
        if(prevType==0)
        {
            prevType = currentType;
        }
        else if(prevType==currentType)
        {
            num++;
        }
        else if(num>2)
        {
			diamondVec.insert(diamondVec.begin(),tempRow.begin(),tempRow.end());
			tempRow.clear();
			prevType = currentType;
			num=1;
        }
        else
        {
			num=1;
			tempRow.clear();
			prevType = currentType;
        }
		if(i==(D_COL-1)&&num>2)
		{
			tempRow.push_back(ds);
			diamondVec.insert(diamondVec.begin(),tempRow.begin(),tempRow.end());
			tempRow.clear();
			prevType = currentType;
			num=1;
		}
		tempRow.push_back(ds);
    }
	vector<DiamondSprite*> tempCol;
	int col = targetDS->col;
	prevType=0;
	num=1;
	for(int i=0;i<D_COL;i++)
	{
		ds = diamonds[i][col];
		if(ds==NULL)
			continue;
		currentType = ds->type;
		if(prevType==0)
		{
			prevType = currentType;
		}
		else if(prevType==currentType)
		{
			num++;
		}
		else if(num>2)
		{
			diamondVec.insert(diamondVec.begin(),tempCol.begin(),tempCol.end());
			tempCol.clear();
			prevType = currentType;
			num=1;
		}
		else
		{
			num=1;
			tempCol.clear();
			prevType = currentType;
		}
		if(i==(D_ROW-1)&&num>2)
		{
			tempCol.push_back(ds);
			diamondVec.insert(diamondVec.begin(),tempCol.begin(),tempCol.end());
			tempCol.clear();
			prevType = currentType;
			num=1;
		}
		tempCol.push_back(ds);
	}

    return diamondVec;
}

void PlayScene::changePosInVector()
{
	int frow = fstDiamond->row,fcol=fstDiamond->col,scol=secDiamond->col,srow=secDiamond->row;
	secDiamond->row = frow;
	secDiamond->col = fcol;
	fstDiamond->row = srow;
	fstDiamond->col = scol;

	diamonds[frow][fcol] = secDiamond;
	diamonds[srow][scol] = fstDiamond;
}

void PlayScene::removeDiamonds( vector<DiamondSprite*> dsVec )
{
	vector<DiamondSprite*>::iterator it = dsVec.begin();
	while(it!=dsVec.end())
	{
		CCActionInterval *act = CCScaleTo::create(REMOVE_TIME,0);
		(*it)->runAction(act);
		//(*it)->setOpacity(128);
		it++;
	}
	CCCallFuncN *fillNew = CCCallFuncN::create(this,callfuncN_selector(PlayScene::fillNewDiamonds));
	CCSequence *seq = CCSequence::create(CCDelayTime::create(REMOVE_TIME),fillNew,NULL);
	runAction(seq);
}

void PlayScene::fillNewDiamonds(CCNode *pSender)
{
	pSender->removeFromParent();
	vector<DiamondSprite*>::iterator it = waitRemove.begin();
	DiamondSprite *ds;
	while(it!=waitRemove.end())
	{
		ds = *it;
		ds->canBeRemove = true;
		diamonds[ds->row][ds->col] = NULL;
		it++;
	}
	waitRemove.clear();
}

void PlayScene::update( float delta )
{
	for(int i=0;i<D_COL;i++){
		DiamondSprite *ds = diamonds[0][i];
		if(ds==NULL){
			int currentType = rand()%(D_TYPE-1)+1;
			CCString *frameName = CCString::createWithFormat("hdpi_jewel%d.png",currentType);
			ds = DiamondSprite::createDiamond(frameName->getCString());
			ds->row = 0;
			ds->col = i;
			diamonds[0][i] = ds;
			ds->type = currentType;
			ds->setPosition(ccp(DIAMOND_WIDTH*(i+0.5),VisibleRect::leftTop().y+DIAMOND_HEIGHT*(0.5)));
			CCPoint targetPoint = ccp(DIAMOND_WIDTH*(i+0.5),VisibleRect::leftTop().y-DIAMOND_HEIGHT*(0.5));
			CCActionInterval *moveDown = CCMoveTo::create(DOWN_TIME,targetPoint);
			diamondBatch->addChild(ds);
			ds->runAction(moveDown);
		}
	}
}

vector<DiamondSprite*> PlayScene::checkAllCanbeRemove( DiamondSprite *source[D_ROW][D_COL] )
{
	vector<DiamondSprite*> tobeRemoveVec;
	DiamondSprite **ds = source[0];
	vector<DiamondSprite*> temp;
	int num=1;
	int prevType=0;
	for(int row=0;row<D_ROW;row++)
	{
		for(int col=0;col<D_COL;col++)
		{
			DiamondSprite *diamondSpr = *ds;
			if(diamondSpr==NULL){
				continue;
			}
			int currentType = diamondSpr->type;
			if(prevType==0)
			{
				prevType = currentType;
			}else if (prevType==currentType)
			{
				num++;
			}else if(num>2){
				tobeRemoveVec.insert(tobeRemoveVec.begin(),temp.begin(),temp.end());
				temp.clear();
				num=1;
				prevType = currentType;
			}else{
				num=1;
				temp.clear();
				prevType = currentType;
			}
			temp.push_back(diamondSpr);
			ds++;
		}
	}
	return tobeRemoveVec;
}

void PlayScene::checkFillDiamonds( CCObject *obj )
{
	vector<DiamondSprite*> r1 = checkAllCanbeRemove(diamonds);
	setRotateDiamonds();
	vector<DiamondSprite*> r2 = checkAllCanbeRemove(rotateDiamonds);
	waitRemove.insert(waitRemove.begin(),r1.begin(),r1.end());
	waitRemove.insert(waitRemove.begin(),r2.begin(),r2.end());
	removeDiamonds(waitRemove);
}

void PlayScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}


