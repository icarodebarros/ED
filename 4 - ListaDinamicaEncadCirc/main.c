#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"

int main(int argc, char *argv[]) {
	printf("| Start| \n");
	int x, i;
    Lista *li;
    li = cria_lista();
    printf("Lista vazia? %s\n", lista_vazia(li) == 1 ? "true" : "false");

    struct aluno dados_aluno, dados_aluno1, dados_aluno2, dados_aluno3, dados_aluno4, dados_aluno5;
    dados_aluno1.matricula = 12;
    dados_aluno1.nome[0] = 'a'; dados_aluno1.nome[1] = 'l'; dados_aluno1.nome[2] = '1';
    dados_aluno1.n1 = 8.0;
    dados_aluno1.n2 = 7.5;
    dados_aluno1.n3 = 7.0;
    x = insere_lista_ordenada(li, dados_aluno1);
    dados_aluno2.matricula = 23;
    dados_aluno2.nome[0] = 'a'; dados_aluno2.nome[1] = 'l'; dados_aluno2.nome[2] = '2';
    dados_aluno2.n1 = 5.5;
    dados_aluno2.n2 = 6.0;
    dados_aluno2.n3 = 10.0;
    x = insere_lista_ordenada(li, dados_aluno2);
    dados_aluno3.matricula = 25;
    dados_aluno3.nome[0] = 'a'; dados_aluno3.nome[1] = 'l'; dados_aluno3.nome[2] = '3';
    dados_aluno3.n1 = 8.0;
    dados_aluno3.n2 = 2.5;
    dados_aluno3.n3 = 5.0;
    x = insere_lista_ordenada(li, dados_aluno3);
    dados_aluno4.matricula = 19;
    dados_aluno4.nome[0] = 'a'; dados_aluno4.nome[1] = 'l'; dados_aluno4.nome[2] = '4';
    dados_aluno4.n1 = 2.5;
    dados_aluno4.n2 = 1.0;
    dados_aluno4.n3 = 3.0;
    x = insere_lista_ordenada(li, dados_aluno4);
    dados_aluno5.matricula = 16;
    dados_aluno5.nome[0] = 'a'; dados_aluno5.nome[1] = 'l'; dados_aluno5.nome[2] = '5';
    dados_aluno5.n1 = 7.0;
    dados_aluno5.n2 = 7.5;
    dados_aluno5.n3 = 7.0;
    x = insere_lista_ordenada(li, dados_aluno5);

	printf("Tamanho lista: %d \n", tamanho_lista(li));
    printf("Lista:\n");
    for (i = 0; i < tamanho_lista(li); i++) {
       x = consulta_lista_posicao(li, i+1, &dados_aluno);
       printf("Matricula: %d - Nome: %s \n", dados_aluno.matricula, dados_aluno.nome);
    }

    x = remove_lista_final(li);

    printf("Lista apos remocao:\n");
    for (i = 0; i < tamanho_lista(li); i++) {
       x = consulta_lista_posicao(li, i+1, &dados_aluno);
       printf("Matricula: %d - Nome: %s \n", dados_aluno.matricula, dados_aluno.nome);
    }


    libera_lista(li);
	
	system("pause");
	return 0;
}


