#include <stdio.h>

int main(void){
	FILE *x;
	x = fopen("lata.txt", "r");
	fscanf(x, "%d", palabra);
	printf("%s\n", palabra);
	fclose(x);
}