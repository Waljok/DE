#include <windows.h>
#include "psapi.h"

#include <fstream>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const double PI = 3.14159265;

class Tail : public RectangleShape
{
public:
	Vector2f xc;
	float r, px, py;

	void fCheck(){
		px=getSize().x/2;
		py=getSize().x/2;
		r=floor(sqrtf(py*py + px*px))+2;
		xc.x=getPosition().x + px;
		xc.y=getPosition().y + py;
	}

	void cCheck(){xc.x=getPosition().x + px;  xc.y=getPosition().y + py;}
	Tail(){setFillColor(Color(100,100,100));}
};

struct sensor
{
	float x,y;
	Tail* t;
};

bool kol(sensor* D, Tail* t);
int  sss(sensor* D, Tail* t);
int  iii(sensor* D, Tail* t);
bool det(Tail* t, Vector2f p, float rp);


class Player : public RectangleShape
{
public:
	float vx, vy, px, py;
	bool  bb;
	int lx;
	sensor A, B, C, D, E, F, O, K;
	float hhd,hhu,hhr,hhl;
	sf::Vector2f xc,pos;
	float r;
	bool sgr,sls,srs,spt,fl;
	vector <Tail*> R;

	ofstream* out2;

	void dk(){
		A.t=0;B.t=0;C.t=0;D.t=0;
		K.t=0;F.t=0;O.t=0;E.t=0;
		//bb=0;
		//pos= getPosition();
		for(int i=0; i<R.size(); ++i)
	//	if (det(R[i],xc,r))
		{
			//bb=1;
			if(kol(&A,R[i])) {A.t=R[i];}
			if(kol(&B,R[i])) {B.t=R[i];}
			if(kol(&C,R[i])) {C.t=R[i];}
			if(kol(&D,R[i])) {D.t=R[i];}
			if(kol(&K,R[i])) {K.t=R[i];}
			if(kol(&F,R[i])) {F.t=R[i];}
			if(kol(&O,R[i])) {O.t=R[i];}
			if(kol(&E,R[i])) {E.t=R[i];}
		}



		if(A.t) hhd = A.t->getPosition().y - getSize().y; else
		if(B.t) hhd = B.t->getPosition().y - getSize().y; else hhd=600-getSize().y;

		if(D.t) hhu = D.t->getPosition().y + D.t->getSize().y; else 
		if(C.t) hhu = C.t->getPosition().y + C.t->getSize().y; else hhu=0;
		
		if(K.t) hhl = K.t->getPosition().x + K.t->getSize().x; else
		if(O.t) hhl = O.t->getPosition().x + O.t->getSize().x; else hhl=0;
		
		if(F.t) hhr = F.t->getPosition().x - getSize().x; else
		if(E.t) hhr = E.t->getPosition().x - getSize().x; else hhr=800-getSize().x;
	}

		
	


	void mvo(){	
		if (pos.y <  hhd && pos.y > hhu) {fl  = 1;} else fl = 0;
		if (pos.y >=  hhd)  {sgr = 1;} else sgr = 0;
		if (pos.y-1<=hhu)   {spt = 1;} else spt = 0;
		if (pos.x <= hhl)   {sls = 1;} else sls = 0;
		if (pos.x >= hhr)   {srs = 1;} else srs = 0;

		if (sgr) { bb=1;  if(vy>0) vy=0; if(pos.y>hhd) move3y(hhd);  } else bb=0;
		if (spt) {  if(vy<0) vy=0; if(pos.y<hhu) move3y(hhu); fl=1; }
		if (sls) {  if(vx<0) vx=0; if(pos.x<hhl) move3x(hhl);  }
		if (srs) {  if(vx>0) vx=0; if(pos.x>hhr) move3x(hhr);  }
		}


		
		
