#ifndef _ARBOL_B_
#define _ARBOL_B_

#include <queue>
#include "nodo.hpp"

#ifndef NULL
#define NULL 0x0
#endif	// NULL

#define IZQ 1
#define DER 0


template<class T>
class arbolBin_t{
	private:
		nodo_t<T>* raiz_;
		void insertar(nodo_t<T>*, nodo_t<T>*);
		void eliminar(T, nodo_t<T>*);
		void borrar(nodo_t<T>*);
		nodo_t<T>* obtMayor(nodo_t<T>*);
		nodo_t<T>* obtMenor(nodo_t<T>*);
	
	public:
		arbolBin_t();
		~arbolBin_t();

		void eliminar(T);
		void insertar(T);
};

template<class T>
arbolBin_t<T>::arbolBin_t():
raiz_(NULL)
{
}

template<class T>
arbolBin_t<T>::~arbolBin_t(){
	if(raiz_)
		borrar(raiz_);
}

template<class T>
void arbolBin_t<T>::insertar(T valor){
	nodo_t<T>* nodo = new nodo_t<T>;
	nodo->valor() = valor;
	if(raiz_)
		insertar(nodo, raiz_);
	else
		raiz_ = nodo;
}

template<class T>
nodo_t<T>* arbolBin_t<T>::obtMenor(nodo_t<T>* nodo){
	if(nodo->obtHI())
		return obtMenor(nodo->obtHI());
	else
		return nodo;
}

template<class T>
nodo_t<T>* arbolBin_t<T>::obtMayor(nodo_t<T>* nodo){
	if(nodo->obtHD())
		return obtMayor(nodo->obtHD());
	else
		return nodo;
}

template<class T>
void arbolBin_t<T>::insertar(nodo_t<T>* nuevoNodo, nodo_t<T>* nodo){
	if(nuevoNodo->valor() < nodo->valor())
		if(nodo->obtHI())
			insertar(nuevoNodo, nodo->obtHI());
		else
			nodo->ponHI(nuevoNodo);

	else if(nuevoNodo->valor() > nodo->valor())
		if(nodo->obtHD())
			insertar(nuevoNodo, nodo->obtHD());
		else
			nodo->ponHD(nuevoNodo);
}

template<class T>
void arbolBin_t<T>::eliminar(T valor){
	eliminar(valor, raiz_);
}

template<class T>
void arbolBin_t<T>::eliminar(T valor, nodo_t<T>* nodo){
	static bool lado;
	/*
		(1) Buscando:
		busca el valor a eliminar
	*/
	if(valor < nodo->valor() && nodo->obtHI()){
		eliminar(valor, nodo->obtHI());
		lado = IZQ;
	}
	else if(valor > nodo->valor() && nodo->obtHD()){
		eliminar(valor, nodo->obtHD());
		lado = DER;
	}
	else if(valor == nodo->valor()){	// comparación obvia, necesaria cuando se borra un elemento no existente
	/*
		(2) Actuando:
		ya se sabe qué valor a eliminar
	*/
		if(!(nodo->obtHI() || nodo->obtHD())){	// si no tiene ningún hijo...
			delete nodo;
			nodo = NULL;
		}
		else if(nodo->obtHD() && !nodo->obtHD()){	// si tiene solo un hijo por la izquierda...
			nodo_t<T>* aux = nodo->obtHI();
			delete nodo;
			nodo = aux;
		}
		else if(nodo->obtHD() && !nodo->obtHD()){	// si tiene solo un hijo por la derecha...
			nodo_t<T>* aux = nodo->obtHD();
			delete nodo;
			nodo = aux;
		}
		else{	// tiene los dos hijos, lo sustituirá el mayor
			nodo_t<T>* aux = obtMayor(nodo->obtHI());
			T valorAux = aux->valor();
			eliminar(aux->valor());
			nodo->valor() = valorAux;
		}
	}
}

template<class T>
void arbolBin_t<T>::borrar(nodo_t<T>* nodo){
	if(nodo->obtHI())
		borrar(nodo->obtHI());
	
	if (nodo->obtHD())
		borrar(nodo->obtHD());

	delete nodo;
	nodo = NULL;
}

#endif	// _ARBOL_B_
