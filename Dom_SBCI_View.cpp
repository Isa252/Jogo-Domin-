//DOM_SBCI_View.cpp - Projeto Domino
//12/08/2023
//Grupo: SBCI

#include "Dom_SBCI_View.h"


//funcao que mostra todas as pecas
void mostraT(tipoP Pe[28])
{
	
	for(int l = 0; l< 28; l++)
		printf("(%d|%d)\t", Pe[l].lado1, Pe[l].lado2);
	printf("\n\n\n");
}
//funcao que mostra as pecas de cada jogador
void mostraJ(tipoP Pe[28], char jogador)
{
	int i=0;
	printf("\npecas do jogador %c:\n", jogador);
	for(int l = 0; l< 28; l++)
	  if(Pe[l].status== jogador)
	    {
	    i++	;
	    printf("%d.(%d|%d)\t",i, Pe[l].lado1, Pe[l].lado2);	
		}
		

	printf("\n");
}
//funcao que mostra um menu e retorna a opção escolida pelo usuario
int menu()
{
  int op;
  do{
  	printf("\t\tMenu\n\n");
    printf("1-Iniciar Jogo(2 Jogadores)\n");
    printf("2-Iniciar Jogo(Contra o computador)\n");
    printf("3-Retornar ao jogo interrompido\n");
    printf("4-Regras Gerais do jogo\n");
    printf("5-Sair do Programa\n");
    printf("6-Recuperar Jogo anterior\n");
    printf("Digite a op%c%co: ",135,198);
    scanf("%d",&op);

    system("cls");
    if(op<1||op>7)
      printf("\t   Op%c%co Inv%clida\n\n",135,198,160);

  
  }while(op<1||op>7);
  
  return op;
}
//funcao que mostra a mesa
void mostraM(tipoM Me[28])
  {
  if(qtmesa==1)
    if(jvez=='1')
      printf("\nA primeira jogada foi do jogador 2\n\n");
    else
      printf("\nA primeira jogada foi do jogador 1\n\n");
  if(qtmesa==2&&jvez=='1')
    printf("\nA primeira jogada foi do jogador 1(automatica) e a segunda foi do computador\n\n");
  if(comp==1)
    printf("\n\t\tO jogador 2 e o computador\n\n");
  printf("===========================================================================================================\n");
  printf("MESA:  ");
  for(int i=0;i<qtmesa;i++)
    printf("[%d|%d] ", Me[i].ladoE,Me[i].ladoD);
  printf("\n===========================================================================================================\n");
  }
  //funcao que mostra um menu para cada jogador e retorna a opcao escolida
int menuJ()
  {
  int op;
  printf("\n\n1-Jogar");
  printf("\n2-Comprar");
  printf("\n3-Passar");
  printf("\n4-Sair(interromper jogo)");
  printf("\n5-Salvar Jogo\n");
  printf("Opcao:");
  scanf("%d",&op);
  return op;
  }

//funcao que interpreta a opcao escolida pelo jogador e apresenta na tela o que for necesssario	  
int jogar(char jogador)
  {
  char op;
  mostraM(mesa);
  mostraJ(peca,jogador);
  if(jvez=='1'||comp==0)
  {
  op = menuJ();
  switch(op)
    {
  	case 1: 
  	    int p,in;
  	    char l;
  	    printf("Escolha a peca a ser jogada:");
  	    scanf("%d",&p);
  	    in=escolherpeca(peca,p,jogador);
  	    if((in <= 28) && testaE(in, peca))
  	    {
  	    	if(mesaE == mesaD||(peca[in].lado1==mesaD&&peca[in].lado2==mesaE)||(peca[in].lado2==mesaD&&peca[in].lado1==mesaE))
  	      {
  	      printf("Escolha o lado da mesa:");
  	      fclear();
  	      scanf("%c",&l);	
  	      if(l=='E'||l=='e')
  	         carregamesaE(escolherpeca(peca,p,jogador));
		  else if(l == 'D' || l == 'd')
		    carregamesaD(escolherpeca(peca,p,jogador));
		    else
		    {
	  	      system("cls");
	  	      printf("lado inv%clido",160);
			}
		    	
	      }
	      
		else
			testaL(escolherpeca(peca,p,jogador));
		  }
  	    else
  	      {
  	      system("cls");
  	      printf("\tpe%ca inv%clida\n", 135, 160);	
		  }
  	    	
        break;
   case 2:
   	    system("cls");
   	    comprar(jvez);
   	    
   	    break;
   	case 3:	
   		system("cls");
   		if (testaP(jvez)==1 && contagem('0',peca)==0)
   		    {
   		    jvez=(jvez=='1')?'2':'1';
   		    passa=passa+1;
			}
   		else
   		  printf("\tNao e possivel passar a jogada\n\n");
   		break;
   	case 4:
   		f=0;
   		system("cls");
   		break;
   	case 5:
   		system("cls");
   		gravaCadastro();
   		printf("\n\tjogo salvo\n");
   		break;
   	default:
   		 system("cls");
         printf("\t   Op%c%co Inv%clida\n\n",135,198,160);
         break;
   }	
  }
  else
    {
    int in=Escomp(peca);
    op=1;
    while(Escomp(peca)==-1&&contagem('0',peca)!=0)
      {
      comprar('2');
	  }
	in=Escomp(peca);  
    if(Escomp(peca)!=-1)
      
      testaL(in);
    else
      {
      op=3;
      system("cls");
      jvez=(jvez=='1')?'2':'1';
   	  passa=passa+1;
	  }
      
	}
   return op;
  }
  //funcao que permite o jogador escolher uma peca
