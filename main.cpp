#include <iostream>
#include <cstdlib>
#include "arbolBin.hpp"
#include "nodo.hpp"
#include <fstream>
#include "matricula.hpp"

template<class T>
class randVec{
	private:
		T* valor_;
		int tam_;
		bool esta_repetido(int);
	public:
		randVec(int);
		~randVec();
		T& operator[](int);
};

template<class T>
bool randVec<T>::esta_repetido(int i){
	for(int j=0; j<i; j++)
		if(valor_[i] == valor_[j]){
			return true;
		}

	return false;
}

template<class T>
randVec<T>::randVec(int tam):
tam_(tam)
{
	bool repetidos = false;
	valor_ = new T[tam_];

	for(int i=0; i<tam_; i++){
		valor_[i] = rand();
		while(esta_repetido(i))
			valor_[i] = rand();
	}
}

template<class T>
randVec<T>::~randVec(){
	if(valor_)
		delete[] valor_;
}

template<class T>
T& randVec<T>::operator[](int i){
	return valor_[i];
}

template<>
randVec<matricula_t>::randVec(int tam):
tam_(tam)
{
	bool repetidos = false;
	valor_ = new matricula_t[tam_];

	for(int i=0; i<tam_; i++)
		while(esta_repetido(i))
			valor_[i].matrAle();
}

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

int minimo(nodo_t<matricula_t>* nodo, int min){
	if(nodo->obtHI()){
		if(nodo->obtHI()->valor().obtCompar() < min)
			min = nodo->obtHI()->valor().obtCompar();
		minimo(nodo->obtHI(), min);
	}
	else if(nodo->obtHD()){
		if(nodo->obtHD()->valor().obtCompar() < min)
			min = nodo->obtHD()->valor().obtCompar();
		minimo(nodo->obtHD(), min);
	}

	return min;
}

int maximo(nodo_t<matricula_t>* nodo, int max){
	if(nodo->obtHI()){
		if(nodo->obtHI()->valor().obtCompar() > max)
			max = nodo->obtHI()->valor().obtCompar();
		maximo(nodo->obtHI(), max);
	}
	else if(nodo->obtHD()){
		if(nodo->obtHD()->valor().obtCompar() < max)
			max = nodo->obtHD()->valor().obtCompar();
		maximo(nodo->obtHD(), max);
	}

	return max;
}

int acumulativo(nodo_t<matricula_t>* nodo){
	if(nodo->obtHI()){
		acum += nodo->obtHI()->valor().obtCompar();
		acumulativo(nodo->obtHI());
	}
	else if(nodo->obtHD()){
		acum += nodo->obtHD()->valor().obtCompar();
		acumulativo(nodo->obtHD());
	}
	return acum;
}

void resetArbol(nodo_t<matricula_t>* nodo){
	nodo->valor().reset();
	if(nodo->obtHI())
		resetArbol(nodo->obtHI());

	else if(nodo->obtHD())
		resetArbol(nodo->obtHD());
}

void estadista(arbolBin_t<matricula_t>* arbol, int tam){
	randVec<matricula_t> paraI(2*tam);
	
	for(int i=0; i<tam; i++)
		arbol->insertar(paraI[i]);
	
	resetArbol(arbol->obtRaiz());

	for(int i=0; i<tam; i++)
		arbol->buscar(paraI[i]);

	int min = minimo(arbol->obtRaiz(), arbol->obtRaiz()->valor().obtCompar());
	int max = maximo(arbol->obtRaiz(), arbol->obtRaiz()->valor().obtCompar());
	int acum = acumulativo(arbol->obtRaiz());

	std::cout << "Inserción N = " << tam  << std::endl;
	std::cout << "Min\tMax\tAcum" << std::endl;
	std::cout << min << '\t' << max << '\t' << acum/tam << std::endl;
	std::cout << std::endl;

	resetArbol(arbol->obtRaiz());

	for(int i=tam; i<2*tam; i++)
		arbol->buscar(paraI[i]);

	min = minimo(arbol->obtRaiz(), arbol->obtRaiz()->valor().obtCompar());
	max = maximo(arbol->obtRaiz(), arbol->obtRaiz()->valor().obtCompar());
	acum = acumulativo(arbol->obtRaiz());

	std::cout << "Búsqueda N = " << tam << std::endl;
	std::cout << "Min\tMax\tAcum" << std::endl;
	std::cout << min << '\t' << max << '\t' << acum << std::endl;
	std::cout << std::endl;
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
					std::cout << std::endl;
					arbol->mostrar(std::cout);
					break;
			case 2:	std::cout << "4 números y 3 letras" << std::endl;
					std::cout << "Eliminar: ";
					std::cin >> cad_matr;
					arbol->eliminar(cad_matr);
					std::cout << std::endl;
					arbol->mostrar(std::cout);
					break;
			default:	std::cout << "Mala opción" << std::endl;
		}
	}
}

template<>
void demostracion(arbolBin_t<int>* arbol){
	bool salida = false;
	int opcion = -1;
	int valor;
	while(!salida){
		std::cout << "0: Salir\n" << "1: Insertar\n" << "2: Eliminar\n" << std::endl;
		std::cin >> opcion;
		switch(opcion){
			case 0:	salida = true;
					break;
			case 1:	std::cout << "Insertar: ";
					std::cin >> valor;
					arbol->insertar(valor);
					std::cout << std::endl;
					arbol->mostrar(std::cout);
					break;
			case 2:	std::cout << "Eliminar: ";
					std::cin >> valor;
					arbol->eliminar(valor);
					std::cout << std::endl;
					arbol->mostrar(std::cout);
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
				case 'd':	demostracion(&arbol); // arbolmtr
							break;

				case 'e':	if(argv[2]){
								int tam = atoi(argv[2]);
								estadista(&arbolmtr, tam);
							}
							break;
			}
		}else
			std::cout << "Mal comando: " << argv[1] << std::endl;
	}
	return argc;
}
