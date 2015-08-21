#include "linea.h"
namespace _3D{
	template<class T>
	class Prisma:public Linea<T>{
		public:
			Prisma():Linea<T>(){}
			Prisma(const Punto<T>& i, const Punto<T>& f):Linea<T>(i,f){}
			Prisma(const Punto<T> a, double b, double c, double d):Linea<T>(a,b,c,d){}
			Prisma(const Linea<T>& l):Linea<T>(l){}
			
			Punto<T> centro()const{
				return this->inicio+(this->fin-this->inicio)*0.5;
			}
	};
}