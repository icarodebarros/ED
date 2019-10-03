#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"

struct hash {
	int qtd, TABLE_SIZE;
	struct aluno **itens;
};

Hash* criaHash(int TABLE_SIZE) {
	Hash* ha = (Hash*) malloc(sizeof(Hash));
	if (ha != NULL) {
		int i;
		ha->TABLE_SIZE = TABLE_SIZE;
		ha->itens = (struct aluno**) malloc(TABLE_SIZE * sizeof(struct aluno*)); // cria o vetor (vetor de ponteiros pra struct aluno)
		// OBS.: lembrando que esse é um vetor de pondeiros pois ele guarda os endereços dos elementos e não seus dados!
		if (ha->itens == NULL) {
			free(ha);
			return NULL;
		}
		ha->qtd = 0;
		for(i = 0; i < ha->TABLE_SIZE; i++) ha->itens[i] = NULL; // inicializa o vetor de ponteiros com NULL
	}
	return ha;
}

void liberaHash(Hash* ha) {
	if (ha != NULL) {
		int i;
		for(i=0; i < ha->TABLE_SIZE; i++) {
			if (ha->itens[i] != NULL) free(ha->itens[i]);
		}
		free(ha->itens);
		free(ha);
	}
}

/*
	Função Hashing
		- Inserção e busca é necessário calcular a posição dos dados dentro da tabela;
		- A função hashing calcula uma posição a apartir de uma chave escolhida a partir dos dados;
		- Responsável por distribuir as informações de forma equilibrada pela tabela hash;
		- Deve satisfazer as seguintes condições:
			* simples e barata de se calcular;
			* garantir que valores diferentes produzam posições diferentes;
			* gerar uma distribuição equilibrada dos dados, ou seja, cada posição da tabela tem a mesma chance de receber uma chave;
	
	IMPORTANTE:
		- a implementação da função de hashing depende do conhecimento prévio da natuzera e domínio da chave a ser utilizada;
		
	Alguns métodos que se pode utilizar para a função hashing:
		- Método da Divisão (ou congruência linear):
			* calcula o resto da divisão do valor inteiro que representa o elemento pelo tamanho da tabela (TABLE_SIZE);
			* função simples e direta;
			* int chaveDivisao(int chave, int TABLE_SIZE) {
			  	  return (chave & 0x7FFFFFFF) % TABLE_SIZE;
			  }
			* a operação de "E bit-a-bit" com o valor 0x7FFFFFFF alimina o bit de sinal do valor da chave;
			* evita o risco de ocorrer um overflow e obtermos um número negativo;
			
		- Método da Multiplicação (congruência linear multiplicativo):
			* usa-se um valor A, onde 0 < A < 1, para multiplicar o valor da chave que representa o elemento. Em seguida
			a parte fracionária resultante é multiplicada pelo tamanho da tabela para calcular a posição do elemento;
			* int chaveMultiplicacao(int chave, int TABLE_SIZE) {
				foat A = 0.6180339887;
				float val = chave * A;
				val = val - (int) val;
				return (int) (TABLE_SIZE * val);
			}
		
		- Exemplo método da multiplicação
			* considere que queremos calcular a posição da chave 123456;
			* constante freacionária "A = 0,618";
			* tamanho da tabela é 1024;
			
			posição = ParteInteira(TABLE_SIZE * ParteFracionária(chave * A))
			posição = ParteInteira(1024 * ParteFracionária(123456 * 0,618))
			posição = ParteInteira(1024 * ParteFracionária(762950,808))
			posição = ParteInteira(1024 * 0,808)
			posição = ParteInteira(827,392)
			posição = 827
			
		- Método da Dobra
			* Utiliza um esquema de dobrar e somar os dígitos do valor para calcular a sua posição;
			* Considera o valor inteiro que representa o elemento como uma sequência de dígitos escritos num pedaço de papel. Enquanto
			 esse valor for maior que o tamanho da tabela, o papel é dobrado e os dígitos sobrepostos são somados, desconsiderando-se as
			 dezenas;
			* int chaveDobra(int chave, int TABLE_SIZE) {
				int num_bits = 10;
				int parte1 = chave >> num_bits;
				int parte2 = chave & (TABLE_SIZE-1);
				return (part1 ^ parte2);
			}
			
		- Exemplo método da dobra
			* Posição do valor 71 (0001000111 em binário)
			* k = 5
			
			posição = 00010 "ou exclusivo" 00111
			posição = 00101
			posição = 5
	
	Tratando uma string como chave
		- calcular o valor numérico a partir dos valores ASCII dos caracteres;
		- deve-se considerar a posição das letras pra evitar que palavras diferentes que contenham as mesmas letras gerem valores iguais;
		- int valorString(char* str) {
			int i, valor = 7;
			int tam = strlen(str);
			for(i = 0; i < tam; i++) valor = 31 * valor + (int) str[i];
			return valor;
		}
*/
int chaveDivisao(int chave, int TABLE_SIZE) {
	return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}
