#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include "ball.h"
#include "system.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_DEPTH 32

using namespace std;

SDL_Surface * loadbg(string name){
	SDL_Surface * oldimg = IMG_Load(name.c_str());
	if (oldimg == NULL){
		cout << "Error to load background : " << SDL_GetError()<<endl;
		return NULL;
	}
	SDL_Surface * bg = SDL_DisplayFormat(oldimg);
	SDL_FreeSurface(oldimg);
	return bg;
}

int main() {

	SDL_Surface * screen = 0;
	bool running = true;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE | SDL_DOUBLEBUF);
	
	Ball * asd = new Ball(200,200,148,"blue_ball.bmp");
	Ball * lol = new Ball(10,200,74,"blue_ball.bmp");
	Ball * b1 = new Ball(263,190,323,"blue_ball.bmp");
	Ball * b2 = new Ball(280,178,248,"blue_ball.bmp");
	Ball * b3 = new Ball(176,279,300,"blue_ball.bmp");
	
	System * sys = new System();
	sys->addBall(asd);
	sys->addBall(lol);
	sys->addBall(b1);
	sys->addBall(b2);
	sys->addBall(b3);
	
	SDL_Surface * bg = loadbg("black_background.bmp");
	
	SDL_Event * event = new SDL_Event();
     	while(running){
     		while(SDL_PollEvent(event)){
     			if(event->type == SDL_QUIT)
     				running = false;
     		}
     		SDL_BlitSurface(bg, NULL, screen, NULL);
     		sys->draw(screen);
     		
     		if(SDL_Flip(screen) == -1)
     			return 1;
     		SDL_Delay(10);
    	}
    	
    	delete sys;
    	SDL_FreeSurface(screen);
    	SDL_Quit();
    	return 0;
}
