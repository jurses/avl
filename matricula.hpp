#ifndef _MATRICULA_H_
#define _MATRICULA_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

class matricula_t{
	private:
		int nCompar_;
		std::string matr_cadena_; //3675BBM

	public:
		matricula_t();
		matricula_t(std::string);
		~matricula_t(){}
		void darMatricula(std::string);
		std::string obtCadena(void){ return matr_cadena_; }
		operator unsigned long();
		void operator =(const matricula_t&);
		void operator =(const std::string&);
		bool operator <(matricula_t&);
		bool operator >(matricula_t&);
		operator std::string();
		int obtCompar(void);
		void reset(void);
};

#endif	// _MATRICULA_H_