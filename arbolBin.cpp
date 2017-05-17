#include "arbolBin.hpp"

template<>
void arbolBin_t<matricula_t>::insertar(const char* matr){
	nodo_t<matricula_t>* nodo = new nodo_t<matricula_t>(matr);
	bool crece = false;
	insertar(raiz_, nodo, crece);
}

template<>
void arbolBin_t<matricula_t>::insertar(void){
	nodo_t<matricula_t>* nodo = new nodo_t<matricula_t>();
	bool crece = false;
	insertar(raiz_, nodo, crece);
}

template<>
void arbolBin_t<matricula_t>::eliminar(const char* matr){
	bool decrece = false;
	matricula_t aux(matr);
	eliminar(raiz_, aux, decrece);
}

template<>
void arbolBin_t<matricula_t>::sustituye(nodo_t<matricula_t>* &eliminado, nodo_t<matricula_t>* &sust, bool &decrece){
	if(sust->obtHD()){
		sustituye(eliminado, sust->obtHD(), decrece);
		if(decrece)
			eliminar_re_bal_D(sust, decrece);
	}
	else{
		eliminado->valor() = sust->valor();
		sust = sust->obtHI();
		decrece = true;
	}
}
