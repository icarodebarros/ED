#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridades.h"

/* 
	Fila de Prioridades
		- Tipo especial de fila que generaliza a ideia de ordena��o;
		- Os elementos da fila possuem um dado extra associados a eles: a sua prioridade;
		- � o valor associado a esta prioridade que determina a posi��o de um elemento na fila, assim como quem deve ser o primeiro a ser
		removido da fila, quando necess�rio;
		
		- A efici�ncia depende da implementa��o:
			* lista encadeada:   inser��o O(N); remo��o O(1);
			* array desordenado: inser��o O(1); remo��o O(N);
			* array ordenado: 	 inser��o O(N); remo��o O(1);
			* heap bin�ria: 	 inser��o O(logN); remo��o O(logN);
 */

int main(int argc, char *argv[]) {
	int x, i;
	char nome[15];
	FilaPrio* fp = cria_FilaPrio();
	
//	x = insere_FilaPrio(fp, "Uguinho", 5);
//	printf("%d\n", x);
//	x = insere_FilaPrio(fp, "Tio Patinhas", 10);
//	x = insere_FilaPrio(fp, "Luizinho", 3);
//	x = insere_FilaPrio(fp, "Zezinho", 4);
//	
//	x = consulta_FilaPrio(fp, nome); 
//	while (x == 1) {
//		printf("%s\n", nome);
//		remove_FilaPrio(fp);
//		x = consulta_FilaPrio(fp, nome);
//	}

	x = insere_FilaPrio2(fp, "Uguinho", 5);
	printf("%d\n", x);
	x = insere_FilaPrio2(fp, "Tio Patinhas", 10);
	x = insere_FilaPrio2(fp, "Luizinho", 3);
	x = insere_FilaPrio2(fp, "Zezinho", 4);

	x = consulta_FilaPrio2(fp, nome);
	while (x == 1) {
		printf("%s\n", nome);
		remove_FilaPrio2(fp);
		x = consulta_FilaPrio2(fp, nome);
	}
			
	system("pause");
	return 0;
}
