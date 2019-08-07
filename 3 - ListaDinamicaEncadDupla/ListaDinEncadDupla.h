struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};
typedef struct elemento* Lista;

Lista* cria_lista(); 		  // igual à lista encadeada simples
void libera_lista(Lista* li); // igual à lista encadeada simples
int tamanho_lista(Lista* li); // igual à lista encadeada simples
//int lista_cheia(Lista* li); // igual à lista encadeada simples
int lista_vazia(Lista* li);   // igual à lista encadeada simples

int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int insere_lista_ordenada2(Lista* li, struct aluno al);

int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int remove_lista(Lista* li, int mat);

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al); // igual à lista encadeada simples
int consulta_lista_matricula(Lista* li, int mat, struct aluno *al);

