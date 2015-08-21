#include <iostream>
#include <iomanip>
#include "imagen.h"
using namespace std;



int main(){
	Imagen I(16,8);
	for(int i=0;i<8;i++){
		for(int j=0;j<16;j++){
			I.en(i,j)=(j>=8?Color::blanco:Color::negro);
		}
	}
	I.guardaBMP("test.bmp");
	I.leeBMP("test.bmp");
	I.guardaJPG("test.jpg");

	return 0;
}