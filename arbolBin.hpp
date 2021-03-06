#ifndef _ARBOL_B_
#define _ARBOL_B_

#include <queue>
#include <ostream>
#include <vector>
#include "nodo.hpp"
#include "matricula.hpp"

#ifndef NULL
#define NULL 0x0
#endif	// NULL

#define IZQ 1
#define DER 0

template<class T>
class arbolBin_t{
	private:
		std::queue<nodo_t<T>* > colaBFS;
		std::queue<int> niveles;
		nodo_t<T>* raiz_;
		void insertar(nodo_t<T>*&, nodo_t<T>*&, bool&);
		void eliminar(nodo_t<T>*&, T, bool&);
		void eliminar_re_bal_I(nodo_t<T>*&, bool&);
		void eliminar_re_bal_D(nodo_t<T>*&, bool&);
		nodo_t<T>* buscar(nodo_t<T>*, T);
		void borrar(nodo_t<T>*);
		nodo_t<T>* obtMayor(nodo_t<T>*);
		nodo_t<T>* obtMenor(nodo_t<T>*);
		void sustituye(nodo_t<T>*&, nodo_t<T>*&, bool&);
		const bool balanceado(nodo_t<T>*);
		void rotacion_II(nodo_t<T>*&);
		void rotacion_ID(nodo_t<T>*&);
		void rotacion_DI(nodo_t<T>*&);
		void rotacion_DD(nodo_t<T>*&);
		void insertar_re_bal_I(nodo_t<T>*&, bool&);
		void insertar_re_bal_D(nodo_t<T>*&, bool&);
	
	public:
		arbolBin_t();
		~arbolBin_t();

		void eliminar(T);
		void eliminar(const char*);
		void insertar(T);
		void insertar(const char*);
		void insertar(void);
		const bool balanceado(void);
		nodo_t<T>* buscar(T);
		nodo_t<T>* obtRaiz(void){ return raiz_; }
		std::ostream& mostrar(std::ostream&);
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
	
	raiz_ = NULL;
}

template<class T>
void arbolBin_t<T>::insertar(const char*){
	std::cout << "¿Árbol binario con cadenas?, no es muy buena idea, ¿no?" << std::endl;
}

template<class T>
void arbolBin_t<T>::insertar(void){
}

