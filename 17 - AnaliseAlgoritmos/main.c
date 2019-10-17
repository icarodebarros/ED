#include <stdio.h>
#include <stdlib.h>

/* 
	Análise de Algoritmos
		- Busca responder a seguinte pergunta: podemos fazer um algoritmo mais eficiente?
		- Para comparar a eficiência entre algoritmos foi criada uma medida chamada de "complexidade computacional";
		- Complexidade computacional
			* indica o custo ao se aplicar o algoritmo, sendo "custo = memória + tempo";
			* onde memória é o quanto de espaço o algoritmo consome, e tempo é a duração de sua execução;
		- Para determonar se um algoritmo é o mais eficiente, podemos utilizar duas abordagens:
			* Análise empírica: comparação entre programas. (Um algoritmo é analisado pela execução de seu programa correspondente. 
				Ex.: comparação de computadores, de linguagens, de memória consumida);
			* Análise matemática: estudo das propriedades do algoritmo. (Um estudo formal do algoritmo, abstraindo detalhes e focando
				nos custos tominantes. A medição do tempo gasto é feita de maneira independente do hardware ou da lingragem usada);
 */

int main(int argc, char *argv[]) {
	/*
	Análise Matemática:
		- Contando instruções de um algoritmo
			* Este algoritmo procura o maior valor presente em um array "A" contendo "n" elementos e o armazena na variável "M"
	*/
			int M = A[0];				// linha 1(semelhante à Grande-O, porém em vez da relação "menor ou igual" tem-se a relação "menor que")
			for (i = 0; i < n; i++) {   // linha 2
				if (A[i] > M) {			// linha 3
					M = A[i];			// linha 4
				}						// linha 5
			}							// linha 6
	
	/*
	Contando instruções de um algoritmo:
		- vamos contar quantas instruções simples ele executa;
		- uma instrução simples é uma instrução que pode ser executada diretamente pelo CPU, ou algo muito perto disso;
		- Tipos de instruções:
			* atribuição de um valor à uma variável;
			* acesso ao valor de um determinado elemento do array (não conta caso seteja seguido de outra instrução. ex.: a[0] > 1);
			* comparação de dois valores;
			* incremento de um valor;
			* operações aritméticas básicas como adição e multiplicação;
		- vamos assumir que:
			* as instruções possuem o mesmo custo;
			* comandos de seleção possuem custo zero Ex.: executar o "if" não custa nada, mas a comparação interna sim!; 
		
		- voltando ao algoritmo acima:
			* o custo da linha 1 é de: 1 instrução (atribuição de valor);
			* o custo da linha 2 (inicialização do for) é de: 2 instruções (atribuição "i = 0" e comparação "i < n");
			* o custo do laço 'for' é de: 2*n instruções (a cada final de laço "i++" e "i < n");
		
			* ignorando os comandos contidos no corpo do laço "for", teremos ao todo:  "3 + 2n" instruções;
			* assim, considerando um "laço vazio", podemos definir uma função matemática que representa o custo do algoritmo em relação ao tamanho
			do array de entrada: "f(n) = 2n + 3";
		
			* o custo da linha 3 (if) é de: 1 instrução (comparação de valores);
			* o custo da linha 4 é de: 1 instrução (atribuição de valor). PROBLEMA: só é executada em caso específico!
			* considerando dois arrays:
				A1 = [1, 2, 3, 4] -> vai gerar mais instruções pois o "if" é sempre verdadeiro
				A2 = [4, 3, 2, 1] -> a linha 4 nunca vai ser executada pois o "if" é sempre falso
			* por isso é comum na análise de algoritmos a consideração do "pior caso"!
			* assim, temos que o custo da linha 4 como: 1 instrução;
			* OBS.: como essas 2 instruções estão dentro do for, nunca esquecer de multiplicar por "n"!
			
			* Função do custo do algoritmo em relação ao tamanho do array: "f(n) = 3 + 2n + 2n" ou "f(n) = 4n + 3"!
	
	Comportamento assintótico
		- Podemos descartar todos os termos que crescem lentamente e manter apenas os que crescem mais rápido à medida que o valor
		de "n" se torna maior;
		- Na função "f(n) = 4n + 3", temos os termos "4n" e "3";
			* o 3 é constante e não se altera a medida que o n cresce;
		- Assim nossa função pode ser reduzida para "f(n) = 4n";
		- Ignorar essas constantes de multiplicação equevale a ignorar as particularidades de cada linguagem e compilador e analizar
		a ideia do algoritmo;
		- Assim nossa função pode ser reduzida simplesmente para "f(n) = n"!;
		
		- Comportamento assintótico é então quando descartamos todos os termos constantes e mantemos apenas o de maior crescimento;
		- Trata-se do comportamento de uma função 'f(n)' quando 'n' tende ao infinito;
		- Isso acontece porque o termo que possui o maior expoente domina o comportamento da função quando 'n' tende ao infinito;
		
		- Exemplo:
			* "g(n) = 1000n + 500";
			* "h(n) = n^2 + n + 1";
		- apesar de g(n) possuir contantes maiores multiplicando seus termos, h(n) é exponencial, logo quando n tender à infinito
		a função h(n) vai ser maior;
		- Dessa forma podemos suprimir os termos de menor importância e considerar apenas os de maior grau (custo dominante):
			* "g(n) = n";
			* "h(n) = n^2";
			
		- Mais exemplos:
			|  função custo		|	comportamento assintótico  |
			| f(n) = 105		|		f(n) = 1			   |
			| f(n) = 15n + 2	|		f(n) = n			   |
			| f(n) = n^2 + 5n+ 2|		f(n) = n^2			   |
			| f(n) = 5n^3+200n^2|		f(n) = n^3			   |
			
		- De modo geral, podemos obter a função de custo de um programa simples apenas contando os comandos de laços aninhados:
			* algoritmo sem laço: número contante de instruções -> f(n) = 1;
			* com 1 laço (indo de 1 a n) -> f(n) = n;
			* com 2 laços ANINHADOS -> f(n) = n^2;
			* ...
			
			
	Notação Grande-O
		- É a forma de análise assintótica mais conhecida;
		- Representa o custo (seja de tempo ou de espaço) do algoritmo no pior caso possível para todas as entradas de tamanho "n";
		
		- Exemplo: ordenação usando o selection sort
			* Dado um array "V" de tamanho "n", procurar o menor valor (posição "me") e colocar na primeira posição;
			* Repetir processo para a segunda posição, depois terceira e etc;
			* Parar quando o array estiver ordenado;			
	*/
		void selecionSort(int *V, int n) {
			int i, j, me, troca;
			for(i = 0; i < n-1; i++) { // Laço externo
				me = i;
				for(j = i+1; j < n; j++) { // Laço interno
					if (V[j] < N[me])
						me = j;
				}
				if (i != me) {
					troca = V[i];
					V[i] = V[me];
					V[me] = troca;
				}
			}
		}
	/*
			* Temos dois comandos de laço;
			* Laço externo: executado "n" vezes;
			* Laço interno: número de execuções depende do valor do índice do laço externo (n-1, n-2, n-3, ..., 2, 1)
		
		- Para calcularmos o custo do selection sort temos que calcular o resultado da soma "1 + 2 + ... + (n-1) + n";
		- Essa soma representa o número de execuções do laço interno, algo que não é tão simples de se calcular;
		- Dependendo do algoritmo, calcular o seu custo exato pode ser uma tarefa muito complicada;
		- No nosso caso, a soma "1 + 2 + ... + (n-1) + n" equivale a soma dos "n" termos de uma prograssão aritmética de razão 1:
			* "1 + 2 + ... + (n-1) + n" => n(1+n)/2;
		
		- Uma alternativa mais simples seria estimar um "limite superior", ou seja, alterar o algoritmo para algo menos eficiente;
		- Assim saberemos que o algoritmo original é no máximo tão ruim que o novo algoritmo;
		- No nosso caso, trocamos o laço interno (que muda de tamanho a cada execução do laço externo) por um laço que seja executado
		sempre "n vezes", simplificando a análise;
		- Agora temos dois laços aninhados sendo executados "n" vezes cada, assim "f(n) = n^2";
		- Utilizando a notação "grando-O" temos que o custo do algoritmo no PIOR CASO é "O(n^2)"!!!
		- Obs.:	Se dois algoritmos são executados em sequência, a complexidade da execução será dada pela complexidade do maior deles;
			* ex: a sequência O(n) e O(n^2) tem complexidade O(n^2);
			* ex: a sequência O(n) e O(n log n) tem complexidade O(n log n);
			* ex: a sequência O(n), O(n log n) e O(n^2) tem complexidade O(n^2);
		
		
	Outras formas de análise assintóticas
		- Notação Grande-O; (descreve o limite assintáotico superior, ou seja, o pior caso do algoritmo)
		- Notação Grande-Omega; (descreve o limite assintáotico inferior, ou seja, o melhor caso do algoritmo)
		- Notação Grande-O; (descreve o limite assintáotico superior, ou seja, o pior caso do algoritmo)
		- Notação Grande-Theta; (descreve o limite assintáotico firme, ou seja, analisa o limite inferior e superior do algoritmo)
		- Notação Pequeno-o; (semelhante ao Grande-O, porém em vez da relação "menor ou igual" tem-se a relação "menor que")
		- Notação Pequeno-omega; (semelhante ao Grande-Omeda, porém em vez da relação "maior ou igual" tem-se a relação "maior que")
		
		
	Classes de problemas
		- O(1): ordem constante;
			* as instruções são executadas um número fixo de vezes. Não depende do tamanho dos dados de entrada;
		- O(log(n)): ordem logarítmica;
			* típica de algoritmos que resolvem um problema transformando-o em problemas menores;
		- O(n): linear;
			* em real, uma certa quantidade de operações é realizada sobre cada um dos elementos de entrada;
		- O(n log(n)): ordem log linear;
			* típica de algoritmos que trabalham com particionamento dos dados. Esses algoritmos resolvem um problema transformando-o
			em problemas menores,  que são resolvidos de forma independente e depois unidos;
		- O(n^2): ordem quadrática;
			* Normalmente ocorre quando os dados são processados aos pares. Uma carcterística deste tipo de algoritmo é a presença de um
			aninhamento de dois comandos de repetição;
		- O(n^3): ordem cúbica;
			* É caracterizada pela presença de um aninhamento de três comandos de repetição;
		- O(2^n): ordem exponencial;
			* Geralmente quando se usa uma solução de "força bruta". Não são úteis do ponto de vista prático. 
		- O(n!): ordem fatorial;
			* Geralmente ocorre quando se usa uma solução de "força bruta". Não são úteis do ponto de vista prático. Possui um
			comportamento muito pior que o exponencial;
			
	Obs.: na análise assintótica as constantes de multiplicação são consideradas irrelevantes e descastadas. Mas na prática,
	caso elas sejam muito grandes, podem sim fazer diferença!
		
	*/	
	
	return 0;
}
