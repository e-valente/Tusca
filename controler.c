#include "controler.h"

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

	if(debug) printf("Cadastrando registro no arquivo de indice primario\n");
	inserirIndicePrimario(cpf, pos);

	if(debug) printf("Cadastrando registro arquivo de indice secundario\n");
	inserirIndiceSecundario("universidade.idx", univ, cpf);
	inserirIndiceSecundario("modalidade.idx", mod, cpf);


}
