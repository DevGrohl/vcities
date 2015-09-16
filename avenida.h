#include "geometria.h"
#include <vector>

class Avenida{
private:
	std::vector<_2D::Punto<double>> lineas;
	double rotacionMaxima;
	void itera(){
		std::vector<_2D::Punto<double>> siguientes;
		siguientes.push_back(lineas[0]);
		for(int i=1;i<lineas.size();i++){
			_2D::Punto<double> nuevo; 
			_2D::Punto<double> centro = (lineas[i-1]+lineas[i])*0.5;
			_2D::Linea<double> l;
			double alpha = rotacionMaxima;
			double betha = M_PI/2.0 - alpha;
			double ladoB = distancia(lineas[i], centro);
			double ladoA = ladoB*sin(alpha)/sin(betha);
			_2D::Linea<double> flecha(centro,lineas[i]);
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
public:
	Avenida(const _2D::Punto<double>& inicio, const _2D::Punto<double>& fin, int iteraciones, double rotacion){
		lineas.push_back(inicio);
		lineas.push_back(fin);
		this->rotacionMaxima = rotacion;
		for(int i=0;i<iteraciones;i++){
			this->itera();
		}
	}

	void dibujar(int w){
		glColor(Color::blanco);
		glLineWidth(w);
		glBegin(GL_LINES);
		for(unsigned i = 1; i < lineas.size(); i++){
			glVertex(lineas[i-1]);
			glVertex(lineas[i]);
		}
		glEnd();
		glLineWidth(1);
	}
}; 