#ifndef testFinal_H
#define testFinal_H

extern void inserir(int opcE);
extern void excluir(int opcE);
extern void atualizar(int opcE);
extern int buscar(int opcE);
extern int menuCrud(int opcE);
extern void inicializaArvore();
extern FILE* abreEntidade(int opcE);
extern FILE* abreIndice(int opcE);
extern Tabela lerHeader(FILE *arqEnt);
extern void createHeader();

#endif
