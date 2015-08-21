#ifndef TRIANGULO2D_H
#define TRIANGULO2D_H

#include "punto.h"

namespace _2D{

	template<class T>
	class Triangulo{
		public:
			Punto<T> p1,p2,p3;
		Triangulo():p1(),p2(),p3(){

		}
		Triangulo(const Punto<T>& a,const Punto<T>& b,const Punto<T>& c){
			p1 = a;
			p2 = b;
			p3 = c;
		}
		Triangulo<T> operator+(const Punto<T>& a)const{
			return Triangulo<T>(p1+a,p2+a,p3+a);
		}
		Triangulo<T> operator+=(const Punto<T>& a){
			p1 += a;
			p2 += a;
			p3 += a;
			return *this;
		}
		Triangulo<T> operator-(const Punto<T>&a)const{
			return Triangulo<T>(p1-a,p2-a,p3-a);
		}
		Triangulo<T> operator-=(const Punto<T>& a){
			p1 -= a;
			p2 -= a;
			p3 -= a;
			return *this;
		}
		T perimetro()const {
			return distancia(p1,p2)+distancia(p2,p3)+distancia(p3,p1);
		}
		T area()const {
			T a = distancia(p1,p2);
			T b = distancia(p2,p3);
			T c = distancia(p3,p1);
			T s = (a+b+c)/2;
			return sqrt(s*(s-a)*(s-b)*(s-c));	
		}

		std::string toString()const {
			return std::string("T(")+p1.toString()+":"+p2.toString()+":"+p3.toString()+")";
		}

		Punto<T> centroDeGravedad()const{
			return (p1+p2+p3)/3;
		}		
	};

	template<class T>
	bool operator==(const Triangulo<T>&a, const Triangulo<T>&b){
		return a.p1==b.p1 and a.p2==b.p2 and a.p3==b.p3; 
	}

	template<class T>
	bool comparteLado(const Triangulo<T>&a, const Triangulo<T>&b){
		int iguales = 0;

		iguales += a.p1 == b.p1;
		iguales += a.p1 == b.p2;
		iguales += a.p1 == b.p3;

		iguales += a.p2 == b.p1;
		iguales += a.p2 == b.p2;
		iguales += a.p2 == b.p3;

		iguales += a.p3 == b.p1;
		iguales += a.p3 == b.p2;
		iguales += a.p3 == b.p3;

		return iguales >= 2;
	}


}





#endif