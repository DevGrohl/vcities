#ifndef LINEA_MULTIPUNTO
#define LINEA_MULTIPUNTO 
#include "geometria.h"
#include <vector>

template<class T>
class LineaMultipunto:public _2D::Linea<T>{
private:
	std::vector<_2D::Linea<T>> segmentos;
public:
	LineaMultipunto():_2D::Linea<T>(){

	}

	LineaMultipunto(const _2D::Linea<T>& l):_2D::Linea<T>(l){
		segmentos.push_back(*this);
	}

	void pruebaLinea(const _2D::Linea<T>& l, std::map<_2D::Linea<int>, LineaMultipunto<T>>& coleccion){
		if(this->colisionaBordes(l)){
			//Partir la linea que choca
			for(int i=0;i<segmentos.size();i++){
				if(l.colisionaBordes(segmentos[i])){
					_2D::Linea<T> segmento = segmentos[i];
					segmentos.erase(segmentos.begin()+i);
					_2D::Punto<T> p = _2D::interseccion(segmento, l);
					segmentos.push_back(_2D::Linea<T>(segmento.inicio,p));
					segmentos.push_back(_2D::Linea<T>(p,segmento.fin));
				}
			}
			coleccion[_2D::Punto<int>(*this)] = *this;	
		}
	}
};

#endif
