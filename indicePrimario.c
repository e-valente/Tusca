#include"indicePrimario.h"

void inserirIndicePrimario(char *pk, int pos){

	FILE *fp = fopen("prim.idx", "r+");
	if(fp == NULL) fp = fopen("prim.idx", "w+");

	// ordenar !!!
	// man qsort
	fprintf(fp,"%-11s %d\n",pk,pos);

	fclose(fp);
}
