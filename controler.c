#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "controler.h"
#include "dump.h"
#include "remove.h"
#include "busca.h"

void cadastrarAtleta(){
	int debug = 0;

	char cpf[12];
	char nome[31];
	char ra[11];
	char univ[16];
	char mod[31];

	if(debug) printf("cpf: ");
	scanf("%s",cpf);
	if(debug) printf("nome: ");
	scanf("%s", nome);
	if(debug) printf("ra: ");
	scanf("%s", ra);
	if(debug) printf("univ: ");
	scanf("%s",univ);
	if(debug) printf("mod: ");
	scanf("%s",mod);

	if(debug) printf("Cadastrando registro no banco de dados\n");
	int pos = inserirNoBanco(cpf, nome, ra, univ, mod);
	if(debug) printf("Pos: %d\n",pos);

	if(pos < 0){
		printf("Conflito de chave primaria. Registro nao inserido!\n");
	}
	else {



		if(debug) printf("Cadastrando registro no arquivo de indice primario\n");
		inserirIndicePrimario(cpf, pos);

		if(debug) printf("Cadastrando registro arquivo de indice secundario\n");
		inserirIndiceSecundario("universidade.idx", univ, cpf);
		inserirIndiceSecundario("modalidade.idx", mod, cpf);
	}


}

void removerAtleta(char *cpf)
{
	removeRegistro(cpf);

}

void dumpToFile(char *filename)
{
	if(strcmp(filename, "data.db") == 0)
	{
		dumpFileData();
	}


	if(strcmp(filename, "prim.idx") == 0)
	{
		dumpFilePrimaryKey();
	}



	if((strcmp(filename, "universidade.idx") == 0) ||
			(strcmp(filename, "modalidade.idx") == 0))
	{
		dumpFileSecondaryKey(filename);
	}



	if((strcmp(filename, "universidadeListaInvertida.idx") == 0) ||
			(strcmp(filename, "modalidadeListaInvertida.idx") == 0))
	{
		dumpFileInvertedListSecKey(filename);
	}


}

void buscar(const char *args)
{
	char buffcmd1[20], buff_equal1[2], buffargcmd1[20];
	char buff_and_or[3];
	char buffcmd2[20], buff_equal2[2], buffargcmd2[20];
	int i, res, pos, pos_and;
	keys_founded_t *mykeys, *mykeys_and;


	res = sscanf(args, "%s %s %s %s %s %s %s", buffcmd1, buff_equal1, buffargcmd1,
			buff_and_or, buffcmd2, buff_equal2, buffargcmd2);


	//busca com 2 opcoes (AND) ou (OR)
	if(res >= 7)
	{
		mykeys = NULL;
		mykeys_and = NULL;
		pos = 0;

		//tratamento com OU
		if(strcmp(buff_and_or, "ou") == 0)
		{
			if(strcmp(buffcmd1, "cpf") == 0)
			{
				//printf("busca por cpf...\n");
				pos = buscaPorCpfOR(buffargcmd1, pos, &mykeys);
			}

			if(strcmp(buffcmd1, "universidade") == 0)
			{
				//printf("busca por universidade...\n");
				pos = buscaPorUniverdadeOR(buffargcmd1, pos, &mykeys);
			}

			if(strcmp(buffcmd1, "modalidade") == 0)
			{
				//printf("busca por modalidade...\n");
				pos = buscaPorModalidadeOR(buffargcmd1, pos, &mykeys);
			}


			if(strcmp(buffcmd2, "cpf") == 0)
			{
				//printf("busca por cpf...\n");
				//pos = buscaPorCpf(buffargcmd2, pos, mykeys);
				buscaPorCpf(buffargcmd2);
			}

			if(strcmp(buffcmd2, "universidade") == 0)
			{
				//printf("busca por universidade...\n");
				pos = buscaPorUniverdadeOR(buffargcmd2, pos, &mykeys);
			}

			if(strcmp(buffcmd2, "modalidade") == 0)
			{
				//printf("busca por modalidade...\n");
				pos = buscaPorModalidadeOR(buffargcmd2, pos, &mykeys);
			}

			//printf("valor de pos %d\n", pos);
			qsort(mykeys, pos, sizeof(keys_founded_t), compare_founded_keys);

			for(i = 0; i < pos; i++)
			{
				//printf("chaves encontradas %s\n",mykeys[i].pk);
				buscaPorCpf(mykeys[i].pk);
			}

			free(mykeys);

		}


		//tratamento com E (AND)
		if(strcmp(buff_and_or, "e") == 0)
		{

			if(strcmp(buffcmd1, "cpf") == 0)
			{
				//printf("busca por cpf...\n");
				pos = buscaPorCpfOR(buffargcmd1, pos, &mykeys);
			}

			if(strcmp(buffcmd1, "universidade") == 0)
			{
				//printf("busca por universidade...\n");
				pos = buscaPorUniverdadeOR(buffargcmd1, pos, &mykeys);
			}

			if(strcmp(buffcmd1, "modalidade") == 0)
			{
				//printf("busca por modalidade...\n");
				pos = buscaPorModalidadeOR(buffargcmd1, pos, &mykeys);
			}

			/*Os argumentos devem ser listas de chaves (encontradadas no passo anterior(*/

			pos_and = 0;

			//segundo argumento, a lista será entrada dos comandos
			if(strcmp(buffcmd2, "cpf") == 0)
			{
				//printf("busca por cpf...\n");
				//pos = buscaPorCpf(buffargcmd2, pos, mykeys);
				pos_and = buscaPorCpfAND(buffargcmd2, pos, mykeys, &mykeys_and);
			}

			if(strcmp(buffcmd2, "universidade") == 0)
			{

				pos_and = buscaPorUniverdadeAND(buffargcmd2, pos, mykeys, &mykeys_and);
			}


			if(strcmp(buffcmd2, "modalidade") == 0)
			{
				//printf("busca por modalidade...\n");
				pos_and = buscaPorModalidadeAND(buffargcmd2, pos, mykeys, &mykeys_and);
			}

			//	printf("valor de pos_and apos modalidade %d\n", pos_and);
			if(pos_and > 0){
				qsort(mykeys_and, pos_and, sizeof(keys_founded_t), compare_founded_keys);

				for(i = 0; i < pos_and; i++)
				{
					//printf("chaves encontradas %s\n",mykeys_and[i].pk);
					buscaPorCpf(mykeys_and[i].pk);
				}

				free(mykeys_and);
			}

			free(mykeys);


		}





	}

	//busca com 1 opcao somente
	if(res < 7)
	{
		//printf("comando com 1 opcao\n");
		res = sscanf(args, "%s %s %s", buffcmd1, buff_equal1, buffargcmd1);

		if(strcmp(buffcmd1, "cpf") == 0)
		{
			//printf("busca por cpf...\n");
			buscaPorCpf(buffargcmd1);
		}

		if(strcmp(buffcmd1, "universidade") == 0)
		{
			//printf("busca por universidade...\n");
			buscaPorUniverdade(buffargcmd1);
		}

		if(strcmp(buffcmd1, "modalidade") == 0)
		{
			//printf("busca por modalidade...\n");
			buscaPorModalidade(buffargcmd1);
		}

	}

}
