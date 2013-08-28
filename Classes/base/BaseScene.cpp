#include "BaseScene.h"


bool BaseScene::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!CCScene::init());
        CCDirector::sharedDirector()->purgeCachedData();
        frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        frameCache->removeUnusedSpriteFrames();
        res = true;
    }
    while (0);
    return res;
}
