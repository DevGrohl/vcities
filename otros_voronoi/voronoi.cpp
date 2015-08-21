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
const double infty = 100000000;

class voronoi_simple{
private:
	Punto<llint> tam;
	Punto<llint> tamMat;
	vector<Punto<double>> puntos;
	vector<Linea<double>> lineas;
public:
	bool cuadricula;
	bool grafica_puntos;
	bool grafica_triangulacion;
	voronoi_simple(){	
	}
	voronoi_simple(int x, int y, int n, int m){
		cuadricula = grafica_puntos = grafica_triangulacion = true;
		tam = Punto<llint>(x,y);
		tamMat = Punto<llint>(n,m);
		int dx = x/n;
		int dy = y/m;
		/*for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				puntos.push_back(Punto<double>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}*/
		puntos.push_back(Punto<double>(590,290));//6
		puntos.push_back(Punto<double>(470,290));//7
		puntos.push_back(Punto<double>(300,300));//2
		puntos.push_back(Punto<double>(460,70)); //3
		puntos.push_back(Punto<double>(10,250)); //1
		puntos.push_back(Punto<double>(190,400));//4
		puntos.push_back(Punto<double>(560,490));//5


		//for(int i=0;i<puntos.size();i++){
		for(int i=0;i<1;i++){
			vector<Linea<double>> bisectores;
			vector<Linea<double>> cerco;
			for(int j=0;j<puntos.size();j++){
				if(i!=j){
					Punto<double> a = puntos[i];
					Punto<double> b = puntos[j];
					Punto<double> centro =(a+b)/2;
					double dx = b.x - a.x;
					double dy = b.y - a.y;
					double m = -dx/dy;
					auto f = [&](double x){
						//y-y1 = m(x-x1)
						return Punto<double>(x,m*(x-centro.x)+centro.y);
					};
					bisectores.push_back(Linea<double>(f(-infty),f(infty)));
				}
			}
			sort(bisectores.begin(), bisectores.end(), 
				[&](const Linea<double>& p,const Linea<double>& q){
					return distancia(p,puntos[i]) < distancia(q,puntos[i]); 
				}
			);	
			auto resuelve = [&](Linea<double>& l,const Linea<double>& l2, const Punto<double>& choque){
				if(Linea<double>(puntos[i],l.fin).colisiona(l2)){
					l.fin = choque;
				}else if(Linea<double>(puntos[i],l.inicio).colisiona(l2)){
					l.inicio = choque;
				}else{
					cout<<"No choca"<<endl;
				}
			};
			cerco.push_back(bisectores[0]);
			for(int j=1;j<bisectores.size();j++){
				Linea<double> Li = bisectores[j];  
				bool agregar = false;
				for(int k=0;k<cerco.size();k++){
					if(bisectores[j].colisiona(cerco[k])){
						Punto<double> choque = interseccion(bisectores[j],cerco[k]);
						Linea<double> aux=cerco[k];
						resuelve(cerco[k],Li,choque);
						resuelve(Li,aux,choque);
						agregar = true;
					}
				}	
				if(agregar){
					cerco.push_back(Li);
				}
			}

			for(auto& l1: cerco){
				for(auto& l2: lineas){
					if(l1.colisiona(l2)){
						Punto<double> choque = interseccion(l1,l2);
						auto aux = l1;
						resuelve(l1,l2,choque);
						resuelve(l2,aux,choque);
					}
				}
			}

			for(int j=0;j<cerco.size();j++){
				lineas.push_back(cerco[j]);
			}


		}
	}

	void dibujar(){
		int dx = tam.x/tamMat.x;
		int dy = tam.y/tamMat.y;
		if(cuadricula){
			glColor(Color::blanco);
			for(int i=1;i<tamMat.x;i++){
				glDraw(Linea<llint>(Punto<llint>(i*dx,0),Punto<llint>(i*dx,tam.y)));
			}
			for(int i=1;i<tamMat.y;i++){
				glDraw(Linea<llint>(Punto<llint>(0,i*dy),Punto<llint>(tam.x,i*dy)));
			}
		}
		if(grafica_puntos){
			glColor(Color::rojo);
			for(int i=0;i<puntos.size();i++){
				glDraw(puntos[i],5);
			}
			glColor(Color::morado);
			glDraw(puntos[5],5);
		}

		//Lineas calculadas
		int k=0;
		for(auto x: lineas){
			glColor(Color::hsl(k++*10));
			glDraw(x);
		}

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
	vs = voronoi_simple(SCREEN_X,SCREEN_Y,3,3);
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


