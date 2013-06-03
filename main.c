
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"controler.h"

int main(int argc, char *argv[]){

	int sair = 0;
	char comando[30];
	int debug = 0;

	while(!sair){
		if(debug) printf("> ");
		scanf("%s",comando);

		if(strcmp(comando,"sair") == 0){
			sair = 1;
		}else if(strcmp(comando,"cadastrar") == 0){
			cadastrarAtleta();
		}else if(strcmp(comando,"remover") == 0){
			char cpf[12];
			scanf("%s",cpf);
			removerAtleta(cpf);
		}else if(strcmp(comando,"buscar") == 0){
			char argbuscar[500], ch;
			int count;

			//obtem argumento de buscar
			ch = getchar();
			count = 0;
			while(ch != '\n')
			{
				argbuscar[count] = ch;
				count++;
				ch = getchar();

			}
			argbuscar[count] = '\0';


			buscar(argbuscar);

		}else if(strcmp(comando,"dump") == 0){
			char filetodump[50];
			scanf("%s", filetodump);
			dumpToFile(filetodump);
		}
	}

	return 0;
}
