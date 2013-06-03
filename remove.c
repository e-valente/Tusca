/*
 * remove.c
 *
 *  Created on: Jun 2, 2013
 *      Author: emanuel
 */

#include"indicePrimario.h"
#include "remove.h"
#include "busca.h"

void removeRegistro(const char *pk)
{
	int pos;
	FILE *fp;
	char *chardel = "***********";
	int nbytes;
	int i;

	char buff[10000];

	//fprintf(stderr, "remvendo cpf %s..\n", pk);

	pos = buscaRegistro(pk);

	if(pos >= 0)
	{
		//carrega o arquivo no buffer
		fp = fopen("data.db", "r+b");
		nbytes = fread(buff, sizeof(char), 10000, fp);

	//	printf("na posicao %d\n", pos);

		if(nbytes >= 10000)
		{
			fprintf(stderr, "Arquivo muito grande! Aumente o buffer!\n");
		}

		fclose(fp);

		fp = fopen("data.db", "w+");

		//printf("Escreve até ond vai apagar...\n");
		for(i = 0; i < pos; i++)
		{
			fprintf(fp,"%c", buff[i]);


		}

		//apaga registro
		fprintf(fp,"%s", chardel);


		//printf("Escreve depois de apagar...\n");
		for(i = pos +11 ; i < nbytes; i++)
		{
			fprintf(fp,"%c", buff[i]);


		}
		fclose(fp);
		//printf("primeiros 200 bytes lidos: %s\n", buff);
		/*
		fseek(fp, pos, SEEK_SET);
		printf("posicao que estou: %d\n", ftell(fp));
		fprintf(fp,"%-11s|",chardel);
		printf("\nvou remover chave %s na posicao %d\n", pk, pos);

		 */
	}



}
