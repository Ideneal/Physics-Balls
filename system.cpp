#include "system.h"

float System::toGrad(float rad){
	return (360 * rad / (2 * M_PI));
}


float System::middleAngle(float a, float b){
	float middle;
	bool traslatoa = false , traslatob = false;
	if(abs(a-b)>180){
		if(a < b){
			a += 360;
			traslatoa = true;
		}else{
			b += 360;
			traslatob = true;
		}
	}
	
	middle = abs(a-b) / 2;
	
	if(abs(a-b) == 180){
		middle = b+180;
		if(middle>=360) middle -=360;
	}
	
	if(traslatoa) a -= 360;
	if(traslatob) b -= 360;
	
	if(abs(a-b) > 180){
		if(a < b)
			middle = a-middle;
		else
			middle = b-middle;
	}else{
		if(a<b)
			middle = a + middle;
		else
			middle = b + middle;
	}
		
	return middle;
}

System::System(){
	this->gravity = false;
}

System::~System(){
	if(this->myBall.size() > 0){
		for(int i = this->myBall.size() - 1 ; i >= 0; i--){
			delete this->myBall[i];
			this->myBall.pop_back();
		}
	}
}


bool System::getGravity() const{
	return this->gravity;
}


void System::setGravity(bool gr){
	this->gravity = gr;
}

void System::addBall(Ball * b){
	this->myBall.push_back(b);
}

void System::addBall(){
	Ball * b = new Ball();
	this->myBall.push_back(b);
}

void System::delBall(){
	delete this->myBall[this->myBall.size() - 1] ;
	this->myBall.pop_back();
}

void System::setCollision(Ball * x , Ball * y){
	//commento molto veloce
	/*quando si intersecano le due palline vengono considerate come due punti P1 e P2 che insieme a P3 formano un triangolo rettangolo.
	con questo triangolo mi trovo l'angolo alfa in P2 che sarebbe l'angolazione delle due palline. La distanza fra gli angoli opposti e 
	alfa mi dice di quanto devo ruotare ulteriormente l'angolo di ogni pallina*/
	float p1x, p1y, p2x, p2y, p3x, p3y; //cordinate dei punti di stato
	float a,b,c; //lati dell'angolo che si forma all'intersezione delle palline
	float alfa; //angolo che si forma fra l'intersezione delle due palle
	float angx , angy, delta;
	bool traslato = false;
	p1x = x->getPosX();
	p1y = x->getPosY();
	p2x = y->getPosX();
	p2y = y->getPosY();
	p3x = p1x;
	p3y = p2y;
	
	a = abs(p1y - p2y);
	b = abs(p2x - p1x);
	c = sqrt(pow(a , 2) + pow (b , 2));
	
	if(c != 0)
		alfa = this->toGrad(acos(b/c));
	else
		alfa = 0;
	
	if(p1x < p2x){
		if(p1y < p2y){
			alfa = 180 - alfa;
		}else{
			alfa += 180;
		}
	}else{
		if(p1y < p2y){
			alfa = alfa;
		}else{
			alfa = 360 - alfa;
		}
	}
	
	
	if(alfa < 0) alfa += 360;
	if(alfa >= 360) alfa -= 360;
	
	x->setAngolo(this->middleAngle(alfa, y->getAngolo()));
	alfa += 180;
	if(alfa >= 360) alfa -= 360;
	y->setAngolo(this->middleAngle(alfa, x->getAngolo()));
	
	while(this->getDistanza(x, y) < x->getRaggio() * 2){
		x->move();
		y->move();
	}
}

void System::checkCollision(){
	if (this->myBall.size() > 1){
		for(int i=0; i < this->myBall.size() ; i++){
			for(int j=0; j<this->myBall.size() ; j++){
				if (i != j && !this->myBall[i]->getVerificato() ){
					if (this->getDistanza(myBall[i], myBall[j]) < myBall[i]->getRaggio() * 2){
						this->setCollision(this->myBall[i], this->myBall[j]);
						this->myBall[j]->setVerificato(true);
					}
				}
			}
			this->myBall[i]->setVerificato(true);
		}
	}
	
	for(int i=0; i < this->myBall.size() - 1 ; i++){
		this->myBall[i]->setVerificato(false);
	}
}

float System::getDistanza(Ball * x, Ball * y) const {
	float a = x->getPosX() - y->getPosX();
	float b = x->getPosY() - y->getPosY();
	return sqrt(pow(a, 2) + pow(b, 2));
	//teorema di pitagora xD
}

void System::draw(SDL_Surface * scr){
	
	this->checkCollision();
	vector<Ball *>::iterator it;
	for( it=this->myBall.begin(); it < this->myBall.end() ; it++){
		(*it)->move();
		(*it)->draw(scr);
	}
}
						
