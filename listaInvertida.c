#include "listaInvertida.h"

int inserirListaInvertida(char *filename, char *pk, int pos){
	int size = 0;
	FILE *fp = fopen(filename, "a+");

	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	
	//Num ordena nao!!!
	fprintf(fp,"%s %d\n",pk,pos);

	fclose(fp);
	return size;
}
