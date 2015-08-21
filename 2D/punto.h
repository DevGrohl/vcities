#ifndef PUNTO2D_H
#define PUNTO2D_H

#include <string>
#include <cstdlib>
#include <cmath>

namespace _2D{

	template<class T>
	class Punto{
		public:
			T x,y;
			Punto(T,T);
			Punto();
			std::string toString() const;
			Punto<T> operator+(const Punto<T>& b) const{
				return Punto<T>(x+b.x, y+b.y);
			}
			Punto<T> operator+=(const Punto<T>& b){
				*this=*this+b;
				return *this;
			}
			Punto<T> operator-(const Punto<T>& b)const {
				return Punto<T>(x-b.x, y-b.y);
			}
			Punto<T> operator-=(const Punto<T>& b){
				*this=*this-b;
				return *this;
			}
			Punto<T> operator*(T r)const {
				return Punto<T>(x*r, y*r);
			}
			Punto<T> operator/(T r)const{
				return Punto<T>(x/r, y/r);
			}
			static Punto<double> polar(double r , double ang){
				return Punto(r*cos(ang), r*sin(ang));
			}
			T angulo() const{
				return (T)fmod(atan2(y, x)+2*M_PI,2*M_PI);
			}
			T norma() const;
			T norma2() const{
				return x*x+y*y;
			}

			template<class NuevoTipo>
			operator Punto<NuevoTipo>(){
				return Punto<NuevoTipo>((NuevoTipo)x,(NuevoTipo)y);				
			} 

			Punto<T> rotar(T ang){
				return Punto<T>::polar(norma(), angulo()+ang);
			}

			Punto<T> rotar(T ang,const Punto<T>& p){
				return (operator-(p).rotar(ang))+p;
			}
	

	};

	template<class T>
	Punto<T>::Punto(T x ,T y){
		this->x=x;
		this->y=y;
	}

	template<class T>
	Punto<T>::Punto():x(), y(){
	}

	template<class T>
	std::string Punto<T>::toString() const{
		std::string ret="";
		ret+='(';
		ret+=std::to_string(this->x);
		ret+=',';
		ret+=std::to_string(this->y);
		ret+=')';
		return ret;
	}

	template<class T>
	T distancia(const Punto<T>& a,const Punto<T>& b){
		T dx= std::abs(a.x-b.x);
		T dy= std::abs(a.y-b.y);
		return sqrt( dx*dx + dy*dy);
	}


	template<class T>
	T distanciaM(const Punto<T>& a,const Punto<T>& b){
		T dx= std::abs(a.x-b.x);
		T dy= std::abs(a.y-b.y);
		return dx+dy;
	}

	template<class T>
	T distancia2(const Punto<T>& a,const Punto<T>& b){
		T dx= std::abs(a.x-b.x);
		T dy= std::abs(a.y-b.y);
		return  dx*dx + dy*dy;
	}

	template<class T>
	T Punto<T>::norma()const{
		return sqrt(x*x+y*y);
	}

	template<class T>
	T productoPunto(const Punto<T>& a,const Punto<T>& b){
		return a.x*b.x+a.y*b.y;
	}

	template<class T>
	T productoCruz(const Punto<T>& a,const Punto<T>& b){
		return a.x*b.y-a.y*b.x;
	}
	template<class T>
	T ccw(const Punto<T> & a, const Punto<T>& b, const Punto<T>& c){
		return productoCruz(b-a,c-a);
	}	

	template<class T>
	T dentroDeTriangulo(const Punto<T>& p, const Punto<T> & a, const Punto<T>& b, const Punto<T>& c){
		T t[3];
		t[0]=ccw(a,b,p);
		t[1]=ccw(b,c,p);
		t[2]=ccw(c,a,p);
		if(t[0]<0 and t[1]<0 and t[2]<0){
			return true;
		}else if(t[0]>0 and t[1]>0 and t[2]>0){
			return true;
		}else{
			return false;
		}

	}

	template<class T>
	bool operator==(const Punto<T>& p,const Punto<T>& q){
		return p.x==q.x and p.y==q.y;
	}

	template<class T>
	bool colineares(const Punto<T>&a, const Punto<T>&b, const Punto<T>&c){
		return (b.y-a.y)/(b.x-a.x)==(c.y-b.y)/(c.x-b.x);
	}


}


#endif