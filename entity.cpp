#include "entity.h"


int Entity::createCycle(int r, int w, int h, int amount, int speed){
	   	cycle tmp;
	   	tmp.row = r;
	   	tmp.w = w;
	   	tmp.h = h;
	   	tmp.amount = amount;
	   	tmp.speed = speed;
	   	tmp.tick = 0;
	   	animations.push_back(tmp);
	   	return animations.size();
}

void Entity::updateAnimation(){
	setSource(animations[curAnim].w*animations[curAnim].tick, animations[curAnim].row*animations[curAnim].h  , animations[curAnim].w, animations[curAnim].h);
	
	if (begin > animations[curAnim].speed){
		   animations[curAnim].tick++;
		   begin = 0;
		
	}
	if (animations[curAnim].tick >= animations[curAnim].amount){
		animations[curAnim].tick = 0;
	}
} 