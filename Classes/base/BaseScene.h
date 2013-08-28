#ifndef _BASESCENE_H
#define _BASESCENE_H

#include "common.h"

class BaseScene:public CCScene,public CCKeypadDelegate
{
public:
    CCSpriteFrameCache *frameCache;
public:
    BaseScene():frameCache(NULL) {};
    virtual bool init();
    CREATE_FUNC(BaseScene);
};

#endif // !_BASESCENE_H
