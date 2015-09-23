#ifndef CIUDAD_H
#define CIUDAD_H 
#include "voronoi.h"   	   	      //Para calcular triangulacionaciones
#include "owl.h"				  //Para generar los xml
#include <map>		  			  //
#include "avenida.h"
#include "multilinea.h"			  //
#include <cstdlib> 				  //Random


// Funcion que calcula una cuadricula de calles dentro de un poligono
// Para adaptarse a los objetivos de la ciudad virtual, existe dependencia entre 
// las lineas en comun que podrian tener varios poligonos, por lo que se requieren tener
// referencias para que se modifique para todos los poligonos
std::vector<_2D::Linea<double>> mallaDePuntos(const _2D::Poligono<double>& region, std::map<_2D::Linea<int>, LineaMultipunto<double>>& coleccionLineas, int largoManzanas, int anchoManzanas){
	_2D::RectanguloGirado<double> r = region.rectanguloRecubridorMinimo();
	//Algunas variables auxiliares precalculadas
	double base = r.base();
	double altura = r.altura();
	double angulo = -r.angulo();
	//Se barre la matriz de punto base x altura
	std::vector<_2D::Linea<double>> res, l;
	for(double y = 0; y-largoManzanas<altura; y+=largoManzanas){
		for(double x= anchoManzanas; x-largoManzanas<base; x+= anchoManzanas){		
			_2D::Linea<double> li (_2D::Punto<double>(-x,-y),_2D::Punto<double>(-x+anchoManzanas,-y));
			li.inicio = li.inicio.rotar(-angulo);
			li.fin = li.fin.rotar(-angulo);
			li+=r.p4;
			l.push_back(li);
		}
	}

	for(double x = 0; x- anchoManzanas <base; x+=anchoManzanas){
		for(double y = largoManzanas; y-largoManzanas<altura; y+=largoManzanas){		
			_2D::Linea<double> li (_2D::Punto<double>(-x,-y),_2D::Punto<double>(-x,-y+largoManzanas));
			li.inicio = li.inicio.rotar(-angulo);
			li.fin = li.fin.rotar(-angulo);
			li+=r.p4;
			l.push_back(li);
		}
	}
	

	//Filtra las lineas que quedan fuera del poligono y recorta aquellas que estan sobre el contorno
	for(auto i: l){
		bool contiene_ini = region.contiene(i.inicio);
		bool contiene_fin = region.contiene(i.fin);
		if(contiene_ini and contiene_fin){
			res.push_back(i);
		}else if(contiene_fin){
			i.inicio = region.puntoInterseccion(i);
			res.push_back(i);
		}else if(contiene_ini){
			i.fin = region.puntoInterseccion(i);
			res.push_back(i);
		}
	}

	//Actualiza las lineas de la coleccion
	for(auto avenida: region.lados()){
		auto lm = coleccionLineas[_2D::Linea<int>(avenida)];
		for(auto calle: res){
			lm.pruebaLinea(calle);
		}
		coleccionLineas[_2D::Linea<int>(avenida)] = lm;
	}
	
	return res;
}

class Ciudad{
public:
	//Datos de entrada
	_2D::Punto<int> tam;
	_2D::Punto<int> tamMat;
	Voronoi<double> voronoi;
	std::vector<_2D::Punto<double>> puntos; //Puntos generados

	//resultados
	std::vector<std::vector<bool>> triangulacion; //Grafo que representa 2 puntos deben conectarse segun la triangulacion de delaunay
	std::vector<_2D::Punto<int>> lineas;		    //Lineas del diagrama
	std::vector<_2D::Poligono<double>> regiones;   //Poligonos de las regiones del diagrama de voronoi
	std::map<int, _2D::Punto<int>> llaves;
	std::map<_2D::Linea<int>, LineaMultipunto<double>> coleccionAvenidas;
	std::vector<Avenida> avenidas;

	//Tamaños de la ciudad (coordendas van de (0,0) a (x,y))
	//Cantidad de puntos para el voronoi inicial (n*m)
	
