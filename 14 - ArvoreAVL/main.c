#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

/* 
	
	Balanceamento:
		- árvore binária balanceada é qudando as alturas das sub-arvores 'esquerda' e 'direita' de cada nó diferem de no máximo uma unidade;
		- essa diferença é chamada de 'fator de balanceamento' do nó;
		- a eficiência da busca da árvore binária depende do seu balanceamento;
		- custo de insersão, busca e remoção:
			* balanceada: O(logN), onde N é o números de nós da árvore;
			* não balanceada: O(N), onde N é o números de nós da árvore;
		- Árvore AVL é um exemplo de árvore que ao inserir/remover elementos, ela já considera a necessidade de balanceamento e assim o faz;
		
	Árvore AVL:
		- árvore binária balanceada;
		- permite balanceamento local:
			* apenas a parte afetada pela inserção ou remoção é balanceada;
			* uso de rotações 'simples' ou 'duplas' na etapa de rebalanceamento;
		- busca manter-se como uma árvore binária quase completa;
		- custo de qualquer ação: O(logN);
		- fator de balanceamento de no máximo 1;
			* fator de balanceamento: diferença entra alturas da sub-arvores esquerda e direita;
			* a altura da sub-dir conta-se como negativa e a da sub-esq conta-se como positiva;
			* somando as sub-alturas tem-se o fator de balanceamento
			
					A   fb = +2; DESBALANCEADA! Pq a sub-esq (+) tem altura 3 a a sub-dir (-) tem altura 1
				  /  \
				B	  C		A: fb=+2	B: fb=-1	C: fb=0		D: fb=0		E: fb=0		F: fb=0		G: fb=0
			  /	 \     		
			 D    E     
			    /  \
			   F    G
		
	OBS.:
		- Na implementação dessa árvore para guardar o primeiro nó utiliza-se um 'ponteiro para ponteiro', assim fica fácil
		  alterar quem é a raiz da árvore quando necessário no balanceamento;
		- Com exceção da inserção e remoção, as demais funções da Árvore AVL são idênticas a da Árvore Binária;
 */

int main(int argc, char *argv[]) {
	int x;
	
	ArvAVL* raiz = cria_arvore();
	
	x = estaVazia_ArvAVL(raiz);
	printf("Arvore vazia? %s\n", x == 1 ? "sim" : "nao");
	x = altura_ArvAVL(raiz);
	printf("Altura da arvore: %d\n", x);
	x = totalNO_ArvAVL(raiz);
	printf("Numero de nos da arvore: %d\n\n", x);
	
//	x = insere_ArvAVL(raiz, 50); //				   50 
//	x = insere_ArvAVL(raiz, 10); //				  /  \ 
//	x = insere_ArvAVL(raiz, 99); //			   10	  99 
//	x = insere_ArvAVL(raiz, 30); //			  /	 \     
//	x = insere_ArvAVL(raiz, 5);  //			 5   30     
//	x = insere_ArvAVL(raiz, 25); //			    /  \ 
//	x = insere_ArvAVL(raiz, 45); //			  25   45
								
								
//	x = insere_ArvAVL(raiz, 1);
//	x = insere_ArvAVL(raiz, 2);
//	x = insere_ArvAVL(raiz, 3);
//	x = insere_ArvAVL(raiz, 10);
//	x = insere_ArvAVL(raiz, 4);
//	x = insere_ArvAVL(raiz, 5);
//	x = insere_ArvAVL(raiz, 9);
//	x = insere_ArvAVL(raiz, 7);
//	x = insere_ArvAVL(raiz, 8);
//	x = insere_ArvAVL(raiz, 6);
	// Resultado esperado pelo balanceamento: 	
	//				    4 	
	//				  /   \ 	          
	//			    2	   7 	
	//			  /	 \    / \ 	
	//			 1    3  5  9 	
	//			         \  /\ 	
	//			         6 8  10 	
	
	
	x = insere_ArvAVL(raiz, 3);
	x = insere_ArvAVL(raiz, 2);
	x = insere_ArvAVL(raiz, 4);
	x = insere_ArvAVL(raiz, 1);
	//	      3  
	//	    /  \  
	//	  2     4  
	//	 /	     
	//	1   
	 
	x = estaVazia_ArvAVL(raiz);
	printf("\n\nArvore vazia? %s\n", x == 1 ? "sim" : "nao");
	x = altura_ArvAVL(raiz);
	printf("Altura da arvore: %d\n", x);
	x = totalNO_ArvAVL(raiz);
	printf("Número de nos da arvore: %d\n", x);

	x = remove_ArvAVL(raiz, 4); // apos remover o nó 4 da terceira árvore ela fica desbalanceada
	// após rebalanceamento automático espera-se:
	//	      2  
	//	    /  \  
	//	   1    3
	
	printf("\n\n");
//	preOrdem_ArvAVL(raiz); // 50 10 5 30 25 45 99 || 4 2 1 3 7 5 6 9 8 10 || 3 2 1 4 --> 2 1 3
//	emOrdem_ArvAVL(raiz);  // 5 10 25 30 45 50 99 || 1 2 3 4 5 6 7 8 9 10 || 1 2 3 4 --> 1 2 3
	posOrdem_ArvAVL(raiz); // 5 25 45 30 10 99 50 || 1 3 2 6 5 8 10 9 7 4 || 1 2 4 3 --> 1 3 2

	
	libera_ArvAVL(raiz);
	
	system("pause");
	return 0;
}

