#ifndef GL2_H
#define GL2_H
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>


#ifdef COLOR_H
	inline void glColor(const Color& c){
		glColor3ub(c.r, c.g, c.b);
	}


	inline void glColorAlpha(const Color& c, unsigned char alpha = 255){
		glColor4ub(c.r, c.g, c.b,alpha);
	}
#endif
#ifdef PUNTO3D_H

	template<class T>
	inline void glVertex(const _3D::Punto<T>& p){
		glVertex3f((GLfloat)p.x, (GLfloat)p.y, (GLfloat)p.z);
	}

	template<class T>
	inline void gluLookAt(const _3D::Punto<T>& from, const _3D::Punto<T>& to, const _3D::Punto<T>& up){
		gluLookAt(from.x, from.y, from.z, to.x, to.y, to.z, up.z, up.y, up.z);
	}


#endif

#ifdef LINEA3D_H
	template<class T>
	inline void glDraw(const _3D::Linea<T>& l,int size=0){
		glBegin(GL_LINES);
		glVertex(l.inicio);
		glVertex(l.fin);
		glEnd();
	}

#endif

#ifdef IMAGEN_H
	void drawAt(const Imagen& M, int h, int k){
		glBegin(GL_POINTS);
		for(int i=0;i<M.y;i++)
			for(int j=0;j<M.x;j++){
				int p,q;
				p=h+i;
				q=k+j;
				try{
					glColor(M.en(i,j));
					glVertex2i(q, p);
				}catch(int e){
				}
			}

		glEnd();
		glFlush();
	}

	inline void glReadPixels(Imagen &M){
		delete M.pixels;
		M.x=glutGet(GLUT_WINDOW_WIDTH);
		M.y=glutGet(GLUT_WINDOW_HEIGHT);
		M.pixels = new Color[M.x*M.y];
		glReadPixels(0,0,M.x,M.y,GL_RGB,GL_UNSIGNED_BYTE,M.pixels);
	}

	inline void glReadPixels(Imagen &M ,int x2, int y2){
		delete M.pixels;
		M.x=x2;
		M.y=y2;
		M.pixels = new Color[M.x*M.y];
		glReadPixels(0,0,M.x,M.y,GL_RGB, GL_UNSIGNED_BYTE, M.pixels);

	}
	
	inline void glDrawPixels(const Imagen &M){
		glDrawPixels(M.x,M.y,GL_RGB,GL_UNSIGNED_BYTE, M.pixels);
	}

	inline void glDrawPixels(const Imagen * M){
		glDrawPixels(M->x,M->y,GL_RGB,GL_UNSIGNED_BYTE, M->pixels);
	}
#endif


#ifdef PUNTO2D_H
	template<class T>
	inline void glVertex(const _2D::Punto<T>& p){
		glVertex2f((GLfloat)p.x, (GLfloat)p.y);
	}

	template<class T>
	inline void glDraw(const _2D::Punto<T>& p, int tam = 1){
		if(tam==1){
			glBegin(GL_POINTS);
			glVertex2f((GLfloat)p.x, (GLfloat)p.y);
			glEnd();
		}else{
			glBegin(GL_QUADS);
			glVertex2f((GLfloat)p.x, (GLfloat)p.y);
			glVertex2f((GLfloat)p.x+tam, (GLfloat)p.y);
			glVertex2f((GLfloat)p.x+tam, (GLfloat)p.y+tam);
			glVertex2f((GLfloat)p.x, (GLfloat)p.y+tam);
			glEnd();
		}
	}
#endif

#ifdef LINEA2D_H

	template<class T>
	inline void glDraw(const _2D::Linea<T>& l, int size=0){
		#ifdef PRIMITIVAS_H
			primitivas::linea(l.inicio.x, l.inicio.y, l.fin.x, l.fin.y, size);
		#else
			glBegin(GL_LINES);
				glVertex(l.inicio);
				glVertex(l.fin);
			glEnd();
		#endif
	}

#endif

#ifdef CIRCULO_H
	template<class T>
	inline void glDraw(const _2D::Circulo<T>& c, bool fill = false, int size = 0){
		if(fill){

		}else{
			glBegin(GL_LINES);
			_2D::Punto<double> ant = c.centro;
			ant.x += c.radio;
			for(double ang = 0.1; ang<=2*M_PI+0.2 ;ang+=0.1){
				_2D::Punto<double> act = c.centro+_2D::Punto<double>::polar(c.radio,ang);
				glVertex(ant);
				glVertex(act);
				ant = act;
			}
			glEnd();
		}
	}

