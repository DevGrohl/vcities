/*
	http://cgm.cs.mcgill.ca/~mcleish/644/Projects/DerekJohns/TitlePage.htm
*/

#include <iostream>
#include <queue>
#include "geometria.h"
#include "gl2.h"
#include "STL2/avl.h"

using namespace std;
using namespace _2D;

const char deSitio = 's';
const char deCirculo = 'c';

class Evento{
public:
	Punto<int> posicion;
	char tipo;
	//Punto<int> ;
	bool operator<(const Evento& e)const{
		return posicion.y<e.posicion.y;
	}
	Evento(const Punto<int>& p){
		posicion = p;
		tipo = deSitio;
	}

	//Evento(const Punto<int>& p,)
};

class SweepLine{
private:
	priority_queue<Evento> cola;
	vector<Linea<int>> voronoi;
	AVL costa;

	SweepLine(const vector<Punto<int>>& v){
		for(Punto<int> p: v){
			cola.push(p);
		}

		while(not cola.empty()){
			Evento e = cola.top();
			cola.pop();
			if(e.tipo = deSitio){

			}else{

			}
		}

		//Pasar AVL a lista de lineas


	}

};



int main(){

}