int chaveMultiplicacao(int chave, int TABLE_SIZE) {
	float A = 0.6180339887;
	float val = chave * A;
	val = val - (int) val;
	return (int) (TABLE_SIZE * val);
}
int chaveDobra(int chave, int TABLE_SIZE) {
	int num_bits = 10;
	int parte1 = chave >> num_bits;
	int parte2 = chave & (TABLE_SIZE-1);
	return (parte1 ^ parte2);
}
int valorString(char* str) {
	int i, valor = 7;
	int tam = strlen(str);
	for(i = 0; i < tam; i++) valor = 31 * valor + (int) str[i];
	return valor;
}

/*
	Inserção sem colisão
		- calcular a posição da chave no array;
		- alocar espaço para os dados;
		- armazenar os dados na posição calculada;
*/
int insereHash_SemColisao(Hash* ha, struct aluno al) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) return 0;
	int chave = al.matricula; // ou  int chave = valorString(al.nome);
	int pos = chaveDivisao(chave, ha->TABLE_SIZE); // chaveDivisao é a função hashing escolhida para esse exemplo
	struct aluno* novo = (struct aluno*) malloc(sizeof(struct aluno));
	if (novo == NULL) return 0;
	*novo = al;
	ha->itens[pos] = novo;
	ha->qtd++;
	return 1;
}
/*
	Busca sem colisão
		- calcular a posição da chave no array;
		- verificar se há dados na posição calculada;
		- retornar os dados;
*/
int buscaHash_SemColisao(Hash* ha, int mat, struct aluno* al) {
	if (ha == NULL) return 0;
	int pos = chaveDivisao(mat, ha->TABLE_SIZE);
	if (ha->itens[pos] == NULL) return 0;
	*al = *(ha->itens[pos]);
	return 1;
}

/*
	Problema
		- Afunção de hashing está sujeita à gerar colisões (gerar posições iguais para cheves diferentes);
	Hashing universal
		- Estratégia que busca minimizar esse problema;
		- Basicamente, devemos escolher aleatoriamente (em tempo de execução) a função de hashing que será utilizada;
		- Para isso, é necessário a construção de um conjunto de funções hashing;
		- Exemplo de conjunto de funções:
			* Escolha um número primo "p" de tal modo que o valor de qualquer chave "k" a ser inserida na tabela seja "menor"
			do que "p" e "maior ou igual" a 0, "0 <= k < p";
			* P é maior do que o tamanho da tabela, "TABLE_SIZE";
			* Escolha, aleatoriamente, "dois" números inteiros, "a" e "b", onde (0 < a <= p) e (0 <= b <= p);
			
			* "h(k)_(a,b) = ((ak + b) % p) % TABLE_SIZE"
			* é basicamente o método da divisão com uma combinação de números aleatórios e um número primo
			
	Hashing Perfeito
		- Garante que não haverá colisão das chaves dentro da tabela;
		- No pior caso as operação de busca e inserção são sempre executadas em tempo constante, O(1);
		- Usado onde a colisão não é tolerável;
		- Ex: conjunto de palavras reservadas de uma linguagem de programação;
		
	Hashing Imperfeito
		- Podem ocorrer colisões;
		- As colisões das chaves na tabela não é algo exatamente ruim, é apenas algo indesejável pois diminui o desempenho do sistema;
		- Muitas tabelas hash fazem uso de alguma outra estrutura de dados para lidar com o problema da colisão;
		
	Tratamento de Colisões
		- Uma escolha adequada da função de hashing e do tamanho da tabela podem minimizar as colisões
		- Colisões são teoricamente inevitáveis, logo é necessário ter uma abordagem para tratá-las
		- Algumas formas de tratar a colisão:
			* endereçamento aberto;
			* encadeamento separado;
	Endereçamento aberto:
		- No caso de colisão percorrer a tabela buscando por uma posisão ainda não ocupada;
		- Evita o uso de listas encadeadas;
		- Existem três estratégias muito utilizadas:
			* Sondagem linear (Tenta espalhar os elementos de forma sequencial a partir da posição calculada pela hashing);
			* Sondagem quadrática (Tenta espalhar os elementos utilizando uma equação do 2º grau: "pos + (c1 * i) + (c2 * i^2)");
			* Duplo hash (Tenta espalhar os elementos utilizando duas funções hashing: H1 + i * H2);
	Encadeamento separado:
		- Armazena dentro de cada posição do array o inínio de uma lista dinâmica encadeada;
		- As colisões são armazenadas dentro dessa lista dinâmica encadeada;
*/
int sondagemLinear(int pos, int i, int TABLE_SIZE) {
	// onde i é a posição calculada pela função hashing, i=0 é o primeiro elemento, com inserção normal na posição 'pos'.
	// O segundo elemento, i=1 (colisão), é colocado na posição "pos+1", e assim por diante
	return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}
