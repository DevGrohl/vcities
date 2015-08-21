#ifndef LINEA4D_H
#define LINEA4D_H

#include "punto.h"

namespace _4D{
	template<class T>
	class Linea{
		public:
			Punto<T> inicio, fin;
			
			Linea():inicio(),fin(){}
			
			Linea(const Punto<T>& i, const Punto<T>& f){
				inicio=i;
				fin=f;
			}
			
			Linea(const Linea<T>& l){
				inicio=l.inicio;
				fin=l.fin;
			}
	
			Linea(const Punto<T> i, const T& hx, const T& hy, const T& hz, const T& hw){
				inicio=i;
				fin=i+Punto<T>(hx, hy, hz,hw);
			}
			
			T longitud()const{
				return (fin-inicio).norma();
			}
			
			std::string toString()const{
				return inicio.toString()+std::string("->")+fin.toString();
			}
			
			Linea operator*(const T& k)const {
				return Linea(inicio,inicio+(fin-inicio)*k); 
			}
	};
}

#endif