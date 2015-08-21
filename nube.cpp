#include <iostream>
#include <queue>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "imagen/imagen.h"
#include "geometria.h"
#include "gl2.h"
#include <vector>
using namespace std;
Imagen I;
const int SCREEN_X = 800;
const int SCREEN_Y = 800;
const char * WINDOW_NAME = "Nube";

_3D::Punto<double> camara(40,10,20);



class nube{
	private:
		int tx, ty;
		vector<vector<int>> colores;
	public:

		nube(int x, int y, int seed1, int seed2, int seed3, int seed4, int (*func)(int), int (*aleatoria)(int)){
			using namespace _2D;
			tx=x;
			ty=y;
			int iteraciones=11;
			x--;
			y--;
			colores = vector<vector<int>>(tx,vector<int>(ty,-1));
			vector<vector<bool>> calc(tx, vector<bool>(ty,false));
			queue<Linea<double> > q;
			q.push(Linea<double>(Punto<double>(0,0), Punto<double>(x, y)));
			colores[0][0]=seed1;
			colores[x][0]=seed2;
			colores[0][y]=seed3;
			colores[x][y]=seed4;

			for(int i=0;i<iteraciones;i++){
				int n = q.size();
				for(int j=0;j<n;j++){
					Linea<double> l = q.front();
					q.pop();
					Punto<double> centros[5];
					centros[0] = Punto<double>((l.inicio.x+l.fin.x)/2,l.inicio.y); 
					centros[1] = Punto<double>(l.inicio.x,(l.fin.y+l.inicio.y)/2); 
					centros[2] = Punto<double>((l.inicio.x+l.fin.x)/2,(l.fin.y+l.inicio.y)/2); 
					centros[3] = Punto<double>(l.fin.x,(l.inicio.y+l.fin.y)/2); 
					centros[4] = Punto<double>((l.inicio.x+l.fin.x)/2,l.fin.y); 
					int longitud = (l.fin-l.inicio).norma2();
					if(not calc[(int)floor(0.5+centros[0].x)][(int)floor(0.5+centros[0].y)]){
						colores[(int)floor(0.5+centros[0].x)][(int)floor(0.5+centros[0].y)]=abs(colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.inicio.y)]+colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.inicio.y)])/2+aleatoria(longitud);
						calc[(int)floor(0.5+centros[0].x)][(int)floor(0.5+centros[0].y)]=true;
					}
					if(not calc[(int)floor(0.5+centros[1].x)][(int)floor(0.5+centros[1].y)]){
						colores[(int)floor(0.5+centros[1].x)][(int)floor(0.5+centros[1].y)]=abs(colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.inicio.y)]+colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.fin.y)])/2+aleatoria(longitud);
						calc[(int)floor(0.5+centros[1].x)][(int)floor(0.5+centros[1].y)]=true;
					}
					if(not calc[(int)floor(0.5+centros[2].x)][(int)floor(0.5+centros[2].y)]){
						colores[(int)floor(0.5+centros[2].x)][(int)floor(0.5+centros[2].y)]=abs(colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.inicio.y)]+colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.fin.y)]+colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.fin.y)]+colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.fin.y)])/4+aleatoria(longitud);
						calc[(int)floor(0.5+centros[2].x)][(int)floor(0.5+centros[2].y)]=true;
					}
					if(not calc[(int)floor(0.5+centros[3].x)][(int)floor(0.5+centros[3].y)]){
						colores[(int)floor(0.5+centros[3].x)][(int)floor(0.5+centros[3].y)]=abs(colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.inicio.y)]+colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.fin.y)])/2+aleatoria(longitud);
						calc[(int)floor(0.5+centros[3].x)][(int)floor(0.5+centros[3].y)]=true;
					}
					if(not calc[(int)floor(0.5+centros[4].x)][(int)floor(0.5+centros[4].y)]){
						colores[(int)floor(0.5+centros[4].x)][(int)floor(0.5+centros[4].y)]=abs(colores[(int)floor(0.5+l.inicio.x)][(int)floor(0.5+l.fin.y)]+colores[(int)floor(0.5+l.fin.x)][(int)floor(0.5+l.fin.y)])/2+aleatoria(longitud);
						calc[(int)floor(0.5+centros[4].x)][(int)floor(0.5+centros[4].y)]=true;
					}
					q.push(Linea<double>(l.inicio,centros[2]));
					//q.push(Linea<double>(l.inicio,centros[2]));
					//q.push(Linea<double>(centros[2],l.fin));
					q.push(Linea<double>(centros[2],l.fin));
				
					q.push(Linea<double>(centros[2],Punto<double>(l.fin.x,l.inicio.y)));
					//q.push(Linea<double>(centros[0],centros[3]));
				
					//q.push(Linea<double>(centros[4],centros[1]));
					q.push(Linea<double>(centros[2],Punto<double>(l.inicio.x,l.fin.y)));
				
					//#4#
					//123
					//#0#
				}
			}
		}

		Imagen construye(Color (*traductora)(int) ){
			Imagen I(tx, ty);
			for(int i=0;i<tx;i++){
				for(int j=0;j<ty;j++){
					I(i,j)=traductora(colores[i][j]);
				}	
			}
			return I;
		}

};



