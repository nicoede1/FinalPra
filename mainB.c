#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main (){
    system("clear");
    char *config;
    
    config = (char *) malloc(MaxBufferConfig+1*sizeof(char));
    if(!config){
        printf("Erro Alloc\n");
        exit(2);
    }

    createInd();
    createHeader();
    
    int opc;
    while(1){
        printf("Insira  a entidade desejada:\n");
        printf("\t1 - Livro\n\t2 - Leitor\n\t3 - Autor\n\t4 - Autor do Livro\n\t5 - Emprestimo\n\t\t\t\t -1 - SAIR\n\t:: ");
        scanf("%i", &opc);
        system("clear");
        if(opc == -1){
            printf("Fim da execucao do programa.\n\t\t\t\tAdios\n");
            break;
        }
        menuCrud(opc);
    }
    
    
    return 0;
}

void lerConfigB(char *config){
    FILE    *arqConfig;
    char    *buffer,
            tipoCampos;
    int     *tamCampos;
    char    name[MaxNameEnt],
            aux[20];
    int     qtdCampos,
            aux,
            isNull,
            isAutoIncrement,
            intPk;        
    size_t  result;
    char aux[20];

    arqConfig = fopen("config.txt", "r");
    if(!arqConfig){
        printf("Erro, n existe arquivo de config do bd.  ERROR 404");
        exit(2);
    }

    while(result = fread(buffer, sizeof(char), MaxBufferConfig, arqConfig)){
        if(!result)
            break;//fim leitura do arquivo
        if(fscanf(buffer,"(Ent%s ,qtdCampos%i ,tipoCampos%s ,tamCampos%s ,NULL?%i ,autoIncrement?%i ,intPK%i )",&tamanho_header,entidade,&qnt_campos,campos,tamanhos,tipo,relacao,localizacao,versao)==9){
    }
    fclose(arqHeader);
}

void createInd(){
    printf("---------------::\n");
    printf("                 Aqui vai o createInd    ::---------------\n");
    printf("                 E assim se fez no 1º dia::---------------\n");
    printf("                                         ::---------------\n");
}

void createHeader(Tabela t){
    //createConfigB();
    printf("---------------::\n");
    printf("                 E disse o programador: Cria-se o header::---------------\n");
    printf("                 E assim se fez no 2º dia               ::---------------\n");
    printf("                                                        ::---------------\n");
    FILE *arqHeader;
    char s[]="()";
    

}

void inserir(int opcE, int opcO){
    printf("\t\t--------------------Aqui vão as coisas do inserir\n");
}
void excluir(int opcE, int opcO){
    printf("\t\t--------------------Aqui vão as coisas do excluir\n");
}
void atualizar(int opcE, int opcO){
    printf("\t\t--------------------Aqui vão as coisas do atualizar\n");
}
void buscar(int opcE, int opcO){
    printf("\t\t--------------------Aqui vão as coisas do buscar\n");
}


int menuCrud(int opcE){
    int opcO,    //var que recebe a oopc do menu crud
        bolinho = 0; //var de controle pra voltar ao menu de ent
    //aqui vai o menu crud
    printf("Insira  a operacao desejada:\n");
        printf("\t1 - Inserir\n\t2 - Excluir\n\t3 - Atualizar\n\t4 - Buscar\n\t\t\t\t -1 - VOLTAR\n\t: ");
        scanf("%i", &opcO);

    switch(opcO){
        case 1:
            inserir(opcE, opcO);
            break;
        case 2:
            excluir(opcE, opcO);
            break;
        
        case 3:
            atualizar(opcE, opcO);
            break;
            
        case 4:
            buscar(opcE, opcO);
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