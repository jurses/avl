#include <iostream>

int suma10(int*&);

int suma10(int* &n){	// You would want to pass a pointer by reference
						// if you have a need to modify the pointer rather
						// than the object that the pointer is pointing to.
	std::cout << n << std::endl;
	return *n+10;
}

int main(void){
	int *a;
	a = new int(4);
	std::cout << a << std::endl;
	suma10(a);
	std::cout << *a << "\t" << suma10(a) << std::endl;
	delete a;
	a = 0x0;
}