#ifndef LINEA3D_H
#define LINEA3D_H

#include "punto.h"

namespace _3D{
	template<class T>
	class Linea{
		public:
			Punto<T> inicio, fin;
			
			Linea():inicio(),fin(){}
			
			Linea(const Punto<T>& i,const Punto<T>& f){
				inicio=i;
				fin=f;
			}
			
			Linea(const Linea<T>& l){
				inicio=l.inicio;
				fin=l.fin;
			}
	
			Linea(const Punto<T>& i, double hx, double hy, double hz){
				inicio=i;
				fin=i+Punto<T>(hx, hy, hz);
			}
			
			double longitud()const{
				return (fin-inicio).norma();
			}
			
			std::string toString()const{
				return inicio.toString()+std::string("->")+fin.toString();
			}
			
			Linea operator*(double k)const{
				return Linea<T>(inicio,inicio+(fin-inicio)*k); 
			}
	};
}

#endif