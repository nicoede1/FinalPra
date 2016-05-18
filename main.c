#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main (){
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

void createInd(){
    printf("---------------::\n");
    printf("                 Aqui vai o createInd    ::---------------\n");
    printf("                 E assim se fez no 1º dia::---------------\n");
    printf("                                         ::---------------\n");
}

void createHeader(){
    printf("---------------::\n");
    printf("                 E disse o programador: Cria-se o header::---------------\n");
    printf("                 E assim se fez no 2º dia               ::---------------\n");
    printf("                                                        ::---------------\n");
    FILE *arqHeader;
    char[]="()";

    arqHeader = fopen("header.txt", "a");
    if(!arqHeader){
        printf("Erro Abertura de arqHeader\n");
        fclose(arqHeader);
        break;
    }

    fclose(arqHeader);
    

}

void inserir(int opcE, int opcO){
    int sal;
    printf("\t\t--------------------Aqui vão as coisas do inserir\n");
    scanf("%i", &sal);
}
void excluir(int opcE, int opcO){
    int sal;
    printf("\t\t--------------------Aqui vão as coisas do excluir\n");
    scanf("%i", &sal);
}
void atualizar(int opcE, int opcO){
    int sal;
    printf("\t\t--------------------Aqui vão as coisas do atualizar\n");
    scanf("%i", &sal);
}
void buscar(int opcE, int opcO){
    int sal;
    printf("\t\t--------------------Aqui vão as coisas do buscar\n");
    scanf("%i", &sal);
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