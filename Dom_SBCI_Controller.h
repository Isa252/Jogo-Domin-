//DOM_SBCI_Controller.h - Projeto Domino
//12/08/2023
//Grupo: SBCI


void criaP(tipoP Pe[28]);
void embaralhaP(tipoP Pe[28]);
void darP (tipoP Pe[28]);
int primJo(tipoP Pe[28]);
char primeirajogada(int pos, tipoP Pe[28], tipoM mes[28]);

void iniciarP();
void executarMenu();
void iniciarjogo();
//void jogar();
void carregamesaE(int pj);
void carregamesaD(int pj);
void fclear();
void comprar(char jogador);
int contagem(char jogador,tipoP Pe[28]);
int testaP(char jogador);
int testaE(int es, tipoP Pe[28]);
void gravaCadastro();
void recuperaCadastro();
void retornaJ();
int Escomp(tipoP peca[28]);

