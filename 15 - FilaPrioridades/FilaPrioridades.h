typedef struct fila_prioridade FilaPrio;

FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);

int insere_FilaPrio(FilaPrio* fp, char* nome, int prio);
int remove_FilaPrio(FilaPrio* fp);
int consulta_FilaPrio(FilaPrio* fp, char* nome);

// ---------------- heap binária
int insere_FilaPrio2(FilaPrio* fp, char* nome, int prio);
int remove_FilaPrio2(FilaPrio* fp);
int consulta_FilaPrio2(FilaPrio* fp, char* nome);
