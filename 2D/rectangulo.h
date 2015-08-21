#ifndef RECTANGULO2D_H
#define RECTANGULO2D_H
#include "../macros.h"
#include "linea.h"
	namespace _2D{

	template<class T>
	class Rectangulo : public Linea<T> {
		public:
			Rectangulo():Linea<T>(){}
			Rectangulo(Punto<T> a, Punto<T> b):Linea<T>(a, b){}
			Rectangulo(Punto<T> a, T b, T c): Linea<T>(a,a+Punto<T>(b,c)){}
			T base() const{
				return this->fin.x-this->inicio.x;
			}
			T altura() const{
				return this->fin.y-this->inicio.y;
			}
			T area() const{
				return base()*altura();
			}
			Punto<T> centro()const{
				return Punto<T>((this->inicio.x+this->fin.x)/2,(this->inicio.y+this->fin.y)/2);
			}
			Rectangulo<T> interseccion(const Rectangulo<T>& o)const{
				Punto<T> a(MAYOR(this->inicio.x, o.inicio.x), MAYOR(this->inicio.y, o.inicio.y));
				Punto<T> b(MENOR(this->fin.x, o.fin.x), MENOR(this->fin.y, o.fin.y));
				if(a.x > b.x or a.y > b.y)
					return Rectangulo<T>();
				else 
					return Rectangulo<T>(a, b);
			}
			bool colision(const Rectangulo<T>& o)const{
				return MENOR(this->fin.x, o.fin.x)-MAYOR(this->inicio.x, o.inicio.x) >= 0 and 
					   MENOR(this->fin.y, o.fin.y)-MAYOR(this->inicio.y, o.inicio.y) >= 0;
			}


			Rectangulo<T> operator+=(const Punto<T>& p){
				this->inicio+=p;
				this->fin+=p;
				return *this;
			}
			Rectangulo<T> operator-=(const Punto<T>& p){
				this->inicio-=p;
				this->fin-=p;
				return *this;
			}

			inline Linea<double> lado1()const{
				return Linea<double>(this->inicio, Punto<double>(this->fin.x, this->inicio.y));
			}
			inline Linea<double> lado2()const{
				return Linea<double>(Punto<double>(this->fin.x, this->inicio.y), this->fin);
			}
			inline Linea<double> lado3()const{
				return Linea<double>(Punto<double>(this->inicio.x, this->fin.y), this->fin);
			}
			inline Linea<double> lado4()const{
				return Linea<double>(this->inicio, Punto<double>(this->inicio.x, this->fin.y));
			}

	};

	template<class T>
	class RectanguloGirado{
	public:
		Punto<T> p1, p2, p3, p4;
		RectanguloGirado():p1(), p2(), p3(), p4(){

		}
		RectanguloGirado(const Rectangulo<T>& r){
			p1 = r.inicio; 
			p2 = Punto<T>(r.fin.x, r.inicio.y); 
			p3 = Punto<T>(r.inicio.x, r.fin.y); 
			p4 = r.fin; 
		}		

		Punto<T> centro(){
			return (p1+p2+p3+p4)*T(0.25);
		}

		RectanguloGirado<T> rotar(T ang, const Punto<T>& p){
			RectanguloGirado res;
			res.p1 = p1.rotar(ang, p);
			res.p2 = p2.rotar(ang, p);
			res.p3 = p3.rotar(ang, p);
			res.p4 = p4.rotar(ang, p);
			return res;
		}

		T base(){
			return distancia(p1, p2);
		}

		T altura(){
			return distancia(p1, p3);
		}

		T area(){
			return base()*altura();
		}

		T angulo(){
			return (p4-p3).angulo();
		}
	};

}
#endif