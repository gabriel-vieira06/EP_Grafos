/*
	Integrantes da equipe:
	
	- Gabriel Vieira Cavalcante
	- Luiz Matheus Sena Macedo
	- 
	- 
*/

// ------------------------------
// Bibliotecas
// ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ------------------------------
// Constantes
// ------------------------------
#define INF INT_MAX 		// Valor infinito para representar distâncias não alcançáveis
#define MAX_VERTICES 100	// Numero maximo de vertices do grafo

// ------------------------------
// Estruturas
// ------------------------------

//Define um nodo da lista de adjacencia
typedef struct nodoListaAdj{	
    int destino;
    double peso;
    struct nodoListaAdj *prox;
} NodoListaAdjacencia;

// Define a lista de adjacencia
typedef struct {
	int numeroVertices;
    NodoListaAdjacencia *cabecalho[MAX_VERTICES];
} Digrafo;

// ------------------------------
// Funcoes primarias
// ------------------------------
void algoritmoDijkstra(); //[WIP]

// ------------------------------
// Funcoes auxiliares
// ------------------------------
void recebeArquivo();
void inicializarDigrafo(Digrafo *grafo, int numeroVertices);
void adicionarArco(Digrafo *grafo, int origem, int destino, int peso);
void imprimir_digrafo(Digrafo *grafo);	// Funcao temporaria

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
	Digrafo digrafo;
	
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
	
	if (arcos == NULL || custos == NULL)
	{
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
			if(j != 2)
			{
				fscanf(arquivo,"%d", &arcos[i][j]);	// Recebe um vertice do arco
			}else{
				fscanf(arquivo,"%lf", &custos[i]);	// Recebe o custo do arco
			}	
	 	}
	}
	
	// Criacao do digrafo a partir dos dados recebidos do arquivo

	inicializarDigrafo(&digrafo, n);
	for(i = 0; i < m; i++) adicionarArco(&digrafo, arcos[i][0], arcos[i][1], custos[i]);
	imprimir_digrafo(&digrafo);
	
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

void algoritmoDijkstra()	//[WIP]
{
	
	printf("Implementar Dijkstra...");
	
	
}	// Fim algoritmoDijkstra

void inicializarDigrafo(Digrafo *grafo, int numeroVertices)
{
	int i;
	grafo->numeroVertices = numeroVertices;
    for (i = 0; i < numeroVertices; i++) grafo->cabecalho[i] = NULL;
}

void adicionarArco(Digrafo *grafo, int origem, int destino, int peso)
{
	NodoListaAdjacencia *novoNodo = malloc(sizeof(NodoListaAdjacencia));
    novoNodo->destino = destino;
    novoNodo->peso = peso;
    novoNodo->prox = grafo->cabecalho[origem-1];	// i-1 porque o primeiro vertice tem valor 1, mas sera indexado a partir do 0
    grafo->cabecalho[origem-1] = novoNodo;
}

void imprimir_digrafo(Digrafo *grafo) {
	int i;
	NodoListaAdjacencia *nodoAtual;
	
    for ( i = 0; i < grafo->numeroVertices; i++) {
        printf("Adjacentes do vertice %d: ", i+1);	// i+1 porque o primeiro vertice tem valor 1, mas esta indexado a partir do 0
        nodoAtual = grafo->cabecalho[i];
        while (nodoAtual != NULL) {
            printf("%d ", nodoAtual->destino);
            nodoAtual = nodoAtual->prox;
        }
        printf("\n");
    }
}

