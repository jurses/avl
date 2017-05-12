#include <iostream>
#include "arbolBin.hpp"
#include "nodo.hpp"



int main(void){
	arbolBin_t<int> arbol;
	arbol.insertar(23);
	arbol.insertar(100);
	arbol.insertar(10);
	arbol.insertar(5);
	arbol.eliminar(100);
	//std::cout << "Hola" << std::endl;
}
