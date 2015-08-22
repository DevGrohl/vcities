#include <iostream>               //Entradas y salidas debugging
#include "imagen/imagen.h"        //Exportacion de resultados
#include "imagen/primitivas.h"    //Exportacion de resultados
#include "voronoi.h"   	   	      //Para calcular triangulacionaciones
#include "gl2.h"				  //Interfaz
#include <cstdlib> 				  //Random
#include <chrono>				  //Debugging con sleeps
#include <thread>				  //Debugging con sleeps
#include "owl.h"				  //Para generar los xml
using namespace std;
using namespace _2D;

typedef long double llint;

const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "VCities";
const int ANCHURA_MANZANAS = 7;
const int LARGO_MANZANAS = 15;

vector<Linea<llint>> mallaDePuntos(const Poligono<llint>& region){
	RectanguloGirado<llint> r = region.rectanguloRecubridorMinimo();
	//Algunas variables auxiliares precalculadas
	llint base = r.base();
	llint altura = r.altura();
	llint angulo = -r.angulo();
	//Se barre la matriz de punto base x altura
	vector<Linea<llint>> res, l;
	for(llint y = 0; y<=altura; y+=LARGO_MANZANAS){
		for(llint x= ANCHURA_MANZANAS; x<=base; x+= ANCHURA_MANZANAS){		
			Linea<llint> li (Punto<llint>(-x,-y),Punto<llint>(-x+ANCHURA_MANZANAS,-y));
			li.inicio = li.inicio.rotar(-angulo);
			li.fin = li.fin.rotar(-angulo);
			li+=r.p4;
			l.push_back(li);
		}
	}

	for(llint x = 0; x<=base; x+=ANCHURA_MANZANAS){
		for(llint y = LARGO_MANZANAS; y<=altura; y+=LARGO_MANZANAS){		
			Linea<llint> li (Punto<llint>(-x,-y),Punto<llint>(-x,-y+LARGO_MANZANAS));
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
	vector<Poligono<llint>> regiones;   //Poligonos de las regiones del diagrama de voronoi


public:
	bool grafica_puntos;
	bool grafica_voronoi;
	interfaz(){	
	}
	interfaz(int x, int y, int n, int m){
		grafica_voronoi  = grafica_puntos = true;
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

		voronoi.calcularRegiones(true);
		voronoi.calcular();
		puntos=voronoi.damePuntos();
		lineas=voronoi.dameLineas();
		triangulacion=voronoi.dameGrafoTriangulacion();	
		regiones = voronoi.regiones();
		int tam = regiones.size();
		int i=0;

		//Calculo de los puntos internos a las regiones
		for(auto region: regiones){
		//	auto region = regiones[36];
			auto temp = mallaDePuntos(region);
			lineas.insert(lineas.end(),temp.begin(), temp.end());
		}
		cout<<"Fin"<<endl;
	}


	void dibujar(){
		cout<<"Inicia dibujo"<<endl;
		cout<<"Cantidad de lineas: "<<lineas.size()<<endl;
		glClear(GL_COLOR_BUFFER_BIT);
		if(grafica_voronoi){
			int k=0;
			glColor(Color::verde);
			glDraw(lineas);		
		}
		if(grafica_puntos){
			glColor(Color::rojo);
			glDraw(puntos,5);
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
		
		
		glutSwapBuffers();
		glFlush();
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
	vs = interfaz(SCREEN_X,SCREEN_Y,8,8);
	glutMainLoop(); 
	return 0; 
} 


