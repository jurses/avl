#include "nodo.hpp"

template<>
nodo_t<matricula_t>::nodo_t(const char* cadena):
HI_(NULL),
HD_(NULL),
valor_(cadena)
{
}