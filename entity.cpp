#include "entity.h"

/**
 *  row in sprite sheet, width and height frame, amount of frames, speed of animation
 */
int Entity::createCycle(int row, int w, int h, int amount, int speed){
	   	cycle tmp;
	   	tmp.row = row -1 ; //-1;
	   	tmp.w = w;
	   	tmp.h = h;
	   	tmp.amount = amount;
	   	tmp.speed = speed;
	   	tmp.tick = 0;
	   	animations.push_back(tmp);
	   	return animations.size() -1; //[0-1]
}

void Entity::updateAnimation(){
	setSource(
		animations[curAnim].w*animations[curAnim].tick, 
		animations[curAnim].row*animations[curAnim].h, 
		animations[curAnim].w, 
		animations[curAnim].h
		);
	
	if (begin > animations[curAnim].speed){
		begin = 0;
		if (!rev)
			animations[curAnim].tick++;
		else
			animations[curAnim].tick--;
	}
	begin++;
	if (animations[curAnim].tick >= animations[curAnim].amount){
		animations[curAnim].tick = 0;
	}
	if (animations[curAnim].tick <= 0){
		if (nAb){
			curAnim = newAnim;
			nAb = 0;
			rev = 0;
		} else {
			animations[curAnim].tick <= 0; 
		}
	}
} 