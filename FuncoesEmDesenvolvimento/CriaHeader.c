#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainB.h"

int main(){

	createHeader();
	inserir(1);
	
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
    
    for(i=0;i<nEntidades;i++){
		fscanf(configDB, "tamHeader=%d", &tamHeader);
		fseek(configDB, -13, SEEK_CUR);
		fread(linha, sizeof(char), tamHeader, configDB);
		linha[tamHeader]='\0';
		sscanf(linha+14, "entidade=[%s ]", entidade);
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

void inserir(int opcE){
    char linhaHeader[275];
    char *pos=NULL;
    int i;
    int tamLinhaDados;
    Tabela tab;
    FILE *arqEnt;
    
    switch (opcE){
    	case 1:
    		arqEnt=fopen("Livro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 2:
    		arqEnt=fopen("Leitor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 3:
    		arqEnt=fopen("Autor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 4:
    		arqEnt=fopen("AutorDoLivro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 5:
    		arqEnt=fopen("Emprestimo", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	default:
    		printf("Isso nunca deveria aontecer ._.\n");
    		printf("Alguma coisa deu muito errado\n");
    		exit(2);
    }
    printf("Abriu o arquivo\n");
    
    //Por algum motivo isso aqui não funciona, sendo que createHeader faz exatamente a mesma coisa e funciona ok
    fscanf(arqEnt, "tamHeader=%d", &(tab.tamHeader));
    
    printf("Leu o tamanho\n");
    printf("tamHeader=%d", tab.tamHeader);
	fseek(arqEnt, -13, SEEK_CUR);
	fread(linhaHeader, sizeof(char), tab.tamHeader, arqEnt);
	linhaHeader[tab.tamHeader]='\0';
	
	
	pos = strstr(linhaHeader, ",qtdCampos=");
	sscanf(pos, ",qtdCampos=[%d]", &(tab.qtdCampos));
	printf("qtdCampos=%d", tab.qtdCampos);
	
	/*
	pos = strstr(linhaHeader, ",campos=");
	pos+=9;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%s", tab.campos[i]);
		pos+=(strlen(tab.campos[i]));
	}
	*/
    
}




















