#ifndef OWL_H
#define OWL_H 

#include <string> 

#ifdef PUNTO2D_H
template<class T>
std::string owl(const _2D::Punto<T> p){
	return "<punto d=\"2\" x=\""+std::to_string(p.x)+"\" y=\""+std::to_string(p.y)+"\"/>";
}
#endif

#ifdef LINEA2D_H
template<class T>
std::string owl(const _2D::Linea<T> l){
	return "<linea d=\"2\" >\n\t" + owl(l.inicio) +"\n\t"+owl(l.fin)+"\n</linea>";
}
#endif

#ifdef POLIGONO_H

template<class T>
std::string owl(const _2D::Poligono<T> p){
	std::string resultado = "<poligono d\"=2\">";
	for(auto v: p.vertices){
		resultado+=owl(v)+"\n";
	}
	return resultado+"</poligono>";
}
#endif

#endif