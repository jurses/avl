#ifndef _NODO_H_
#define _NODO_H_

#include <iostream>

#ifndef NULL
#define NULL 0x0
#endif	// NULL

template<class T>
class nodo_t{
	private:
		nodo_t<T>* HI_;
		nodo_t<T>* HD_;
		T valor_;

	public:
		nodo_t();
		~nodo_t();

		nodo_t<T>* obtHI();
		nodo_t<T>* obtHD();
		void ponHI(nodo_t<T>*);
		void ponHD(nodo_t<T>*);
		T& valor(void);
};

template<class T>
nodo_t<T>::nodo_t():
HI_(NULL),
HD_(NULL)
{
	std::cout << "Creo: " << valor_ << std::endl;
}

template<class T>
nodo_t<T>::~nodo_t(){
	std::cout << "Borro: " << valor_ << std::endl;
}

template<class T>
T& nodo_t<T>::valor(void){
	return valor_;
}

template<class T>
nodo_t<T>* nodo_t<T>::obtHI(void){
	return HI_;
}

template<class T>
nodo_t<T>* nodo_t<T>::obtHD(void){
	return HD_;
}

template<class T>
void nodo_t<T>::ponHI(nodo_t<T>* nodo){
	HI_ = nodo;
}

template<class T>
void nodo_t<T>::ponHD(nodo_t<T>* nodo){
	HD_ = nodo;
}

#endif	// _NODO_H_
