#ifndef CIRCULO_H	
#define CIRCULO_H	 

#include "punto.h"
namespace _2D{

	template<class T>
	class Circulo{
		private: T radio2_;
	public:
		Punto<T> centro;
		T radio;

		Circulo():centro(),radio(){
		}

		Circulo(const Punto<T>& c, const T& r):centro(c),radio(r){
		}

		Circulo(const Punto<T>& p1,const Punto<T>& p2, const Punto<T>& p3){
			T a1, b1, c1, d1;
			a1 = p1.x;
			b1 = p1.y;
			c1 = 1;
			d1 = -p1.norma2();
			T a2, b2, c2, d2;
			a2 = p2.x;
			b2 = p2.y;
			c2 = 1;
			d2 = -p2.norma2();
			T a3, b3, c3, d3;
			a3 = p3.x;
			b3 = p3.y;
			c3 = 1;
			d3 = -p3.norma2();

			T Dg, Dx, Dy, Dz;
			/*
				a1x + b1y + c1z = d1
				a2x + b2y + c2z = d2
				a3x + b3y + c3z = d3
			*/

			Dg = a1*b2*c3 + b1*c2*a3 + c1*a2*b3 - 
				(c1*b2*a3 + b1*a2*c3 + a1*c2*b3);

			Dx = d1*b2*c3 + b1*c2*d3 + c1*d2*b3 - 
				(c1*b2*d3 + b1*d2*c3 + d1*c2*b3);

			Dy = a1*d2*c3 + d1*c2*a3 + c1*a2*d3 - 
				(c1*d2*a3 + d1*a2*c3 + a1*c2*d3);

			Dz = a1*b2*d3 + b1*d2*a3 + d1*a2*b3 - 
				(d1*b2*a3 + b1*a2*d3 + a1*d2*b3);


			T D = Dx / Dg;	
			T E = Dy / Dg;	
			T F = Dz / Dg;	

			centro = Punto<T>(-D/2,-E/2);
			radio2_ = abs(centro.norma2()-F);
			radio = sqrt(radio2_);
		}

		T radio2(){
			if(radio2_==T()){
				radio2_ = radio*radio;
			}
			return radio2_;
		}

		std::string toString() const{
			return std::string("[C")+centro.toString()+":"+std::to_string(radio)+"]";
		}



	};

}
#endif