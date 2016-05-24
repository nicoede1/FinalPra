#define MaxBufferConfig 50
#define MaxBufferHeader 100
#define MaxBufferHeaderInd 5000
#define MaxBuffer 10000

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


void lerConfig(FILE *arqConfig, char *config);
void createHeader();

void createInd();
int menuCrud(int opcE);
