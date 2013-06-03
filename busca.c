/*
 * busca.c
 *
 *  Created on: Jun 2, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "indicePrimario.h"
#include "indiceSecundario.h"
#include "busca.h"

/*Busca Registro pela chave primaria
 * e retorna a posicao (offset) no arquivo de dados
 */
int buscaRegistro(const char *key)
{
	int offset, nbytes, count;
	char pk[50];
	FILE *fp;
	prim_idx_t *my_vect_prim_idx, *res;

	fp = fopen("prim.idx", "r");

	my_vect_prim_idx = NULL;



	count = 0;
	while(!feof(fp))
	{
		if(!feof(fp)){
			my_vect_prim_idx = (prim_idx_t*)realloc(my_vect_prim_idx, (sizeof(prim_idx_t) * (count + 1)));
			nbytes = fscanf(fp, "%s %d", pk, &offset);

			//printf("bytes lidos : %d\n", nbytes);
			if(nbytes > 0) {
				strcpy(my_vect_prim_idx[count].cpf, pk);
				my_vect_prim_idx[count].offset = offset;
				//printf("gravei no vetor idx: %s %d bytes lidos %d\n",my_vect_prim_idx[count].cpf, my_vect_prim_idx[count].offset, nbytes);
				count++;
			}
		}

	}

	res = bsearch(key, my_vect_prim_idx, count, sizeof(prim_idx_t), compare_bsearch_busca_pk);



	/*
	printf("\nPrinting prim.idx on buca.c....\n");
	for(i = 0; i < count; i++)
	{
		printf("%s - %d\n", my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);
	}

	 */


	fclose(fp);

	if(res != NULL)
	{
		offset = res->offset;
	} else offset = -1;


	free(my_vect_prim_idx);

	return offset;

}

int compare_bsearch_busca_pk(const void *a, const void *b)
{
	prim_idx_t *x = (prim_idx_t*)a;
	prim_idx_t *y = (prim_idx_t*)b;


	return (strcmp(x->cpf, y->cpf));


}

int compare_bsearch_busca_sk(const void *a, const void *b)
{
	sec_key_idx_t *x = (sec_key_idx_t*)a;
	sec_key_idx_t *y = (sec_key_idx_t*)b;


	return (strcmp(x->sk, y->sk));


}

void buscaPorCpf(char *cpf)
{
	int pos;

	pos = buscaRegistro(cpf);

	//encontrou
	if(pos >= 0)
		exibeRegistro(pos);
	else{
		fprintf(stderr, "registro %s nao encontrado!\n", cpf);
	}

}




int buscaPorCpfOR(char *key, int start, keys_founded_t **mykeys)
{
	int count;
	int i, j,  pos;


	count = start;



		pos = buscaRegistro(key);
		if(pos >= 0)
		{
			(*mykeys) = (keys_founded_t*)realloc((*mykeys), sizeof(keys_founded_t) * (count +1));
			//strcpy(mykeys[count].pk, pk);
			strcpy((*mykeys)[count].pk, key);
			count++;

		}



	return count;


}

int buscaPorCpfAND(char *key, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and)
{
	int count;
	int i, j,  pos;


	count = 0;


	for(j = 0; j < size; j++)
	{

		pos = buscaRegistro(mykeys[j].pk);
		if(pos >= 0)
		{
			(*mykeys_and) = (keys_founded_t*)realloc((*mykeys_and), sizeof(keys_founded_t) * (count +1));
			//strcpy(mykeys[count].pk, pk);
			strcpy((*mykeys_and)[count].pk,mykeys[j].pk);
			count++;

		}

	}

	return count;


}



