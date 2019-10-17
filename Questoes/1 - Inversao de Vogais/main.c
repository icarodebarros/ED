#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************

#1 Algoritmo de inversão de vogais numa frase;

*******************************************************************************/

int ehVogal(char ch);
void abordagemUm(char* nome);
void abordagemDois(char* nome);

int main(int argc, char *argv[]) {
	char nome[] = "icaro nogueira\0";
	char vogais[50];
	int i, contVogais = 0;
	printf("Nome: %s (%d)\n", nome, strlen(nome));
	
//	abordagemUm(nome);
//	printf("Resultado: %s\n\n", nome);
	
	abordagemDois(nome);
	printf("Resultado: %s\n\n", nome);		

	
	system("pause");
	return 0;
}

// Primeira abordagem pensada: percorrer nome guardando vogais nula lista, inverter ordem da lista, aplicar elementos da lista no nome original;
// Complexidade: O(n) -> apesar de ter mais de um loop, eles não estão aninhados;
void abordagemUm(char* nome) {
	char vogais[50];
	int i, contVogais = 0;
	
	for (i = 0; i < strlen(nome); i++) {
		if (ehVogal(nome[i])) {
			vogais[contVogais] = nome[i];
			contVogais++;
			vogais[contVogais] = '\0';
		}
	}
	printf("Vogais: %s (%d)\n", vogais, strlen(vogais));
	
	for (i = 0; i < strlen(nome); i++) {
		if (ehVogal(nome[i])) {
			nome[i] = vogais[contVogais-1];
			contVogais--;
		}
	}
}

// Segunda abordagem: usar apenas um loop, sem número de iterações predefinidas, usando auxiliares 'dir' e 'esq';
// Complexidade: O(n) -> tem custo menor que o anterior pois possui apenas 1 loop. Pior caso (AXXX..X) percorre toda a frase;
void abordagemDois(char* nome) {
	int esq = 0, dir = strlen(nome)-1;
	char vogalEsq = '\0', vogalDir = '\0';
		
	while (esq < dir) {
		if (ehVogal(nome[esq])) vogalEsq = nome[esq];
		if (ehVogal(nome[dir])) vogalDir = nome[dir];
		
		if (vogalEsq != '\0' && vogalDir != '\0') {
			nome[esq] = vogalDir;
			nome[dir] = vogalEsq;
			esq++;
			dir--;
			vogalEsq = '\0';
			vogalDir = '\0';
		} else {
			if (vogalEsq == '\0') esq++;
			if (vogalDir == '\0') dir--;
		}
		
	}
}

int ehVogal(char ch) {
	return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
		ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') ? 1 : 0;
}
