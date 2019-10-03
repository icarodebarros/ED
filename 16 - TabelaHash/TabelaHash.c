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
		// OBS.: lembrando que esse � um vetor de pondeiros pois ele guarda os endere�os dos elementos e n�o seus dados!
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
	Fun��o Hashing
		- Inser��o e busca � necess�rio calcular a posi��o dos dados dentro da tabela;
		- A fun��o hashing calcula uma posi��o a apartir de uma chave escolhida a partir dos dados;
		- Respons�vel por distribuir as informa��es de forma equilibrada pela tabela hash;
		- Deve satisfazer as seguintes condi��es:
			* simples e barata de se calcular;
			* garantir que valores diferentes produzam posi��es diferentes;
			* gerar uma distribui��o equilibrada dos dados, ou seja, cada posi��o da tabela tem a mesma chance de receber uma chave;
	
	IMPORTANTE:
		- a implementa��o da fun��o de hashing depende do conhecimento pr�vio da natuzera e dom�nio da chave a ser utilizada;
		
	Alguns m�todos que se pode utilizar para a fun��o hashing:
		- M�todo da Divis�o (ou congru�ncia linear):
			* calcula o resto da divis�o do valor inteiro que representa o elemento pelo tamanho da tabela (TABLE_SIZE);
			* fun��o simples e direta;
			* int chaveDivisao(int chave, int TABLE_SIZE) {
			  	  return (chave & 0x7FFFFFFF) % TABLE_SIZE;
			  }
			* a opera��o de "E bit-a-bit" com o valor 0x7FFFFFFF alimina o bit de sinal do valor da chave;
			* evita o risco de ocorrer um overflow e obtermos um n�mero negativo;
			
		- M�todo da Multiplica��o (congru�ncia linear multiplicativo):
			* usa-se um valor A, onde 0 < A < 1, para multiplicar o valor da chave que representa o elemento. Em seguida
			a parte fracion�ria resultante � multiplicada pelo tamanho da tabela para calcular a posi��o do elemento;
			* int chaveMultiplicacao(int chave, int TABLE_SIZE) {
				foat A = 0.6180339887;
				float val = chave * A;
				val = val - (int) val;
				return (int) (TABLE_SIZE * val);
			}
		
		- Exemplo m�todo da multiplica��o
			* considere que queremos calcular a posi��o da chave 123456;
			* constante freacion�ria "A = 0,618";
			* tamanho da tabela � 1024;
			
			posi��o = ParteInteira(TABLE_SIZE * ParteFracion�ria(chave * A))
			posi��o = ParteInteira(1024 * ParteFracion�ria(123456 * 0,618))
			posi��o = ParteInteira(1024 * ParteFracion�ria(762950,808))
			posi��o = ParteInteira(1024 * 0,808)
			posi��o = ParteInteira(827,392)
			posi��o = 827
			
		- M�todo da Dobra
			* Utiliza um esquema de dobrar e somar os d�gitos do valor para calcular a sua posi��o;
			* Considera o valor inteiro que representa o elemento como uma sequ�ncia de d�gitos escritos num peda�o de papel. Enquanto
			 esse valor for maior que o tamanho da tabela, o papel � dobrado e os d�gitos sobrepostos s�o somados, desconsiderando-se as
			 dezenas;
			* int chaveDobra(int chave, int TABLE_SIZE) {
				int num_bits = 10;
				int parte1 = chave >> num_bits;
				int parte2 = chave & (TABLE_SIZE-1);
				return (part1 ^ parte2);
			}
			
		- Exemplo m�todo da dobra
			* Posi��o do valor 71 (0001000111 em bin�rio)
			* k = 5
			
			posi��o = 00010 "ou exclusivo" 00111
			posi��o = 00101
			posi��o = 5
	
	Tratando uma string como chave
		- calcular o valor num�rico a partir dos valores ASCII dos caracteres;
		- deve-se considerar a posi��o das letras pra evitar que palavras diferentes que contenham as mesmas letras gerem valores iguais;
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
	Inser��o sem colis�o
		- calcular a posi��o da chave no array;
		- alocar espa�o para os dados;
		- armazenar os dados na posi��o calculada;
