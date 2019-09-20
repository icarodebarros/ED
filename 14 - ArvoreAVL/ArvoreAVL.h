typedef struct NO* ArvAVL;

ArvAVL* cria_arvore(); // igua a �rvore bin�ria comum
void libera_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum
int estaVazia_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum
int altura_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum
int totalNO_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum

void preOrdem_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum
void emOrdem_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum
void posOrdem_ArvAVL(ArvAVL *raiz); // igua a �rvore bin�ria comum

int insere_ArvAVL(ArvAVL *raiz, int valor);
int remove_ArvAVL(ArvAVL *raiz, int valor);

int consulta_ArvAVL(ArvAVL *raiz, int valor); // igua a �rvore bin�ria comum
