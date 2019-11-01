#include <stdio.h>
#include <stdlib.h>

 /******************************************************************************

#3 M�todo que verifica se �rvore bin�ria informada � ou n�o 'sim�trica espelhada'
Ex.:			O
			  /  \
			O	  O
		   /\	  /\
	     O	O   O	O
	     \	       /
	      O		  O  

*******************************************************************************/

struct NO {
	int info;
	struct NO *esq;
	struct NO *dir;
};

typedef struct NO* ArvBin;

ArvBin* cria_arvore();
int insere_ArvBin(ArvBin *raiz, int valor);
void emOrdem_ArvBin(ArvBin *raiz);
int subArvoresEspelhadas(ArvBin n1, ArvBin n2);

int contador = 0;

int main(int argc, char *argv[]) {
	int x;
	
	ArvBin* raiz = cria_arvore();

//	x = insere_ArvBin(raiz, 50); //				   50		|
//	x = insere_ArvBin(raiz, 10); //				  /  \ 		|
//	x = insere_ArvBin(raiz, 99); //			   10	  99 	|
//	x = insere_ArvBin(raiz, 30); //			  /	 \     		|
//	x = insere_ArvBin(raiz, 5);  //			 5   30     	|
//	x = insere_ArvBin(raiz, 25); //			    /  \ 		|
//	x = insere_ArvBin(raiz, 45); //			  25   45		|
	
//	// Tornando espelhada sim�trica:
//	x = insere_ArvBin(raiz, 80); //				   50		|
//	x = insere_ArvBin(raiz, 101);// 			 /    \ 	|
//	x = insere_ArvBin(raiz, 85); //			   10	   99 	|
//	x = insere_ArvBin(raiz, 62); //			 /	\      / \ 	|
//								//			5  30    80  101|
//								//			  / \    / \	|
//								//			25  45 62  85	|
//  // OU								
//	// Casca de banana:
//	x = insere_ArvBin(raiz, 80); //				   50		|
//	x = insere_ArvBin(raiz, 101);// 			 /    \ 	|
//	x = insere_ArvBin(raiz, 102);//			   10	   99 	|
//	x = insere_ArvBin(raiz, 100);//			 /	\      / \ 	|
//								//			5  30    80  101|
//								//			  / \    	/ \	|
//								//			25  45 	 100 102|

// -----------------------------------------
	x = insere_ArvBin(raiz, 50);
	x = insere_ArvBin(raiz, 20);
	x = insere_ArvBin(raiz, 75);
	x = insere_ArvBin(raiz, 10);
	x = insere_ArvBin(raiz, 30);
	x = insere_ArvBin(raiz, 65);
	x = insere_ArvBin(raiz, 85);
	x = insere_ArvBin(raiz, 5);
	x = insere_ArvBin(raiz, 15);
	x = insere_ArvBin(raiz, 25);
	x = insere_ArvBin(raiz, 35);
	x = insere_ArvBin(raiz, 55);
	x = insere_ArvBin(raiz, 74);
	x = insere_ArvBin(raiz, 80);
	x = insere_ArvBin(raiz, 100);
	x = insere_ArvBin(raiz, 3);
	x = insere_ArvBin(raiz, 7);
	x = insere_ArvBin(raiz, 90);
	x = insere_ArvBin(raiz, 110); // sim�trico (19 n�s)
	x = insere_ArvBin(raiz, 36); // n�o sim�trico (20)
// -----------------------------------------

	emOrdem_ArvBin(raiz);
	printf("\n");
	
	// Abtraindo o caso onde *raiz == NULL
	x = subArvoresEspelhadas((*raiz)->esq, ((*raiz)->dir));	
	printf("\nNumero de chamadas da funcao recursiva: %d", contador);
	printf("\nArvore binaria eh espelhadamente simetrica? %s\n\n", x == 1 ? "SIM!" : "NAO!");
	
	system("pause");
	return 0; 
}