void buscaPorUniverdade(char *universidade)
{
	int pos_lista_invertida, count;
	int i, pos_pk_idx_file;
	char pk[12];
	FILE *fp;
	keys_founded_t *mykeys;

	pos_lista_invertida = buscaSecKeyAtIdxFile(universidade, "universidade.idx");
	//printf("busca por universidade %s esta na posicao %d\n", universidade, pos);

	//busca na lista invertida as posicoes
	fp = fopen("universidadeListaInvertida.idx", "r");

	mykeys = NULL;
	count = 0;
	while(pos_lista_invertida != -1){
		fseek(fp, pos_lista_invertida, SEEK_SET);
		fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
		mykeys = (keys_founded_t*)realloc(mykeys, sizeof(keys_founded_t) * (count +1));
		strcpy(mykeys[count].pk, pk);
		count++;

	}


	qsort(mykeys, count, sizeof(keys_founded_t), compare_founded_keys);

	for(i = 0; i < count; i++)
	{
		//printf("chaves: %s\n", mykeys[i].pk);
		buscaPorCpf(mykeys[i].pk);

	}


	free(mykeys);

	fclose(fp);

}
int buscaPorUniverdadeOR(char *universidade, int start, keys_founded_t **mykeys)
{
	int pos_lista_invertida, count;
	int i, pos_pk_idx_file;
	char pk[12];
	FILE *fp;

	pos_lista_invertida = buscaSecKeyAtIdxFile(universidade, "universidade.idx");
	//printf("busca por universidade %s esta na posicao %d\n", universidade, pos);

	//busca na lista invertida as posicoes
	fp = fopen("universidadeListaInvertida.idx", "r");

	count = start;
	while(pos_lista_invertida != -1){
		fseek(fp, pos_lista_invertida, SEEK_SET);
		fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
		(*mykeys) = (keys_founded_t*)realloc((*mykeys), sizeof(keys_founded_t) * (count +1));
		//strcpy(mykeys[count].pk, pk);
		strcpy((*mykeys)[count].pk, pk);
		count++;

	}



	fclose(fp);

	return count;

}

int buscaPorUniverdadeAND(char *universidade, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and)
{
	int pos_lista_invertida, count;
	int i, j,  pos_pk_idx_file;
	char pk[12];
	FILE *fp;


	//printf("busca por universidade %s esta na posicao %d\n", universidade, pos);

	count = 0;


	for(j = 0; j < size; j++)
	{
		//printf("universidade buscando na chave %s\n", mykeys[j].pk);

		//busca na lista invertida as posicoes
		pos_lista_invertida = buscaSecKeyAtIdxFile(universidade, "universidade.idx");
		fp = fopen("universidadeListaInvertida.idx", "r");

		while(pos_lista_invertida != -1){
			fseek(fp, pos_lista_invertida, SEEK_SET);
			fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
			if(strcmp(mykeys[j].pk, pk) == 0)
			{
				(*mykeys_and) = (keys_founded_t*)realloc((*mykeys_and), sizeof(keys_founded_t) * (count +1));
				//strcpy(mykeys[count].pk, pk);
				strcpy((*mykeys_and)[count].pk, pk);
				count++;
			}

		}



		fclose(fp);
	}

	return count;


}

void buscaPorModalidade(char *modalidade)
{
	int count, i, pos_lista_invertida;
	int pos_pk_idx_file;
	char pk[12];
	FILE *fp;
	keys_founded_t *mykeys;

	pos_lista_invertida = buscaSecKeyAtIdxFile(modalidade, "modalidade.idx");

	//printf("busca por universidade %s esta na posicao %d\n", modalidade, pos);


	//busca na lista invertida as posicoes
	fp = fopen("modalidadeListaInvertida.idx", "r");

	mykeys = NULL;
	count = 0;
	while(pos_lista_invertida != -1){
		fseek(fp, pos_lista_invertida, SEEK_SET);
		fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
		mykeys = (keys_founded_t*)realloc(mykeys, sizeof(keys_founded_t) * (count +1));
		strcpy(mykeys[count].pk, pk);
		count++;

	}


	qsort(mykeys, count, sizeof(keys_founded_t), compare_founded_keys);

	for(i = 0; i < count; i++)
	{
		//printf("chaves: %s\n", mykeys[i].pk);
		buscaPorCpf(mykeys[i].pk);

	}


	free(mykeys);

	fclose(fp);





}

