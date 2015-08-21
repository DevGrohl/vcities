#ifndef PUNTO4D_H
#define PUNTO4D_H
#include "../macros.h"

namespace _4D{

	template<class T>
	class Punto{
		public:
			T x,y,z,w;
			Punto(){
				z=x=y=w=0;
			}
			Punto(const T& a, const T& b,const T& c,const T& d){
				x=a;
				y=b;
				z=c;
				w=d;
			}

			T norma()const{
				return sqrt(x*x+y*y+z*z+w*w);
			}
			T norma2()const{
				return x*x+y*y+z*z+w*w;
			}
			Punto operator+(const Punto<T>& otro)const{
				return Punto(x+otro.x, y+otro.y, z+otro.z,w+otro.w);
			}
			Punto operator-(const Punto<T>& otro)const{
				return Punto(x-otro.x, y-otro.y, z-otro.z,w-otro.w);
			}
			Punto operator*(T f)const {
				return Punto(x*f, y*f, z*f,w*f);
			}

			Punto operator-=(const Punto<T>& otro){
				x-=otro.x;
				y-=otro.y;
				z-=otro.z;
				w-=otro.w;
				return *this;
			}

			Punto operator+=(const Punto<T>& otro){
				x+=otro.x;
				y+=otro.y;
				z+=otro.z;
				w+=otro.w;
				return *this;
			}

			Punto operator*=(T f){
				x*=f;
				y*=f;
				z*=f;
				w*=f;
				return *this;
			}

			Punto unitario()const{
				T u=norma();
				return Punto(x/u, y/u, z/u,w/u);
			}
			std::string toString()const{
				return std::string("(")+std::to_string(x)+std::string(" , ")+std::to_string(y)+std::string(" , ")+std::to_string(z)+std::string(",")+std::to_string(w)+std::string(")");
			}

	};

	template<class T>
	T productoPunto(const Punto<T>& a, const Punto<T>& b){
		return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
	}

	template<class T>
	Punto<T> productoCruz(const Punto<T>& a, const Punto<T>& b, const Punto<T>& c){
		return Punto<T>(
			a.y*(b.z*c.w - c.z*b.w) - a.z*(b.y*c.w - c.y*b.w) + a.w*(b.y*c.z - c.y*b.z),
			-a.x*(b.z*c.w - c.z*b.w) + a.z*(b.x*c.w - c.x*b.w) - a.w*(b.x*c.z - c.x*b.z), 
			a.x*(b.y*c.w - c.y*b.w) - a.y*(b.x*c.w - c.x*b.w) + a.w*(b.x*c.y - c.x*b.y) ,
			-a.x*(b.y*c.z - c.y*b.z) + a.y*(b.x*c.z - c.x*b.z) - a.z*(b.x*c.y - c.x*b.y)
		);
	}

	template<class T>
	Punto<T> PuntoDeVista(const Punto<T>& desde, const Punto<T>& hacia, const Punto<T>& arriba, const Punto<T>& sobre, const Punto<T>&  p){
		Punto<T> A, B, C, D;

		D = (hacia-desde).unitario();
		A = productoCruz(arriba, sobre, D).unitario();
		B = productoCruz(sobre, D, A).unitario();
		C = productoCruz(D, A, B);

		Punto<T> temp = p-desde;

		return Punto<T>(productoPunto(temp,A), productoPunto(temp,B), productoPunto(temp,C), productoPunto(temp,D));
 
	}
}

#endif