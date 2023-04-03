/*
	Integrantes da equipe:
	
	- Gabriel Vieira Cavalcante
	- Luiz Matheus Sena Macedo
	- 
	- 
*/

#include <stdio.h>
#include <stdlib.h>

// Funcoes primarias

void recebeArquivo();	//[WIP]
void algoritmoDijkstra(); //[WIP]

// Funcoes auxiliares

int** criaDigrafo(); //[WIP]


int main()
{
     
	recebeArquivo();
	
	return 0;
	
} // Fim main

void recebeArquivo()
{    
	char nomeArquivo[50];
	FILE *arquivo;
	int n,m,s,t;
	
	printf("\n\tDigite o nome e extensao do arquivo a ser lido: ");
	scanf("%s%*c", nomeArquivo);
	
	arquivo = fopen(nomeArquivo, "rt");
	
	if(arquivo == NULL)
	{
		printf("\n\n\tArquivo nao encontrado.\n");
		return;
	}
	
	fscanf(arquivo,"%d %d %d %d", &n, &m, &s, &t);
	
	// TESTA SE OS VALORES FORAM RECEBIDOS CORRETAMENTE
	printf("%d %d %d %d", n, m, s, t);
	
	fclose(arquivo);
	
}
