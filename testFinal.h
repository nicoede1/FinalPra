#ifndef testFinal_H
#define testFinal_H

extern void inserir(int);
extern void excluir(int);
extern void atualizar(int);
extern int buscar(int);
extern int menuCrud(int);
extern void inicializaArvore();
extern FILE* abreEntidade(int);
extern FILE* abreIndice(int);
extern Tabela lerHeader(FILE *);
extern void createHeader();

#endif
