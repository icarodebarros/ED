typedef struct NO* ArvAVL;

ArvAVL* cria_arvore(); // igua a árvore binária comum
void libera_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum
int estaVazia_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum
int altura_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum
int totalNO_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum

void preOrdem_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum
void emOrdem_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum
void posOrdem_ArvAVL(ArvAVL *raiz); // igua a árvore binária comum

int insere_ArvAVL(ArvAVL *raiz, int valor);
int remove_ArvAVL(ArvAVL *raiz, int valor);

int consulta_ArvAVL(ArvAVL *raiz, int valor); // igua a árvore binária comum
