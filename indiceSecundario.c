#include "indiceSecundario.h"

void inserirIndiceSecundario(const char *filename, char *sk, char *pk){
	FILE *fp = fopen(filename, "r+");
	if(fp == NULL)
		fp = fopen(filename, "w+");
	
	//busca binaria
	//ISSO NAO EH UMA BUSCAR BINARIA!!! ACREDITE!!!
	int achou = 0;
	fseek(fp, 0, SEEK_SET);	
	char skAux[31];
	int posAux;
	while(fscanf(fp, "%s %d",skAux, &posAux) != EOF){
		if(strcmp(skAux, sk) == 0){
			achou = 1;
			break;
		}
	}
	
	//RTPermanente
	char filename2[50];
	if(strcmp(filename, "universidade.idx") == 0){
		sprintf(filename2,"universidadeListaInvertida.idx");
	}else if(strcmp(filename, "modalidade.idx") == 0){
		sprintf(filename2,"modalidadeListaInvertida.idx");
	}

	//------
	if(achou){				
		//Garantido pelo Andre
		int pos = inserirListaInvertida(filename2, pk, posAux); 
		fseek(fp,-11*sizeof(char),SEEK_CUR);
		fprintf(fp,"%11d", pos);

	}else{
		int pos = inserirListaInvertida(filename2, pk, -1); 
		fprintf(fp,"%s %11d\n", sk, pos);
		//Ordenar
		// qsort
	}
	
	fclose(fp);
}
