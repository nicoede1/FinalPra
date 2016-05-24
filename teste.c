void lerHeader(char nameEnt){
    int qtdCampos;
    int tamHeader;
    char **campo;
    char **tipo;
    int *tamanhos;
    char nomeEntidade[100];    
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