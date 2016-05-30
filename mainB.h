#define MaxBufferConfig 50
#define MaxBufferHeader 100
#define MaxBufferHeaderInd 5000
#define MaxBuffer 10000
#define MaxNameEnt 20

/*
typedef struct{
    int qtdCampos,
    	tamHeader,
    	*tamanhos,
    	*null,
    	autoIncrement;
    char 	**campo,
    		**tipo;
    char nomeEntidade[100];
}Tabela;
*/

typedef struct{
    int tamHeader;
    //char nomeEntidade[100];
    int qtdCampos;
    char campos[6][30];
    int tamanhos[6];
    char tipos[6][4];
    int null[6];
    int autoInc[6];
    int nPk;
    char pk[3][10]; 
}Tabela;

void inserir(int opcE);
void excluir(int opcE);
void atualizar(int opcE);
void buscar(int opcE);
int menuCrud(int opcE);

Tabela lerHeader(FILE *arqEnt);


void lerConfig(FILE *arqConfig, char *config);
void createHeader();

void createInd();
int menuCrud(int opcE);