#endif

#ifdef RECTANGULO2D_H

	template<class T>
	inline void glDraw(const _2D::Rectangulo<T>& r, bool fill = false, int size = 0){
		if(fill){
			glBegin(GL_TRIANGLES);
				glVertex(r.inicio);
				glVertex2f(r.fin.x,r.inicio.y);
				glVertex2f(r.inicio.x,r.fin.y);
				glVertex2f(r.fin.x,r.inicio.y);
				glVertex2f(r.inicio.x,r.fin.y);
				glVertex(r.fin);
			glEnd();
		}else{
			glDraw(_2D::Linea<T>(_2D::Punto<T>(r.inicio.x,r.inicio.y),_2D::Punto<T>(r.fin.x,r.inicio.y)),size);
			glDraw(_2D::Linea<T>(_2D::Punto<T>(r.inicio.x,r.inicio.y),_2D::Punto<T>(r.inicio.x,r.fin.y)),size);
			glDraw(_2D::Linea<T>(_2D::Punto<T>(r.fin.x,r.fin.y),_2D::Punto<T>(r.inicio.x,r.fin.y)),size);
			glDraw(_2D::Linea<T>(_2D::Punto<T>(r.fin.x,r.fin.y),_2D::Punto<T>(r.fin.x,r.inicio.y)),size);
		}
	}

	template<class T>
	inline void glDraw(const _2D::RectanguloGirado<T>& r, bool fill = false, int size = 0){
		_2D::Punto<T> a=r.p1 , b=r.p2, c=r.p3, d=r.p4;
		

		if(fill){
		/*	glBegin(GL_TRIANGLES);
				glVertex(r.inicio);
				glVertex2f(r.fin.x,r.inicio.y);
				glVertex2f(r.inicio.x,r.fin.y);
				glVertex2f(r.fin.x,r.inicio.y);
				glVertex2f(r.inicio.x,r.fin.y);
				glVertex(r.fin);
			glEnd();
			*/
		}else{
			glDraw(_2D::Linea<T>(a,b));
			glDraw(_2D::Linea<T>(a,c));
			glDraw(_2D::Linea<T>(d,b));
			glDraw(_2D::Linea<T>(d,c));
		}
	}

#endif

#ifdef OBJETO2D_H
	void glDrawPixels(Imagen * render,const _2D::Punto<double>& posicion, const Color& fondo= Color::negro){
		for(int i=0;i<render->filas();i++)
			for(int j=0;j<render->columnas();j++){
				double p,q;
				p=posicion.x+j;
				q=posicion.y+i;
				Color c = render->en(i,j);
				if(c!=fondo){
					glBegin(GL_QUADS);
					glColor(c);
					glVertex2f(p,q);
					glVertex2f(p+1, q);
					glVertex2f(p+1, q+1);
					glVertex2f(p, q+1);	
					glEnd();
				}
			}
		glFlush();
	}

#endif


#ifdef TRIANGULO2D_H
	template<class T>
	inline void glDraw(const _2D::Triangulo<T> & t, bool fill = false, int size = 0){
		if(fill){
			glBegin(GL_TRIANGLES);
			glVertex(t.p1);
			glVertex(t.p2);
			glVertex(t.p3);
			glEnd();
		}else{
			glDraw(_2D::Linea<T>(t.p1,t.p2),size);
			glDraw(_2D::Linea<T>(t.p2,t.p3),size);
			glDraw(_2D::Linea<T>(t.p3,t.p1),size);
		}
	}
#endif


#ifdef COLOR_H
	template<class T>
	void glDrawHSL(const std::vector<T>& v, int salto, int inicio = 0){
		int k=inicio;
		for(T e: v){
			glColor(Color::hsl(k));
			k+=salto;
			glDraw(e);
		}
	}
#endif



template<class T>
void glDraw(const std::vector<T>& v){
	for(T e: v){
		glDraw(e);
	}
}

#ifdef PUNTO2D_H
	template<class T>
	void glDraw(const std::vector<_2D::Punto<T>>& v, int tam = 0){
		for(auto e: v){
			glDraw(e,tam);
		}
	}
#endif

#ifdef POLIGONO_H
	template<class T>
	void glDraw(const _2D::Poligono<T>& p){
		glBegin(GL_POLYGON);
			for(auto v: p.vertices){
				glVertex(v);
			}
		glEnd();
	}

#endif

#endif

