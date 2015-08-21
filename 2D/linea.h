#ifndef LINEA2D_H
#define LINEA2D_H

#include "punto.h"
#include <cmath>

namespace _2D{
	template<class T>
	class Linea{
		public:
			Punto<T> inicio;
			Punto<T> fin;
			Linea<T>();
			Linea<T>(const Punto<T>& a,const Punto<T>& b);
			Linea<T>(const Punto<T>& ini, T r, T a);
			T angulo() const;
			Linea<T> rotar(T ang)const ;		
			T longitud() const;
			T longitud2() const;
			Linea invierte()const;
			Linea operator*(T d) const;
			Linea operator*=(T d);
			Linea operator/(T d) const;
			Linea operator/=(T d);
			Linea operator+(const Punto<T>& d) const;
			std::string toString()const{
				return inicio.toString()+std::string("->")+fin.toString();
			}			
			bool colisiona(const Linea<T>& b)const {
				return (ccw(inicio,fin,b.inicio) * ccw(inicio, fin, b.fin) <= 0) and (ccw(b.inicio, b.fin, inicio)*ccw(b.inicio, b.fin, fin)<=0);
			}
			Linea bisector(const T& x1, const T& x2)const{
				T dx = fin.x-inicio.x;
				T dy = fin.y-inicio.y;
				T m = -dx/dy;
				Punto<T> centro;
				centro.x = (inicio.x+fin.x)/2;
				centro.y = (inicio.y+fin.y)/2;
				T b = centro.y - m * centro.x;
				auto f = [&](const T& p){
					return Punto<T>(p,m*p+b);
				};
				return Linea<T>(f(x1),f(x2));
			}
			Linea<T> operator+=(const Punto<T>& p){
				inicio+=p;
				fin+=p;
				return *this;
			}


	};

	Punto<double> interseccion(const Linea<double>& a,const Linea<double>& b){
		double A1, B1, C1, dx1, dy1;
		dx1 = a.fin.x-a.inicio.x;
		dy1 = a.fin.y-a.inicio.y;
		A1 = dy1;
		B1 = -dx1;
		C1 = a.inicio.y*dx1-a.inicio.x*dy1;

		double A2, B2, C2, dx2, dy2;
		dx2 = b.fin.x-b.inicio.x;
		dy2 = b.fin.y-b.inicio.y;
		A2 = dy2;
		B2 = -dx2;
		C2 = b.inicio.y*dx2-b.inicio.x*dy2;

		//A1x + B1y = -C1x
		//A2x + B2y = -C2x
		double Dg = A1*B2-A2*B1;
		double Dx = -B1*C2+C1*B2;
		double Dy = -A1*C2+C1*A2;
		return Punto<double>(-Dx/Dg,Dy/Dg);
	}
	
	template<class T>
	Linea<T>::Linea():inicio(),fin(){
	}

	template<class T>
	Linea<T>::Linea(const Punto<T>& a,const Punto<T>& b){
		inicio=a;
		fin=b;
	}
	
	template<class T>
	Linea<T>::Linea(const Punto<T>& ini, T r, T a){
		inicio=ini;
		fin=Punto<T>(ini.x+r*cos(a), ini.y+r*sin(a));
	}

	template<class T>
	T Linea<T>::angulo()const {
		return (fin - inicio).angulo();
	}

	template<class T>
	Linea<T> Linea<T>::rotar(T ang)const {
		return Linea(inicio, longitud(), angulo()+ang); 
	}


	template<class T>
	T Linea<T>::longitud()const{
		return (fin-inicio).norma();
	}
	template<class T>
	T Linea<T>::longitud2()const{
		return (fin-inicio).norma();
	}

	template<class T>
	Linea<T> Linea<T>::operator*(T d)const{
		return Linea(inicio, longitud()*d, angulo());
	}
	template<class T>
	Linea<T> Linea<T>::operator*=(T d){
		*this=*this*d;
		return *this;
	}
	template<class T>
	Linea<T> Linea<T>::invierte()const{
		return Linea<T>(fin,inicio);
	}

	template<class T>
	Linea<T> Linea<T>::operator/(T d) const{
		return Linea(inicio/d,fin/d);
	}

	template<class T>
	Linea<T> Linea<T>::operator/=(T d){
		*this=*this/d;
		return *this;		
	}

	template<class T>
	Linea<T> Linea<T>::operator+(const Punto<T>& p) const{
		return Linea<T>(inicio+p, fin+p);
	}

	template<class T>
	T distancia(const Linea<T>& l,const Punto<T>& p){
		double A, B, C, dx, dy, d;
		dx = l.fin.x-l.inicio.x;
		dy = l.fin.y-l.inicio.y;
		A = dy;
		B = -dx;
		C = l.inicio.y*dx-l.inicio.x*dy;
		d = abs(A*p.x+B*p.y+C)/sqrt(A*A+B*B);
		return d;
	}
}
#endif
