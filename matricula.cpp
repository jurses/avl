#include "matricula.hpp"
#define MCAR 65

matricula_t::matricula_t(std::string matr_cadena):
	matr_cadena_(matr_cadena)
{
	nCompar_ = 0;
}

matricula_t::matricula_t(){
	nCompar_ = 0;
	matr_cadena_.resize(7);
	for(int i=0; i<4; i++)
		matr_cadena_[i] = rand()%10 + '0';

	for(int i=4; i<7; i++)
		matr_cadena_[i] = rand()%26 + MCAR;
}

matricula_t::operator unsigned long(){
	unsigned long suma = 0;

	for(int i = 4; i < 7; i++)
		suma += (matr_cadena_[i]-MCAR) * pow(10, i);

	return(atoi(matr_cadena_.substr(0,4).c_str()) + suma);
}

matricula_t::operator std::string(){
	return matr_cadena_;
}

void matricula_t::darMatricula(std::string matr_cadena){
	matr_cadena_ = matr_cadena;
}

void matricula_t::operator=(const matricula_t& otra_matricula){
	nCompar_ = otra_matricula.nCompar_;
	matr_cadena_ = otra_matricula.matr_cadena_;
}

void matricula_t::operator=(const std::string& cadena){
	matr_cadena_ = cadena;
}

bool matricula_t::operator<(matricula_t& otra_matricula){
	nCompar_++;
	otra_matricula.nCompar_++;
	return (*this) < static_cast<unsigned long>(otra_matricula);
}

bool matricula_t::operator>(matricula_t& otra_matricula){
	nCompar_++;
	otra_matricula.nCompar_++;
	return (*this) > static_cast<unsigned long>(otra_matricula);
}

int matricula_t::obtCompar(void){
	return nCompar_;
}

void matricula_t::reset(void){
	nCompar_ = 0;
}

void matricula_t::swap(matricula_t& matricula){
	int aux = matricula.nCompar_;
	matricula.nCompar_ = nCompar_;
	nCompar_ = aux;
}
