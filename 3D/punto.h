#ifndef PUNTO3D_H
#define PUNTO3D_H

#include <cmath>
#include <string>
#include "../macros.h"
#include "angulo.h"

namespace _3D{
	template<class T>
	class Punto{
		public:
			T x, y, z;
			Punto(){
				x=y=z=0;
			}
			Punto(T X, T Y,T Z){
				x=X;
				y=Y;
				z=Z;
			}
			T norma() const{
				return sqrt(x*x+y*y+z*z);
			}
			T norma2() const{
				return x*x+y*y+z*z;
			}
			Punto operator+(const Punto<T>& otro) const{
				return Punto(x+otro.x, y+otro.y, z+otro.z);
			}
			Punto operator-(const Punto<T>& otro) const{
				return Punto(x-otro.x, y-otro.y, z-otro.z);
			}
			Punto operator-=(const Punto<T>& otro){
				x-=otro.x;
				y-=otro.y;
				z-=otro.z;
				return *this;
			}
			Punto operator*(T f)const {
				return Punto(x*f, y*f, z*f);
			}
			Punto unitario() const {
				T u=norma();
				return Punto(x/u, y/u, z/u);
			}
			std::string toString()const {
				return std::string("(")+std::to_string(x)+std::string(" , ")+std::to_string(y)+std::string(" , ")+std::to_string(z)+std::string(")");
			}
	};

	template<class T>
	T productoPunto(const Punto<T>& a,const Punto<T>& b){
		return a.x*b.x + a.y*b.y + a.z*b.z; 
	}

	template<class T>
	Punto<T> productoCruz(const Punto<T>& a,const Punto<T>& b){
		return Punto<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
	}

	template<class T>
	Punto<T> puntoDeVista(const Punto<T>& desde,const Punto<T>& hacia,const Punto<T>& arriba,const Punto<T>& p){
		Punto<T> A, B, C;
		C=(hacia-desde).unitario();
		A=productoCruz(arriba, C).unitario();
		B=productoCruz(C,A);
		Punto<T> aux=p-desde;
		return Punto<T>(productoPunto(aux, A), productoPunto(aux,B), productoPunto(aux,C));
	}

	template<class T>
	bool operator==(const Punto<T>&a, const Punto<T>&b){
		return a.x == b.x and a.y==b.y and a.z == b.z;
	}

}

#endif