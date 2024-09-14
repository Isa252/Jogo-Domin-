//DOM_SBCI_Controller.cpp - Projeto Domino 
//12/08/2023
//Grupo: SBCI

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Dom_SBCI_Controller.h"
#include "Dom_SBCI_View.cpp"

//funcao que cria as pecas
void criaP(tipoP Pe[28])
{
	
	int i, j;
	int k = 0;

	for(i = 0; i< 7; i++)
		for (j = i; j < 7; j++)
			{
			
				Pe[k].lado1 = i;
				Pe[k].lado2 = j;
				Pe[k].status = '0';
				k++;
			}
}

//funcao que embaralha as pecas
void embaralhaP(tipoP Pe[28])
{
	tipoP aux;
	int k, seed;
	
	
	srand(time(NULL));
	
	for(k = 0; k < 28; k++)
	{
		seed = (rand()%28);
		aux = Pe[k];
		Pe[k] = Pe[seed];
		Pe[seed] = aux;
	}
}
//funcao que distribui as pecas para cada jogador
void darP (tipoP Pe[28])
{
	for(int k = 0; k < 7; k++)
		{
			Pe[k].status = '1';
			Pe[k+7].status = '2';
		}
	for(int a=14; a<28; a++)
	  Pe[a].status = '0';
	
}

//essa funcao retorna a posicao da primeira peca a ser jogada
int primJo(tipoP Pe[28])
{
	int i=-1,s=0,a;
	tipoP maiorp;
	maiorp.lado1=-1;
	maiorp.lado2=-1;
 	for(a=0;a<14;a++)
	  if(Pe[a].lado1==Pe[a].lado2)
	    if(Pe[a].lado1>=maiorp.lado1)
	      {
	      maiorp.lado1=Pe[a].lado1;
	      maiorp.lado2=Pe[a].lado2;
	      i=a;
		  }
	if(i!=-1)
	  return i;
	else
	  {
	  for(a=0;a<14;a++)
	    if(Pe[a].lado1+Pe[a].lado2>s)
	      s = Pe[a].lado1+Pe[a].lado2;
	      i=a;
	  }
	return a;
}

//essa funcao retorna de quem sera o primeiro jogador e atualiza a mesa com a primeira peca
char primeirajogada(int pos, tipoP Pe[28], tipoM mes[28])
{
	char jvez;
	mes[0].ladoE = Pe[pos].lado1;
	mes[0].ladoD = Pe[pos].lado2;
	mesaE = Pe[pos].lado1;
	mesaD = Pe[pos].lado2;
	if(Pe[pos].status == '1')
		jvez = '2';
	else
		jvez = '1';
	Pe[pos].status = 'm';
	qtmesa = 1;
	return jvez;
}

//funcao cria as pecas, mostra todas as pecas, as embaralha e as mostra novamente
void iniciarP()
{
	criaP(peca);
	mostraT(peca);
	embaralhaP(peca);
	mostraT(peca);
}
//funcao que interpreta a opcao escolida pelo usuario
void executarMenu()
{
	int op;
	do{
	
	op = menu();
	switch(op)
	    {
	  case 1: 
	    comp=0;
		iniciarjogo();
		break;
	  case 2:
	  	comp=1;
	  	iniciarjogo();
		break;
	  case 3:
	  	recuperaCadastro();
	  	apresentaMensagem("\tretornando ao jogo recuperado");
	  	retornaJ();
		break;
	  case 4:
	   apresentaregras();
	  	break;
	  case 5:
	  	break;
	  case 6:
	  	recuperaCadastro();
	  	apresentaMensagem("\t\tJogo recuperado\n");
        }     	
	}while(op!=5);
	 
}
//funcao que inicia o jogo
void iniciarjogo()
{
	char jant;
	darP (peca);
	passa=0;
	jvez = primeirajogada(primJo(peca), peca, mesa);
    f=1;
	char ganha;
	 while(f==1) 
	  {
	  jant=(jvez=='1')?'2':'1';
	  if(jogar(jvez) == 4)
	    f=0;
	  if((contagem(jvez, peca)== 0 && contagem('0', peca)== 0)||(passa==2))
	    {
	    ganhador('1','2');
	    f=0;
		}
	  }
	  comp=0;
      embaralhaP(peca);
}
//funcao que coloca uma peca escolhida pelo jogador no lado esquerdo da mesa
void carregamesaE(int pj)
  {
  	
  	  for(int i=qtmesa;i>0;i--)
       mesa[i]=mesa[i-1];
  
  	if(peca[pj].lado2==mesaE)
      {
      mesa[0].ladoD=peca[pj].lado2;
	  mesa[0].ladoE=peca[pj].lado1;
	  }
    else
      {
      mesa[0].ladoD=peca[pj].lado1;
      mesa[0].ladoE=peca[pj].lado2;	
	  } 
      mesaE=mesa[0].ladoE;
      qtmesa++;
      peca[pj].status='m';
      passa=0;
      jvez=(jvez=='1')?'2':'1';
      system("cls");
	    }
 
  //funcao que coloca uma peca escolida pelo jogador no lado direito da mesa
