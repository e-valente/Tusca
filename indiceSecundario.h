#ifndef INDICESECUNDARIO_H
#define INDICESECUNDARIO_H

	#include<stdio.h>
	#include<stdlib.h>

typedef struct {
	char sk[50];
	int pos;
}sec_key_idx_t;

void inserirIndiceSecundario(const char *filename, char *sk, char *pk);
void ordenaIdxSecKeyFile(const char *filename);
int seckey_compare_qsort(const void *a, const void *b);
void atualizaArquivoChaveSecundaria(sec_key_idx_t *vector, int length, const char *filename);


#endif
