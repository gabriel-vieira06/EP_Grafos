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



int main()
{
     
	recebeArquivo();
	
	return 0;
	
}	// Fim main

void recebeArquivo()
{    
	char nomeArquivo[50] = "digrafo.txt";
	FILE *arquivo;
	
	int** arcos;
	double* custos;
	int n,m,s,t,i,j;
	
	/*
	printf("\n\tDigite o nome e extensao do arquivo a ser lido: ");
	scanf("%s%*c", nomeArquivo);
	*/
	
	arquivo = fopen(nomeArquivo, "rt");
	
	if(arquivo == NULL)
	{
		printf("\n\n\tArquivo nao encontrado.\n");
		return;
	}
	
	fscanf(arquivo,"%d %d %d %d", &n, &m, &s, &t);
	
	// Recebe os arcos e custos a partir do arquivo aberto
	
	arcos = malloc(sizeof (int*) * m);
	custos = malloc(sizeof (double) * m);
	
	if (arcos == NULL || custos == NULL){
		printf("\n\n\tMemória insuficiente.");
		return;	// Falta de memoria.
	}
	for (i = 0; i < m; i++)
	{
		arcos[i] = malloc(sizeof(int) * 2);
		if (arcos[i] == NULL)		// Falta de memoria.
		{
			for (j = 0; j < i; j++) free (arcos[j]);
			free (arcos);
			printf("\n\n\tMemória insuficiente.");
			return;
		}
	}
	
	for(i = 0; i < m; i++)
	{
		for(j = 0; j <= 2; j++)
		{
			if(j != 2){
				fscanf(arquivo,"%d", &arcos[i][j]);	// Recebe um vertice do arco
			}else{
				fscanf(arquivo,"%lf", &custos[i]);	// Recebe o custo do arco
			}	
	 	}
	}
	
	algoritmoDijkstra(); //[WIP]
	
	/* Testa se os valores foram recebidos devidamente
	for(i = 0; i < m; i++)
	{
		for(j = 0; j <= 2; j++)
		{
			printf("\n");
			if(j != 2){
				printf("%d ", arcos[i][j]);
			}else{
				printf("%.1lf ", custos[i]);
			}	
	 	}
	}
	*/
	
	for (i = 0; i < m; i++) free(arcos[i]);
	free(arcos);
	free(custos);
	
	fclose(arquivo);
	
}	// Fim recebeArquivo

void algoritmoDijkstra(){ //[WIP]
	
	printf("Implementar Dijkstra...");
	
}	// Fim algoritmoDijkstra
