#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainB.h"

int main(){

	createHeader();
	
	return 0;

}

void createHeader(){
    FILE *arqEnt, *configDB;
    char linha[275], entidade[15];
    int nEntidades, tamHeader;
    int i;
    
    configDB=fopen("configDB.txt", "r");
    if(configDB == NULL){
	   	printf("Erro ao abrir arquivo de configuracao do banco de dados\n");
		exit(2);
    }
    fscanf(configDB, "nEntidades=%d\n", &nEntidades);
    //printf("nEntidades=%d\n", nEntidades);
    
    for(i=0;i<nEntidades;i++){
		fscanf(configDB, "tamHeader=%d", &tamHeader);
		//printf("tamHeader=%d\n", tamHeader);
		fseek(configDB, -13, SEEK_CUR);
		fread(linha, sizeof(char), tamHeader, configDB);
		linha[tamHeader]='\0';
		sscanf(linha+14, "entidade=[%s ]", entidade);
		//printf("%s\n", entidade);
		arqEnt=fopen(entidade, "r");
		if(arqEnt == NULL){
			arqEnt=fopen(entidade, "w");
			if(arqEnt == NULL){
				printf("Erro ao criar arquivo de entidade\n");
				exit(2);
			}
			fprintf(arqEnt, "%s", linha);
		}
		fclose(arqEnt);
		
    }
    

}