template<class T>
void arbolBin_t<T>::insertar(T valor){
	nodo_t<T>* nodo = new nodo_t<T>;
	nodo->valor() = valor;
	bool crece = false;
	insertar(raiz_, nodo, crece);
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
void arbolBin_t<T>::insertar(nodo_t<T>* &nodo, nodo_t<T>* &nuevo, bool& crece){
	if(!nodo){
		nodo = nuevo;
		crece = true;
	}
	else if(nuevo->valor() < nodo->valor()){
		insertar(nodo->obtHI(), nuevo, crece);
		if(crece)
			insertar_re_bal_I(nodo, crece);
	}
	else{
		insertar(nodo->obtHD(), nuevo, crece);
		if(crece)
			insertar_re_bal_D(nodo, crece);
	}
}

template<class T>
void arbolBin_t<T>::insertar_re_bal_I(nodo_t<T>* &nodo, bool& crece){
	switch(nodo->balance()){
		case -1:	nodo->balance() = 0;
					crece = false;
					break;

		case 0:		nodo->balance() = 1;
					break;

		case 1:		nodo_t<T>* nodo1 = nodo->obtHI();
					if(nodo1->balance() == 1)
						rotacion_II(nodo);
					else
						rotacion_ID(nodo);
					crece = false;
	}
}

template<class T>
void arbolBin_t<T>::insertar_re_bal_D(nodo_t<T>* &nodo, bool& crece){ //al parecer funciona
	switch(nodo->balance()){
		case 1:	nodo->balance() = 0;
					crece = false;
					break;

		case 0:		nodo->balance() = -1;
					break;

		case -1:	nodo_t<T>* nodo1 = nodo->obtHD();
					if(nodo1->balance() == -1)
						rotacion_DD(nodo);
					else
						rotacion_DI(nodo);
					crece = false;
	}
}

template<class T>
void arbolBin_t<T>::eliminar(T valor){
	bool decrece = false;
	eliminar(raiz_, valor, decrece);
}

template<class T>
void arbolBin_t<T>::eliminar(const char*){
	std::cout << "¿Árbol binario con cadenas?, no es muy buena idea, ¿no?" << std::endl;
}

template<class T>
void arbolBin_t<T>::eliminar(nodo_t<T>* &nodo, T valor, bool& decrece){
	if(!nodo)
		return;
	if(valor < nodo->valor()){
		eliminar(nodo->obtHI(), valor, decrece);
		if(decrece)
			eliminar_re_bal_I(nodo, decrece);
	}
	else if(valor > nodo->valor()){
		eliminar(nodo->obtHD(), valor,decrece);
		if(decrece)
			eliminar_re_bal_D(nodo, decrece);
	}
	else{
		nodo_t<T>* eliminado = nodo;
		if(!nodo->obtHI()){
			nodo = nodo->obtHD();
			decrece = true;
		}
		else if(!nodo->obtHD()){
			nodo = nodo->obtHI();
			decrece = true;
		}
		else{
			sustituye(eliminado, nodo->obtHI(), decrece);
			if(decrece)
				eliminar_re_bal_I(nodo, decrece);
		}
		delete eliminado;
	}
}

template<class T>
void arbolBin_t<T>::sustituye(nodo_t<T>* &eliminado, nodo_t<T>* &sust, bool &decrece){
	if(sust->obtHD()){
		sustituye(eliminado, sust->obtHD(), decrece);
		if(decrece)
			eliminar_re_bal_D(sust, decrece);
	}
	else{
		eliminado->valor() = sust->valor();
		eliminado = sust;	// Cuidado con esto.
		sust = sust->obtHI();
		decrece = true;
	}
}

template<class T>
void arbolBin_t<T>::eliminar_re_bal_I(nodo_t<T>* &nodo, bool& decrece){
	nodo_t<T>* nodo1 = nodo->obtHD();
	switch(nodo->balance()){
		case -1:	if(nodo1->balance() > 0)
						rotacion_DI(nodo);
					else{
						if(nodo1->balance() == 0)
							decrece = false;
						rotacion_DD(nodo);
					}
					break;
		case 0:		nodo->balance() = -1;
					decrece = false;
					break;
		case 1:		nodo->balance() = 0;
	}
}

template<class T>
void arbolBin_t<T>::eliminar_re_bal_D(nodo_t<T>* &nodo, bool& crece){
	nodo_t<T>* nodo1 = nodo->obtHI();
	switch(nodo->balance()){
		case 1:		if(nodo1->balance() < 0)
						rotacion_ID(nodo);
					else{
						if(nodo1->balance() == 0)
							crece = false;
						rotacion_II(nodo);
					}
					break;
		case 0:		nodo->balance() = 1;
					crece = false;
					break;
		case -1:	nodo->balance() = 0;
	}
}

template<class T>
void arbolBin_t<T>::borrar(nodo_t<T>* nodo){
	if(nodo->obtHI()){
		borrar(nodo->obtHI());
		nodo->ponHI(NULL);
	}
	
	if (nodo->obtHD()){
		borrar(nodo->obtHD());
		nodo->ponHD(NULL);
	}

	delete nodo;
	nodo = NULL;
}

template<class T>
const bool arbolBin_t<T>::balanceado(void){
	return balanceado(raiz_);
}

template<class T>
const bool arbolBin_t<T>::balanceado(nodo_t<T>* nodo){
	if(!nodo)
		return true;
	int balance = altura(nodo->obtHI()) - altura(nodo->obtHD());
	switch(balance){
		case -1:
		case 0:
		case 1 :
			return balance(nodo->obtHI()) && balance(nodo->obtHD());
		default: return false;
	}
}

template<class T>
void arbolBin_t<T>::rotacion_II(nodo_t<T>* &nodo){	// al parecer bien
	nodo_t<T>* nodo1 = nodo->obtHI();
	nodo->ponHI(nodo1->obtHD());
	nodo1->ponHD(nodo);

	if(nodo1->balance() == 1){
		nodo->balance() = 0;
		nodo1->balance() = 0;
	}
	else{
		nodo->balance() = 1;
		nodo1->balance() = -1;
	}
	nodo = nodo1;
}

template<class T>
void arbolBin_t<T>::rotacion_DD(nodo_t<T>* &nodo){ //funciona
	nodo_t<T>* nodo1 = nodo->obtHD();
	nodo->ponHD(nodo1->obtHI());
	nodo1->ponHI(nodo);

	if(nodo1->balance() == -1){
		nodo->balance() = 0;
		nodo1->balance() = 0;
	}
	else{
		nodo->balance() = -1;
		nodo1->balance() = 1;
	}
	nodo = nodo1;
}

template<class T>
void arbolBin_t<T>::rotacion_ID(nodo_t<T>* &nodo){
	nodo_t<T>* nodo1 = nodo->obtHI();
	nodo_t<T>* nodo2 = nodo1->obtHD();

	nodo->ponHI(nodo2->obtHD());
	nodo2->ponHD(nodo); // arreglado
	nodo1->ponHD(nodo2->obtHI());
	nodo2->ponHI(nodo1);

	if(nodo2->balance() == -1)
		nodo1->balance() = 1;
	else
		nodo1->balance() = 0;
	
	if(nodo2->balance() == 1)
		nodo->balance() = -1;
	else
		nodo->balance() = 0;
	
	nodo2->balance() = 0;
	nodo = nodo2;
}

template<class T>
void arbolBin_t<T>::rotacion_DI(nodo_t<T>* &nodo){
	nodo_t<T>* nodo1 = nodo->obtHD();
	nodo_t<T>* nodo2 = nodo1->obtHI();

	nodo->ponHD(nodo2->obtHI());
	nodo2->ponHI(nodo);
	nodo1->ponHI(nodo2->obtHD());
	nodo2->ponHD(nodo1);

	if(nodo2->balance() == 1)
		nodo1->balance() = -1;
	else
		nodo1->balance() = 0;
	
	if(nodo2->balance() == -1)
		nodo->balance() = 1;
	else
		nodo->balance() = 0;
	
	nodo2->balance() = 0;
	nodo = nodo2;
}

template<class T>
std::ostream& arbolBin_t<T>::mostrar(std::ostream& os){ // mala representación por niveles
	nodo_t<T>* nodo;
	int nivel, nivel_actual = 0;
	if(raiz_){
		colaBFS.push(raiz_);
		niveles.push(0);
		os << std::endl << "Nivel 0:" << std::endl;
	}

	while(!colaBFS.empty()){
		nodo = colaBFS.front();
		nivel = niveles.front();

		colaBFS.pop();
		niveles.pop();

		if(nivel > nivel_actual){
		    nivel_actual = nivel;
		    os << std::endl << "Nivel: " << nivel_actual << std::endl;
		}
		
		if(nodo){
		    os << " " << nodo->valor();
		    colaBFS.push(nodo->obtHI());
		    niveles.push(nivel + 1);
		    colaBFS.push(nodo->obtHD());
		    niveles.push(nivel + 1);
		}
		else
		    os << "(.)";
	}
	os << std::endl;
}

template<class T>
nodo_t<T>* arbolBin_t<T>::buscar(T valor){
	if(raiz_)
		return buscar(raiz_, valor);
}

template<class T>
nodo_t<T>* arbolBin_t<T>::buscar(nodo_t<T>* nodo, T valor){
	if(nodo->valor() > valor){
		if(nodo->obtHI())
			buscar(nodo->obtHI(), valor);
	}else if(nodo->valor() < valor){
		if(nodo->obtHD())
			buscar(nodo->obtHD(), valor);
	}else if(nodo->valor() == valor)
		return nodo;
}

#endif	// _ARBOL_B_
