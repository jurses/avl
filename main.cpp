#include <iostream>
#include "arbolBin.hpp"
#include "nodo.hpp"
#include <fstream>

template<class T>
void lector(const char* nombre, arbolBin_t<T>* arbol){
	char c;
	int x;
	std::ifstream archivo;
	if(nombre)
		archivo.open(nombre, std::ifstream::in);
	else
		archivo.open("lata.txt", std::ifstream::in);

	if(archivo.is_open()){
		while (archivo.good()) {
			archivo >> c;
			archivo >> (int&)x;
			switch(c){
				case 'i':
				case 'I':	arbol->insertar(x);
							std::cout << "A insertar: " << x << std::endl;
							break;
				case 'e':
				case 'E':	arbol->eliminar(x);
							std::cout << "A eliminar: " << x << std::endl;
							break;
			}
		}
		archivo.close();
	}
}

int main(void){
	arbolBin_t<int> arbol;
	lector("x.txt", &arbol);
}
