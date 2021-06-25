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
unsigned char* string_longitud(char* cadena, unsigned short longitud_maxima){
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
unsigned short string_a_ushort(unsigned char* cadena){
	unsigned short i=0;
	--cadena;
	while(*++cadena!=0){
		i*=10;
		i+=*cadena-'0';
	}
	return i;
}
unsigned short ushort_longitud(unsigned char* cadena, unsigned short longitud_maxima){
	unsigned char* string_longi = malloc(longitud_maxima+1);
	unsigned short ushort_longi = 0;
	string_longi = string_longitud(cadena,longitud_maxima);
	ushort_longi = string_a_ushort(string_longi);
	return ushort_longi;
}
int main(int a, char *b[]){
	int c = a-1; // Cantidad de argumentos pero sin la ruta
	char* ruta = b[0]; // Argumento cero: Ruta
	char** d = &b[1];

	unsigned char* a0;
	unsigned char* a1;

	unsigned short longishort = 0;
	unsigned short longitud_maxima = 6;
	if(c==0){
		printf("0: Cadena");
	}
	if(c>=1){
		a0 = d[0]; // arg 0: Cadena
	}
	if(c>=2){
		a1 = d[1]; // arg 1: Longitud máxima
		longitud_maxima = string_a_ushort(a1);
	}
	if(c>=1){
		longishort = ushort_longitud(a0,longitud_maxima);
		printf("Longitud: %i\n",longishort);
		printf("Longitud maxima: %i\n",longitud_maxima);
	}
    return 0;
}
