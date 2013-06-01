#ifndef INDICEPRIMARIO_H
#define INDICEPRIMARIO_H

	#include<stdio.h>
	#include<stdlib.h>
#include <string.h>


typedef struct {
	char cpf[12];
	int offset;
}prim_idx_t;

	void inserirIndicePrimario(char *pk, int pos);
	int buscaChavePrimaria(char *pk, FILE *fp);
	int compare_qsort(const void *a, const void *b);
	int compare_bsearch(const void *a, const void *b);
	int verificaSeExisteChavePrimaria(char *cpf);

	void atualizaArquivoChavePrimaria(prim_idx_t *vector, int length);


#endif
