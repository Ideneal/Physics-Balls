#include "ball.h"

float Ball::toRad(float gradi){
	return (gradi * 2 * M_PI / 360);
}

Ball::Ball(){
	this->raggio = 16;
	this->verificato = false;
	this->ballimg = 0;
	this->velocita = 5;
	this->setAngolo(0);
	this->setPosX(0);
	this->setPosY(0);
	this->setImage("blue_ball.bmp");
}

Ball::Ball(SDL_Surface * img){
	this->ballimg = img;
	this->velocita = 5;
	this->setAngolo(0);
	this->setPosX(0);
	this->setPosY(0);
	this->raggio = 16;
	this->verificato = false;
}

Ball::Ball(string img){
	this->ballimg = 0; 
	this->setImage(img);
	this->velocita = 5;
	this->setAngolo(0);
	this->setPosX(0);
	this->setPosY(0);
	this->raggio = 16;
	this->verificato = false;
}

Ball::Ball(int px, int py, float angle){
	this->ballimg = 0;
	this->velocita = 5;
	this->setAngolo(angle);
	this->setPosX(px);
	this->setPosY(py);
	this->setImage("blue_ball.bmp");
	this->raggio = 16;
	this->verificato = false;
}

Ball::Ball(int px, int py, float angle, SDL_Surface * img){
	this->ballimg = 0;
	this->velocita = 5;
	this->setAngolo(angle);
	this->setPosX(px);
	this->setPosY(py);
	this->ballimg = img;
	this->raggio = 16;
	this->verificato = false;
}

Ball::Ball(int px, int py, float angle, string img){
	this->ballimg = 0;
	this->velocita = 5;
	this->setAngolo(angle);
	this->setPosX(px);
	this->setPosY(py);
	this->setImage(img);
	this->raggio = 16;
	this->verificato = false;
}

Ball::~Ball(){
	SDL_FreeSurface(this->ballimg);
	this->ballimg = 0;
}

float Ball::getDX() const{
	return this->dx;
}

float Ball::getDY() const{
	return this->dy;
}

float Ball::getPosX() const{
	return this->posx;
}

float Ball::getPosY() const{
	return this->posy;
}

float Ball::getAngolo() const{
	return this->angolo;
}

int Ball::getVelocita() const{
	return this->velocita;
}

SDL_Surface * Ball::getImage() const{
	return this->ballimg;
}

void Ball::setImage(SDL_Surface * img){
	this->ballimg = img;
}

void Ball::setImage(string name){
	SDL_Surface * oldimg = IMG_Load(name.c_str());
	//SDL_Surface * oldimg = SDL_LoadBMP(name.c_str());
	if(oldimg == NULL){
		cout << "Error to load img : " << SDL_GetError()<<endl;
		return;
	}
	this->ballimg = SDL_DisplayFormat(oldimg);
	if(this->ballimg == NULL){
		cout << "Errot to convert img : " << SDL_GetError() << endl;
		this->ballimg = 0;
		return;
	}
	Uint32 colorkey = SDL_MapRGB(this->ballimg->format, 0xFF, 0xFF, 0xFF);
	SDL_SetColorKey(this->ballimg, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
     	
     	SDL_FreeSurface(oldimg);
}

void Ball::setVelocita(int v){
	this->velocita = v;
}

void Ball::setAngolo(float angle){
	if (angle >= 360) angle -= 360;
	if (angle < 0) angle += 360;
	float a = this->toRad(angle);
	this->dx = this->velocita * cos(a);
	this->dy = this->velocita * sin(a);
	this->angolo = angle;
}

void Ball::setPosX(float X){
	this->posx = X;
}

void Ball::setPosY(float Y){
	this->posy = Y;
}

void Ball::setDX(float ddx){
	this->dx = ddx;
	float c = sqrt(pow(abs(this->dx),2) + pow(abs(this->dy),2));
	float alfa = asin( abs(this->dx) / c);
	if(this->dx < 0 && this->dy < 0)
		alfa += 180;
	else if(this->dx < 0 && this->dy > 0)
		alfa += 90;
	else if(this->dx > 0 && this->dy < 0)
		alfa = - alfa;
	this->setAngolo(alfa);
}

void Ball::setDY(float ddy){
	this->dy = ddy;
	float c = sqrt(pow(abs(this->dx),2) + pow(abs(this->dy),2));
	float alfa = acos( abs(this->dy) / c);
	if(this->dx < 0 && this->dy < 0)
		alfa += 180;
	else if(this->dx < 0 && this->dy > 0)
		alfa += 90;
	else if(this->dx > 0 && this->dy < 0)
		alfa = - alfa;
	this->setAngolo(alfa);
}

void Ball::cleanUp(){
	SDL_FreeSurface(this->ballimg);
	SDL_Quit();
}

void Ball::draw(SDL_Surface * screen){
	
	SDL_Rect * rettangolo = new SDL_Rect();
	//the rectangle has 4 parameters: x , y , w , h 
        rettangolo->x = this->posx;
        rettangolo->y = this->posy;
        
        SDL_BlitSurface(this->ballimg, NULL, screen, rettangolo);
        delete rettangolo;
        SDL_Flip(this->ballimg);
}

void Ball::move(){
	this->posx += this->dx;
	this->posy -= this->dy;
	if (this->getPosX() <= 0 || this->getPosX() >= 640 - (this->raggio * 2)){
		this->setAngolo(180 - this->getAngolo());
		while(this->getPosX() <= 0 || this->getPosX() >= 640 - (this->raggio * 2)){
			this->posx += this->dx;
			this->posy -= this->dy;
		}
	}
	if (this->getPosY() <= 0 || this->getPosY() >= 480 - (this->raggio * 2)){
		this->setAngolo(-this->getAngolo());
		while(this->getPosY() <= 0 || this->getPosY() >= 480 - (this->raggio * 2)){
			this->posx += this->dx;
			this->posy -= this->dy;
		}
	}
}

int Ball::getRaggio() const{
	return this->raggio;
}

void Ball::setRaggio(int r){
	this->raggio = r;
}

bool Ball::getVerificato() const{
	return this->verificato;
}

void Ball::setVerificato(bool v){
	this->verificato = v;
}
