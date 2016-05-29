#include <iostream>               //Entradas y salidas debugging
#include "imagen/imagen.h"        //Exportacion de resultados
#include "imagen/primitivas.h"    //Exportacion de resultados
#include "voronoi.h"   	   	      //Para calcular triangulacionaciones
#include "gl2.h"				  //Interfaz
#include <cstdlib> 				  //Random
#include <chrono>				  //Debugging con sleeps
#include <thread>				  //Debugging con sleeps
#include "owl.h"				  //Para generar los xml
#include <map>		  			  //
#include "avenida.h"
#include "multilinea.h"			  //
#include "ciudad.h"
using namespace std;
using namespace _2D;

typedef double llint;

const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "VCities";
const int ANCHURA_MANZANAS = 12;
const int LARGO_MANZANAS = 25;
const int AVENIDAS_VER = 3;
const int AVENIDAS_HOR = 3;
const double ROTACION_MAXIMA  = M_PI/15.0;
const int ITERACIONES_AVENIDA = 3;




class interfaz{
private:
	

public:
	bool grafica_puntos;
	bool grafica_voronoi;
	Ciudad ciudad;
	interfaz(int x, int y, int n, int m):ciudad(x, y, n, m, ANCHURA_MANZANAS,LARGO_MANZANAS, AVENIDAS_HOR, AVENIDAS_VER, ITERACIONES_AVENIDA, ROTACION_MAXIMA){
		grafica_voronoi  = grafica_puntos = true;
		
	}

	interfaz(const string& file):ciudad(file){
	}

	void dibujar(){
		cout<<"Inicia dibujo"<<endl;
		cout<<"Cantidad de lineas: "<<ciudad.lineas.size()<<endl;
		glClear(GL_COLOR_BUFFER_BIT);

		if(grafica_voronoi){
			int k=0;
			glColor(Color::verde);
			for(auto p: ciudad.lineas){
				glDraw(Linea<int>(ciudad.llaves[p.x], ciudad.llaves[p.y]));
			}

		}
		{
			int k=0;	
			for(auto av: ciudad.coleccionAvenidas){
				for(auto s: av.second.segmentos){
					glColor(Color::hsl(k++*17));
					glDraw(s);
				}
			}
		}
		if(grafica_puntos){
			glColor(Color::rojo);
			glDraw(ciudad.puntos,5);
		}
		
		//Debugg de los rectangulos sobre las regiones
		/*
		int k=0;
		Imagen I;
		glReadPixels(I);
		for(auto region: regiones){
			glDrawPixels(I);
			glColor(Color::azul);
			glDraw(region);		
			glColor(Color::magenta);
			glDraw(region.rectanguloRecubridorMinimo());
			glutSwapBuffers();
			glFlush();
			int x;
			cin>>x;
			if(x)
				cout<<region.toString()<<endl;
		//	this_thread::sleep_for(chrono::seconds(1));
		}
		*/
		/*for(auto& av : avenidas){
			av.dibujar(3);
		}*/
	
		
		glutSwapBuffers();
		glFlush();
	}

	void guardaOntologia(const string& nombre){
		ciudad.guardaOntologia(nombre);
	}
};

interfaz *vs;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	vs->dibujar();
	glFlush();
	glutSwapBuffers();
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case 'p':
			vs->grafica_puntos^=true;
			break;
		case 'v':
			vs->grafica_voronoi^=true;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
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
	srand(time(NULL));
	if(argc == 1){	
		vs = new interfaz(SCREEN_X,SCREEN_Y,15,15);
		vs->guardaOntologia("ontologia_prueba.owl");
	}else{
		vs = new interfaz(argv[1]);
	}
	glutMainLoop(); 
	return 0; 
} 


