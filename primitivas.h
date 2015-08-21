#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <GL/freeglut.h>
#include <GL/gl.h>
#define round(X) (int)floor(X+0.5)
#define MAYOR(a,b) (a>b?a:b)
#define MENOR(a,b) (a<b?a:b)

using namespace std;

namespace primitivas{

	void pintar(int x, int y, int size=0){
		glBegin(GL_POINTS);
		for(int i=-size;i<=size;i++){
			for(int j=-size;j<=size;j++){
				glVertex2i(x+i, y+j);
			}
		}
		glEnd();
	}
	
	void borrar(int x, int y){
		float colores[4];
		float colores2[4];
		glGetFloatv(GL_CURRENT_COLOR, colores);
		glGetFloatv(GL_COLOR_CLEAR_VALUE, colores2);
		glColor4f(colores2[0], colores2[1], colores2[2], colores2[3]);
		for(int i=-10;i<=10;i++)
			for(int j=-10;j<=10;j++)
					pintar(x+i, y+j);
		glColor4f(colores[0], colores[1], colores[2], colores[3]);
	}

	void linea(int x1,int  y1,int x2, int y2,int size=0){
		int dx=abs(x2-x1);
		int dy=abs(y2-y1);
		if(dy==0){
			if(x2<x1)
			swap(x1,x2);
			for(;x1<=x2;x1++)
			pintar(x1,y1,size);
		}else if(dx==0){
			if(y1>y2)
			swap(y1,y2);
			for(;y1<=y2;y1++)
			pintar(x1,y1,size);
			
		}else if(dx==dy){
			if(x1>x2){
				swap(x1,x2);
				swap(y1, y2);
			}
			int incremento=(y1<y2?1:-1);
			for(;x1<=x2;x1++,y1+=incremento){
				pintar(x1,y1,size);
			}
		}
		else if(dy<dx){
			if(x1>x2){
				swap(x1,x2);
				swap(y1, y2);
			}
			int x=x1, y=y1;
			int incremento=(y1<y2?1:-1);
			int p=0;
			p=2*dy-dx;
			while(x!=x2 or y!=y2){
				pintar(x,y,size);
				if(p>=0){
					x++;
					y+=incremento;
					p=p+2*dy-2*dx;
				}else{
					x++;
					p=p+2*dy;
				}
			}
		}else{	
			if(y1>y2){
				swap(x1,x2);
				swap(y1, y2);
			}
			int y=y1, x=x1;
			int incremento=(x1<x2?1:-1);
			int p=0;
			p=2*dx-dy;
			while(y!=y2 or x!=x2){
				pintar(x,y,size);
				if(p>0){
					y++;
					x+=incremento;
					p=p+2*dx-2*dy;
				}else{
					y++;
					p=p+2*dx;
				}
			}
		}
		pintar(x2,y2,size);
		glFlush();
	}

	void elipse(int h, int k, double a, double b, int size=0){
		int x=0;
		int y=b;
		int p;
		p=int(b*b-a*a*b+0.25*a*a);
		pintar(h+x,k+y,size);
		pintar(h-x,k+y,size);
		pintar(h+x,k-y,size);
		pintar(h-x,k-y,size);
		
		while(x*b*b < y*a*a){
			if(p<0){
				p=p+2*x*b*b+b*b;
			}else{
				y--;
				p=p+2*x*b*b+b*b-2*y*a*a;
			}
			x++;
			pintar(h+x,k+y,size);
			pintar(h-x,k+y,size);
			pintar(h+x,k-y,size);
			pintar(h-x,k-y,size);
		}
		
		p=int(b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b);
		
		while(y>0){
			if(p>0){
				y--;
				p=p-2*a*a*y+a*a;
			}else{
				x++;
				y--;
				p=p+2*b*b*x-2*a*a*y+a*a;
			}
			pintar(h+x,k+y,size);
			pintar(h-x,k+y,size);
			pintar(h+x,k-y,size);
			pintar(h-x,k-y,size);
		}
		glFlush();
	}

