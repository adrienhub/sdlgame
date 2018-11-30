#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "object.h"


//tutorials
//http://www.cplusplus.com/forum/beginner/140628/
//http://www.cplusplus.com/doc/tutorial/inheritance/
//http://www.cplusplus.com/reference/vector/vector/

class Entity: public Object{
	public:
		void setHealth(int h) {
			health = h;
		}
		void setMaxHealth(int h) {
			maxHealth = h;
		}
		int getHealth() const {
			return health;
		}
	   	int getMaxHealth() const {
		   return maxHealth;
		}
		/**
		 * row in sprite sheet, width and height frame, amount of frames, speed of animation
		 */
	   	int createCycle(int row, int w, int h, int amount, int speed);
	   	void setCurAnimation(int c){
			begin = 0; 
			curAnim = c;
		}
	   	void updateAnimation();
	   	void reverse(bool r){
		   rev = r;
		}
		void reverse(bool r, int nA){
		   rev = r;
		   nAb = 1;
		   nA = newAnim;
		}
	   	
	private:
		int health, maxHealth;
		struct cycle {
			int row;
			int w;
			int h;
			int amount;
			int speed;
			int tick;
		};
		vector<cycle> animations;
		int curAnim;
		int begin;
		bool rev, nAb;
		int newAnim;

};

#endif //ENTITY_H
