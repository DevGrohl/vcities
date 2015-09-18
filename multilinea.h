#ifndef LINEA_MULTIPUNTO
#define LINEA_MULTIPUNTO 
#include "geometria.h"
#include <vector>


template<class T>
class LineaMultipunto:public _2D::Linea<T>{
private:
public:
	std::vector<_2D::Linea<T>> segmentos;
	LineaMultipunto():_2D::Linea<T>(){

	}

	LineaMultipunto(const _2D::Linea<T>& l):_2D::Linea<T>(l){
		segmentos.push_back(l);
	}

	void pruebaLinea(const _2D::Linea<T>& l){
		if(this->colisionaBordes(l)){
			//Partir la linea que choca
			unsigned tam = segmentos.size();
			for(unsigned i=0;i<tam;i++){
				if(l.colisionaBordes(segmentos[i])){
					_2D::Linea<T> segmento = segmentos[i];
					segmentos.erase(segmentos.begin()+i);
					_2D::Punto<T> p = _2D::interseccion(segmento, l);
					segmentos.push_back(_2D::Linea<T>(segmento.inicio,p));
					segmentos.push_back(_2D::Linea<T>(p,segmento.fin));
					i--;tam--;
				}
			}
		}
	}

	void pruebaLineaCorte(std::vector<_2D::Linea<T>>& v){
		for(int k = v.size()-1 ; k >= 0 ; k--){
			if(this->colisiona(v[k])){
				unsigned tam = segmentos.size();
				for(unsigned i=0;i<tam;i++){
					if(v[k].colisionaBordes(segmentos[i])){
						_2D::Linea<T> segmento = segmentos[i];
						segmentos.erase(segmentos.begin()+i);
						_2D::Punto<T> p = _2D::interseccion(segmento, v[k]);
						segmentos.push_back(_2D::Linea<T>(segmento.inicio,p));
						segmentos.push_back(_2D::Linea<T>(p,segmento.fin));
						v.push_back(_2D::Linea<T>(p,v[k].fin));
						v.push_back(_2D::Linea<T>(p,v[k].inicio));
						v.erase(v.begin()+k);
						break;
					}
				}
			}else if(this->colisionaBordes(v[k])){
				//Partir la linea que choca
				std::cout<<":vv"<<std::endl;
				unsigned tam = segmentos.size();
				for(unsigned i=0;i<tam;i++){
					if(v[k].colisionaBordes(segmentos[i])){
						_2D::Linea<T> segmento = segmentos[i];
						segmentos.erase(segmentos.begin()+i);
						_2D::Punto<T> p = _2D::interseccion(segmento, v[k]);
						segmentos.push_back(_2D::Linea<T>(segmento.inicio,p));
						segmentos.push_back(_2D::Linea<T>(p,segmento.fin));
						i--;tam--;
						break;
					}
				}
			}
		}
	}
};

#endif
