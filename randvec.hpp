#include <ctime>
#include <cstdlib>
#include "matricula.hpp"
#pragma once
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
	for(int j=0; j<tam_; j++)
		if(valor_[i] == valor_[j])
			return true;

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
