#include "imagen/imagen.h"
#include "geometria.h"
#include "gl2.h"
const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "Poligono";
const int ANCHURA_MANZANAS = 7;
const int LARGO_MANZANAS = 15;

using namespace std;
using namespace _2D;

vector<Linea<double>> mallaDePuntos(const Poligono<double>& region){
	RectanguloGirado<double> r = region.rectanguloRecubridorMinimo();
	//Algunas variables auxiliares precalculadas
	double base = r.base();
	double altura = r.altura();
	double angulo = -r.angulo();
	//Se barre la matriz de punto base x altura
	vector<Linea<double>> res, l;
	for(double y = 0; y-LARGO_MANZANAS<altura; y+=LARGO_MANZANAS){
		for(double x= ANCHURA_MANZANAS; x-LARGO_MANZANAS<base; x+= ANCHURA_MANZANAS){		
			Linea<double> li (Punto<double>(-x,-y),Punto<double>(-x+ANCHURA_MANZANAS,-y));
			li.inicio = li.inicio.rotar(-angulo);
			li.fin = li.fin.rotar(-angulo);
			li+=r.p4;
			l.push_back(li);
		}
	}

	for(double x = 0; x- ANCHURA_MANZANAS <base; x+=ANCHURA_MANZANAS){
		for(double y = LARGO_MANZANAS; y-LARGO_MANZANAS<altura; y+=LARGO_MANZANAS){		
			Linea<double> li (Punto<double>(-x,-y),Punto<double>(-x,-y+LARGO_MANZANAS));
			li.inicio = li.inicio.rotar(-angulo);
			li.fin = li.fin.rotar(-angulo);
			li+=r.p4;
			l.push_back(li);
		}
	}
	
	for(auto i: l){
		bool contiene_ini = region.contiene(i.inicio);
		bool contiene_fin = region.contiene(i.fin);
		if(contiene_ini and contiene_fin){
			res.push_back(i);
		}else if(contiene_fin){
			i.inicio = region.puntoInterseccion(i);
			res.push_back(i);
		}else if(contiene_ini){
			i.fin = region.puntoInterseccion(i);
			res.push_back(i);
		}
	}
	return res;
}

void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	Poligono<double> region;
	region.agregaPunto(Punto<double>(570.665236,662.493562));
	region.agregaPunto(Punto<double>(496.866953,576.044145));
	region.agregaPunto(Punto<double>(505.514533,542.998036));
	region.agregaPunto(Punto<double>(683.777527,598.560528));
	glColor(Color::azul);
	glBegin(GL_LINES);
		glVertex(Punto<double>(570.665236,662.493562));
	glVertex(Punto<double>(496.866953,576.044145));
	glVertex(Punto<double>(496.866953,576.044145));
	glVertex(Punto<double>(505.514533,542.998036));
	glVertex(Punto<double>(505.514533,542.998036));
	glVertex(Punto<double>(683.777527,598.560528));
	glVertex(Punto<double>(683.777527,598.560528));
		glVertex(Punto<double>(570.665236,662.493562));
	glEnd();

	glColor(Color::verde);
	glDraw(region);
	auto grid = mallaDePuntos(region);
	for(auto l:grid){
		cout<<region.contiene(l)<<endl;
	}
	glColor(Color::rojo);
	glDraw(grid);
	glFlush();
	glutSwapBuffers();
}

void eventoTeclado(unsigned char k, int x, int y){
	switch(k){
		case ' ':
		break;
		default:
		break;
	}
	glutPostRedisplay();
}

void eventoClick(int b , int e, int x, int y){
}

void eventoArrastre(int x, int y){
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
	gluOrtho2D(400, 700, 500,800); 
	glFlush(); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	glutMouseFunc(eventoClick);
	glutMainLoop(); 
	return 0; 
} 


