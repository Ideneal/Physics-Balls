#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "ball.h"

using namespace std;

class System {
	private:
		vector<Ball *> myBall;
		bool gravity;
		float toGrad(float);
		float middleAngle(float, float);
	public:
		System();
		~System();
		
		bool getGravity() const;
		float getDistanza(Ball *, Ball *) const;
		
		void setGravity(bool);
		void addBall(Ball *);
		void addBall();
		void delBall();
		
		void setCollision(Ball *, Ball *);
		void checkCollision();
		void draw(SDL_Surface *);
};
#endif
