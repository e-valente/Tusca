#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indiceSecundario.h"
#include "listaInvertida.h"

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
		//fprintf(fp,"%s %11d\n", sk, pos);
		fprintf(fp,"%-30s %10d\n", sk, pos);

		//Ordenar
	}


	/*ordena idx sec key*/


	fclose(fp);

	ordenaIdxSecKeyFile(filename);
}

void ordenaIdxSecKeyFile(const char *filename)
{
	sec_key_idx_t *myvect;
	FILE *fp = fopen(filename, "r");
	int count, pos, nbytes;
	char seckey[50];

	myvect = NULL;



	count = 0;

	fseek(fp, 0L, SEEK_SET);

	while(!feof(fp))
	{
		if(!feof(fp)){
			myvect = (sec_key_idx_t*)realloc(myvect, (sizeof(sec_key_idx_t) * (count + 1)));
			nbytes = fscanf(fp, "%s %d", seckey, &pos);

			//printf("bytes lidos : %d\n", nbytes);
			if(nbytes > 0) {
				strcpy(myvect[count].sk, seckey);
				myvect[count].pos = pos;
				//printf("gravei no vetor idx: %s %d bytes lidos %d\n",my_vect_prim_idx[count].cpf, my_vect_prim_idx[count].offset, nbytes);
				count++;
			}
		}

	}

	//ordena arquivo (vetor)
	qsort(myvect, count, sizeof(sec_key_idx_t), seckey_compare_qsort);

	/*

	printf("Imprimindo vetor ordenado idx do arquivo %s ...\n", filename);
	for(i = 0; i < count; i++)
	{
		printf("%-30s %10d\n", myvect[i].sk, myvect[i].pos);

	}

   */
	//atualiza arquivo idx (flush para arquivo)


	fclose(fp);
	atualizaArquivoChaveSecundaria(myvect, count, filename);


	free(myvect);

}

int seckey_compare_qsort(const void *a, const void *b)
{
	sec_key_idx_t *x = (sec_key_idx_t*)a;
	sec_key_idx_t *y = (sec_key_idx_t*)b;

	if(strcmp(x->sk, y->sk) > 0) return 1;
	else return 0;


}

void atualizaArquivoChaveSecundaria(sec_key_idx_t *vector, int length, const char *filename)
{
	int i;
	FILE *fp = fopen(filename, "w+");


	for(i = 0; i < length; i++)
	{
		//printf("gravando: %-11s %d\n",my_vect_prim_idx[i].cpf, my_vect_prim_idx[i].offset);

		fprintf(fp,"%-30s %10d\n",vector[i].sk, vector[i].pos);
	}



	fclose(fp);
}
