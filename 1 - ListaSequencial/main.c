#include <stdio.h>
#include <stdlib.h>
#include "listasequencial.h"

int main(int argc, char *argv[]) {
	printf("| Start| \n");
    Lista *li;
    li = cria_lista();
    printf("Lista vazia? %s\n", lista_vazia(li) == 1 ? "true" : "false");

    struct aluno dados_aluno, dados_aluno1, dados_aluno2, dados_aluno3;
    dados_aluno1.matricula = 101;
    dados_aluno1.nome[0] = 'a'; dados_aluno1.nome[1] = 'l'; dados_aluno1.nome[2] = '1';
    dados_aluno1.n1 = 8.0;
    dados_aluno1.n2 = 7.5;
    dados_aluno1.n3 = 7.0;
    int x = insere_lista_ordenada(li, dados_aluno1);
    dados_aluno2.matricula = 102;
    dados_aluno2.nome[0] = 'a'; dados_aluno2.nome[1] = 'l'; dados_aluno2.nome[2] = '2';
    dados_aluno2.n1 = 5.5;
    dados_aluno2.n2 = 6.0;
    dados_aluno2.n3 = 10.0;
    x = insere_lista_ordenada(li, dados_aluno2);
    dados_aluno3.matricula = 103;
    dados_aluno3.nome[0] = 'a'; dados_aluno3.nome[1] = 'l'; dados_aluno3.nome[2] = '3';
    dados_aluno3.n1 = 8.0;
    dados_aluno3.n2 = 2.5;
    dados_aluno3.n3 = 5.0;
    x = insere_lista_ordenada(li, dados_aluno3);

    printf("Lista:\n");
    int i;
    for (i = 0; i < tamanho_lista(li); i++) {
       x = consulta_lista_posicao(li, i+1, &dados_aluno);
       printf("Matricula: %d - Nome: %s \n", dados_aluno.matricula, dados_aluno.nome);
    }

    x = remove_lista(li, 102);

    printf("Lista apos remocao:\n");
    for (i = 0; i < tamanho_lista(li); i++) {
       x = consulta_lista_posicao(li, i+1, &dados_aluno);
       printf("Matricula: %d - Nome: %s \n", dados_aluno.matricula, dados_aluno.nome);
    }


    libera_lista(li);
	
	system("pause");
	return 0;
}
