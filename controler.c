#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "controler.h"
#include "dump.h"

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
	printf("Removendo atleta com cpf %s...\n", cpf);

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