int escolherpeca(tipoP Pe[28],int pe, char jogador)
  {
  	int i=0 ;
    for(int l = 0; l< 28; l++)
             if(Pe[l].status== jogador)
               {
               	i++;
			    if(i==pe)
			      return l;
			   }
  }
//funcao que permite o controller apresentar uma mensagem
void apresentaMensagem(char msg[100])
  {
  printf("%s\n",msg);
  }
//funcao que retorna o ganhador da partida
void ganhador(char jogador1, char jogador2)
  {
  int jog1=0,jog2=0, v=1;
  char ganhador;
  jog1=contagem('1',peca);
  jog2=contagem('2',peca);
  if(jog1>jog2)
    ganhador = '2';	
    
    
  else if(jog2>jog1)
    ganhador = '1';
  
  else
    {
    for(int i=0;i<28;i++)
      {
       if(peca[i].status=='1')
        jog1 = jog1 + peca[i].lado1 + peca[i].lado2;
       else if(peca[i].status=='2')
        jog2 = jog2 + peca[i].lado1 + peca[i].lado2;
	  }
	if(jog1>jog2)
      ganhador = '2';
    
    if(jog2>jog1)
      ganhador = '1';
    v=1;
	}
   if(v==1)
   printf("\t\tParabens, jogador %c!! O deposito esta vazio e voce ganhou por ter menos pecas\n\n",ganhador);
   if(v==2)
   printf("\t\tParabens, jogador %c!! O deposito esta vazio e voce ganhou por ter menos pontos\n\n",ganhador);
  }
  //funcao que apresenta as regras
  void apresentaregras()
  {
  	printf("\n*******************************************************************************************************************************************************************************************************************************************************************************************************************************\n");
  	printf("\n\tRegras Gerais:\t\n");
  	printf("\n\nCada jogador inicia com sete pecas obtidas aleatoriamente e pode comprar quantas vezes for necessario sempre que precisar de uma peca para poder jogar. ");
  	printf("O jogo inicia-se com o jogador que tiver a peca com o valor mais alto.\nO jogo acontece no sentido anti-horario e os jogadores devem colocar pecas que tenham os mesmos numeros das pecas que se encontram nas pontas do jogo, de forma que os pontos de um dos lados coincidam com os da extremidade onde esta sendocolocada.");
  	printf("\nAntes de cada jogada o jogador pode comprar quantas pecas quiser do deposito de pecas ainda disponiveis, lembrando sempre que perde a partida aquele que no final tiver maior quantidade de pecas.\n");
  	printf("A partida continua com os jogadores colocando suas pecas sobre a mesa ate que o estoque de pecas disponiveis a serem compradas esteja vazio e alem disso, ainda se apresente alguma das seguintes situacoes:\n");
  	printf("Quando um jogador coloca sua ultima pedra na mesa, essa acao e chamada de bater e ele torna-se o vencedor do jogo...\n");
  	printf("Existem casos onde nenhum dos jogadores pode continuar a partida. Isto ocorre quando nenhum dos jogadores tem peca possivel de ser lancada na mesa e tambem o deposito de pecas a comprar esta vazio. Vence aquele que tiver menos pecas.\n\n");
    printf("\n*******************************************************************************************************************************************************************************************************************************************************************************************************************************\n");
  }
  
