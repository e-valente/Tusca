#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"indicePrimario.h"

void inserirIndicePrimario(char *pk, int pos){

	FILE *fp = fopen("prim.idx", "a+");
	prim_idx_t *my_vect_prim_idx, *res;
	int count;
	char cpf[12];
	int offset;
	int i, nbytes;
	int size_file;

	if(fp == NULL) {
		printf("erro como somente leitura\n crindo idx\n");
		fp = fopen("prim.idx", "w+");

	}

	//busca binaria pra ver se chave existe


	fseek(fp, 0L, SEEK_END);
	size_file = ftell(fp);


	if (size_file == 0 )
	{
		fprintf(fp,"%-11s %d\n", pk, pos);
		fclose(fp);
		return;
	}

	my_vect_prim_idx = NULL;

	count = 0;

	fseek(fp, 0L, SEEK_SET);

	while(!feof(fp))
	{
		if(!feof(fp)){
			my_vect_prim_idx = (prim_idx_t*)realloc(my_vect_prim_idx, (sizeof(prim_idx_t) * (count + 1)));
			nbytes = fscanf(fp, "%s %d", cpf, &offset);

			//printf("bytes lidos : %d\n", nbytes);
			if(nbytes > 0) {
				strcpy(my_vect_prim_idx[count].cpf, cpf);
				my_vect_prim_idx[count].offset = offset;
				//printf("gravei no vetor idx: %s %d bytes lidos %d\n",my_vect_prim_idx[count].cpf, my_vect_prim_idx[count].offset, nbytes);
				count++;
			}
		}

	}

	//inser elemento atual
	my_vect_prim_idx = (prim_idx_t*)realloc(my_vect_prim_idx, (sizeof(prim_idx_t) * (count + 1)));
	strcpy(my_vect_prim_idx[count].cpf, pk);
	my_vect_prim_idx[count].offset = pos;
	count++;




	qsort(my_vect_prim_idx, count, sizeof(prim_idx_t), compare_qsort);
	/*

	printf("Imprimindo vetor ordenado... count vale %d\n", count);
	for(i = 0; i < count; i++)
	{
		printf("charve: %s offset: %d\n",my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);

	}
	*/


	//atualiza vetor -> arquivo

	fclose(fp);
	atualizaArquivoChavePrimaria(my_vect_prim_idx, count);






	free(my_vect_prim_idx);

	//fclose(fp);
}


//retorna -1 se chave nao está sendo usada
//retorna 1 se a chave está em uso
int verificaSeExisteChavePrimaria(char *pk)
{
	FILE *fp = fopen("prim.idx", "a+");
	prim_idx_t *my_vect_prim_idx, *res;
	int count, exist_key;
	char cpf[12];
	int offset;
	int nbytes;
	int i;



	fseek(fp, 0L, SEEK_END);
	count = ftell(fp);

	if(count == 0) {
		fclose(fp);
		return -1; //nao existe chave ->arquivo zerado
	}


	//inicia vetor
	my_vect_prim_idx = NULL;

	//posiciona no inicio do arquivo
	fseek(fp, 0L, SEEK_SET);

	count = 0;

	//carrega vetor na memória (já estará ordenado)
	while(!feof(fp))
	{
		if(!feof(fp)){
			my_vect_prim_idx = (prim_idx_t*)realloc(my_vect_prim_idx, (sizeof(prim_idx_t) * (count + 1)));
			nbytes = fscanf(fp, "%s %d", cpf, &offset);

			if(nbytes > 0) {
				strcpy(my_vect_prim_idx[count].cpf, cpf);
				my_vect_prim_idx[count].offset = offset;
				//printf("gravei no vetor idx: %s %d bytes lidos %d\n",my_vect_prim_idx[count].cpf, my_vect_prim_idx[count].offset, nbytes);
				count++;
			}
		}

	}


	/*
	printf("veriicando chave %s no vetor\n...total de chaves \n", pk);

	//printf("Imprimindo vetor ordenado...\n");
	for(i = 0; i < count; i++)
	{
		printf("charve: %s offset: %d\n",my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);

	}

*/



	//utiliza busca binária pra ver se chave existe
	res = bsearch(pk, my_vect_prim_idx, count, sizeof(prim_idx_t), compare_bsearch);

	if(res != NULL) exist_key = 1; //chave em uso
	else exist_key = -1;  //chave liberada


	free(my_vect_prim_idx);
	fclose(fp);

	return exist_key;


}
int compare_qsort(const void *a, const void *b)
{
	prim_idx_t *x = (prim_idx_t*)a;
	prim_idx_t *y = (prim_idx_t*)b;

	if(strcmp(x->cpf, y->cpf) > 0) return 1;
	else return 0;


}

int compare_bsearch(const void *a, const void *b)
{
	prim_idx_t *x = (prim_idx_t*)a;
	prim_idx_t *y = (prim_idx_t*)b;


	return (strcmp(x->cpf, y->cpf));


}


void atualizaArquivoChavePrimaria(prim_idx_t *my_vect_prim_idx, int length)
{
	int i;
	FILE *fp = fopen("prim.idx", "w+");


	for(i = 0; i < length; i++)
	{
		//printf("gravando: %-11s %d\n",my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);

		fprintf(fp,"%-11s %d\n",my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);
	}



	fclose(fp);


}
