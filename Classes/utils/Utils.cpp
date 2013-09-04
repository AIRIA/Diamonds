#include "Utils.h"

bool Utils::isDuplicate( vector<DiamondSprite*> vec,DiamondSprite *ds )
{
	vector<DiamondSprite*>::iterator it = vec.begin();
	DiamondSprite *currentDs;
	while(it!=vec.end()){
		currentDs = *it;
		if(currentDs->row==ds->row&&currentDs->col==ds->col){
			return true;
		}
		it++;
	}
	return false;
}

