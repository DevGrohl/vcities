#include "imagen/imagen.h"        //Exportacion de resultados
#include "delaunay.h"   	   	  //Para calcular triangulacionaciones
#include "geometria.h"			  //Operaciones con puntos


template<class T>
class VoronoiNoGeometrico{
private:
	std::vector<_2D::Punto<T>> puntos;
	int x, y;
	Imagen grafica;
	T (*func)(const _2D::Punto<T>&,const _2D::Punto<T>&);
public:
	VoronoiNoGeometrico(){	
	}
	VoronoiNoGeometrico(int x, int y,const std::vector<_2D::Punto<T>>& v, T (*f_dist)(const _2D::Punto<T>&,const _2D::Punto<T>&)){
		this->x = x;
		this->y = y;
		this->puntos = v;
		this->func = f_dist;
	}

	void agregaPunto(const _2D::Punto<T>&p){
		puntos.push_back(p);
	}
	Imagen obtenerImagen(){
		Imagen I(x,y);	
		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				T dist_min = func(_2D::Punto<T>(),_2D::Punto<T>(x,y));;
				int id = 0;
				_2D::Punto<T> actual(j,i);
				for(int k=0;k<puntos.size();k++){
					T dist = func(actual,puntos[k]);
					if(dist<dist_min){
						dist_min = dist;
						id=k;
					}
				}
				try{
					I.en((int)actual.y,(int)actual.x)  =Color::hsl(113*id+113*4);
				}catch(...){
				}	
					
			}
		}

		for(auto p:puntos){
			try{
				I.en((int)p.y,(int)p.x) = Color::rojo;
			}catch(...){

			}

		}

		return I-I.laplace().umbral(1,Color::negro, Color::blanco);
	}
};

template<class T>
class Voronoi{
private:
	//puntos de entrada
	std::vector<_2D::Punto<T>> puntos;

	//Calculo de la triangulacion
	Delaunay<T> delaunay;
	//Triangulos en delaunay
	std::vector<_2D::Triangulo<T>> triangulos;

	//Centros de los circulos que pasan por los triangulos
	std::vector<_2D::Punto<T>> centrosCT;
	std::vector<std::vector<bool>> G; //Grafo que representa si 2 triangulos tienen un lado en comun
	std::vector<_2D::Linea<T>> lineas; //Lineas del diagrama
	//Calculo de las regiones
	std::vector<_2D::Poligono<T>> regiones_; //Regiones en el diagrama
	std::vector<std::vector<bool>> GT; 		//grafo de delaunay
	bool calcularRegiones_;
public:
	Voronoi(){
		calcularRegiones_ = true;
	}

	void agregaPunto(const _2D::Punto<T>& p){
		delaunay.agregaPunto(p);
	}

	void calcularRegiones(bool t){
		calcularRegiones_ = t;
	}


	std::vector<_2D::Punto<T>> damePuntos(){
		return puntos;
	}

	std::vector<_2D::Linea<T>> dameLineas(){
		return lineas;
	}

	std::vector<std::vector<bool>> dameGrafo(){
		return G;
	}

	int cantidadPuntos(){
		return delaunay.cantidadPuntos();
	}

	std::vector<std::vector<bool>> dameGrafoTriangulacion(){
		return GT;
	}

	void calcular(){
		puntos = delaunay.damePuntos();
		std::cout<<"Iniciando el Calculo de voronoi con "<<puntos.size()<<" Puntos "<<std::endl;
		delaunay.calcular();
		triangulos = delaunay.dameTriangulos();
	//Calculo de los triangulos adyacentes	
		//inicializacion del grafo
		G = std::vector<std::vector<bool>>(triangulos.size(),std::vector<bool>(triangulos.size(),false));	
		GT = delaunay.dameGrafo();
		for(int i=0;i<triangulos.size();i++){
			for(int j=i+1;j<triangulos.size();j++){
				if(comparteLado(triangulos[i],triangulos[j])){
					G[i][j]=G[j][i]=true;
				}
			}
		}	
	//Se calculan los centros de los circulos en los 
	// triangulos para evitar volverlos a calcular
		for(auto t: triangulos){
			centrosCT.push_back(_2D::Circulo<T>(t.p1,t.p2,t.p3).centro);
		}
	//Ahora las lineas, se revisa sobre el grafo de los triangulos que comparten un lado
		for(int i=0;i<G.size();i++){
			for(int j=i+1;j<G.size();j++){
				if(G[i][j]){
					lineas.push_back(_2D::Linea<T>(centrosCT[i],centrosCT[j]));
				}
			}
		}
		if(calcularRegiones_){
			std::vector<std::vector<bool>> grafoTriangulos = GT;//delaunay.dameGrafo();
			std::cout<<grafoTriangulos.size()<<" "<<puntos.size()<<std::endl;
			for(int i=0;i<grafoTriangulos.size();i++){
				_2D::Poligono<T> region;
				std::vector<_2D::Punto<T>> p;
				for(int j=0;j<grafoTriangulos[i].size();j++){
					if(grafoTriangulos[i][j]){
						p.push_back(puntos[j]);
					}
				}
				std::sort(p.begin(), p.end(),[&](const _2D::Punto<T>& a, const _2D::Punto<T>& b){
					return (a-puntos[i]).angulo() < (b-puntos[i]).angulo();
				});
				for(int j=1;j<p.size();j++){
					region.agregaPunto(_2D::Circulo<T>(puntos[i],p[j],p[j-1]).centro);
				}
				region.agregaPunto(_2D::Circulo<T>(puntos[i],p[0],p[p.size()-1]).centro);
				std::sort(region.vertices.begin(), region.vertices.end(),[&](const _2D::Punto<T>& a, const _2D::Punto<T>& b){
					return (a-puntos[i]).angulo() < (b-puntos[i]).angulo();
				});
				bool choca=false;
				for(auto l: lineas){
					if(region.colisiona(l)){
						choca=true;
						break;	
					}
				}
				if(not choca){	
					regiones_.push_back(region);
				}
			}
		}
	}

	std::vector<_2D::Poligono<T>> regiones(){
		return regiones_;
	}
};
