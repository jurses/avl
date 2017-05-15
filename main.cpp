#include <iostream>
#include "arbolBin.hpp"
#include "nodo.hpp"
#include <fstream>
#include "matricula.hpp"

template<class T>
void lector(const char* nombre, arbolBin_t<T>* arbol){
	char c;
	int x;
	std::ifstream archivo;
	if(nombre)
		archivo.open(nombre, std::ifstream::in);
	else
		std::cout << "No se especificó el nombre" << std::endl;

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
				case 'm':
				case 'M':	arbol->mostrar(std::cout);
							break;
			}
		}
		archivo.close();
	}
}

template<class T>
void demostracion(arbolBin_t<T>* arbol){
	bool salida = false;
	int opcion = -1;
	char cad_matr[7];
	while(!salida){
		std::cout << "0: Salir\n" << "1: Insertar\n" << "2: Eliminar\n" << std::endl;
		std::cin >> opcion;
		switch(opcion){
			case 0:	salida = true;
					break;
			case 1:	std::cout << "4 números y 3 letras" << std::endl;
					std::cout << "Insertar: ";
					std::cin >> cad_matr;
					arbol->insertar(cad_matr);
					break;
			case 2:	std::cout << "4 números y 3 letras" << std::endl;
					std::cout << "Eliminar: ";
					std::cin >> cad_matr;
					arbol->eliminar(cad_matr);
					break;
			default:	std::cout << "Mala opción" << std::endl;
		}
	}
}

int main(int argc, char** argv){
	arbolBin_t<int> arbol;
	arbolBin_t<matricula_t> arbolmtr;
	if(argc == 1){
		std::cout << "-f <archivo>" << std::endl;
		std::cout << "-d [modo demostración]" << std::endl;
		std::cout << "-e [modo estadista]" << std::endl;
	}
	else if(argc > 1){
		if(argv[1][0] == '-'){
			switch(argv[1][1]){
				case 'f':	lector(argv[2], &arbol);
							break;
				case 'd':	demostracion(&arbolmtr);
							break;
			}
		}else
			std::cout << "Mal comando: " << argv[1] << std::endl;
	}
	return argc;
}