void carregamesaD(int pj)
    {
  	  if(peca[pj].lado2==mesaD)
      {
      mesa[qtmesa].ladoD=peca[pj].lado1;
	  mesa[qtmesa].ladoE=peca[pj].lado2;
	  }
      else
      {
      mesa[qtmesa].ladoD=peca[pj].lado2;
      mesa[qtmesa].ladoE=peca[pj].lado1;	
	  }
      mesaD=mesa[qtmesa].ladoD;
      qtmesa++;
      peca[pj].status='m';
      jvez=(jvez=='1')?'2':'1';
      passa=0;
      system("cls");
	}
  
void fclear()
  {
  int ch;
  while((ch=fgetc(stdin))!=EOF&&ch!='\n');
  }
  //funcao que permite o jogador comprar uma peca 
void comprar(char jogador)
  {
  int i=14;
  while(i<28)
    {
    if(peca[i].status=='0')
      {
      peca[i].status=jogador;
      break;
	  }
	i++;
	}
  if(i>=28)
    apresentaMensagem("Nada para comprar");
  }
  //funcao que conta a quantidade de pecas de um jogador
int contagem(char jogador,tipoP Pe[28])
  {
  int c = 0;  
  for(int i=0;i<28;i++)
    {
    if(Pe[i].status==jogador)
    c++;
	}
  return c;
  }
  //funcao que testa o lado da peca escolida pelo jogador
  void testaL(int pj)
  {
  	if(peca[pj].lado1 == mesaD || peca[pj].lado2 == mesaD)
  		carregamesaD(pj);
	else if(peca[pj].lado1 == mesaE || peca[pj].lado2 == mesaE)
  		carregamesaE(pj);
	else 
	  {
  	  system("cls");
  	  apresentaMensagem("\t\tPECA INVALIDA\n");
  	  }	
  }
  //funcao que testa a peca escolhida pelo jogador
int testaP(char jogador)
  {
  int p=1;
  for(int i=0; i<28;i++)
    if(peca[i].status==jogador)
      {
      if(peca[i].lado1==mesaE||peca[i].lado2==mesaE||peca[i].lado1==mesaD||peca[i].lado2==mesaD)
        p=0;
	  }
  return p;
  }
  //funcao que testa a escolha de peca do jogador
 int testaE(int es, tipoP Pe[28])
 {
 	int ver = 0;
 	if(Pe[es].status == jvez)
	 	if(Pe[es].lado1 == mesaE || Pe[es].lado1 == mesaD || Pe[es].lado2 == mesaE || Pe[es].lado2 == mesaD)
 			ver = 1;
 	return ver;
 }
 //funcao que salva o jogo
