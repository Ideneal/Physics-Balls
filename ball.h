#ifndef BALL_H
#define BALL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Ball{
	private:
		SDL_Surface * ballimg;
		int velocita;
		int raggio;
		float dx;
		float dy;
		float posx;
		float posy;
		float angolo;
		float toRad(float);
		
		bool verificato; //serve per il system.h
	public:
		Ball();
		Ball(SDL_Surface *);
		Ball(string);
		Ball(int, int, float);
		Ball(int, int, float, SDL_Surface *);
		Ball(int, int, float, string);
		~Ball();
		
		float getDX() const;
		float getDY() const;
		float getAngolo() const;
		int getVelocita() const;
		SDL_Surface * getImage() const;
		float getPosX() const;
		float getPosY() const;
		int getRaggio() const;
		bool getVerificato() const;
		
		void setImage(SDL_Surface *);
		void setImage(string);
		void setVelocita(int);
		void setAngolo(float);
		void setPosX(float);
		void setPosY(float);
		void setDX(float);
		void setDY(float);
		void setRaggio(int);
		void setVerificato(bool);
		void cleanUp();
		
		void draw(SDL_Surface *);
		void move();
};
#endif
