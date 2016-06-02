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
        scanf("%d", &opc);
        //fflush(stdin);
        system("clear");
        if(opc == -1){
            printf("Fim da execucao do programa.\n\t\t\t\tAdios\n");
            break;
        }
        menuCrud(opc);
    }
	
	
	//inserir(1);
	//inserir(4);
	
	return 0;

}

int menuCrud(int opcE){
    int opcO,    //var que recebe a oopc do menu crud
        bolinho = 0; //var de controle pra voltar ao menu de ent
    //aqui vai o menu crud
    printf("Insira  a operacao desejada:\n");
        printf("\t1 - Inserir\n\t2 - Excluir\n\t3 - Atualizar\n\t4 - Buscar\n\t\t\t\t -1 - VOLTAR\n\t: ");
        scanf("%d", &opcO);
        getchar();
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
            buscar(opcE);
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
    char linhaHeader[275], posArqS[7];
    char *linhaDados, *info, *linhaIndice;
    int i, j;
    int tamLinhaDados=0, maiorCampo=0, posAtual=0, tamLinhaIndice=0, posIndice=1, posArq=0, pkAtual=0;
    long long int indiceInt;
    Tabela tab;
    FILE *arqEnt, *index;
    
    switch (opcE){
    	case 1:
    		arqEnt=fopen("Livro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		index=fopen("LivroIndice", "r+");
    		if(index==NULL){
    			printf("Erro ao abrir arquivo de índice\n");
    			exit(2);
    		}
    		break;
    	case 2:
    		arqEnt=fopen("Leitor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		index=fopen("LeitorIndice", "r+");
    		if(index==NULL){
    			printf("Erro ao abrir arquivo de índice\n");
    			exit(2);
    		}
    		break;
    	case 3:
    		arqEnt=fopen("Autor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		index=fopen("AutorIndice", "r+");
    		if(index==NULL){
    			printf("Erro ao abrir arquivo de índice\n");
    			exit(2);
    		}
    		break;
    	case 4:
    		arqEnt=fopen("AutorDoLivro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		index=fopen("AutorDoLivroIndice", "r+");
    		if(index==NULL){
    			printf("Erro ao abrir arquivo de índice\n");
    			exit(2);
    		}
    		break;
    	case 5:
    		arqEnt=fopen("Emprestimo", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		index=fopen("EmprestimoIndice", "r+");
    		if(index==NULL){
    			printf("Erro ao abrir arquivo de índice\n");
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
    posArq=ftell(arqEnt);
    sprintf(posArqS, "%05d", posArq);
    //printf("%s\n", posArqS);
    fseek(index, 0, SEEK_END);
    
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
    
    j=0;
    for(i=0;(i<tab.qtdCampos)&&(j<tab.nPk);i++){
    	if(strcmp(tab.campos[i], tab.pk[j])==0){
    		//printf("%s\n", tab.campos[i]);
    		//printf("%s\n", tab.pk[j]);
    		tamLinhaIndice+=tab.tamanhos[i];
    		j++;
    	}
    }
    
    tamLinhaIndice+=8;
    //printf("%d\n", tamLinhaIndice);
    
    linhaIndice=(char*)malloc(tamLinhaIndice*sizeof(char));
    
    //linhaIndice[0]=opcE;
    sprintf(linhaIndice, "%d", opcE);
    for(i=1;i<tamLinhaIndice;i++){
        linhaIndice[i]='0';
    }
    linhaIndice[tamLinhaIndice-1]='\0';
    linhaIndice[tamLinhaIndice-2]='\n';
    
    
    printf("Informe os campos a seguir:\n");
    for(i=0;i<tab.qtdCampos;i++){
    	if(tab.autoInc[i]==1){
            if((valorAutoInc[opcE-1]==0)&&(ftell(index)!=0)){
    			fseek(arqEnt, -(tamLinhaDados), SEEK_CUR);
    			fscanf(arqEnt, "%d", &(valorAutoInc[opcE-1]));
    			fseek(arqEnt, 0, SEEK_END);
    		}
            
            valorAutoInc[opcE-1]++;
            sprintf(linhaDados+posAtual, "%d", valorAutoInc[opcE-1]);
            for(j=0;linhaDados[j]!='\0';j++){
                //if(linhaDados[j]=='\n')
                //    break;
            }
            if(linhaDados[j-1]!='\n'){
            	linhaDados[j]=' ';
            }
            posAtual+=tab.tamanhos[i];
            
            sprintf(linhaIndice+posIndice, "%d", valorAutoInc[opcE-1]);
            for(j=0;linhaIndice[j]!='\0';j++){
            	//if(linhaIndice[j]=='\n')
                //    break;
            }
            if(linhaIndice[j-1]!='\n'){
            	linhaIndice[j]='0';
            }
            posIndice+=tab.tamanhos[i];
            pkAtual++;
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
        
        if(strcmp(tab.campos[i], tab.pk[pkAtual])==0){
    		sprintf(linhaIndice+posIndice, "%s", info);
    		if(linhaIndice[posIndice+strlen(info)-1]=='\n'){
		    	linhaIndice[posIndice+strlen(info)-1]='0';
		    }
		    if(linhaIndice[posIndice+strlen(info)+1]=='0'){
		        linhaIndice[posIndice+strlen(info)]='0';
		    }
		    else if(linhaIndice[posIndice+strlen(info)+1]=='\0'){
		        linhaIndice[posIndice+strlen(info)]='\n';
		    }
		    pkAtual++;
		    posIndice+=tab.tamanhos[i];
    	}
        
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

    //printf("%s\n", linhaDados);
    fprintf(arqEnt, "%s", linhaDados);
    
    //strcat(linhaIndice, posArqS);
    sprintf(linhaIndice+posIndice, "%s", posArqS);
    //printf("%s\n", linhaIndice);
    linhaIndice[tamLinhaIndice-1]='\0';
    linhaIndice[tamLinhaIndice-2]='\n';
    fprintf(index, "%s", linhaIndice);
    
    indiceInt = atoll(linhaIndice);
    //printf("%s\n", linhaIndice);
    //printf("%lli\n", indiceInt);
    insertion(indiceInt);
    //int b;
    //searching(indiceInt, &b, root);
    
    
    free(linhaDados);
    free(info);
    free(linhaIndice);
    
    fclose(arqEnt);
    fclose(index);
    
}

void buscar(int opcE){
	int tamLinhaIndice=0, posIndice=1, maiorCampo=0, posArq=0, tamLinhaArq=0;
	int i, j;
	long long int indiceBusca=0, indiceEncontrado=-1;
	char *linhaIndice=NULL, *info=NULL, *infoBusca=NULL, *linhaArq=NULL;
	char linhaHeader[15];
	Tabela tab;
	FILE *arqEnt=NULL;
	
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
    
    j=0;
    for(i=0;(i<tab.qtdCampos)&&(j<tab.nPk);i++){
    	if(strcmp(tab.campos[i], tab.pk[j])==0){
    		if(tab.tamanhos[i]>maiorCampo){
    			maiorCampo=tab.tamanhos[i];
    		}
    		tamLinhaIndice+=tab.tamanhos[i];
    		j++;
    	}
    }
    
    tamLinhaIndice+=2;
    //infoBusca=tamLinhaIndice+5;
    
    linhaIndice=(char*)malloc(tamLinhaIndice*sizeof(char));
    infoBusca=(char*)malloc((tamLinhaIndice+5)*sizeof(char));
    
    sprintf(linhaIndice, "%d", opcE);
    for(i=1;i<tamLinhaIndice;i++){
        linhaIndice[i]='0';
    }
    linhaIndice[tamLinhaIndice-1]='\0';
    //linhaIndice[tamLinhaIndice-2]='\n';
    
    info=(char*)malloc((maiorCampo+1)*sizeof(char));
    info[maiorCampo]='\0';
    
    printf("Informe os campos para busca:\n");
    j=0;
    for(i=0;(i<tab.qtdCampos)&&(j<tab.nPk);i++){
    	if(strcmp(tab.campos[i], tab.pk[j])==0){
    		printf("%s:\n", tab.pk[j]);
    		fgets(info, tamLinhaIndice, stdin);
        	sprintf(linhaIndice+posIndice, "%s", info);
        	if(linhaIndice[posIndice+strlen(info)-1]=='\n'){
		    	linhaIndice[posIndice+strlen(info)-1]='0';
		    }
		    if(linhaIndice[posIndice+strlen(info)+1]=='0'){
		        linhaIndice[posIndice+strlen(info)]='0';
		    }
		    /*
		    else if(linhaIndice[posIndice+strlen(info)+1]=='\0'){
		        linhaIndice[posIndice+strlen(info)]='\n';
		    }
		    */
		    j++;
		    posIndice+=tab.tamanhos[i];
    	}
    }
    /*
    printf("%s\n", linhaIndice);
    indiceBusca = atoll(linhaIndice);
    printf("%lli\n", indiceBusca);
    getchar();
    */
    indiceBusca = atoll(linhaIndice);
    buscaIndice(indiceBusca, &i, root, &indiceEncontrado);
    //printf("%lli\n", indiceEncontrado);
    posArq=indiceEncontrado%indiceBusca;
    //printf("%d\n", posArq);
    
    fseek(arqEnt, posArq, SEEK_SET);
    
    for(i=0;i<tab.qtdCampos;i++){
    	tamLinhaArq+=tab.tamanhos[i];
    }
    linhaArq=(char*)malloc((tamLinhaArq+1)*sizeof(char));
    
    fread(linhaArq, sizeof(char), tamLinhaArq, arqEnt);
    //printf("%s\n", linhaArq);
    
    posArq=0;
    for(i=0;i<tab.qtdCampos;i++){
    	printf("%s:\n", tab.campos[i]);
    	printf("%.*s\n", tab.tamanhos[i], linhaArq+posArq);
    	posArq+=tab.tamanhos[i];
    }
    
    free(linhaIndice);
    free(info);
    free(infoBusca);
    fclose(arqEnt);
    
    printf("Pressione enter para continuar\n");
    getchar();
	
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


/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Funcoes da árvore
Fonte B-tree:
  http://mercury.pr.erau.edu/~siewerts/cs317/code/b-tree/
  https://github.com/smlle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/* Places the value in appropriate position */
void addValToNode(long long int val, int pos, struct btreeNode *node, struct btreeNode *child) {
      int j = node->count;
      while (j > pos) {
              node->val[j + 1] = node->val[j];
              node->link[j + 1] = node->link[j];
              j--;
      }
      node->val[j + 1] = val;
      node->link[j + 1] = child;
      node->count++;
}

/* split the node */
void splitNode (long long int val, long long int *pval, int pos, struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode) {
      int median, j;

      if (pos > MIN)
              median = MIN + 1;
      else
              median = MIN;

      *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
      j = median + 1;
      while (j <= MAX) {
              (*newNode)->val[j - median] = node->val[j];
              (*newNode)->link[j - median] = node->link[j];
              j++;
      }
      node->count = median;
      (*newNode)->count = MAX - median;

      if (pos <= MIN) {
              addValToNode(val, pos, node, child);
      } else {
              addValToNode(val, pos - median, *newNode, child);
      }
      *pval = node->val[node->count];
      (*newNode)->link[0] = node->link[node->count];
      node->count--;
}

/* sets the value val in the node */
int setValueInNode(long long int val, long long int *pval, struct btreeNode *node, struct btreeNode **child) {

      int pos;
      if (!node) {
              *pval = val;
              *child = NULL;
              return 1;
      }

      if (val < node->val[1]) {
              pos = 0;
      } else {
              for (pos = node->count;
                      (val < node->val[pos] && pos > 1); pos--);
              if (val == node->val[pos]) {
                      //printf("Duplicates not allowed\n");
                      return 0;
              }
      }
      if (setValueInNode(val, pval, node->link[pos], child)) {
              if (node->count < MAX) {
                      addValToNode(*pval, pos, node, *child);
              } else {
                      splitNode(*pval, pval, pos, node, *child, child);
                      return 1;
              }
      }
      return 0;
}

/* insert val in B-Tree */
void insertion(long long int val) {
      int flag;
      long long int i;

      struct btreeNode *child;

      flag = setValueInNode(val, &i, root, &child);
      if (flag)
              root = createNode(i, child);
}

/* copy successor for the value to be deleted */
void copySuccessor(struct btreeNode *myNode, int pos) {
      struct btreeNode *dummy;
      dummy = myNode->link[pos];

      for (;dummy->link[0] != NULL;)
              dummy = dummy->link[0];
      myNode->val[pos] = dummy->val[1];

}

/* removes the value from the given node and rearrange values */
void removeVal(struct btreeNode *myNode, int pos) {
      int i = pos + 1;
      while (i <= myNode->count) {
              myNode->val[i - 1] = myNode->val[i];
              myNode->link[i - 1] = myNode->link[i];
              i++;
      }
      myNode->count--;
}

/* shifts value from parent to right child */
void doRightShift(struct btreeNode *myNode, int pos) {
      struct btreeNode *x = myNode->link[pos];
      int j = x->count;

      while (j > 0) {
              x->val[j + 1] = x->val[j];
              x->link[j + 1] = x->link[j];
      }
      x->val[1] = myNode->val[pos];
      x->link[1] = x->link[0];
      x->count++;

      x = myNode->link[pos - 1];
      myNode->val[pos] = x->val[x->count];
      myNode->link[pos] = x->link[x->count];
      x->count--;
      return;
}

/* shifts value from parent to left child */
void doLeftShift(struct btreeNode *myNode, int pos) {
      int j = 1;
      struct btreeNode *x = myNode->link[pos - 1];

      x->count++;
      x->val[x->count] = myNode->val[pos];
      x->link[x->count] = myNode->link[pos]->link[0];

      x = myNode->link[pos];
      myNode->val[pos] = x->val[1];
      x->link[0] = x->link[1];
      x->count--;

      while (j <= x->count) {
              x->val[j] = x->val[j + 1];
              x->link[j] = x->link[j + 1];
              j++;
      }
      return;
}

/* merge nodes */
void mergeNodes(struct btreeNode *myNode, int pos) {
      int j = 1;
      struct btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

      x2->count++;
      x2->val[x2->count] = myNode->val[pos];
      x2->link[x2->count] = myNode->link[0];

      while (j <= x1->count) {
              x2->count++;
              x2->val[x2->count] = x1->val[j];
              x2->link[x2->count] = x1->link[j];
              j++;
      }

      j = pos;
      while (j < myNode->count) {
              myNode->val[j] = myNode->val[j + 1];
              myNode->link[j] = myNode->link[j + 1];
              j++;
      }
      myNode->count--;
      free(x1);
}

/* adjusts the given node */
void adjustNode(struct btreeNode *myNode, int pos) {
      if (!pos) {
              if (myNode->link[1]->count > MIN) {
                      doLeftShift(myNode, 1);
              } else {
                      mergeNodes(myNode, 1);
              }
      } else {
              if (myNode->count != pos) {
                      if(myNode->link[pos - 1]->count > MIN) {
                              doRightShift(myNode, pos);
                      } else {
                              if (myNode->link[pos + 1]->count > MIN) {
                                      doLeftShift(myNode, pos + 1);
                              } else {
                                      mergeNodes(myNode, pos);
                              }
                      }
              } else {
                      if (myNode->link[pos - 1]->count > MIN)
                              doRightShift(myNode, pos);
                      else
                              mergeNodes(myNode, pos);
              }
      }
}

/* delete val from the node */
int delValFromNode(long long int val, struct btreeNode *myNode) {
      int pos, flag = 0;
      if (myNode) {
              if (val < myNode->val[1]) {
                      pos = 0;
                      flag = 0;
              } else {
                      for (pos = myNode->count;
                              (val < myNode->val[pos] && pos > 1); pos--);
                       if (val == myNode->val[pos]) {
                              flag = 1;
                      } else {
                              flag = 0;
                      }
              }
              if (flag) {
                      if (myNode->link[pos - 1]) {
                              copySuccessor(myNode, pos);
                              flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
                              if (flag == 0) {
                                      //printf("Given data is not present in B-Tree\n");
                              }
                      } else {
                              removeVal(myNode, pos);
                      }
              } else {
                      flag = delValFromNode(val, myNode->link[pos]);
              }
              if (myNode->link[pos]) {
                      if (myNode->link[pos]->count < MIN)
                              adjustNode(myNode, pos);
              }
      }
      return flag;
}

/* delete val from B-tree */
void deletion(long long int val, struct btreeNode *myNode) {
      struct btreeNode *tmp;
      if (!delValFromNode(val, myNode)) {
              //printf("Given value is not present in B-Tree\n");
              return;
      } else {
              if (myNode->count == 0) {
                      tmp = myNode;
                      myNode = myNode->link[0];
                      free(tmp);
              }
      }
      root = myNode;
      return;
}

/* search val in B-Tree */
void searching(long long int val, int *pos, struct btreeNode *myNode) {
      if (!myNode) {
              return;
      }

      if (val < myNode->val[1]) {
              *pos = 0;
      } else {
              for (*pos = myNode->count;
                      (val < myNode->val[*pos] && *pos > 1); (*pos)--);
              if (val == myNode->val[*pos]) {
                      //printf("Given data %lli is present in B-Tree\n", val);
                      return;
              }
      }
      searching(val, pos, myNode->link[*pos]);
      return;
}

/* Procura o índice */
void buscaIndice(long long int val, int *pos, struct btreeNode *myNode, long long int *v) {
      if (!myNode) {
              return;
      }

      if (val < (myNode->val[1])/100000) {
              *pos = 0;
      } else {
              for (*pos = myNode->count;
                      (val < (myNode->val[*pos]/100000) && *pos > 1); (*pos)--);
              if (val == (myNode->val[*pos]/100000)) {
                      //printf("Given data %d is present in B-Tree", val);
                      *v = myNode->val[*pos];
                      return;
              }
      }
      buscaIndice(val, pos, myNode->link[*pos], v);
      return;
}

/* B-Tree Traversal */
void traversal(struct btreeNode *myNode) {
      int i;
      if (myNode) {
              for (i = 0; i < myNode->count; i++) {
                      traversal(myNode->link[i]);
                      printf("%lli ", myNode->val[i + 1]);
              }
              traversal(myNode->link[i]);
      }
}

/*
int main() {
      int val, ch;
      while (1) {
              printf("1. Inserção\t2. Deletar\n");
              printf("3. Procurar\t4. Mostrar\n");
              printf("5. Sair\nEntre com a opcao:");
              scanf("%d", &ch);
              switch (ch) {
                      case 1:
                              printf("Entre com o elemento a ser inserido:");
                              scanf("%d", &val);
                              insertion(val);
                              break;
                      case 2:
                              printf("Entre com o elemento que deseja remover:");
                              scanf("%d", &val);
                              deletion(val, root);
                              break;
                      case 3:
                              printf("Entre com o elemento que deseja procurar");
                              scanf("%d", &val);
                              searching(val, &ch, root);
                              break;
                      case 4:
                              traversal(root);
                              break;
                      case 5:
                              exit(0);
                      default:
                              printf("Voce entrou com uma opcao invalida!!\n");
                              break;
              }
              printf("\n");
      }
}
*/
