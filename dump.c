/*
 * dump.c
 *
 *  Created on: Jun 1, 2013
 *      Author: emanuel
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dump.h"


void dumpFileData()
{
	FILE *fp = fopen("data.db", "r");
	char ch;


	while(!feof(fp))
	{
		ch = fgetc(fp);
		if(!feof(fp))
		{
			printf("%c", ch);

		}

	}

	printf("\n");

	fclose(fp);

}


void dumpFilePrimaryKey()
{
	FILE *fp = fopen("prim.idx", "r");
	char pk[12];
	int offset;


	while(!feof(fp))
	{
		fscanf(fp, "%s %d", pk, &offset);
		if(!feof(fp))
		{
			printf("%s - %d\n", pk, offset);

		}

	}

	fclose(fp);

}

void dumpFileSecondaryKey(char *filename)
{
	FILE *fp = fopen(filename, "r");

	char sk[30];
	int posListaInvertida;


	while(!feof(fp))
	{
		fscanf(fp, "%s %d", sk, &posListaInvertida);
		if(!feof(fp))
		{
			printf("%s - %d\n", sk, posListaInvertida);

		}

	}

	fclose(fp);


}
