#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "3D/linea.h"
#include "3D/punto.h"
#include "3D/prisma.h"
#include "3D/angulo.h"
#include "3D/angulo.h"

#include "2D/linea.h"
#include "2D/poligono.h"
#include "2D/punto.h"
#include "2D/triangulo.h"
#include "2D/rectangulo.h"
#include "2D/circulo.h"

#include "4D/punto.h"
#include "4D/linea.h"

template<class T>
_2D::Punto<T> conversionParalela(const _3D::Punto<T>& desde,const _3D::Punto<T>& hacia,const _3D::Punto<T>& arriba,const _3D::Punto<T>& p){
	_3D::Punto<T> t= _3D::puntoDeVista(desde,hacia,arriba,p);
	return _2D::Punto<T>(t.x,t.y);
}

template<class T>
_3D::Punto<T> conversionParalela(const _4D::Punto<T>& desde,const  _4D::Punto<T>& hacia,const _4D::Punto<T>& arriba,const _4D::Punto<T>& sobre,const _4D::Punto<T>&  p){
	_4D::Punto<T> x = _4D::PuntoDeVista<T>( desde,  hacia,  arriba,  sobre, p);
	return _3D::Punto<T>(x.x, x.y, x.z);
}

template<class T>
_2D::Linea<T> conversionParalela(const _3D::Punto<T>& desde,const _3D::Punto<T>& hacia, const _3D::Punto<T>& arriba, const _3D::Linea<T>& l){
	return _2D::Linea<T>(conversionParalela<T>(desde, hacia, arriba, l.inicio), conversionParalela<T>(desde, hacia, arriba, l.fin));
}

template<class T>
_3D::Linea<T> conversionParalela(const _4D::Punto<T>& desde,const _4D::Punto<T>& hacia, const _4D::Punto<T>& arriba,const _4D::Punto<T>& sobre,const _4D::Linea<T>& l){
	return _3D::Linea<T>(conversionParalela<T>(desde,hacia,arriba,sobre,l.inicio), conversionParalela<T>(desde,hacia,arriba,sobre,l.fin));
}

#endif