int sondagemQuadratica(int pos, int i, int TABLE_SIZE) {
	// O primeiro elemento, i=0 tem inserção normal na posição 'pos'.
	// O segundo elemento, i=1 (colisão), é colocado na posição "pos + (c1 * 1) + (c2 * 1^2)"
	// O terceiro elemento, i=2 (colisão), é colocado na posição "pos + (c1 * 2) + (c2 * 2^2)"
	// onde 'pos' é a posição obtida pela hashing, 'i' é a tentatica atual, 'c1' e 'c2' são os coeficientes da equação
	pos = pos + 2*i + 5*i*i;
	return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}
int duploHash(int H1, int chave, int i, int TABLE_SIZE) {
	// O primeiro elemento, i=0 tem inserção normal na posição obtida por "H1".
	// O segundo elemento, i=1 (colisão), é colocado na posição "H1 + 1 * H2".
	// O terceiro elemento, i=2 (colisão), é colocado na posição "H1 + 2 * H2".
	// onde H1 é utilizada para calcular a posição inicial do elemento, H2 é utilizada para calcular os descolamentos
	// em relação à posição inicial no caso de uma colisão
	int H2 = chaveDivisao(chave, TABLE_SIZE - 1) + 1;
	return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
	// OBS.: É necessário que a segunda função de hashing seja diferente da primeira!
}

/*
	Inserção com colisão
		- calcular a posição da chave no array;
		- recalcular a posição enquanto houver colisão;
		- alocar espaço para os dados;
		- armazenar os dados na posição calculada;
*/
int insereHash_EnderAberto(Hash* ha, struct aluno al) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) return 0;
	int chave = al.matricula;
	int i, pos, newPos;
	pos = chaveDivisao(chave, ha->TABLE_SIZE);
	for (i = 0; i < ha->TABLE_SIZE; i++) {
		newPos = sondagemLinear(pos, i, ha->TABLE_SIZE); // ou sondagemQuadratica ou duploHash
		if (ha->itens[newPos] == NULL) {
			struct aluno* novo;
			novo = (struct aluno*) malloc(sizeof(struct aluno));
			if (novo == NULL) return 0;
			*novo = al;
			ha->itens[newPos] = novo;
			ha->qtd++;
			return 1;
		}
	}
	return 0;
}

/*
	Busca sem colisão
		- calcular a posição da chave no array;
		- verificar se há dados na posição calculada e se esses dados combinam com a chave;
		- recalcular a posição enquanto os dados forem diferentes da chave;
		- retornar os dados;
*/
int buscaHash_EnderAberto(Hash* ha, int mat, struct aluno* al) {
	if (ha == NULL) return 0;
	int i, pos, newPos;
	pos = chaveDivisao(mat, ha->TABLE_SIZE);
	for(i = 0; i < ha->TABLE_SIZE; i++) {
		newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
		if (ha->itens[newPos] == NULL) return 0;
		if (ha->itens[newPos]->matricula == mat) {
			*al = *(ha->itens[newPos]);
			return 1;
		}
	}
	return 0;
}
