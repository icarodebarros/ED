struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

int buscaLinear(int *V, int N, int elem);
int buscaOrdenada(int *V, int N, int elem);
int buscaBinaria(int *V, int N, int elem);

int buscaLinearMatricula(struct aluno *V, int N, int mat);
int buscaLinearNome(struct aluno *V, int N, char* nome);
// ...