void gravaCadastro()
 {
 	if(qtmesa==0)
 	{
 		apresentaMensagem("Sem jogo a ser gravado");
 		return;
	 }
	 if(f==0)
	 {
	 	apresentaMensagem("Jogo terminado nao pode ser gravado");
	 	return;
	 }
	
	int i;
	FILE *fp;
	FILE *fpm;
	FILE *fps;
	
	sitJogo.qtmesaJogo = qtmesa;
	sitJogo.jogadorJogo = jvez;
	sitJogo.jogadorComp = comp;
	sitJogo.mesaDJogo = mesaD;
	sitJogo.mesaEJogo = mesaE;
	
	if(( fp = fopen ("CAD_DOMINO", "w")) == NULL)
	{
		apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto para cadastrar");
		return;
	}
	
	if ((fpm= fopen("CAD_MESA", "w"))== NULL)	
	{
		apresentaMensagem("O arquivo CAD_MESA nao pode ser aberto para cadastrar");
		return;
	}
	
	if ((fps=fopen("CAD_JOGO", "w"))==NULL)
	{
		apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto para cadastrar");
		return;
	}
	
	for (i=0;i<28;i++)
	{
	   if (fwrite(&peca[i], sizeof(struct pc), 1, fp) !=1)
	   {
	   	    apresentaMensagem("Erro na grvacao do arquivo CAD_DOMINO");
	   	    break;
	   }
	}
	
	for (i=0; i<28; i++)
	{
		if(fwrite(&mesa[i], sizeof(struct Mesa), 1, fpm) !=1)
		{
			apresentaMensagem("Erro na grvacao do arquivo CAD_MESA");
	   	    break;
		}
	}
	
	if (fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) !=1)
	    apresentaMensagem("Erro na grvacao do arquivo CAD_JOGO");
	
	fclose(fps);
	fclose(fpm);
	fclose(fp);
	apresentaMensagem("Gravados os arquivos CAD_DOMINO, CAD_MESA e CAD_JOGO");  
 }
  //funcao que recupera um jogo salvo
 void recuperaCadastro()
 {
 	int i;
 	FILE * fp;
 	FILE * fpm;
 	FILE * fps;
 	
 	if ((fp=fopen("CAD_DOMINO", "r")) == NULL)
 	{
 		apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto");
 		return;
	}
	
	if ((fpm=fopen("CAD_MESA", "r")) == NULL)
 	{
 		apresentaMensagem("O arquivo CAD_MESA nao pode ser aberto");
 		return;
	}
	
	if ((fps=fopen("CAD_JOGO", "r")) == NULL)
 	{
 		apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto");
 		return;
	}
	
	for(i=0; i<28;i++)
	{
		if (fread(&peca[i], sizeof(struct pc), 1, fp) !=1)
		{
			apresentaMensagem("Erro na leitura do arquivo CAD_DOMINO");
			break;
		}
	}
	
	for(i=0; i<28;i++)
	{
		if (fread(&mesa[i], sizeof(struct Mesa), 1, fpm) !=1)
		{
			apresentaMensagem("Erro na leitura do arquivo CAD_MESA");
			break;
		}
	}
	
	if (fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
	  apresentaMensagem("Erro na leitura do arquivo CAD_JOGO");
	  
	fclose(fps);  
	fclose(fpm);  
	fclose(fp);
	
	qtmesa=sitJogo.qtmesaJogo;
	jvez = sitJogo.jogadorJogo;
	comp = sitJogo.jogadorComp;
	mesaD= sitJogo.mesaDJogo;
	mesaE=sitJogo.mesaEJogo;
	//apresentaMensagem("retornando ao jogo recuperado");  
 }
//funcao que retorna ao jogo
void retornaJ()
  {
	char jant;
	passa=0;
    f=1;
	char ganha;
	 while(f==1) 
	  {
	  jant=(jvez=='1')?'2':'1';
	  if(jogar(jvez) == 4)
	    f=0;
	  if((contagem(jant, peca)== 0 && contagem('0', peca)== 0)||(passa==2))
	    {
	    ganhador('1','2');
	    f=0;
     
		}
	  }
      embaralhaP(peca);
}
  
int Escomp(tipoP peca[28])
{
	int i;
	int o=-1;
	for(i=0; i<28;i++)
      if(peca[i].status==jvez)
        if(peca[i].lado1==mesaE||peca[i].lado2==mesaE||peca[i].lado1==mesaD||peca[i].lado2==mesaD)
          {
          o=i;
          return o; 	
		  }
	return o;  
}
