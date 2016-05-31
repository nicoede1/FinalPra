#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainB.h"

int main(){

	system("clear");
	createHeader();
	
	int opc;
    while(1){
        printf("Insira  a entidade desejada:\n");
        printf("\t1 - Livro\n\t2 - Leitor\n\t3 - Autor\n\t4 - Autor do Livro\n\t5 - Emprestimo\n\t\t\t\t -1 - SAIR\n\t:: ");
        scanf("%i\n", &opc);
        //fflush(stdin);
        system("clear");
        if(opc == -1){
            printf("Fim da execucao do programa.\n\t\t\t\tAdios\n");
            break;
        }
        menuCrud(opc);
    }
	
	
	//inserir(2);
	//inserir(1);
	
	return 0;

}

int menuCrud(int opcE){
    int opcO,    //var que recebe a oopc do menu crud
        bolinho = 0; //var de controle pra voltar ao menu de ent
    //aqui vai o menu crud
    printf("Insira  a operacao desejada:\n");
        printf("\t1 - Inserir\n\t2 - Excluir\n\t3 - Atualizar\n\t4 - Buscar\n\t\t\t\t -1 - VOLTAR\n\t: ");
        scanf("%i\n", &opcO);
        //fflush(stdin);

    switch(opcO){
        case 1:
            inserir(opcE);
            break;
        case 2:
            //excluir(opcE);
            break;
        
        case 3:
            //atualizar(opcE);
            break;
            
        case 4:
            //buscar(opcE);
            break;
            
        case -1:
            bolinho = 1;
            printf("Bolinho com mostarda\n");
            break;
        default:
            printf("Opção invalida!");
            break;
    }
    system("clear");
    if(bolinho == 1){
        return 1;
    }else{
        menuCrud(opcE);
    }

    return 0;
}



void createHeader(){
    FILE *arqEnt, *configDB, *index;
    char linha[275], entidade[15], indice[22];
    int nEntidades, tamHeader;
    int i;
    
    configDB=fopen("configDB.txt", "r");
    if(configDB == NULL){
	   	printf("Erro ao abrir arquivo de configuracao do banco de dados\n");
		exit(2);
    }
    fscanf(configDB, "nEntidades=%d\n", &nEntidades);

    valorAutoInc = (int*)malloc(nEntidades*sizeof(int));
    for(i=0;i<nEntidades;i++){
        valorAutoInc[i]=0;
    }
    
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
			fprintf(arqEnt, "CADEABABA\n");
			fprintf(arqEnt, "%s", linha);
		}
		fclose(arqEnt);
		strcpy(indice, entidade);
		strcat(indice, "Indice");
		index=fopen(indice, "r");
		if(index==NULL){
			index=fopen(indice, "w");
			if(indice == NULL){
				printf("Erro ao criar arquivo de inidice\n");
				exit(2);
			}
		}
		fclose(index);
		
    }
    
}

