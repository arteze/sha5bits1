// Longitudes a partir de strings

#include <stdio.h>
#include <stdlib.h>

char* sumar_uno(char* s, unsigned short longitud_maxima){
	char* t = &s[longitud_maxima-1];
	++*t;
	++t;
	while(*--t>'9'){
		*t -= 10;
		++*(t-1);
	}
	return s;
}
unsigned char* longitud(char* cadena, unsigned short longitud_maxima){
	char* s = malloc(longitud_maxima+1);
	unsigned short i=0;
	for(;i<longitud_maxima;++i){
		s[i] = '0';
	}
	s[i] = 0;
	while(*cadena++!=0){
		sumar_uno(s,longitud_maxima);
	}
	return s;
}
unsigned short string_a_unsignedshort(char* cadena){
	unsigned short i=0;
	--cadena;
	while(*++cadena!=0){
		i*=10;
		i+=*cadena-'0';
	}
	return i;
}

int main(int a, char *b[]){
	int c = a-1; // Cantidad de argumentos pero sin la ruta
	char* ruta = b[0]; // Argumento cero: Ruta
	b = &b[1];
	unsigned char* a0;
	unsigned char* a1;

	unsigned char* longi;
	unsigned short longishort = 0;
	unsigned short longitud_maxima = 6;
	if(c==0){
		printf("0: Cadena");
	}
	if(c>=1){
		a0 = b[0]; // arg 0: Cadena
	}
	if(c>=2){
		a1 = b[1]; // arg 1: Longitud máxima
		longitud_maxima = string_a_unsignedshort(a1);
		longi = malloc(longitud_maxima+1);
	}
	if(c>=1){
		longi = longitud(a0,longitud_maxima);
		longishort = string_a_unsignedshort(longi);
		printf("%i ",longishort);
		printf("%i ",longitud_maxima);
	}
	printf("\n");
    return 0;
}
