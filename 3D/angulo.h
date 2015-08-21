#ifndef ANGULO3D_H
#define ANGULO3D_H

namespace _3D{
	class angulo{
		public:
			double phi, theta;
			angulo(){
				phi=theta=0;
			}
			angulo(double x, double y){
				phi=x;
				theta=y;
			}
	};
}

#endif
