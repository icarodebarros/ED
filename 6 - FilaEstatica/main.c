#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h"

int main(int argc, char *argv[]) {
	
	printf("| Start| \n");
	int x, i;
    Fila *fi;
    fi = cria_fila();
    printf("Fila vazia? %s\n", fila_vazia(fi) == 1 ? "true" : "false");

    struct aluno dados_aluno, dados_aluno1, dados_aluno2, dados_aluno3, dados_aluno4, dados_aluno5;
    dados_aluno1.matricula = 12;
    dados_aluno1.nome[0] = 'a'; dados_aluno1.nome[1] = 'l'; dados_aluno1.nome[2] = '1';
    dados_aluno1.n1 = 8.0;
    dados_aluno1.n2 = 7.5;
    dados_aluno1.n3 = 7.0;
    x = insere_fila(fi, dados_aluno1);
    dados_aluno2.matricula = 23;
    dados_aluno2.nome[0] = 'a'; dados_aluno2.nome[1] = 'l'; dados_aluno2.nome[2] = '2';
    dados_aluno2.n1 = 5.5;
    dados_aluno2.n2 = 6.0;
    dados_aluno2.n3 = 10.0;
    x = insere_fila(fi, dados_aluno2);
    dados_aluno3.matricula = 25;
    dados_aluno3.nome[0] = 'a'; dados_aluno3.nome[1] = 'l'; dados_aluno3.nome[2] = '3';
    dados_aluno3.n1 = 8.0;
    dados_aluno3.n2 = 2.5;
    dados_aluno3.n3 = 5.0;
    x = insere_fila(fi, dados_aluno3);
    dados_aluno4.matricula = 19;
    dados_aluno4.nome[0] = 'a'; dados_aluno4.nome[1] = 'l'; dados_aluno4.nome[2] = '4';
    dados_aluno4.n1 = 2.5;
    dados_aluno4.n2 = 1.0;
    dados_aluno4.n3 = 3.0;
    x = insere_fila(fi, dados_aluno4);
    dados_aluno5.matricula = 16;
    dados_aluno5.nome[0] = 'a'; dados_aluno5.nome[1] = 'l'; dados_aluno5.nome[2] = '5';
    dados_aluno5.n1 = 7.0;
    dados_aluno5.n2 = 7.5;
    dados_aluno5.n3 = 7.0;
    x = insere_fila(fi, dados_aluno5);

	printf("Tamanho fila: %d \n", tamanho_fila(fi));
    printf("Fila:\n");
    int tamanho =  tamanho_fila(fi);
    for (i = 0; i < tamanho + 1; i++) {
       x = consulta_fila(fi, &dados_aluno);
       printf("consultou? %s\n", x == 1 ? "true" : "false");
       printf("Matricula: %d - Nome: %s \n", dados_aluno.matricula, dados_aluno.nome);
       x = remove_fila(fi);
    }

    libera_fila(fi);
	
	system("pause");
	return 0;
}
