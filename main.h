typedef struct{
    int qtdCampos;
    int tamHeader;
    char **campo;
    char **tipo;
    int *tamanhos;
    char nomeEntidade[100];
}Tabela;

void inserir(int opcE, int opcO);
void excluir(int opcE, int opcO);
void atualizar(int opcE, int opcO);
void buscar(int opcE, int opcO);
int menuCrud(int opcE);

void createHeader();
void createInd();
int menuCrud(int opcE);
