#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "geometria.h"
#include "imagen/imagen.h"
#include "gl2.h"
#include <vector>
#include <cstdlib>
#include <set>
#include <map>
#include <chrono>
#include <thread>
using namespace std;
using namespace _2D;

typedef long long int llint;

const int SCREEN_X = 600;
const int SCREEN_Y = 600;
const char * WINDOW_NAME = "Voronoi";

class voronoi_simple{
private:
	vector<Punto<llint>> puntos;
	vector<Punto<int>> triangulacion;
	int x, y;
	int n, m;
	Imagen grafica;
public:
	bool grafica_puntos;
	bool cuadricula;
	bool grafica_triangulacion;


	voronoi_simple(){	
	}
	voronoi_simple(int x, int y, int n, int m){
		this->x = x;
		this->y = y;
		this->n = n;
		this->m = m;
		cuadricula = grafica_puntos = grafica_triangulacion = true;
		//tam = Punto<llint>(x,y);
		//tamMat = Punto<llint>(n,m);
		int dx = x/n;
		int dy = y/m;
		/*
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				puntos.push_back(Punto<llint>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}*/
		puntos.push_back(Punto<llint>(300,300));
		puntos.push_back(Punto<llint>(460,70));
		puntos.push_back(Punto<llint>(190,400));
		puntos.push_back(Punto<llint>(560,490));
		puntos.push_back(Punto<llint>(590,290));
		puntos.push_back(Punto<llint>(470,290));
		puntos.push_back(Punto<llint>(10,250));

		grafica = obtenerImagen();
		for(int i=0;i<puntos.size();i++){
			for(int j=0;j<i;j++){
				int a = (puntos[i].x+puntos[j].x)/2;
				int b = (puntos[i].y+puntos[j].y)/2;
				//if(grafica.en(b,a)==Color::blanco){
					triangulacion.push_back(Punto<int>(i,j));
				//}
			}
		}
		sort(triangulacion.begin(), triangulacion.end(),
			[&](const Punto<int>& a, const Punto<int>& b){
				return Linea<llint>(
					puntos[a.x],puntos[a.y]
				).longitud2() < 
				       Linea<llint>(
				    puntos[b.x],puntos[b.y]
				).longitud2();
			}
		);


		for(int i=0; i < triangulacion.size();i++){
			for(int j=0;j<i;j++){
				if((Linea<llint>(puntos[triangulacion[i].x],puntos[triangulacion[i].y])).colisiona(Linea<llint>(puntos[triangulacion[j].x],puntos[triangulacion[j].y]))){
					triangulacion.erase(triangulacion.begin()+i);
					i--;
					break;
				}
			}
		}
		
	}

	void dibujar(){
		glDrawPixels(grafica);
		if(grafica_puntos){
			glColor(Color::negro);
			for(int i=0;i<puntos.size();i++){
				glDraw(puntos[i],5);
			}
		}
		if(cuadricula){
			int dx = x/n;
			int dy = y/m;
			glColor(Color::blanco);
			for(int i=1;i<n;i++){
				glDraw(Linea<llint>(Punto<llint>(i*dx,0),Punto<llint>(i*dx,y)));
			}
			for(int i=1;i<m;i++){
				glDraw(Linea<llint>(Punto<llint>(0,i*dy),Punto<llint>(x,i*dy)));
			}
		}
		if(grafica_triangulacion){
			glColor(Color::negro);
			for(int i=0;i<triangulacion.size();i++){
				glDraw(Linea<llint>(puntos[triangulacion[i].x],puntos[triangulacion[i].y]));
			}
		}
	}

	Imagen obtenerImagen(){
		Imagen I(x,y);		
		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				llint dist_min = x*y*x*y;
				int id = 0;
				Punto<llint> actual(j,i);
				int cant_pts = 1;
				for(int k=0;k<puntos.size();k++){
					llint dist = distancia2(actual,puntos[k]);
					if(dist<dist_min){
						dist_min = dist;
						id=k;
						cant_pts=1;
					}else if(dist == dist_min){
						cant_pts++;
					}
				}
				try{
					I.en((int)actual.y,(int)actual.x)  =Color::hsl(113*id);
				}catch(...){

				}
					
			}
		}
		return I-I.laplace().umbral(1,Color::negro, Color::blanco);
	}
	
};

voronoi_simple vs;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	vs.dibujar();
	glFlush();
	glutSwapBuffers();
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case 'g':
			vs.cuadricula^=true;
			break;
		case 't':
			vs.grafica_triangulacion^=true;
			break;
		case 'p':
			vs.grafica_puntos^=true;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
	srand(time(NULL));
	vs = voronoi_simple(SCREEN_X,SCREEN_Y,5,5);
	vs.obtenerImagen().guardaBMP("voronoi.bmp");
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(SCREEN_X,SCREEN_Y); 
	glutInitWindowPosition(0,0); 
	glutCreateWindow(WINDOW_NAME); 
	glClearColor(0, 0,0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glClear(GL_COLOR_BUFFER_BIT); 
	gluOrtho2D(0, SCREEN_X, 0,SCREEN_Y); 
	glFlush(); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	glutMainLoop(); 
	return 0; 
} 


