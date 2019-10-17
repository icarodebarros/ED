#include <stdio.h>
#include <stdlib.h>

/* 
	An�lise de Algoritmos
		- Busca responder a seguinte pergunta: podemos fazer um algoritmo mais eficiente?
		- Para comparar a efici�ncia entre algoritmos foi criada uma medida chamada de "complexidade computacional";
		- Complexidade computacional
			* indica o custo ao se aplicar o algoritmo, sendo "custo = mem�ria + tempo";
			* onde mem�ria � o quanto de espa�o o algoritmo consome, e tempo � a dura��o de sua execu��o;
		- Para determonar se um algoritmo � o mais eficiente, podemos utilizar duas abordagens:
			* An�lise emp�rica: compara��o entre programas. (Um algoritmo � analisado pela execu��o de seu programa correspondente. 
				Ex.: compara��o de computadores, de linguagens, de mem�ria consumida);
			* An�lise matem�tica: estudo das propriedades do algoritmo. (Um estudo formal do algoritmo, abstraindo detalhes e focando
				nos custos tominantes. A medi��o do tempo gasto � feita de maneira independente do hardware ou da lingragem usada);
 */

int main(int argc, char *argv[]) {
	/*
	An�lise Matem�tica:
		- Contando instru��es de um algoritmo
			* Este algoritmo procura o maior valor presente em um array "A" contendo "n" elementos e o armazena na vari�vel "M"
	*/
			int M = A[0];				// linha 1(semelhante � Grande-O, por�m em vez da rela��o "menor ou igual" tem-se a rela��o "menor que")
			for (i = 0; i < n; i++) {   // linha 2
				if (A[i] > M) {			// linha 3
					M = A[i];			// linha 4
				}						// linha 5
			}							// linha 6
	
	/*
	Contando instru��es de um algoritmo:
		- vamos contar quantas instru��es simples ele executa;
		- uma instru��o simples � uma instru��o que pode ser executada diretamente pelo CPU, ou algo muito perto disso;
		- Tipos de instru��es:
			* atribui��o de um valor � uma vari�vel;
			* acesso ao valor de um determinado elemento do array (n�o conta caso seteja seguido de outra instru��o. ex.: a[0] > 1);
			* compara��o de dois valores;
			* incremento de um valor;
			* opera��es aritm�ticas b�sicas como adi��o e multiplica��o;
		- vamos assumir que:
			* as instru��es possuem o mesmo custo;
			* comandos de sele��o possuem custo zero Ex.: executar o "if" n�o custa nada, mas a compara��o interna sim!; 
		
		- voltando ao algoritmo acima:
			* o custo da linha 1 � de: 1 instru��o (atribui��o de valor);
			* o custo da linha 2 (inicializa��o do for) � de: 2 instru��es (atribui��o "i = 0" e compara��o "i < n");
			* o custo do la�o 'for' � de: 2*n instru��es (a cada final de la�o "i++" e "i < n");
		
			* ignorando os comandos contidos no corpo do la�o "for", teremos ao todo:  "3 + 2n" instru��es;
			* assim, considerando um "la�o vazio", podemos definir uma fun��o matem�tica que representa o custo do algoritmo em rela��o ao tamanho
			do array de entrada: "f(n) = 2n + 3";
		
			* o custo da linha 3 (if) � de: 1 instru��o (compara��o de valores);
			* o custo da linha 4 � de: 1 instru��o (atribui��o de valor). PROBLEMA: s� � executada em caso espec�fico!
			* considerando dois arrays:
				A1 = [1, 2, 3, 4] -> vai gerar mais instru��es pois o "if" � sempre verdadeiro
				A2 = [4, 3, 2, 1] -> a linha 4 nunca vai ser executada pois o "if" � sempre falso
			* por isso � comum na an�lise de algoritmos a considera��o do "pior caso"!
			* assim, temos que o custo da linha 4 como: 1 instru��o;
			* OBS.: como essas 2 instru��es est�o dentro do for, nunca esquecer de multiplicar por "n"!
			
			* Fun��o do custo do algoritmo em rela��o ao tamanho do array: "f(n) = 3 + 2n + 2n" ou "f(n) = 4n + 3"!
	
	Comportamento assint�tico
		- Podemos descartar todos os termos que crescem lentamente e manter apenas os que crescem mais r�pido � medida que o valor
		de "n" se torna maior;
		- Na fun��o "f(n) = 4n + 3", temos os termos "4n" e "3";
			* o 3 � constante e n�o se altera a medida que o n cresce;
		- Assim nossa fun��o pode ser reduzida para "f(n) = 4n";
		- Ignorar essas constantes de multiplica��o equevale a ignorar as particularidades de cada linguagem e compilador e analizar
		a ideia do algoritmo;
		- Assim nossa fun��o pode ser reduzida simplesmente para "f(n) = n"!;
		
		- Comportamento assint�tico � ent�o quando descartamos todos os termos constantes e mantemos apenas o de maior crescimento;
		- Trata-se do comportamento de uma fun��o 'f(n)' quando 'n' tende ao infinito;
		- Isso acontece porque o termo que possui o maior expoente domina o comportamento da fun��o quando 'n' tende ao infinito;
		
		- Exemplo:
			* "g(n) = 1000n + 500";
			* "h(n) = n^2 + n + 1";
		- apesar de g(n) possuir contantes maiores multiplicando seus termos, h(n) � exponencial, logo quando n tender � infinito
		a fun��o h(n) vai ser maior;
		- Dessa forma podemos suprimir os termos de menor import�ncia e considerar apenas os de maior grau (custo dominante):
			* "g(n) = n";
			* "h(n) = n^2";
			
		- Mais exemplos:
			|  fun��o custo		|	comportamento assint�tico  |
			| f(n) = 105		|		f(n) = 1			   |
			| f(n) = 15n + 2	|		f(n) = n			   |
			| f(n) = n^2 + 5n+ 2|		f(n) = n^2			   |
			| f(n) = 5n^3+200n^2|		f(n) = n^3			   |
			
		- De modo geral, podemos obter a fun��o de custo de um programa simples apenas contando os comandos de la�os aninhados:
			* algoritmo sem la�o: n�mero contante de instru��es -> f(n) = 1;
			* com 1 la�o (indo de 1 a n) -> f(n) = n;
			* com 2 la�os ANINHADOS -> f(n) = n^2;
			* ...
			
			
	Nota��o Grande-O
		- � a forma de an�lise assint�tica mais conhecida;
		- Representa o custo (seja de tempo ou de espa�o) do algoritmo no pior caso poss�vel para todas as entradas de tamanho "n";
		
		- Exemplo: ordena��o usando o selection sort
			* Dado um array "V" de tamanho "n", procurar o menor valor (posi��o "me") e colocar na primeira posi��o;
			* Repetir processo para a segunda posi��o, depois terceira e etc;
			* Parar quando o array estiver ordenado;			
	*/
		void selecionSort(int *V, int n) {
			int i, j, me, troca;
			for(i = 0; i < n-1; i++) { // La�o externo
				me = i;
				for(j = i+1; j < n; j++) { // La�o interno
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
			* Temos dois comandos de la�o;
			* La�o externo: executado "n" vezes;
			* La�o interno: n�mero de execu��es depende do valor do �ndice do la�o externo (n-1, n-2, n-3, ..., 2, 1)
		
		- Para calcularmos o custo do selection sort temos que calcular o resultado da soma "1 + 2 + ... + (n-1) + n";
		- Essa soma representa o n�mero de execu��es do la�o interno, algo que n�o � t�o simples de se calcular;
		- Dependendo do algoritmo, calcular o seu custo exato pode ser uma tarefa muito complicada;
		- No nosso caso, a soma "1 + 2 + ... + (n-1) + n" equivale a soma dos "n" termos de uma prograss�o aritm�tica de raz�o 1:
			* "1 + 2 + ... + (n-1) + n" => n(1+n)/2;
		
		- Uma alternativa mais simples seria estimar um "limite superior", ou seja, alterar o algoritmo para algo menos eficiente;
		- Assim saberemos que o algoritmo original � no m�ximo t�o ruim que o novo algoritmo;
		- No nosso caso, trocamos o la�o interno (que muda de tamanho a cada execu��o do la�o externo) por um la�o que seja executado
		sempre "n vezes", simplificando a an�lise;
		- Agora temos dois la�os aninhados sendo executados "n" vezes cada, assim "f(n) = n^2";
		- Utilizando a nota��o "grando-O" temos que o custo do algoritmo no PIOR CASO � "O(n^2)"!!!
		- Obs.:	Se dois algoritmos s�o executados em sequ�ncia, a complexidade da execu��o ser� dada pela complexidade do maior deles;
			* ex: a sequ�ncia O(n) e O(n^2) tem complexidade O(n^2);
			* ex: a sequ�ncia O(n) e O(n log n) tem complexidade O(n log n);
			* ex: a sequ�ncia O(n), O(n log n) e O(n^2) tem complexidade O(n^2);
		
		
	Outras formas de an�lise assint�ticas
		- Nota��o Grande-O; (descreve o limite assint�otico superior, ou seja, o pior caso do algoritmo)
		- Nota��o Grande-Omega; (descreve o limite assint�otico inferior, ou seja, o melhor caso do algoritmo)
		- Nota��o Grande-O; (descreve o limite assint�otico superior, ou seja, o pior caso do algoritmo)
		- Nota��o Grande-Theta; (descreve o limite assint�otico firme, ou seja, analisa o limite inferior e superior do algoritmo)
		- Nota��o Pequeno-o; (semelhante ao Grande-O, por�m em vez da rela��o "menor ou igual" tem-se a rela��o "menor que")
		- Nota��o Pequeno-omega; (semelhante ao Grande-Omeda, por�m em vez da rela��o "maior ou igual" tem-se a rela��o "maior que")
		
		
	Classes de problemas
		- O(1): ordem constante;
			* as instru��es s�o executadas um n�mero fixo de vezes. N�o depende do tamanho dos dados de entrada;
		- O(log(n)): ordem logar�tmica;
			* t�pica de algoritmos que resolvem um problema transformando-o em problemas menores;
		- O(n): linear;
			* em real, uma certa quantidade de opera��es � realizada sobre cada um dos elementos de entrada;
		- O(n log(n)): ordem log linear;
			* t�pica de algoritmos que trabalham com particionamento dos dados. Esses algoritmos resolvem um problema transformando-o
			em problemas menores,  que s�o resolvidos de forma independente e depois unidos;
		- O(n^2): ordem quadr�tica;
			* Normalmente ocorre quando os dados s�o processados aos pares. Uma carcter�stica deste tipo de algoritmo � a presen�a de um
			aninhamento de dois comandos de repeti��o;
		- O(n^3): ordem c�bica;
			* � caracterizada pela presen�a de um aninhamento de tr�s comandos de repeti��o;
		- O(2^n): ordem exponencial;
			* Geralmente quando se usa uma solu��o de "for�a bruta". N�o s�o �teis do ponto de vista pr�tico. 
		- O(n!): ordem fatorial;
			* Geralmente ocorre quando se usa uma solu��o de "for�a bruta". N�o s�o �teis do ponto de vista pr�tico. Possui um
			comportamento muito pior que o exponencial;
			
	Obs.: na an�lise assint�tica as constantes de multiplica��o s�o consideradas irrelevantes e descastadas. Mas na pr�tica,
	caso elas sejam muito grandes, podem sim fazer diferen�a!
		
	*/	
	
	return 0;
}
