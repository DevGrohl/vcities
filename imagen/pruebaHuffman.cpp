#include "huffman.h"

int main(){
	char cadena[] = "go go gophers";
	NodoHuffman<char>* arbol = codifica<char,char*>(cadena,cadena+13);
	muestraHuffman(arbol);
	cout<<endl;
	return 0;
}