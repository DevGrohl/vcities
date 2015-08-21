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

typedef double llint;

const int SCREEN_X = 1000;
const int SCREEN_Y = 1000;
const char * WINDOW_NAME = "VCities";
const int ANCHURA_MANZANAS = 7;
const int LARGO_MANZANAS = 15;




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


		//voronoi.calcular();
		puntos=voronoi.damePuntos();
		lineas=voronoi.dameLineas();
		triangulacion=voronoi.dameGrafoTriangulacion();	
		regiones = voronoi.regiones();
		int tam = regiones.size();
		int i=0;

		//Calculo de los puntos internos a las regiones
		for(auto region: regiones){
			Voronoi<llint> ciudad;
			cout<<owl(region)<<endl;
			//Se calcula el rectangulo recubridor
			RectanguloGirado<llint> r = region.rectanguloRecubridorMinimo();
			//Algunas variables auxiliares precalculadas
			llint base = r.base();
			llint altura = r.altura();
			llint angulo = -r.angulo();
			//Se barre la matriz de punto base x altura
			for(llint x = ANCHURA_MANZANAS; x<base; x+=ANCHURA_MANZANAS){
				for(llint y = LARGO_MANZANAS; y<altura; y+=LARGO_MANZANAS){
					Punto<llint> p(-x,-y);
					p=p.rotar(-angulo);
					p+=r.p4;
					if(region.contiene(p)){
						ciudad.agregaPunto(p);
					//	puntos.push_back(p);
					//	cout<<":P"<<endl;
					}
				}
			}

			ciudad.calcularRegiones(false);
			cout<<"Region: "<<i++<<"/"<<tam<<"::"<<ciudad.cantidadPuntos()<<endl;
			if(ciudad.cantidadPuntos()<350){	
				ciudad.calcular();
			}
			vector<Linea<llint>> temp=ciudad.dameLineas();
			/*
			glClear(GL_COLOR_BUFFER_BIT);
			glColor(Color::verde);
			glDraw(temp);
			glutSwapBuffers();
			glFlush();
			this_thread::sleep_for(chrono::seconds(1));		
			*/
			lineas.insert(lineas.end(),temp.begin(), temp.end());
		}
		cout<<"Fin"<<endl;
	}


	void dibujar(){
		Poligono<llint> region;
		region.agregaPunto(Punto<llint>(868.017688,674.985424));
		region.agregaPunto(Punto<llint>(748.532302,718.078514));
		region.agregaPunto(Punto<llint>(740.507740,711.551072));
		region.agregaPunto(Punto<llint>(740.368421,704.631579));
		region.agregaPunto(Punto<llint>(834.643836,610.356164));
		region.agregaPunto(Punto<llint>(850.983158,620.231579));
	/*	glClear(GL_COLOR_BUFFER_BIT);
		glColor(Color::azul);
		glDraw(region);
		glColor(Color::verde);
		glDraw(region.rectanguloRecubridorMinimo());
		glColor(Color::rojo);*/
		Voronoi<llint> v;
		RectanguloGirado<llint> r = region.rectanguloRecubridorMinimo();
			//Algunas variables auxiliares precalculadas
			llint base = r.base();
			llint altura = r.altura();
			llint angulo = -r.angulo();
			//Se barre la matriz de punto base x altura
			for(llint x = ANCHURA_MANZANAS; x<base; x+=ANCHURA_MANZANAS){
				for(llint y = LARGO_MANZANAS; y<altura; y+=LARGO_MANZANAS){
					Punto<llint> p(-x,-y);
					p=p.rotar(-angulo);
					p+=r.p4;
					if(region.contiene(p)){
						glDraw(p,3);
						v.agregaPunto(p);
					//	puntos.push_back(p);
					//	cout<<":P"<<endl;
					}
				}
			}
		VoronoiNoGeometrico<llint> vng(SCREEN_X, SCREEN_Y, v.damePuntos(), distanciaM);
		Imagen I;
		//glReadPixels(I);
		//v.calcularRegiones(false);
		//v.calcular();
		glColor(Color::blanco);
	//	auto l = v.dameLineas();
	//	for(auto i: l){
	//		primitivas::linea(I,i.inicio.x, i.inicio.y, i.fin.x, i.fin.y, Color::blanco);
	//	}
	//	ofstream file("lineas.xml");
	//	for(auto zzz: l){
	//		file<<owl(zzz)<<endl;
	//	}
	//	file.close();
		glDrawPixels(vng.obtenerImagen());
		glutSwapBuffers();
		glFlush();
		return;
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
		glReadPixels(I);
		for(auto region: regiones){
			glDrawPixels(I);
		//	glColor(Color::azul);
		//	glDraw(region);		
			glColor(Color::morado);
			glDraw(region.rectanguloRecubridorMinimo());
			glutSwapBuffers();
			glFlush();
			this_thread::sleep_for(chrono::seconds(1));
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
	vs = interfaz(SCREEN_X,SCREEN_Y,10,10);
	glutMainLoop(); 
	return 0; 
} 


