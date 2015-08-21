#include <iostream>               //Entradas y salidas debugging
#include "imagen/imagen.h"        //Exportacion de resultados
#include "voronoi.h"   	   	      //Para calcular triangulacionaciones
#include "gl2.h"				  //Interfaz
#include <cstdlib> 				  //Random
#include <chrono>				  //Debugging con sleeps
#include <thread>				  //Debugging con sleeps
using namespace std;
using namespace _2D;

typedef double llint;

const int SCREEN_X = 600;
const int SCREEN_Y = 600;
const char * WINDOW_NAME = "Voronoi";





class interfaz{
private:
	//Datos de entrada
	Punto<int> tam;
	Punto<int> tamMat;
	Voronoi<llint> voronoi;
	vector<Punto<llint>> puntos; //Puntos generados

	//resultados
	vector<vector<bool>> triangulacion; //Grafo que representa 2 puntos deben conectarse segun la triangulacion de delaunay
	vector<Linea<llint>> lineas;		    //Lineas del diagrama
public:
	bool cuadricula;
	bool grafica_puntos;
	bool grafica_triangulacion;
	bool grafica_voronoi;
	interfaz(){	
	}
	interfaz(int x, int y, int n, int m){
		grafica_voronoi = cuadricula = grafica_puntos = grafica_triangulacion = true;
		tam = Punto<int>(x,y);
		tamMat = Punto<int>(n,m);
		int dx = x/n;
		int dy = y/m;


		//Generacion de los puntos aleatorios
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				voronoi.agregaPunto(Punto<llint>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}


		voronoi.calcular();
		puntos=voronoi.damePuntos();
		lineas=voronoi.dameLineas();
		triangulacion=voronoi.dameGrafoTriangulacion();

		/*
			Mas debugging
		*/
			for(auto p: puntos){
				cout<<p.toString()<<endl;
			}

			for(int i=0;i<triangulacion.size();i++){
				for(int j=i+1;j<triangulacion[i].size();j++){
					for(int k=j+1;k<triangulacion.size();k++){
						if(triangulacion[i][j] and triangulacion[j][k] and triangulacion[k][i]){
							cout<<"("<<i+1<<","<<j+1<<","<<k+1<<")"<<endl;
						}
					}
				}
			}	
		/*
		//debugging, para comprobar contra un resultado exacto
		VoronoiNoGeometrico<llint> vms(x,y,puntos,distanciaM);
		vms.obtenerImagen().guardaBMP("vms.bmp");
		*/		
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
			glDraw(puntos,5);
		}
		if(grafica_triangulacion){
			int k=0;
			for(int i=0;i<triangulacion.size();i++){
				for(int j=i+1;j<triangulacion[i].size();j++){
					if(triangulacion[i][j]){
						glColor(Color::hsl(k++*17));//blanco);
						glDraw(Linea<llint>(puntos[i],puntos[j]));
					}
				}
			}			
		}
		if(grafica_voronoi){
			int k=0;
			glColor(Color::verde);
			glDraw(lineas);		
		}
		
	}
};

interfaz vs;

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
		case 'v':
			vs.grafica_voronoi^=true;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
	srand(time(NULL));
	vs = interfaz(SCREEN_X,SCREEN_Y,5,5);
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


