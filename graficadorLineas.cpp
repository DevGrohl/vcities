#include <iostream>               //Entradas y salidas debugging
#include <vector>
#include "imagen/color.h"
#include "geometria.h"
#include "gl2.h"				  //Interfaz
#include "primitivas.h"
#include "voronoi.h"

using namespace std;
using namespace _2D;

typedef double llint;

const int SCREEN_X = 600;
const int SCREEN_Y = 600;
const char * WINDOW_NAME = "lineas";


vector<Linea<llint>> lineas;

int x[30], y[30];
void renderFunction(){
	glClear(GL_COLOR_BUFFER_BIT); 
	//glDraw(lineas);
		x[1]=64; y[1]=84;
		x[2]=37; y[2]=162;
		x[3]=15; y[3]=316;
		x[4]=68; y[4]=385;
		x[5]=60; y[5]=565;
		x[6]=154; y[6]=99;
		x[7]=156; y[7]=239;
		x[8]=146; y[8]=245;
		x[9]=193; y[9]=362;
		x[10]=190; y[10]=482;
		x[11]=259; y[11]=60;
		x[12]=321; y[12]=204;
		x[13]=274; y[13]=249;
		x[14]=272; y[14]=385;
		x[15]=323; y[15]=579;
		x[16]=423; y[16]=30;
		x[17]=432; y[17]=147;
		x[18]=456; y[18]=341;
		x[19]=478; y[19]=439;
		x[20]=397; y[20]=524;
		x[21]=495; y[21]=58;
		x[22]=537; y[22]=191;
		x[23]=556; y[23]=291;
		x[24]=525; y[24]=443;
		x[25]=566; y[25]=502;
	Voronoi<llint> vor;
	for(int i=1;i<=25;i++){
		vor.agregaPunto(Punto<llint>(x[i],y[i]));
	}
	vor.calcularRegiones(false);
	glColor(Color::azul);
	vor.calcular();
	glDraw(vor.dameLineas());
	auto triangulacion  =vor.dameGrafoTriangulacion();
	auto puntos = vor.damePuntos();
	glColor(Color::verde);
	for(int i=0;i<triangulacion.size();i++){
		for(int j=i+1;j<triangulacion[i].size();j++){
			if(triangulacion[i][j]){
				glDraw(Linea<llint>(puntos[i],puntos[j]));
			}
		}
	}
	glColor(Color::blanco);
	for(int i=1;i<=25;i++){
		primitivas::ponerTexto(x[i],y[i],GLUT_BITMAP_HELVETICA_10 ,to_string(i));
	}

	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv){ 
	/*do{
		llint a, b, c, d;
		cin>>a>>b>>c>>d;
		lineas.push_back(Linea<llint>(Punto<llint>(a,b),Punto<llint>(c,d)));
	}while(not cin.eof());*/
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
	glutMainLoop(); 
	return 0; 
} 


