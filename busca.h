/*
 * busca.h
 *
 *  Created on: Jun 2, 2013
 *      Author: emanuel
 */

#ifndef BUSCA_H_
#define BUSCA_H_

typedef struct{
	char pk[12];
}keys_founded_t;

int buscaRegistro(const char *key);
int compare_bsearch_busca_pk(const void *a, const void *b);
int compare_bsearch_busca_sk(const void *a, const void *b);

void buscaPorCpf(char *cpf);
int buscaPorCpfOR(char *key, int start, keys_founded_t **mykeys);
int buscaPorCpfAND(char *key, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and);
void buscaPorUniverdade(char *universidade);
void buscaPorModalidade(char *modalidade);
int buscaPorUniverdadeOR(char *universidade, int start, keys_founded_t **mykeys);
int buscaPorModalidadeOR(char *modalidade, int start, keys_founded_t **mykeys);
int buscaPorUniverdadeAND(char *universidade, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and);
int buscaPorModalidadeAND(char *modalidade, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and);

void exibeRegistro(int pos);

int buscaSecKeyAtIdxFile(char *key, char *filename);
int compare_founded_keys(const void *a, const void *b);


#endif /* BUSCA_H_ */
