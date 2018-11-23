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
	   	int createCycle(int r, int w, int h, int amount, int speed);
	   	void setCurAnimation(int c){
			begin = 0; 
			curAnim = c;
		}
	   	void updateAnimation();
	   	
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

};

#endif //ENTITY_H