*/
int insereHash_SemColisao(Hash* ha, struct aluno al) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) return 0;
	int chave = al.matricula; // ou  int chave = valorString(al.nome);
	int pos = chaveDivisao(chave, ha->TABLE_SIZE); // chaveDivisao � a fun��o hashing escolhida para esse exemplo
	struct aluno* novo = (struct aluno*) malloc(sizeof(struct aluno));
	if (novo == NULL) return 0;
	*novo = al;
	ha->itens[pos] = novo;
	ha->qtd++;
	return 1;
}
/*
	Busca sem colis�o
		- calcular a posi��o da chave no array;
		- verificar se h� dados na posi��o calculada;
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
		- Afun��o de hashing est� sujeita � gerar colis�es (gerar posi��es iguais para cheves diferentes);
	Hashing universal
		- Estrat�gia que busca minimizar esse problema;
		- Basicamente, devemos escolher aleatoriamente (em tempo de execu��o) a fun��o de hashing que ser� utilizada;
		- Para isso, � necess�rio a constru��o de um conjunto de fun��es hashing;
		- Exemplo de conjunto de fun��es:
			* Escolha um n�mero primo "p" de tal modo que o valor de qualquer chave "k" a ser inserida na tabela seja "menor"
			do que "p" e "maior ou igual" a 0, "0 <= k < p";
			* P � maior do que o tamanho da tabela, "TABLE_SIZE";
			* Escolha, aleatoriamente, "dois" n�meros inteiros, "a" e "b", onde (0 < a <= p) e (0 <= b <= p);
			
			* "h(k)_(a,b) = ((ak + b) % p) % TABLE_SIZE"
			* � basicamente o m�todo da divis�o com uma combina��o de n�meros aleat�rios e um n�mero primo
			
	Hashing Perfeito
		- Garante que n�o haver� colis�o das chaves dentro da tabela;
		- No pior caso as opera��o de busca e inser��o s�o sempre executadas em tempo constante, O(1);
		- Usado onde a colis�o n�o � toler�vel;
		- Ex: conjunto de palavras reservadas de uma linguagem de programa��o;
		
	Hashing Imperfeito
		- Podem ocorrer colis�es;
		- As colis�es das chaves na tabela n�o � algo exatamente ruim, � apenas algo indesej�vel pois diminui o desempenho do sistema;
		- Muitas tabelas hash fazem uso de alguma outra estrutura de dados para lidar com o problema da colis�o;
		
	Tratamento de Colis�es
		- Uma escolha adequada da fun��o de hashing e do tamanho da tabela podem minimizar as colis�es
		- Colis�es s�o teoricamente inevit�veis, logo � necess�rio ter uma abordagem para trat�-las
		- Algumas formas de tratar a colis�o:
			* endere�amento aberto;
			* encadeamento separado;
	Endere�amento aberto:
		- No caso de colis�o percorrer a tabela buscando por uma posis�o ainda n�o ocupada;
		- Evita o uso de listas encadeadas;
		- Existem tr�s estrat�gias muito utilizadas:
			* Sondagem linear (Tenta espalhar os elementos de forma sequencial a partir da posi��o calculada pela hashing);
			* Sondagem quadr�tica (Tenta espalhar os elementos utilizando uma equa��o do 2� grau: "pos + (c1 * i) + (c2 * i^2)");
			* Duplo hash (Tenta espalhar os elementos utilizando duas fun��es hashing: H1 + i * H2);
	Encadeamento separado:
		- Armazena dentro de cada posi��o do array o in�nio de uma lista din�mica encadeada;
		- As colis�es s�o armazenadas dentro dessa lista din�mica encadeada;
*/
int sondagemLinear(int pos, int i, int TABLE_SIZE) {
	// onde i � a posi��o calculada pela fun��o hashing, i=0 � o primeiro elemento, com inser��o normal na posi��o 'pos'.
	// O segundo elemento, i=1 (colis�o), � colocado na posi��o "pos+1", e assim por diante
	return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}
int sondagemQuadratica(int pos, int i, int TABLE_SIZE) {
	// O primeiro elemento, i=0 tem inser��o normal na posi��o 'pos'.
	// O segundo elemento, i=1 (colis�o), � colocado na posi��o "pos + (c1 * 1) + (c2 * 1^2)"
	// O terceiro elemento, i=2 (colis�o), � colocado na posi��o "pos + (c1 * 2) + (c2 * 2^2)"
	// onde 'pos' � a posi��o obtida pela hashing, 'i' � a tentatica atual, 'c1' e 'c2' s�o os coeficientes da equa��o
	pos = pos + 2*i + 5*i*i;
	return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}
int duploHash(int H1, int chave, int i, int TABLE_SIZE) {
	// O primeiro elemento, i=0 tem inser��o normal na posi��o obtida por "H1".
	// O segundo elemento, i=1 (colis�o), � colocado na posi��o "H1 + 1 * H2".
	// O terceiro elemento, i=2 (colis�o), � colocado na posi��o "H1 + 2 * H2".
	// onde H1 � utilizada para calcular a posi��o inicial do elemento, H2 � utilizada para calcular os descolamentos
	// em rela��o � posi��o inicial no caso de uma colis�o
	int H2 = chaveDivisao(chave, TABLE_SIZE - 1) + 1;
	return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
	// OBS.: � necess�rio que a segunda fun��o de hashing seja diferente da primeira!
}

/*
	Inser��o com colis�o
		- calcular a posi��o da chave no array;
		- recalcular a posi��o enquanto houver colis�o;
		- alocar espa�o para os dados;
		- armazenar os dados na posi��o calculada;
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
	Busca sem colis�o
		- calcular a posi��o da chave no array;
		- verificar se h� dados na posi��o calculada e se esses dados combinam com a chave;
		- recalcular a posi��o enquanto os dados forem diferentes da chave;
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
