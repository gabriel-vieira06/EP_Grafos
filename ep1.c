/*
	Integrantes da equipe:
	
	- Gabriel Vieira Cavalcante
	- Luiz Matheus Sena Macedo
	- Joao Bruno Rodrigues de Freitas
	- Antonio Cicero Nascimento
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
		printf("\n\n\tArquivo nao encontrado.");
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
		arcos[i].origem = u - 1;	// -1 porque o menor vertice sera 1, mas serao indexados a partir do 0
		arcos[i].destino = v - 1;	// para evitar complicacoes, o indice e vertice serao os mesmos
		arcos[i].custo = custo;
	}
	
	fclose(arquivo);
	
	algoritmoDijkstra(n, m, s, t, arcos);
	
}	// Fim recebeArquivo

void algoritmoDijkstra(int num_vertices, int num_arcos, int origem, int destino, Arco *arcos)
{
	/*
		Metodo algoritmoDijkstra
		
		Dados de entrada:
		- numero de vertices do grafo
		- numero de arcos do grafo
		- vertice origem do problema
		- vertice destino do problema
		- vetor de arcos do digrafo, contendo seus custos
		  e vertices de origem e destino.
		
		Saida: Mostra o caminho minimo entre o vertice
		origem e destino do problema, assim como o seu custo.
	*/
	
	
	double *distancia = malloc(sizeof(double) * num_vertices);	// Vetor para armazenar a menor distancia entre os vertices
	int *anterior = malloc(sizeof(int) * num_vertices);	// Vetor para armazenar o caminho a ser percorrido entre a origem e o destino
	int *visitados = malloc(sizeof(int) * num_vertices);	// Vetor para armazenar os vertices na fronteira marcando-os como visitados
	
	int i, j;
	int u, v;
	double custo;
	
	if(distancia == NULL || anterior == NULL || visitados == NULL)	// Falta memoria
	{
		printf("\n\n\tMemoria insuficiente.");
		return;
	}
	
	for (i = 0; i < num_vertices; i++)	// Marca todos os vertices com distancia infinita e nao visitados
	{
	    distancia[i] = INF;
	    anterior[i] = -1;
	    visitados[i] = 0;
	}
	
	distancia[origem-1] = 0;	// Distancia da origem para ela mesma = 0
	
	for (i = 0; i < num_vertices - 1; i++)
	{
	    u = -1;	// Vertice u
	    for (j = 0; j < num_vertices; j++) 
		{
			// Busca um vertice nao visitado, na primeira iteracoo sera a origem
			// em seguida seram os vertices mais proximos a ela e ligados por arcos
			// de menor custo.
	    	if (!visitados[j] && (u == -1 || distancia[j] < distancia[u])) u = j;
	    }
	    
		visitados[u] = 1;	// Marca o vertice como visitado
	    
		for (j = 0; j < num_arcos; j++)
		{
		    if (arcos[j].origem == u) // Percorre cada arco com origem em u e seleciona o de menor custo
			{
		        v = arcos[j].destino;
		        custo = arcos[j].custo;
		        if (distancia[u] + custo < distancia[v]) 
				{ 
		          distancia[v] = distancia[u] + custo;
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
	    
	    // Variavel auxiliar para formatar a mensagem devidamente
	    int *lista_impressao = malloc(sizeof(int) * num_vertices);
	    
	    if (lista_impressao == NULL)	// Falta de memoria.
		{
			printf("\n\n\tMemoria insuficiente.");
			return;
		}
	    
	    printf("\n\n\tCaminho minimo do vertice %d para o vertice %d: ", origem, destino);
	    
	    u = destino - 1;	// Vertice u e o destino do problema
	    i = 0;
	    
	    while(anterior[u] != -1)	// Enquanto houver vertices no caminho do destino a origem
	    {
	    	lista_impressao[i] = u;	// Armazena o vertice
	    	u = anterior[u];	// u armazena o vertice anterior
	    	i++;
		}
		
		lista_impressao[i] = origem-1;	// Inclui a origem no fim da lista
		
		for(j = i; j > 0; j--)	// Para cada vertice no caminho da origem ao destino, imprime
		{
			printf("(%d, ", lista_impressao[j] + 1);	// +1 para compensar a subtracao feita no metodo recebeArquivo
			printf("%d) ", lista_impressao[j - 1] + 1);
		}
	    
	    free(lista_impressao);
	    
	    printf("\n\n\tCusto: %0.4lf", distancia[destino - 1]);

	}
  
  free(arcos);
  free(distancia); 
  free(anterior);

}	// Fim algoritmoDijkstra

void esperaResposta()
{
	
	/*
		Metodo esperaResposta
		
		Simplesmente garante que o programa nao feche e permite a analise dos resultados
		solicitando que o usuario pressione ENTER para encerra-lo.
		
	*/
	
	printf("\n\n\t------------------------------");
	printf("\n\t| Pressione ENTER para sair. |");
	printf("\n\t------------------------------");
	getchar();
	
}	// Fim esperaResposta