ArvBin* cria_arvore() {
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if (raiz != NULL) *raiz = NULL;
	return raiz;
}

int insere_ArvBin(ArvBin *raiz, int valor) {
	if (raiz == NULL) return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if (novo == NULL) return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	
	if (*raiz == NULL) { // se �rvore vazia
		*raiz = novo;
	} else {
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while (atual != NULL) { // navega nos n�s da �rvore at� chegar num n� folha
			ant = atual;
			if (valor == atual->info) { // elemento j� existe
				free(novo);
				return 0;
			}
			if (valor > atual->info) atual = atual->dir;
			else atual = atual->esq;
		}
		// insere como filho do n� folha selecionado
		if (valor > ant->info) ant->dir = novo;
		else ant->esq = novo;
	}
	return 1;
}

void emOrdem_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	emOrdem_ArvBin(&((*raiz)->esq));
	printf("%d ", (*raiz)->info);
	emOrdem_ArvBin(&((*raiz)->dir));
}

// --------------------- SOLU��O DO PROBLEMA --------------------------

// Complexidade: O(n)
/*
Vendo o comportamento do algoritmo a cada n� adicionado, temos:
N� de n�s -> N� max de chamadas da fun��o 
OBS.: cada adi��o de 1 n� leva-se em conta que este seja colocado para tornar a arvore simetrica (se possivel) pois
assim o algoritmo � obrigado a fazer mais um loop de recursividade, tendo assim o "N� max de chamadas da fun��o"!
Ex.: no caso de arvore com 3 n�s, leva-se em conta:  O      e n�o: O
													/ \				\
												   O   O			 O
												   					  \
												   					   O
1 -> 1 (tendo apenas a raiz, vai ser chamada a fun��o subArvoresEspelhadas no main passando os filhos nulos, sem recursividade)
2 -> 1 (raiz + 1 filho, essa nova camada de filhos que torna a arvore n�o espelhada e a fun��o morre na primeira chamada)
3 -> 3 (com os 2 filhos n�o nulos, o algoritmo acaba chegando na ultima linha disparando a recursividade)
4 -> 3 (essa nova camada de filhos n�o tem simetria, logo a fun��o para no in�cio)
5 -> 5
6 -> 5
7 -> 7
8 -> 7
9 -> 9
10-> 9
...
19-> 19
20-> 19
*/	
int subArvoresEspelhadas(ArvBin n1, ArvBin n2) {
	contador++;
	if (n1 == NULL) {
		return n2 == NULL ? 1 : 0;		
	} else {
		if (n2 == NULL) return 0;
		
		return subArvoresEspelhadas(n1->esq, n2->dir) && subArvoresEspelhadas(n1->dir, n2->esq);
	}
}

// SOLU��O MELHORADA -----------

// Complexidade: O(log n)
/*
N� de n�s -> N� max de chamadas da fun��o 
1 -> 1
2 -> 1
3 -> 1
4 -> 1
5 -> 3
6 -> 3
7 -> 3
8 -> 3
9 -> 5
10-> 5
...
19-> 9
20-> 9
*/
int subArvoresEspelhadas2(ArvBin n1, ArvBin n2) {
	contador++;
	if (n1 == NULL) {
		return n2 == NULL ? 1 : 0;		
	} else {
		if (n2 == NULL) return 0;
		
		
		// Chegando aqui significa que n1 e n2 tem conte�do
		if (n1->esq == NULL && n1->dir == NULL) { // n1 � folha
			return (n2->esq == NULL && n2->dir == NULL) ? 1 : 0;  // se n2 tamb�m � folha retorna 1;			
		} else { // se n1 n�o � folha
			if (n2->esq == NULL && n2->dir == NULL) return 0; // e n2 � folha ent�o returna 0;
			
			// Chegando aqui significa que n1 e n2 s�o ra�zes de sua pr�prias sub-arvores
			return subArvoresEspelhadas2(n1->esq, n2->dir) && subArvoresEspelhadas2(n1->dir, n2->esq);
		}
		
	}
}

