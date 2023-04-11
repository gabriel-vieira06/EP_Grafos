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
#include <float.h>

// ------------------------------
// Constantes
// ------------------------------
#define INF DBL_MAX 		// Valor infinito para representar distancias não alcancaveis
#define MAX_VERTICES 100	// Numero maximo de vertices do grafo

// ------------------------------
// Estruturas
// ------------------------------

//Define um nodo da lista de adjacencia
typedef struct nodoListaAdj{	
    int destino;
    int origem;
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
void algoritmoDijkstra(Digrafo *grafo, int origem, int destino);

// ------------------------------
// Funcoes auxiliares
// ------------------------------
void recebeArquivo();
void inicializarDigrafo(Digrafo *grafo, int numeroVertices);
void adicionarArco(Digrafo *grafo, int origem, int destino, double peso);
int encontraMenorDistancia(Digrafo *grafo, double *distancia, int *visitados, int verticeAtual);

int main()
{
     
	recebeArquivo();
	
	return 0;
	
}	// Fim main


void recebeArquivo()
{    
	char nomeArquivo[50];
	FILE *arquivo;
	
	int** arcos;
	double* custos;
	int n,m,s,t,i,j;
	Digrafo digrafo;
	
	printf("\n\tDigite o nome e extensao do arquivo a ser lido: ");
	scanf("%s%*c", nomeArquivo);
	
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
				fscanf(arquivo,"%lf", &custos[i]);	// Recebe o custo do arco, consideramos que o custo poderia ser nao-inteiro
			}	
	 	}
	}
	
	// Criacao do digrafo a partir dos dados recebidos do arquivo

	inicializarDigrafo(&digrafo, n);
	for(i = 0; i < m; i++) adicionarArco(&digrafo, arcos[i][0], arcos[i][1], custos[i]);
	
	algoritmoDijkstra(&digrafo, s, t);
	
	for (i = 0; i < m; i++) free(arcos[i]);
	free(arcos);
	free(custos);
	
	fclose(arquivo);
	
	printf("\n\n\t------------------------------");
	printf("\n\t| Pressione ENTER para sair. |");
	printf("\n\t------------------------------");
	getchar();
	
}	// Fim recebeArquivo

int encontraMenorDistancia(Digrafo *grafo, double *distancia, int *visitados, int verticeAtual)
{
    int i, indice = verticeAtual;
    double menorCaminho = INF;
	NodoListaAdjacencia *nodoAtual;
	
	nodoAtual = grafo->cabecalho[verticeAtual-1];
	while (nodoAtual != NULL) 
	{
    	if(!visitados[nodoAtual->destino-1] && nodoAtual->peso + distancia[verticeAtual-1] < menorCaminho)
    	{
    		distancia[nodoAtual->destino-1] = nodoAtual->peso + distancia[verticeAtual-1];
    		menorCaminho = distancia[nodoAtual->destino-1];
    		indice = nodoAtual->destino;
		}
        nodoAtual = nodoAtual->prox;
    }
    
    return indice;
    
}	// Fim encontraMenorDistancia

void algoritmoDijkstra(Digrafo *grafo, int origem, int destino)	//[WIP]
{
	int visitados[grafo->numeroVertices];
	double distancia[grafo->numeroVertices];
	int i, j, verticeAtual = origem;
	
	for(i = 0; i < grafo->numeroVertices; i++)
	{
		distancia[i] = INF;
		visitados[i] = 0;
	}
	
	distancia[origem-1] = 0;
	
	printf("\n\tCaminho minimo do vertice %d para o vertice %d: ", origem, destino);
	
	for(i = 0; i < grafo->numeroVertices; i++)
	{
		while(verticeAtual != destino)
		{
			printf("(%d, ", verticeAtual);
			verticeAtual = encontraMenorDistancia(grafo, distancia, visitados, verticeAtual);
			printf("%d) ", verticeAtual);
		}
	}
	
	printf("\n\n\tCusto: %.2lf", distancia[destino-1]);
	
}	// Fim algoritmoDijkstra

void inicializarDigrafo(Digrafo *grafo, int numeroVertices)
{
	int i;
	grafo->numeroVertices = numeroVertices;
    for (i = 0; i < numeroVertices; i++) grafo->cabecalho[i] = NULL;
    
}	// Fim inicializarDigrafo

void adicionarArco(Digrafo *grafo, int origem, int destino, double peso)
{
	NodoListaAdjacencia *novoNodo = malloc(sizeof(NodoListaAdjacencia));
	novoNodo->origem = origem;
    novoNodo->destino = destino;
    novoNodo->peso = peso;
    novoNodo->prox = grafo->cabecalho[origem-1];	// i-1 porque o primeiro vertice tem valor 1, mas sera indexado a partir do 0
    grafo->cabecalho[origem-1] = novoNodo;
    
}	// Fim adicionarArco

