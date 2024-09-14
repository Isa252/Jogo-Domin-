//DOM_SBCI_Model.cpp - Projeto Domino
//12/08/2023
//Grupo: SBCI

#include "Dom_SBCI_Model.h"

//criacao de uma estrutura de dados que possui informacoes que serao salvas
typedef struct Jogo
{
	int qtmesaJogo; 
	int jogadorJogo;
	int jogadorComp;
	int mesaDJogo;
	int mesaEJogo;
}sJogo; 


typedef struct pc
	{
		int lado1;
		int lado2;
		char status;
	} tipoP;

typedef struct Mesa
{
	int ladoE;
	int ladoD;
} tipoM;

tipoM mesa[28];
	
tipoP peca[28];
tipoP paux;
sJogo sitJogo;