void inserir(int opcE){
    char linhaHeader[275];
    char *linhaDados, *info;
    int i, j;
    int tamLinhaDados=0, maiorCampo=0, posAtual=0;
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
    fread(linhaHeader, sizeof(char), 10, arqEnt);
    linhaHeader[9]='\0';
    //printf("%s\n", linhaHeader);
    if(strcmp(linhaHeader, "CADEABABA")!=0){
    	printf("Arquivo de entidade inválido\n");
    	exit(2);
    }
    
    tab = lerHeader(arqEnt);
    
    fseek(arqEnt, 0, SEEK_END);
    
    for(i=0;i<tab.qtdCampos;i++){
    	tamLinhaDados+=tab.tamanhos[i];
    	if(tab.tamanhos[i]>maiorCampo){
    		maiorCampo=tab.tamanhos[i];
    	}
    }
    tamLinhaDados+=2;
    //printf("%d\n", tamLinhaDados);
    //printf("%d\n", maiorCampo);
    
    linhaDados=(char*)malloc(tamLinhaDados*sizeof(char));
    for(i=0;i<tamLinhaDados;i++){
        linhaDados[i]=' ';
    }
    linhaDados[tamLinhaDados-1]='\0';
    linhaDados[tamLinhaDados-2]='\n';

    //printf("%s\n", linhaDados);
    
    info=(char*)malloc((maiorCampo+1)*sizeof(char));
    info[maiorCampo]='\0';
    
    printf("Informe os campos a seguir:\n");
    for(i=0;i<tab.qtdCampos;i++){
    	if(tab.autoInc[i]==1){
            valorAutoInc[opcE-1]++;
            sprintf(linhaDados+posAtual, "%d", valorAutoInc[opcE-1]);
            for(j=0;linhaDados[j]!='\0';j++){
                if(linhaDados[j]=='\n')
                    break;
            }
            linhaDados[j]=' ';
            posAtual+=tab.tamanhos[i];
    		continue;
    	}
    	
        printf("%s:\n", tab.campos[i]);

    	if(tab.null[i]==0){
    		printf("(Campo obrigatório)\n");
    	}
    	else{
    		printf("(Pressione espaço e enter para deixar o campo vazio)\n");
    	}
    	
        fgets(info, tamLinhaDados, stdin);
        sprintf(linhaDados+posAtual, "%s", info);
        
        if(linhaDados[posAtual+strlen(info)-1]=='\n'){
        	linhaDados[posAtual+strlen(info)-1]=' ';
        }
        if(linhaDados[posAtual+strlen(info)+1]==' '){
            linhaDados[posAtual+strlen(info)]=' ';
        }
        else if(linhaDados[posAtual+strlen(info)+1]=='\0'){
            linhaDados[posAtual+strlen(info)]='\n';
        }

        posAtual+=tab.tamanhos[i];
    }

    printf("%s\n", linhaDados);
    fprintf(arqEnt, "%s", linhaDados);
    
    
}

Tabela lerHeader(FILE *arqEnt){
	char linhaHeader[275];
    char *pos=NULL;
    int i;
    Tabela tab;
	
	fscanf(arqEnt, "tamHeader=%d", &(tab.tamHeader));
    
    //printf("tamHeader=%d\n", tab.tamHeader);
	fseek(arqEnt, -13, SEEK_CUR);
	fread(linhaHeader, sizeof(char), tab.tamHeader, arqEnt);
	linhaHeader[tab.tamHeader]='\0';
	
	pos = strstr(linhaHeader, ",qtdCampos=");
	sscanf(pos, ",qtdCampos=[%d]", &tab.qtdCampos);	
	
	pos = strstr(linhaHeader, ",campos=");
	pos+=9;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%s", tab.campos[i]);
		//printf("%s\n", tab.campos[i]);
		pos+=(2+strlen(tab.campos[i]));
	}
	
	pos = strstr(linhaHeader, ",tamanho=");
	pos+=10;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.tamanhos[i]));
		//printf("%d\n", tab.tamanhos[i]);
		while((pos[0]!=',')&&(pos[0]!=']')){
			pos++;
		}
		pos++;
	}
	
	pos = strstr(linhaHeader, ",tipo=");
	pos+=7;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%s", tab.tipos[i]);
		//printf("%s\n", tab.tipos[i]);
		pos+=(2+strlen(tab.tipos[i]));
	}
    
    pos = strstr(linhaHeader, ",null=");
	pos+=7;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.null[i]));
		//printf("%d\n", tab.null[i]);
		pos+=2;
	}
	
	pos = strstr(linhaHeader, ",autoIncrement=");
	pos+=16;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.autoInc[i]));
		//printf("%d\n", tab.autoInc[i]);
		pos+=2;
	}
	
	pos = strstr(linhaHeader, ",nPk=");
	sscanf(pos, ",nPk=[%d]", &tab.nPk);
	//printf("%d\n", tab.nPk);
	
	pos = strstr(linhaHeader, ",pk=");
	pos+=5;
	for(i=0;i<tab.nPk;i++){
		sscanf(pos, "%s", tab.pk[i]);
		//printf("%s\n", tab.pk[i]);
		pos+=(2+strlen(tab.pk[i]));
	}
	
	return tab;
}