int buscaPorModalidadeOR(char *modalidade, int start, keys_founded_t **mykeys)
{
	int count, i, pos_lista_invertida;
	int pos_pk_idx_file;
	char pk[12];
	FILE *fp;

	pos_lista_invertida = buscaSecKeyAtIdxFile(modalidade, "modalidade.idx");

	//printf("busca por universidade %s esta na posicao %d\n", modalidade, pos);


	//busca na lista invertida as posicoes
	fp = fopen("modalidadeListaInvertida.idx", "r");

	count = start;
	while(pos_lista_invertida != -1){
		fseek(fp, pos_lista_invertida, SEEK_SET);
		fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
		*mykeys = (keys_founded_t*)realloc((*mykeys), sizeof(keys_founded_t) * (count +1));
		//strcpy(mykeys[count].pk, pk);
		strcpy((*mykeys)[count].pk, pk);
		count++;

	}


	fclose(fp);

	return count;

}

int buscaPorModalidadeAND(char *modalidade, int size, keys_founded_t *mykeys, keys_founded_t **mykeys_and)
{
	int count, i,j, pos_lista_invertida;
	int pos_pk_idx_file;
	char pk[12];
	FILE *fp;

	count = 0;

	for(j = 0; j < size; j++)
	{

		pos_lista_invertida = buscaSecKeyAtIdxFile(modalidade, "modalidade.idx");

		//printf("busca por universidade %s esta na posicao %d\n", modalidade, pos);


		//busca na lista invertida as posicoes
		fp = fopen("modalidadeListaInvertida.idx", "r");

		while(pos_lista_invertida != -1){
			fseek(fp, pos_lista_invertida, SEEK_SET);
			fscanf(fp, "%s %d\n", pk, &pos_lista_invertida);
			if(strcmp(mykeys[j].pk, pk) == 0)
			{
				*mykeys_and = (keys_founded_t*)realloc((*mykeys_and), sizeof(keys_founded_t) * (count +1));
				//strcpy(mykeys[count].pk, pk);
				strcpy((*mykeys_and)[count].pk, pk);
				count++;
			}

		}


		fclose(fp);
	}

	return count;



}
void exibeRegistro(int pos)
{
	FILE *fp;
	char buff[111];
	char *tokens1, *tokens2;


	fp = fopen("data.db", "rb");

	fseek(fp, pos, SEEK_SET);
	fread(buff, sizeof(char), 111, fp);

	tokens1 = strtok(buff, "|");

	//nao exibe registros excluídos
	if(strcmp(tokens1, "***********") !=0)
	{
		tokens2 = strtok(NULL, "|");

		printf("%s - %s\n", tokens1, tokens2);

		tokens1 = strtok(NULL, "|");
		printf("\tRegistro Academico: %s\n", tokens1);

		tokens1 = strtok(NULL, "|");
		printf("\tUniversidade: %s\n", tokens1);

		tokens1 = strtok(NULL, "|");
		printf("\tModalidade: %s\n", tokens1);
	}

	fclose(fp);



}

int buscaSecKeyAtIdxFile(char *key, char *filename)
{
	int offset, nbytes, count;
	char sk[50];
	FILE *fp;
	sec_key_idx_t *myvector, *res;

	fp = fopen(filename, "r");

	myvector= NULL;



	count = 0;
	while(!feof(fp))
	{
		if(!feof(fp)){
			myvector = (sec_key_idx_t*)realloc(myvector, (sizeof(sec_key_idx_t) * (count + 1)));
			nbytes = fscanf(fp, "%s %d", sk, &offset);

			//printf("bytes lidos : %d\n", nbytes);
			if(nbytes > 0) {
				strcpy(myvector[count].sk, sk);
				myvector[count].pos = offset;
				//printf("gravei no vetor idx: %s %d bytes lidos %d\n",my_vect_prim_idx[count].cpf, my_vect_prim_idx[count].offset, nbytes);
				count++;
			}
		}

	}

	res = bsearch(key, myvector, count, sizeof(sec_key_idx_t), compare_bsearch_busca_sk);



	/*
		printf("\nPrinting prim.idx on buca.c....\n");
		for(i = 0; i < count; i++)
		{
			printf("%s - %d\n", my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);
		}

	 */


	fclose(fp);

	if(res != NULL)
	{
		offset = res->pos;
	} else offset = -1;


	free(myvector);

	return offset;
}

int compare_founded_keys(const void *a, const void *b)
{
	keys_founded_t *x = (keys_founded_t*)a;
	keys_founded_t *y = (keys_founded_t*)b;


	return (strcmp(x->pk, y->pk));


}


