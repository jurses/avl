#include <iostream>
#include "arbolBin.hpp"
#include "nodo.hpp"

int main(void){
	arbolBin_t<int> arbol;
	arbol.insertar(8);
	arbol.eliminar(8);
	arbol.insertar(14);
	//arbol.insertar(38);
	//arbol.insertar(23);
}