	virtual void move(){
		float x=1.0f, vx1,vy1,vm,vxa,vya;
		*out2 << pos.x << ' ' << pos.y << '\n';
		if (vx!=0 && vy!=0) {
			vx1=vx;vy1=vy;
			vxa=abs(vx);vya=abs(vy);
			if(vxa>=vya){vm=vxa; vx/=vxa; vy/=vxa;}else {vm=vya; vx/=vya; vy/=vya;}
			for(float i=0;i<vm;++i){  setPosition(pos.x + vx*x, pos.y + vy*x); checkPos();dk(); mvo();   }
			vx=vx1;vy=vy1;return;
		}
		else
		if (vx!=0){
			vx1=vx;
			vxa=abs(vx);
			vx/=vxa;
			for(float i=0;i<vxa;++i){  setPosition(pos.x + vx*x, pos.y); checkPos(); dk(); mvo();  }  
			vx=vx1;return;
		}
		else
		if (vy!=0){
			vy1=vy;  
			vya=abs(vy);
			vy/=vya;
			for(float i=0;i<vya;++i){  setPosition(pos.x, pos.y + vy*x); checkPos(); dk(); mvo(); }  
			vy=vy1;return;
		}
	}



	void ts(RectangleShape hp){
		if (fl)  {  if(vy<=6.0f) vy+=0.05f;}
		if(Keyboard::isKeyPressed(Keyboard::A) && !sls)  { vx= -12.0f;}
		else
		if(Keyboard::isKeyPressed(Keyboard::D) && !srs)  { vx=  7.0f;}
		if(Keyboard::isKeyPressed(Keyboard::W) && sgr && !spt)  { vy=-7.f;}
		
	}




	void checkPos(){
		pos = getPosition();
		
		// коллайдеры
		A.x=pos.x;		 A.y=pos.y+10;    // левый  нижний  нижний
		B.x=pos.x+9;     B.y=pos.y+10;    // правый нижний  нижний
		C.x=pos.x;		 C.y=pos.y-1;	  // левый  верхний верхний
		D.x=pos.x+9;     D.y=pos.y-1;	  // правый верхний верхний

		K.x=pos.x-1;	 K.y=pos.y+9;     // левый  нижний левый
		F.x=pos.x+10;    F.y=pos.y+9;     // правый нижний правый
		O.x=pos.x-1;	 O.y=pos.y;		  // левый  верхний левый
		E.x=pos.x+10;    E.y=pos.y;		  // правый верхний правый

		xc.x=pos.x + px;
		xc.y=pos.y + py;
	}


	void fCheck(vector <Tail*> T){
		R = T;
		px=getSize().x/2;
		py=getSize().x/2;
		r=floor(sqrtf(py*py + px*px))+2;
	}


	Player(){
		vx=0;  
		vy=0;  
		setFillColor(Color(255,100,200));
		setSize(Vector2f(10,10));
		setPosition(Vector2f(140,480));

	}



	bool mov(){if ((vx!=0 ) || (vy!=0 )) return true;  return false;}
	void stop(){if(vx!=0)vx=0; if(vy!=0)vy=0;}
	void move2(float x,float y){sf::Vector2f pos= getPosition();RectangleShape::setPosition(pos.x + x, pos.y + y);}
	void move3x(float x){sf::Vector2f pos= getPosition();RectangleShape::setPosition(x, pos.y);}
	void move3y(float y){sf::Vector2f pos= getPosition();RectangleShape::setPosition(pos.x, y);}
	void move3xy(float x, float y){sf::Vector2f pos= getPosition();RectangleShape::setPosition(x, y);}
	//void cCheck(){}
};


string IntToStr(float x)
{
    char buf[20];
    sprintf_s(buf,"%.5f",x);
    return buf;
}



string fIntToStr(int x)
{
    char buf[20];
    sprintf_s(buf,"%d",x);
    return buf;
}

string BTS(bool x)
{
	if (x) return "true";
	if (!x) return "false";
	return 0;
}



bool kol(sensor* D, Tail* t)
{
	if( ( D->x >= t->getPosition().x && D->x < t->getPosition().x + t->getSize().x ) && ( D->y >= t->getPosition().y && D->y < t->getPosition().y + t->getSize().y ) ) return true;
	return false;
}

bool det(Tail* t, Vector2f p, float rp)
{
	float xd,yd,sr;
	xd=t->xc.x-p.x;
	yd=t->xc.y-p.y;
	sr=rp+t->r;

	if((sr>=sqrtf(xd*xd + yd*yd)) || (p.x==t->xc.x && p.y==t->xc.y && rp==t->r)) return true;
	return false;
}