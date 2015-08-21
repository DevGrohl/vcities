#ifndef POLIGONO_H
#define POLIGONO_H 
#include "punto.h"
#include "linea.h"
#include "rectangulo.h"
#include <vector>
namespace _2D{

template<class T>
class Poligono{
public:
	std::vector<Punto<T>> vertices;
	Poligono(){
	}
	void agregaPunto(const Punto<T>& p){
		vertices.push_back(p);
	}
	Punto<T> centro() const {
		Punto<T> c;
		for(auto p: vertices){
			c+=p;
		}
		c.x/=vertices.size();
		c.y/=vertices.size();
		return c;
	}
	int tam() const{
		return vertices.size();
	}
	const Punto<T> operator[](int i)const {
		return vertices[i];
	}

	bool colisiona(const Linea<T>& l)const{
		for(int i=1;i<vertices.size();i++){
			if(l.colisiona(Linea<T>(vertices[i], vertices[i-1]))){
				return true;
			}
		}
		return l.colisiona(Linea<T>(vertices[0],vertices[tam()-1]));
	}

	Rectangulo<T> rectanguloRecubridor()const{
		Rectangulo<T> resultado(vertices[0],vertices[0]);
		for(auto p: vertices){
			resultado.inicio.x = min(resultado.inicio.x,p.x);
			resultado.inicio.y = min(resultado.inicio.y,p.y);
			resultado.fin.x = max(resultado.fin.x,p.x);
			resultado.fin.y = max(resultado.fin.y,p.y);
		}
		return resultado;
	}

	Poligono<T> rotar(T angulo)const{
		Punto<T> c = centro();
		Poligono<T> resultado;
		for(auto p: vertices){
			resultado.agregaPunto(c+(p-c).rotar(angulo));
		}
		return resultado;
	}

	RectanguloGirado<T> rectanguloRecubridorMinimo(int iteraciones=36)const{
		double da = 2.0*M_PI/iteraciones; //diferencia de angulo
		RectanguloGirado<T> resultado = this->rectanguloRecubridor();
		for(int i=1;i<iteraciones;i++){
			T angulo = (T)i*da;
			Poligono<T> p=this->rotar(angulo);
			RectanguloGirado<T> calculado = p.rectanguloRecubridor();
			calculado=calculado.rotar(-angulo, p.centro());
			if(calculado.area()<resultado.area()){
				resultado=calculado;
			}
		}
		return resultado;
	}

	bool contiene(const Punto<T>& p){
		for(int i=1;i<tam();i++){
			if(ccw(p,vertices[i-1], vertices[i])<0){
				return false;
			}
		}
		return true;
	}
};

}
#endif