	Ciudad(int x, int y, int n, int m, int anchoManzanas,int largoManzanas, int avenidas_hor, int avenidas_ver,int iteracionesAvenida, double rotacionMaxima){
		tam = _2D::Punto<int>(x,y);
		tamMat = _2D::Punto<int>(n,m);
		int dx = x/n;
		int dy = y/m;
		std::vector<_2D::Linea<double>> lineas_temp;

		//Generacion de los puntos aleatorios
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				voronoi.agregaPunto(_2D::Punto<double>(dx*i+rand()%dx,dy*j+rand()%dy));
			}
		}

		//Se realizan los calculos de voronoi
		voronoi.calcularRegiones(true);
		voronoi.calcular();
		puntos=voronoi.damePuntos();

		auto lineasvoronoi = voronoi.dameLineas();

		//Se agregan como avenidas secundarias las lineas generadas por voronoi
		for(auto& l: lineasvoronoi){
			//Se castean los tipos a enteros para que sean identificadores unicos
			auto l2 = _2D::Linea<int>(l);
			coleccionAvenidas[l2] = l;
		}

		//Se obtiene la triangulacion
		//triangulacion=voronoi.dameGrafoTriangulacion();	
		regiones = voronoi.regiones();
		int tam = regiones.size();
		int i=0;

		//Calculo de los puntos internos a las regiones
		for(auto region: regiones){
			auto temp = mallaDePuntos(region,coleccionAvenidas,largoManzanas,anchoManzanas);
			lineas_temp.insert(lineas_temp.end(),temp.begin(), temp.end());
		}

		//Se crean las avenidas
		for(int i=0;i<avenidas_hor;i++){
			avenidas.push_back(Avenida(_2D::Punto<double>(0,random()%y), _2D::Punto<double>(x,random()%y), iteracionesAvenida, rotacionMaxima));
		}
		for(int i=0;i<avenidas_ver;i++){
			avenidas.push_back(Avenida(_2D::Punto<double>(random()%x,0), _2D::Punto<double>(random()%x,y), iteracionesAvenida, rotacionMaxima));
		}

		//Se cortan las lineas de las avenidas en las intersecciones
		for(auto& avenida: avenidas){
			std::vector<LineaMultipunto<double>> multilineas = avenida.multilineas();
			for(auto& ml : multilineas){
				ml.pruebaLineaCorte(lineas_temp);
				lineas_temp.insert(lineas_temp.begin(),ml.segmentos.begin(),ml.segmentos.end());
			}
		}
		
		//Una vez que fueron calculadas las avenidas y movidas al vector principal pueden ser eliminadas
		avenidas.clear();


		//Se eliminan las lineas que son muy pequeñas, para estas lineas que van de A a B, se calcula
		//El punto intermedio C y se intercambian los valores de A y B en las demas lineas por C. 
		//Trunca los valores reales para asi trabajar con enteros
		std::vector<_2D::Linea<int>> lineas;
		for(auto& l: lineas_temp){
			lineas.push_back(_2D::Linea<int>(l));
		}



		std::map<_2D::Punto<int>, int> puntos;
		int cont_id=0;

		//Eliminacion de lineas muy pequeñas
		for(auto l: lineas){
			if(puntos.count(l.inicio) == 0){
				puntos[l.inicio] = cont_id++;
			}
			if(puntos.count(l.fin) == 0){
				puntos[l.fin] = cont_id++;
			}
		//	int longitud = l.longitud2();
		/*	if( longitud< largoManzanas*largoManzanas or longitud < anchoManzanas*anchoManzanas){
				_2D::Punto<int> centro = (l.inicio+l.fin)/2;
				if(puntos.count(centro) == 0){
					puntos[centro] = cont_id++;
				}
				puntos[l.inicio] = puntos[centro];
				puntos[l.fin] = puntos[centro];
			}*/
		}

		for(auto l: lineas){
			_2D::Punto<int> p(puntos[l.inicio],puntos[l.fin]);
			this->lineas.push_back(p);
			llaves[p.x] = l.inicio;
			llaves[p.y] = l.fin;
		}

		//lineas_temp=voronoi.dameLineas();
		



		std::cout<<"Fin"<<std::endl;
	}
};

#endif