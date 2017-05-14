#include "arbolBin.hpp"

template<>
void arbolBin_t<matricula_t>::insertar(const char* matr){
	nodo_t<matricula_t>* nodo = new nodo_t<matricula_t>(matr);
	//nodo->valor() = valor;
	bool crece = false;
	insertar(raiz_, nodo, crece);
}

template<>
void arbolBin_t<matricula_t>::eliminar(const char* matr){
	bool decrece = false;
	matricula_t aux(matr);
	eliminar(raiz_, aux, decrece);
}