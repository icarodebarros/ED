#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

/* 
	�rvore:
		- tipo especial de grafo;
		- s� existe uma aresta conectando o par de v�rtices;
		- grafo conexo (existe exatamente um caminho entre quaisquer dois de seus vertices);
		- gtafo aciclico (nao possui ciclos);
		
	�rvore bin�ria:
		- tipo especial de �rvore;
		- cada v�rtice pode possuir duas sub-arvores: 'sub-arvore esquerda' e 'sub-arvore direita';
		- o grau de cada vertice (numero de filhos) pode ser 0, 1 ou 2;
		
					O
				  /  \
				O	  O
			  /	 \     \
			 O    O     O
			    /  \
			   O    O
	
	�rvore estritamente bin�ria:
		- �rvore bin�ria que so pode ter 0 ou 2 filhos;
		
	�rvore bin�ria completa:
		- �rvore estritamente bin�ria em que todos os n� folha est�o no mesmo v�vel;
		- o n�mero de n�s dessa �rvore � '2^h-1' onde 'h' � a altura da �rvore;
		
	�rvore bin�ria quase completa:
		- �rvore estritamente bin�ria em que todos os n� folha est�o divididos pelos n�veis 'D' e 'D-1', onde D � o ultimo n�vel;
		
 */

int main(int argc, char *argv[]) {
	int x;
	
	ArvBin* raiz = cria_arvore();
	
	x = estaVazia_ArvBin(raiz);
	printf("Arvore vazia? %s\n", x == 1 ? "sim" : "nao");
	x = altura_ArvBin(raiz);
	printf("Altura da arvore: %d\n", x);
	x = totalNO_ArvBin(raiz);
	printf("Numero de nos da arvore: %d\n", x);
	
	x = insere_ArvBin(raiz, 50); //				   50
	x = insere_ArvBin(raiz, 10); //				  /  \ 
	x = insere_ArvBin(raiz, 99); //			   10	  99 
	x = insere_ArvBin(raiz, 30); //			  /	 \     
	x = insere_ArvBin(raiz, 5);  //			 5   30     
	x = insere_ArvBin(raiz, 25); //			    /  \ 
	x = insere_ArvBin(raiz, 45); //			  25   45
	 
	x = estaVazia_ArvBin(raiz);
	printf("\n\nArvore vazia? %s\n", x == 1 ? "sim" : "nao");
	x = altura_ArvBin(raiz);
	printf("Altura da arvore: %d\n", x);
	x = totalNO_ArvBin(raiz);
	printf("N�mero de nos da arvore: %d\n", x);
	// ...
//	x = remove_ArvBin(raiz, 50);
	
	printf("\n\n");
//	preOrdem_ArvBin(raiz); // 50 10 5 30 25 45 99
	emOrdem_ArvBin(raiz); // 5 10 25 30 45 50 99 
//	posOrdem_ArvBin(raiz); // 5 25 45 30 10 99 50 
	
	libera_ArvBin(raiz);
	
	system("pause");
	return 0;
}
