
void removeEntity(char *nome){
    int ID,qnt_elementos=0,i=0,j,flag=0,qtd_relacoes=0,tam_header,k=0;
    tabela *vet;
    FILE *fp;
    char string[1000],relacao[100],localizacao[100],nome2[100],nome3[100],**localizacoes,**relacoes,*aux;
    puts("Digite o ID do elemento que deseja remover");
    scanf("%i",&ID);
    carrega_entidadeGeral(nome);
    vet=chargeEntity(nome);
    i=0;
    while(vet[i].qtd_campos!=-1){
        qnt_elementos++;
        i++;
    }
    for(i=0;i<qnt_elementos;i++){
        if(ID==atoi(vet[i].campos[1])){
            flag=1;
            break;
        }
    }
    if(flag==0){
        puts("ID da entidade nao encontrado!");
        return;
    }
    else{
        arqGeral=fopen(nome,"rb");
        fread(string,sizeof(char),entidadeGeral.tamanho_header,arqGeral);
        sscanf(string,"qnt=%*i,entidade=[%*s ],qnt_campos=[%*i ],campos=[%*s ],tamanho=[%*s ],tipo=[%*s ],relacao=[%s ],localizacao=[%s ],versao=[%*s ]",relacao,localizacao);
        /*********************************************************************************/
        /*QUEBRANDO QUANTAS RELACOES TEMOS*/
        relacoes=(char **)malloc(sizeof(char *));
        relacoes[i]=(char *)malloc(sizeof(char )*100);
        aux=(char *)strtok(relacao,",");
        if(aux!=NULL){
            strcpy(relacoes[i],aux);
            while(aux!=NULL){
                i++;
                relacoes=(char **)realloc(relacoes,sizeof(char *)*i+1);
                relacoes[i]=(char *)malloc(sizeof(char )*100);
                aux= (char*)strtok(NULL, ",");
                if(aux!=NULL)
                    strcpy(relacoes[i],aux);
            }
        }
        else{
            strcpy(relacoes[i],relacao);
        }
        qtd_relacoes=i;
        /*FIM DA QUEBRA DE RELACOES*/
        /**********************************************************************************/
        /*QUEBRANDO QUANTAS LOCALIZACOES TEMOS*/
        i=0;
        localizacoes=(char **)malloc(sizeof(char *));
        localizacoes[i]=(char *)malloc(sizeof(char )*100);
        aux=(char *)strtok(localizacao,",");
        if(aux!=NULL){
            strcpy(localizacoes[i],aux);
            while(aux!=NULL){
                i++;
                localizacoes=(char **)realloc(localizacoes,sizeof(char *)*i+1);
                localizacoes[i]=(char *)malloc(sizeof(char )*100);
                aux= (char*)strtok(NULL, ",");
                if(aux!=NULL)
                    strcpy(localizacoes[i],aux);
            }
        }
        else{
            strcpy(localizacoes[i],localizacao);
        }
        __fpurge(stdin);
        /*FIM DA QUEBRA DE LOCALIZACOES*/
        /**********************************************************************************/
        /*INICIO DA EXCLUSAO NO ARQUIVO PRINCIPAL*/
        fclose(arqGeral);
        arqGeral=fopen(nome,"wb");
        fwrite(string,sizeof(char),entidadeGeral.tamanho_header,arqGeral);
        for(i=0;i<qnt_elementos;i++){
            for(j=0;j<entidadeGeral.qtd_campos;j++){
                if(ID!=atoi(vet[i].campos[1]))
                    fwrite(vet[i].campos[j],entidadeGeral.tamanhos[j],1,arqGeral);
            }
        }
        fclose(arqGeral);
        /*FIM DA EXCLUSAO NO ARQUIVO PRINCIPAL*/
        /*************************************************************************************/
        /*EXCLUIR DOS ARQUIVOS DE RELACOES*/
        for(k=0;k<qtd_relacoes;k++){
            carrega_entidadeGeral(relacoes[k]);
            vet=chargeEntity(relacoes[k]);
            strcpy(nome2,relacoes[k]);
            strcpy(nome3,relacoes[k]);
            strcat(nome2,".bin");
            rename(relacoes[k],nome2);
            strcat(relacoes[k],".bin");
            if((arqGeral=fopen(relacoes[k],"rb"))!=NULL){
                char auxiliar[1000];
                if((fp=fopen("aux","wb"))!=NULL){
                    fread(auxiliar,sizeof(char),entidadeGeral.tamanho_header,arqGeral);
                    fwrite(auxiliar,sizeof(char),entidadeGeral.tamanho_header,fp);
                    i=0;
                    while(vet[i].qtd_campos!=-1){
                        puts("oi");
                        for(j=0;j<entidadeGeral.qtd_campos;j++){
                            if(ID!=atoi(vet[i].campos[atoi(localizacoes[k])-1]))
                                fwrite(vet[i].campos[j],entidadeGeral.tamanhos[j],1,fp);
                        }
                        i++;
                    }
                }
                fclose(fp);
            }
            fclose(arqGeral);
            remove(nome2);
            rename("aux",nome3);
        }
        /*FIM DE EXCLUIR DOS ARQUIVOS DE RELACOES*/
        /*************************************************************************************/
        /*EXCLUIR DO ARQUIVO DE INDICES*/
        carrega_entidadeGeral(nome);
        ordena(nome);
        /*FIM EXCLUSAO DOS INDICES*/
        /*************************************************************************************/
    }
    puts("Entidade Removida com Sucesso!");
}