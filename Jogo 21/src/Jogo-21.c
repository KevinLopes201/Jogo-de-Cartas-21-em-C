/*
 ======================================================================================================================
 Name        : Trabalho.c
 Author      : Kevin Guerke Lopes
 Version     :
 Copyright   : Your copyright notice
 Description : Elabore um jogo de cartas em linguagem C que simule o jogo 21 de acordo com as especificacoes abaixo.

 No jogo 21, o jogador solicita quantas cartas quiser ao computador na tentativa de somar 21 pontos.
 Para as cartas abaixo do valete, soma-se o seu proprio valor. Para as cartas valete, dama, rei e As, soma-se o valor 10.

 No inicio do jogo o usuario deve informar o valor de uma aposta. Caso some os 21 pontos, ganha o dobro do valor apostado.
 Caso some 19 ou 20 pontos, ganha o valor apostado. Caso contrario, perde o valor da aposta.

 1. Represente um baralho considerando o numero da carta e o seu naipe. Os naipes devem ser representados por um
 caracter (o para ouros, p para paus, c para copas, e para espadas) e os numeros devem variar de 2 a 14, sendo 11 para o valete,
 12 para a dama, 13 para o rei e 14 para o As.

 2. Como variavel global, declare o baralho com 52 cartas.

 3. Elabore um procedimento para criar o baralho.

 4. Elabore um procedimento para embaralhar as cartas.

 5. Elabore um procedimento para mostrar todo o baralho na tela. Apresente o baralho apos a sua criacao e
 apos o seu embaralhamento.

 6. A cada rodada deve-se apresentar na tela:
 a. O numero da rodada.
 b. A carta dada ao usuario.
 c. O valor da carta.
 d. A soma de todas as cartas do usuario.

 7. Caso o usuario atinja os 21 pontos, o jogo deve ser encerrado e o usuario declarado vencedor.

 8. Caso o usuario passe dos 21 pontos, o jogo deve ser encerrado e o usuario declarado como perdedor.

 9. Caso o jogo nao seja encerrado por pontos, deve-se questionar o usuario se ele deseja uma nova carta. Caso afirmativo,
 uma nova rodada deve ser feita. Caso contrario, o jogo deve ser encerrado.

 10. Ao final do jogo deve-se avaliar a soma dos pontos do jogador:
 a. Caso atinja 19 ou 20 pontos, o usuario deve ganhar o valor apostado.
 b. Caso atinja 21 pontos, o usuario deve ganhar o dobro do valor apostado.
 c. Caso contrario, o usuario deve perder o valor apostado.
 ======================================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//variaveis globais
int num[52];
char naipe[52];

//funções e procedimentos
void gerar_baralho();
void embaralhar();
void mostrar_baralho();
void mostrar_carta(int i);

//função main
int main(void) {
	int op, escolha = 2, aux = 1, rodada, i, soma;
	char jogada;
	float dinheiro = 200, aposta;
	setbuf(stdout, NULL);
	srand(time(0));

	do {
		gerar_baralho();
		while (aux == 1) {
			printf("1. Iniciar o jogo\n");
			printf("2. Mostrar o baralho (testar)\n");
			printf("3. Sair");
			scanf(" %d", &escolha);
			if (escolha == 1 || escolha == 2 || escolha == 3) {
				aux = 2;
			}
		}
		if (escolha == 1 || escolha == 2) {
			switch (escolha) {
			case 1:
				embaralhar();
				do {
					//jogador faz a aposta
					while (aposta <= aux) {
						aux = 1;
						printf("\nVoce tem $ %.2f\n", dinheiro);
						printf("Faca sua aposta: ");
						scanf(" %f", &aposta);
						if (aposta <= dinheiro) {
							dinheiro = dinheiro - aposta;
							jogada = 'S';
							rodada = 0;
							soma = 0;
							rodada++;
						} else {
							printf("Aposte uma quantia valida!");

							aux = aposta + 1;
						}
					}

					// sorteia a carta
					while (jogada == 's' || jogada == 'S') {
						i = rand() % 52;
						soma = soma + num[i];
						printf("\n\nRodada %d		pontos %d", rodada, soma);
						mostrar_carta(i);

						if (soma < 21) {
							printf("\n\nDeseja comprar mais uma carta? [S/N]");
							scanf(" %c", &jogada);

							if (jogada != 'S' && jogada != 's' && jogada != 'N'
									&& jogada != 'n') {
								printf("\nDigite S ou N");
								scanf(" %c", &jogada);
							}

						} else if (soma > 21) {
							jogada = 'n';
							printf("\n\nVoce passou de 21. Voce perdeu!!!\n\n");
							aposta = 0;
							rodada = 0;
						}
						if (jogada == 'n' || jogada == 'N') {
							if (soma == 21) {
								dinheiro = dinheiro + (aposta * 2);
							} else if (soma == 20 || soma == 19) {
								dinheiro = dinheiro + aposta;
							}
						}
					}
					if (jogada == 'n' || jogada == 'N') {

						printf(
								"Voce terminou o jogo com %d pontos, seu dinheiro agora eh $ %.2f",
								soma, dinheiro);
					}
					if (dinheiro > 0 && jogada == 'n') {
						printf("\nDeseja jogar mais uma vez? [S/N]");
						scanf(" %c", &jogada);
						if (jogada != 'S' && jogada != 's' && jogada != 'N'
								&& jogada != 'n') {
							printf("Digite S ou N");
							scanf(" %c", &jogada);
						}
					} else if (dinheiro <= 0) {
						jogada = 'N';
						op = 3;
						printf("\n\nVoce perdeu tudo!");
					} else if (jogada == 'n' || jogada == 'N') {
						op = 3;
					}
				} while (jogada == 's' || jogada == 'S');
				break;

			case 2:
				mostrar_baralho();
				op = 3;
				break;

			}
		} else if (escolha == 3) {
			op = 3;
		}
	} while (op != 3);
	return EXIT_SUCCESS;
}

//funções se procedimentos

void gerar_baralho() {
	for (int i = 0; i < 52; i++) {
		num[i] = i / 4 + 1;

		switch (i % 4) {
		case 0:
			naipe[i] = 'C';
			break; //copas
		case 1:
			naipe[i] = 'E';
			break; //espada
		case 2:
			naipe[i] = 'O';
			break; //ouros
		case 3:
			naipe[i] = 'P';
			break; //paus
		}
	}
}

void mostrar_baralho() {
	printf("\n\nBaralho antes de ser embaralhado:\n");
	for (int i = 0; i < 52; i++) {
		printf(" %d-%c ", num[i], naipe[i]);
	}
	embaralhar();
	printf("\nBaralho depois de ser embaralhado:\n");
	for (int i = 0; i < 52; i++) {
		printf(" %d-%c ", num[i], naipe[i]);
	}
}

void embaralhar() {
	int ai, j;
	char ac;
	for (int i = 0; i < 52; i++) {
		do {
			j = rand() % 52;
		} while (i == j);

		ai = num[i];
		num[i] = num[j];
		num[j] = ai;

		ac = naipe[i];
		naipe[i] = naipe[j];
		naipe[j] = ac;
	}
}

void mostrar_carta(int i) {
	printf("\n+-------------+\n");
	if (num[i] == 10) {
		printf("|10 %c         |\n", naipe[i]);
	} else if (num[i] == 11) {
		printf("|J %c          |\n", naipe[i]);
	} else if (num[i] == 12) {
		printf("|Q %c          |\n", naipe[i]);
	} else if (num[i] == 13) {
		printf("|K %c          |\n", naipe[i]);
	} else if (num[i] == 14) {
		printf("|A %c          |\n", naipe[i]);
	} else {
		printf("|%d %c          |\n", num[i], naipe[i]);
	}
	printf("|  +-------+  |\n");
	printf("|  |       |  |\n");
	printf("|  |       |  |\n");
	if (num[i] == 10) {
		printf("|  |  10   |  |\n");
	} else if (num[i] == 11) {
		printf("|  |   J   |  |\n");
	} else if (num[i] == 12) {
		printf("|  |   Q   |  |\n");
	} else if (num[i] == 13) {
		printf("|  |   K   |  |\n");
	} else if (num[i] == 14) {
		printf("|  |   A   |  |\n");
	} else {
		printf("|  |   %d   |  |\n", num[i]);
	}
	printf("|  |       |  |\n");
	printf("|  |       |  |\n");
	printf("|  +-------+  |\n");

	if (num[i] == 10) {
		printf("|         %c 10|\n", naipe[i]);
	} else if (num[i] == 11) {
		printf("|          %c J|\n", naipe[i]);
	} else if (num[i] == 12) {
		printf("|          %c Q|\n", naipe[i]);
	} else if (num[i] == 13) {
		printf("|          %c K|\n", naipe[i]);
	} else if (num[i] == 14) {
		printf("|          %c A|\n", naipe[i]);
	} else {
		printf("|          %c %d|\n", naipe[i], num[i]);
	}
	printf("+-------------+\n");
}
