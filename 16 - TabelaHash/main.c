#include <stdio.h>
#include <stdlib.h>
#include "TabelaHash.h"

/* 
	Busca:
		- Para algoritmos eficientes de busca � necess�rio que os dados estejam ordenados;
		- Problema:
			* Custo da ordena��o no melhor caso: O(N logN);
			* Custo da busca: O(logN);
		- Ideal:
			* Acesso direto ao elemento procurado. Custo: O(1). (Ex.: Quando se busca um elemento no array pelo �ndice);
			
	Tabela Hash:
		- S�o tabelas de indexa��o, usam uma fun��o para espalhar os elementos que queremos armazenar na tabela;
		- Essa fun��o dispersa os elementos de forma n�o ordenada se chama Fun��o de hashing;
		- A tabela hash permite a associa��o de valores e chaves
			* chave: parte da informa��o que comp�es o elemento;
			* valor: � a posi��o (�ndice) onde o elemento se encontra no array;
		- Melhor caso: O(1);
		- Pior caso: O(N) (alto n�mero de colis�es);
		
		- A implementa��o da tabela hash � similar a uma lista sequencial est�tica, ou seja, o tamanho � deficido previamente;
		
	IMPORTANTE: 
		- a nossa tabela hash vai guardar apenas os endere�os para as estruturas que cont�m os dados dos alunos e n�o os dados em si;
		- o tamanho m�ximo da tabela � est�tico, mas a inser��o exige aloca��o para cada novo elemento;
*/

int main(int argc, char *argv[]) {
	
	/*
		IMOPRTANTE: o tamanho da tabela hash � importante que seja n�mero primo e evitar potencia de 2;
			- Um n�mero primo resuz a probabilidade de colis�es mesmo com fun��o hashsing n�o eficaz;
			- Uma pot�ncia de dois melhora a velocidade mas caussa colis�es caso a fun��o hashing seja simples;
	*/
	Hash *ha = criaHash(47);
	int x;
	
	struct aluno al, al1, al2, al3;
    al1.matricula = 101;
    al1.nome[0] = 'a'; al1.nome[1] = 'l'; al1.nome[2] = '1';
    al1.n1 = 8.0;
    al1.n2 = 7.5;
    al1.n3 = 7.0;
    al2.matricula = 102;
    al2.nome[0] = 'a'; al2.nome[1] = 'l'; al2.nome[2] = '2';
    al2.n1 = 5.5;
    al2.n2 = 6.0;
    al2.n3 = 10.0;
    al3.matricula = 103;
    al3.nome[0] = 'a'; al3.nome[1] = 'l'; al3.nome[2] = '3';
    al3.n1 = 8.0;
    al3.n2 = 2.5;
    al3.n3 = 5.0;
    
//	x = insereHash_SemColisao(ha, al1);
//	x = insereHash_SemColisao(ha, al2);
//	x = insereHash_SemColisao(ha, al3);
//	
//	x = buscaHash_SemColisao(ha, 101, &al);
//	if (x == 1) {
//		printf("Aluno: %d - %s\n", al.matricula, al.nome);
//	} else {
//		printf("Aluno nao encontrado!\n");
//	}

	x = insereHash_EnderAberto(ha, al1);
	x = insereHash_EnderAberto(ha, al2);
	x = insereHash_EnderAberto(ha, al3);
	
	x = buscaHash_EnderAberto(ha, 103, &al);
	if (x == 1) {
		printf("Aluno: %d - %s\n", al.matricula, al.nome);
	} else {
		printf("Aluno nao encontrado!\n");
	}
	
	
	liberaHash(ha);
	
	system("pause");
	return 0;
}
