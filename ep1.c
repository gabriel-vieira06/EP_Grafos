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
typedef struct {
  int origem, destino;
  double custo;
} Arco;

// ------------------------------
// Funcoes
// ------------------------------
void recebeArquivo();
void esperaResposta();
void algoritmoDijkstra(int num_vertices, int num_arcos, int origem, int destino, Arco *arcos);

int main()
{
	recebeArquivo();
	esperaResposta();
	
	return 0;

}	// Fim main

void recebeArquivo()
{
	/*
		Metodo recebeArquivo
		
		Recebe o nome de um arquivo e sua extensao para entao
		obter as informacoes do digrafo, sendo elas
		- n o numero de vertices
		- m o numero de arcos
		- s o vertice origem
		- t o vertice destino
		- os arcos do digrafo
		- o custo de cada arco do digrafo
		Em seguida realiza a chamada do algoritmo de Dijkstra
	*/
	
	char nomeArquivo[50];
	FILE *arquivo;
	Arco *arcos;
	
	int i;
	int n,m,s,t;
	int u, v;
	double custo;
	
	printf("\n\tDigite o nome e extensao do arquivo a ser lido (Ex: arquivo.txt): ");
	scanf("%s%*c", nomeArquivo);
	
	arquivo = fopen(nomeArquivo, "rt");
	
	if(arquivo == NULL)
	{
		printf("\n\n\tArquivo nao encontrado.\n");
		return;
	}
	
	fscanf(arquivo,"%d %d %d %d", &n, &m, &s, &t);
	
	arcos = malloc(sizeof(Arco) * m);
	
	if (arcos == NULL)	// Falta de memoria.
	{
		printf("\n\n\tMemoria insuficiente.");
		return;
	}
	
	for (i = 0; i < m; i++)
	{
		fscanf(arquivo, "%d %d %lf", &u, &v, &custo); // Le os dados de cada arco
		arcos[i].origem = u - 1;
		arcos[i].destino = v - 1;
		arcos[i].custo = custo;
	}
	
	fclose(arquivo);
	
	algoritmoDijkstra(n, m, s, t, arcos);
	
}	// Fim recebeArquivo

void algoritmoDijkstra(int num_vertices, int num_arcos, int origem, int destino, Arco *arcos)
{
	double *distancia = malloc(sizeof(double) * num_vertices);
	int *anterior = malloc(sizeof(int) * num_vertices);
	int *visitados = malloc(sizeof(int) * num_vertices);
	
	int i, j;
	int u, v, c;
	
	if(distancia == NULL || anterior == NULL || visitados == NULL)
	{
		printf("\n\n\tMemoria insuficiente.");
		return;
	}
	
	for (i = 0; i < num_vertices; i++) 
	{
	    distancia[i] = INF;
	    anterior[i] = -1;
	    visitados[i] = 0;
	}
	
	distancia[origem-1] = 0;
	
	for (i = 0; i < num_vertices - 1; i++)
	{
	    u = -1;
	    for (j = 0; j < num_vertices; j++) 
		{
	      if (!visitados[j] && (u == -1 || distancia[j] < distancia[u])) u = j;
	    }
	    
		visitados[u] = 1;
	    
		for (j = 0; j < num_arcos; j++) 
		{
		    if (arcos[j].origem == u) 
			{
		        v = arcos[j].destino;
		        c = arcos[j].custo;
		        if (distancia[u] + c < distancia[v]) 
				{ 
		          distancia[v] = distancia[u] + c;
		          anterior[v] = u;
	    		}
	    	}
	    }
	}
	
	free(visitados);
	
	if (distancia[destino - 1] == INF) 
	{
	    printf("\n\n\tNao ha caminho entre os vertices %d e %d \n", origem, destino);
	} else {
	    
	    int *lista_impressao = malloc(sizeof(int) * num_vertices);
	    
	    printf("\n\n\tCaminho minimo do vertice %d para o vertice %d: ", origem, destino);
	    
	    u = destino - 1;
	    i = 0;
	    while(anterior[u] != -1)
	    {
	    	lista_impressao[i] = u;
	    	u = anterior[u];
	    	i++;
		}
		
		lista_impressao[i] = origem-1;
		
		for(j = i; j > 0; j--)
		{
			printf("(%d, ", lista_impressao[j]+1);
			printf("%d) ", lista_impressao[j-1]+1);
		}
	    
	    printf("\n\n\tCusto: %0.4lf\n", distancia[destino - 1]);
	}
  
  free(arcos); // Libera a memoria alocada para o vetor de arcos
  free(distancia);  // Libera a memoria alocada para o vetor de diatancia
  free(anterior);

}	// Fim algoritmoDijkstra

void esperaResposta()
{
	
	/*
		Metodo esperaResposta
		
		Simplesmente garante que o programa nao feche e permite a analise dos resultados
		solicitando que o usuário pressione ENTER para encerra-lo.
		
	*/
	
	printf("\n\n\t------------------------------");
	printf("\n\t| Pressione ENTER para sair. |");
	printf("\n\t------------------------------");
	getchar();
	
}	// Fim esperaResposta
