#ifndef DELAUNAY_H
#define DELAUNAY_H 

#include "geometria.h"
#include <unordered_set>
#include <algorithm>


//Hash para el set de puntos que guarda los triangulos
namespace std{
	template<>
	struct hash<_3D::Punto<int>> : public __hash_base<size_t, _3D::Punto<int>>{
   		size_t operator()(const _3D::Punto<int>& p) const{
        	hash<string> hasher;
        	return hasher.operator ()(p.toString());
    	}
	};
}


template<class T>
class Delaunay{
private:
	std::vector<_2D::Punto<T>> puntos;
	std::vector<std::vector<bool>> G;
	std::vector<_2D::Linea<T>> lineasT;
	std::unordered_set<_3D::Punto<int>> triangulitos;

	void pruebaTriangulo(int i, int j, int k){
		_2D::Circulo<T> c(puntos[i],puntos[j],puntos[k]);
		_2D::Punto<T> centro = c.centro;
		T dist = c.radio2();
		double area = _2D::Triangulo<T>(puntos[i],puntos[j],puntos[k]).area();
		//std::cout<<c.toString()<<" "<<area<<std::endl;
		if(colineares(puntos[i],puntos[j],puntos[k]) or not isfinite(c.radio)){
			return;
		}
		for(int w = 0; w < puntos.size(); w++){
			if(w!=i and w!=j and w!=k){
				if(distancia2(puntos[w],centro)<=dist){
					return;
				}
			}
		}

		G[i][j]=G[j][i]=G[i][k]=G[k][i]=G[k][j]=G[j][k]=true;
		triangulitos.insert(_3D::Punto<int>(i,j,k));
	}

	void calculaLineas(){
		for(int i=0;i<G.size();i++){
			for(int j=i+1;j<G.size();j++){
				if(G[i][j]){
					lineasT.push_back(_2D::Linea<T>(puntos[i],puntos[j]));
				}
			}
		}
	}

public:
	void agregaPunto(const _2D::Punto<T>& p){
		puntos.push_back(p);
	}

	std::vector<_2D::Punto<T>> damePuntos(){
		return puntos;
	}

	std::vector<_2D::Linea<T>> dameLineas(){
		return lineasT;
	}
	std::vector<std::vector<bool>> dameGrafo(){
		return G;
	}

	std::vector<_2D::Triangulo<T>> dameTriangulos(){
		std::vector<_2D::Triangulo<T>> v;
		for(auto t: triangulitos){
			v.push_back(_2D::Triangulo<T>(puntos[t.x],puntos[t.y],puntos[t.z]));
		}
		return v;
	}


	void calcular(){
		G = std::vector<std::vector<bool>>(puntos.size(),std::vector<bool>(puntos.size(),0));
		for(int i=0;i<puntos.size();i++){	
			for(int j=i+1;j<puntos.size();j++){
				for(int k=j+1;k<puntos.size();k++){	
					pruebaTriangulo(i,j,k);
				}
			}
		}

		calculaLineas();
	}

	//Retorna un grafo que 
	std::vector<std::vector<bool>> grafoDeTriangulos(){
		std::vector<std::vector<bool>> grafo(puntos.size(),vector<bool>(puntos.size()));
		for(auto t: triangulitos){
			grafo[t.x][t.y] = true;
			grafo[t.x][t.z] = true;

			grafo[t.y][t.x] = true;
			grafo[t.y][t.z] = true;

			grafo[t.z][t.x] = true;
			grafo[t.z][t.y] = true;
		}
		return grafo;
	}

	int cantidadPuntos(){
		return puntos.size();
	}

};

#endif