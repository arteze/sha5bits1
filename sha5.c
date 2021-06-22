// Código creado por Emiliano Ezequiel Parenti
// Se compila así:
// gcc ./sha5.c -o ./sha5
// Dar permisos de ejecución
// chmod +x ./sha5

// /initrd/mnt/dev_save/Lsave-n/root/documentos/programar/c/sha256-master/sha256-master
// ./sha5
// Ruta: ./sha5
// Argumentos: 1
// Ruta del programa: ./sha5
// Hash: 0000000000000000000000000000000000000000000000000000000000000000
// 2 elevado a la: 37
// Menor que tantos bits positivos: 77
// Microsegundos de espera para menor uso de CPU: 101234
// ./sha5 0000000000000000000000000000000000000000000000000000000000000000 37 77 101234


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sha256.c" // Uso de https://github.com/CurieBSP/sha256

int longitud(char* cad){
	int i=0;
	for(;cad[i]!=0;++i){;}
	return i;
}
long string_a_int(char* cad){
	long s=0;
	for(short i=0;cad[i]!=0;++i){
		s = s*10+(cad[i]-'0');
	}
	return s;
}
short contarbits(unsigned char* hash,int suma){
	int conta = 0;
	unsigned char h = 0;
	for(int i=0;i<32;++i){
		h = hash[i];
		while(h!=0){
			conta+=h%2;
			h/=2;
		}
		if(suma>256){
			printf("\t%c %02x |",hash[i],conta);
		}
		if(conta>(suma%256) && suma<256){conta+=256;break;}
	}
	if(suma>256){
		printf("\n%i\n",conta);
	}
	return conta;
}
unsigned char hex_a_entero(unsigned char hex){
	return hex>='0' && hex<='9' ? hex-'0':
		    hex>='a' && hex<='f' ? hex+10-'a':
									16;
}
unsigned char* hex_a_bin(char* cad){
	short i = 0;
	for(;cad[i]!=0;++i){;}
	unsigned char* bin = malloc(i/2+1);
	unsigned char j=0;
	unsigned char k=0;
	unsigned char p=32;
	printf("Longitud: %i\n",i);
	--i;
	for(j=0;j<i;++j){
		unsigned char c = hex_a_entero(cad[2*j]);
		unsigned char d = hex_a_entero(cad[2*j+1]);
		unsigned char s = (c==16?0:16*c)+(d==16?0:d);
		if(c==16||d==16){
			break;
		}
		bin[j] = s;
		if(j%p==0 && k!=0){printf("\n");}
		printf(" %02x",s);
	}
	printf("\n");
	for(;k<j;++k){
		if(k%p==0 && k!=0){printf("\n");}
		printf(" %02x",k);
	}
	bin[j] = 0;
	printf("\n");
	printf("Binario: %s\n",bin);
	return bin;
}
long pot(int base,int exponente){
	long total = 1;
	for(int i=0;i<exponente;++i){
		total*=base;
	}
	return total;
}

void bin_a_hex(unsigned char* data) {
    for(short i=0;data[i]!=0;++i){
		printf("%02x",data[i]);
	}
}
void bin_a_hexl(unsigned char* data,unsigned char longi) {
    for(short i=0;i<longi;++i){
		printf("%02x",data[i]);
	}
}
void bin_a_hexn(unsigned char* data) {
    bin_a_hex(data);
	printf("\n");
}
void bin_a_hexnl(unsigned char* data,unsigned char longi) {
    bin_a_hexl(data,longi);
	printf("\n");
}
void copiar(unsigned char* a,unsigned char* b,unsigned char longi) {
    for(short i=0;i<longi+1;++i){
		b[i] = a[i];
	}
}

int main(int argc, char *argv[]){
	int argd = argc-1;
	char* ruta = argv[0];
	unsigned char* a1 = argd>=1? hex_a_bin(argv[1])           :0;
	long total         = argd>=2? pot(2,string_a_int(argv[2])) :0;
	long suma          = argd>=3? string_a_int(argv[3])        :0;
	int espera         = argd>=4? string_a_int(argv[4])        :0;

	printf("Ruta: %s\n",ruta);
	printf("Argumentos: %i\n",argc);

	if(argd==0){
		char* hash_nulo = "0000000000000000000000000000000000000000000000000000000000000000";
		int potencia = 37;
		int bits_ejemplo = 77;
		int microsegundos = 101234;

		printf("Ruta del programa: %s\n",ruta);
		printf("Hash: %s\n",hash_nulo);
		printf("2 elevado a la: %i\n",potencia);
		printf("Menor que tantos bits positivos: %i\n",bits_ejemplo);
		printf("Microsegundos de espera para menor uso de CPU: %i\n",microsegundos);
		printf(
			"%s %s %i %i %i\n",
			ruta,         // Ruta del programa
			hash_nulo,    // Hash
			potencia,     // Potencia: 2^29
			bits_ejemplo, // Menor que tantos bits positivos
			microsegundos // Microsegundos de espera para menor uso de CPU
		);
		return 0;
	}
	if(argd==1){
		contarbits(a1,256+256);
		return 0;
	}
	unsigned char *d = a1;
	unsigned char m[SHA256_DIGEST_LENGTH];
	size_t n = longitud(d);
	short bits = 0;
	float porcentaje = 0;

	printf("Longitud: %i\n",n);
	copiar(a1,m,n);
	for(long i=0;i<total;++i){
		sha256(m,n,m);
		bits = contarbits(m,suma);
		porcentaje = (float)100*i/total;
		if(i%10000==0){
			printf("\r");
			printf(" %i %f ",bits,porcentaje);
			bin_a_hexl(m,32);
			fflush(stdout);
			if(espera>0){
				usleep(espera);
			}
		}
		if(bits<256){
			printf("\r");
			printf(" %i %f ",bits,porcentaje);
			bin_a_hexl(m,32);
			printf("\n");
			fflush(stdout);
		}
	}
	printf("\n");
    return 0;
}
