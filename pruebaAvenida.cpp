#include <iostream>               //Entradas y salidas debugging
#include "imagen/imagen.h"        //Exportacion de resultados
#include "geometria.h"			
#include "gl2.h"				  //Interfaz
#include <cstdlib> 				  //Random
#include <chrono>				  //Debugging con sleeps
#include <thread>				  //Debugging con sleeps
#include <vector>
using namespace std;
using namespace _2D;

const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "VCities";

const double ROTACION_MAXIMA  = M_PI/15.0;

vector<Punto<double>> lineas;

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 

	glBegin(GL_LINES);
	glColor(Color::blanco);

	for(int i=1;i<lineas.size();i++){
		glVertex(lineas[i-1]);
		glVertex(lineas[i]);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void iterar(){
	vector<Punto<double>> siguientes;
	siguientes.push_back(lineas[0]);
	for(int i=1;i<lineas.size();i++){
		glClear(GL_COLOR_BUFFER_BIT); 

		Punto<double> nuevo; 
		Punto<double> centro = (lineas[i-1]+lineas[i])*0.5;
		Linea<double> l;
		double alpha = ROTACION_MAXIMA;
		double betha = M_PI/2.0 - alpha;
		double ladoB = distancia(lineas[i], centro);
		double ladoA = ladoB*sin(alpha)/sin(betha);
		Linea<double> flecha(centro,lineas[i]);
		flecha *= 1.0/flecha.longitud();
		flecha=flecha.rotar(M_PI/2);
		flecha *= ladoA;
		l.inicio = flecha.fin;
		flecha=flecha.rotar(M_PI);
		l.fin = flecha.fin;
		double aleatorio = (rand()%1000+1.0)/1000.0;
		nuevo = (l*aleatorio).fin;
		siguientes.push_back(nuevo);
		siguientes.push_back(lineas[i]);

	}
	lineas = siguientes;
}


void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case 'i':
			iterar();
		break;

	}
	glutPostRedisplay();
}


void inicializa(){
	lineas.push_back(Punto<double>(300,50));
	lineas.push_back(Punto<double>(800,950));
}

int main(int argc, char** argv){ 
	inicializa();


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
	glutMainLoop(); 
	return 0; 
} 