	void poligono(int x, int y, int r, double ang, int l, int size=0){
		int h, k;
		int p, q;
		h=(int)floor(r*cos(ang)); 
		k=(int)floor(r*sin(ang)); 
		for(int i=1;i<=l;i++){
			p=(int)floor(r*cos(i*(2.0*M_PI/l)+ang));
			q=(int)floor(r*sin(i*(2.0*M_PI/l)+ang));
			linea(h+x, k+y, p+x, q+y,size);
			h=p;
			k=q;
		}
	}

	void puntosCirc(int h,int k, int x, int y, int size=0){
		pintar(h+x, k+y,size);
		pintar(h-x, k+y,size);
		pintar(h+x, k-y,size);
		pintar(h-x, k-y,size);
		pintar(h+y, k+x,size);
		pintar(h-y, k+x,size);
		pintar(h+y, k-x,size);
		pintar(h-y, k-x,size);
	}

	void circulo(int h, int k, int r, int size=0){
		int x, y;
		x=0;
		y=r;
		double p;
		p = 1-r;
		puntosCirc(h, k, x, y, size);

		while(x<y){
			x++;
			if(p<0){
				p+=2*x+1;
			}else{
				y--;
				p+=2*(x-y)+1;
			}
			puntosCirc(h, k, x, y,size);
		}
	}

	void estrella(int x, int y, int r, double ang, int l, int size=0){
		int h, k;
		int p, q;
		int s, t;
		s=(int)floor(double(r)*cos(M_PI/l+ang)/2);
		t=(int)floor(double(r)*sin(M_PI/l+ang)/2);
		for(int i=1;i<=l;i++){
			p=(int)floor(r*cos(i*(2.0*M_PI/l)+ang));
			q=(int)floor(r*sin(i*(2.0*M_PI/l)+ang));
			linea(s+x, t+y, p+x, q+y,size);
			s=(int)floor(r*cos((2.0*i+1.0)*M_PI/l+ang)/2);
			t=(int)floor(r*sin((2.0*i+1.0)*M_PI/l+ang)/2);
			linea(s+x, t+y, p+x, q+y, size);
			h=p;
			k=q;
		}
	}
	
	void corazon(int x, int y, int a, int b, int size=0){
		int h, k;
		int p, q;
		int IT=100;
		double t=0;
		h=round(a*pow(sin(t),3));
		k=round(((13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t)+2.5)/29+0.5)*b);
		for(int i=0;i<=IT;i++){
			p=round(a*pow(sin(t),3));
			q=round(((13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t)+2.5)/29+0.5)*b);
			linea(x+h, y+k, x+p, y+q, size);
			h=p;
			k=q;
			t+=2*M_PI/IT;
		}
		
	}
	
	void curvaSpline(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int size){
		int p, q;
		p=round(x1);
		q=round(y1);
		for(double t=0;t<=1;t+=1.0/45){
			int x=round(pow(1-t, 3)*x1+3*t*pow(1-t, 2)*x3+3*t*t*(1-t)*x4+t*t*t*x2);
			int y=round(pow(1-t, 3)*y1+3*t*pow(1-t, 2)*y3+3*t*t*(1-t)*y4+t*t*t*y2);
			linea(p,q, x, y, size);
			p=x;
			q=y;
		}
	}
	
	void ponerTexto(int x, int y, void* font, const char *string){
		glRasterPos2f(x, y);
		int i;
		for (i = 0; string[i]!='\0'; i++) {
			glutBitmapCharacter(font, string[i]);
		}
	}

	void ponerTexto(int x, int y, void* font, const std::string s){
		glRasterPos2f(x, y);
		int i;
		for (i = 0;i< s.size(); i++) {
			glutBitmapCharacter(font, s[i]);
		}
	}
}
#endif