void renderFunction(){
	using namespace _3D;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(camara.x,camara.y, camara.z,0,0,0,0,1,0);

	glColor(Color::rojo);
	glBegin(GL_LINES);
		glVertex3i(0,0,0);
		glVertex3i(1000,0,0);
	glEnd();
	glColor(Color::verde);
	glBegin(GL_LINES);
		glVertex3i(0,0,0);
		glVertex3i(0,255,0);
	glEnd();
	glColor(Color::azul);
	glBegin(GL_LINES);
		glVertex3i(0,0,0);
		glVertex3i(0,0,1000);
	glEnd();

	glColor(Color::cafe);
	int dl=5;

	for(int i=1;i<I.filas();i++){
		for(int j=1;j<I.columnas();j++){
			glDraw(Linea<double>(Punto<double>(i*dl,I(i,j).luz(),j*dl),Punto<double>(i*dl,I(i,j-1).luz(),j*(dl-1))));
			glDraw(Linea<double>(Punto<double>(i*dl,I(i,j).luz(),j*dl),Punto<double>(i*(dl-1),I(i-1,j).luz(),j*dl)));
		}
	}


	glPopMatrix();
	glFlush();
}

void eventoClick(int b , int e, int x, int y){

}

void eventoArrastre(int x, int y){

}

void eventoTeclado(unsigned char k, int x, int y){ 
	Imagen M;
	switch(k){
		case 'q': camara.z-=1; break;
		case 'a': camara.x+=1; break;
		case 'w': camara.y+=1; break;
		case 's': camara.y-=1; break;
		case 'e': camara.z+=1; break;
		case 'd': camara.x-=1; break;
 		case 'k': cout<<camara.toString()<<endl; break;
		case ' ': 
			glReadPixels(M);
			M.guardaBMP("Render.bmp");
			I.guardaBMP("Matriz.bmp");
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){ 
	srand((unsigned)time(NULL));
	nube nub(200,200, 00, 100, 100, 400, NULL, [](int distancia){return int( double(rand()%(distancia+1))/1000.0*(rand()%2?1:-1) );} );
	I = nub.construye([](int x){return Color::hsl(x).aGris();});
	glutInit(&argc,argv); 
	glutInitWindowSize(SCREEN_X,SCREEN_Y); 
	glutInitWindowPosition(0,0); 
	glutCreateWindow(WINDOW_NAME); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0,0.0,0.0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1000.0, 1000.0,-1000.0,1000.0,-1000.0,1000.0);


	glutMouseFunc(eventoClick); 
	glutMotionFunc(eventoArrastre); 
	glutDisplayFunc(renderFunction); 
	glutKeyboardFunc(eventoTeclado); 
	glutMainLoop();
	return 0; 
} 