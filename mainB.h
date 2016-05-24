#define MaxBufferConfig 50
#define MaxBufferHeader 100
#define MaxBufferHeaderInd 5000
#define MaxBuffer 10000
#define MaxNameEnt 20

typedef struct{
    char nomeEntidade[MaxNameEnt];
    int qtdCampos;
    int tamHeader;
    char **campo;#define MaxBufferConfig 50
#define MaxBufferHeader 100
#define MaxBufferHeaderInd 5000
#define MaxBuffer 10000
#define MaxNameEnt 40

typedef struct{
    int qtdCampos,
    	tamHeader,
    	*tamanhos,
    	*null?,
    	autoIncrement?;
    char 	**campo,
    		**tipo;
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
    char **tipo;
    int *tamanhos;
    int **PK;
    
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
