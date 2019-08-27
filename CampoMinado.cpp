/**
 * Programa: JOGO CAMPO MINADO
 * Programadores:
	* GABRIEL ARTHUR TEIXEIRA PERPETUO - 2018006170
	* GUILHERME FRAGA ÁVILA - 2018001502
	* GUSTAVO COTA LIMA - 2018002911
	* JOHNATA DAVI TEIXEIRA SILVA - 2018010459
 * Data: 09/06/2018
*/

#include <iostream>
#include <tchar.h>
#include <algorithm>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>

//AQUI DEFINE O TAMANHO DO CAMPO
#define N 10
#define LINHA N
#define COLUNA N
//TAMANHO DA MATRIZ QUE GUARDA AS POSIÇÕES DAS MINAS
#define IM N - 1
#define JM 2


using namespace std;
//Tamanhos matriz

void menu();
void iniciarJogo();
void instrucoes();
void sobre();
void gerarMinas(char campo[LINHA][COLUNA], char posicaoMinas[IM][JM]);
void indicarMinas(char campo[LINHA][COLUNA]);
void imprimirCampo(char campo[LINHA][COLUNA]);
void jogar(char campo[LINHA][COLUNA], char posicaoMinas[IM][JM], char jogo[LINHA][COLUNA]);
void zerarJogo(char jogo[LINHA][COLUNA]);
void preencherPosicaoMinas(char jogo[LINHA][COLUNA], char posicaoMinas[IM][JM]);
bool validaPosicao(int posicaoLinha, int posicaoColuna);
bool verificaPosicaoMarcada(int posicaoLinha, int posicaoColuna, char posicaoMinas[IM][JM]);
bool estadoJogo = false;

/**
* Função Main
*Função principal que chama o menu de opções
*/
int main() {
	menu();
	system("pause");
	return 0;
}

/**
* Função de menu principal, para escolher se irá jogar, ler as instruções de jogo, sobre os criadores, ou sair do jogo.
*/
void menu() {
	system("cls");
	int opcao;
	system("color 04");
	cout << "CAMPO MINADO" << endl;
	cout << "1 - Jogar" << endl;
	cout << "2 - Instrucoes" << endl;
	cout << "3 - Creditos" << endl;
	cout << "0 - Sair" << endl;
	cout << "Opcao: ";
	cin >> opcao;

	switch (opcao) {
	case 1:
		system("color 0F");
		iniciarJogo();
		break;
	case 0:
		exit(0);
		break;
	case 2:
		instrucoes();
		break;
	case 3:
		sobre();
		break;
	default:
		int tempo = clock();
		cout << "\aOpcao invalida!\n\n";
		while (clock() - tempo < 1000);
		menu();
	}
}

/**
 * Funcão que diz as intruções de como jogar
*/
void instrucoes() {
	system("cls");
	char a = 218, b = 196, c = 194, d = 191, e = 195, f = 197, g = 180, h = 192, i = 193, j = 217, k = 179;
	cout << "Instrucoes:\n\n";
	cout << a;
	for (int i = 0; i < 100; i++)
		cout << b;
	cout << d;
	cout << "\n";
	cout << k << "O jogo funciona da seguinte forma: voce devera digitar a linha (A-J) e a coluna (1-10) do tabuleiro " << k << "\n";
	cout << k << "para tentar achar uma mina,caso voce ache aparacera um asterisco, caso contrario revelara um digito " << k << "\n";
	cout << k << "que indica quantas bombas estao proximas a posicao dada. Seu objetivo e' encontrar todas as bombas  " << k << "\n";
	cout << k << "sem explodir!                                                                                       " << k << "\n";
	cout << h;
	for (int p = 0; p < 100; p++)
		cout << b;
	cout << j << endl;
	system("Pause");
	menu();
}

/**
 * Função que mostra sobre o jogo
*/
void sobre() {
	system("cls");
	char a = 218, b = 196, c = 194, d = 191, e = 195, f = 197, g = 180, h = 192, i = 193, j = 217, k = 179;
	cout << "Autores:\n\n";
	cout << a;
	for (int i = 0; i < 27; i++)
		cout << b;
	cout << d << "\n";
	cout << k << "Gabriel Arthur Teixeira    " << k << "\n";
	cout << k << "Guilherme Fraga Avila      " << k << "\n";
	cout << k << "Gustavo Cota Lima          " << k << "\n";
	cout << k << "Johnata Davi Teixeira Silva" << k << "\n";
	cout << h;
	for (int p = 0; p < 27; p++)
		cout << b;
	cout << j << endl;
	system("Pause");
	menu();
}

/**
 * Função de inicialização do jogo: criação do campo completo, do campo vazio para ser preenchido, etc
*/
void iniciarJogo() {
	estadoJogo = true;
	char campo[LINHA][COLUNA], posicaoMinas[IM][JM], jogo[LINHA][COLUNA];
	gerarMinas(campo, posicaoMinas);
	indicarMinas(campo);
	zerarJogo(jogo);
	//Aqui vc pode colocar para imprimir o campo em vez da mina (Para saber o resultado e facilitar a sua conferencia (Claudia))
	imprimirCampo(jogo);
	jogar(campo, posicaoMinas, jogo);
}

/**
* Funcao que gera as minas
* @param  campo[LINHA][COLUNA] matriz de campo no qual a posição das minasserão geradas
* @param  posicaoMinas[IM][JM] matriz que conterá a posição das minas geradas
*/
void gerarMinas(char campo[LINHA][COLUNA], char posicaoMinas[IM][JM]) {
	int linhaAleatoria, colunaAleatoria;
	for (int i = 0; i < LINHA; i++) {
		for (int j = 0; j < COLUNA; j++) {
			campo[i][j] = '0';
		}
	}
	srand(time(NULL));
	for (int i = 0; i < IM; i++) {
		linhaAleatoria = rand() % (LINHA-1);
		colunaAleatoria = rand() % (COLUNA-1);
		if (campo[linhaAleatoria][colunaAleatoria] == '*') {
			i--;
		}
		else {
			campo[linhaAleatoria][colunaAleatoria] = '*';
			posicaoMinas[i][0] = linhaAleatoria;
			posicaoMinas[i][1] = colunaAleatoria;
		}

	}
}

/**
* Funcao que indica a quantidade de minas ao redor
* @param campo [LINHA][COLUNA] campo na qual onde a posição das minas serão indicadas
*/
void indicarMinas(char campo[LINHA][COLUNA]) {
	int i, j, ai, aj;
	for (i = 0; i < LINHA; i++) {
		for (j = 0; j < COLUNA; j++) {
			if (campo[i][j] == '*') {
				for (ai = i - 1; ai <= i + 1; ai++) {
					if (ai == -1) continue;
					for (aj = j - 1; aj <= j + 1; aj++) {
						if (aj == -1) continue;
						if (campo[ai][aj] != '*') campo[ai][aj] += 1;
					}
				}
			}
		}
	}
}

/**
 * Funcao que imprime um tabuleiro de jogo
 * @param campo[LINHA][COLUNA] é passado qualquer um dos tabuleiros para ser impresso
 */
void imprimirCampo(char campo[LINHA][COLUNA]) {
	system("cls");
	char a = 218, b = 196, c = 194, d = 191, e = 195, f = 197, g = 180, h = 192, i = 193, j = 217, k = 179;
	char letra = 'A';
	cout << "    ";
	for (int i = 1; i <= COLUNA; i++) {
		cout << i <<"   ";
	}
	cout << endl;
	cout << "  " << a;
	for (int i = 0; i < COLUNA; i++){

		if (i == COLUNA - 1) {
			cout << b << b << b << d << endl;
		}
		else {
			cout << b << b << b << c;
		}
	}
	for (int iL = 0; iL < LINHA; iL++, letra++) {
		cout << letra << " " << k;
		for (int iC = 0; iC < COLUNA; iC++) {
			cout << " " << campo[iL][iC] << " " << k;
		}
		if (iL < LINHA-1) {
			cout << "\n  " << e;
			for (int i = 0; i < COLUNA; i++)
			{
				if (i == COLUNA - 1) {
					cout << b << b << b << g << endl;
				}
				else {
					cout << b << b << b << f;
				}
			}

		}
		else {
			cout << "\n  " << h;
			for (int j = 0; j < LINHA; j++) {
				if (j != LINHA-1) {
					cout << b << b << b << i;
				}
			}
			cout << b << b << b << j << endl;
		}
	}
}

/**
* Funcao que gerencia o jogo
* @param campo[LINHA][COLUNA] Que defina o todo o campo minado que ocorrerá o jogo
* @param posicaoMinas[IM][JM] Onde é passado todas as posições das minas
* @param jogo[LINHA][COLUNA] Campo que é atualizado para mostrar a posição que o jogardor precionou
*/
void jogar(char campo[LINHA][COLUNA], char posicaoMinas[IM][JM], char jogo[LINHA][COLUNA]){
	char a = 65, b = 65 + COLUNA-1;
	int contador = 0;
	char aposi;
	int posi = 0, posj = 0;
	do {
		cout << endl << "Escolha uma posicao:";
		cout << endl << a << "-" << b << ": ";
		cin >> aposi;
		aposi = toupper(aposi);
		posi = (int)aposi - 65;
		cout << "1-"<<LINHA<<": ";
		cin >> posj;
		posj -= 1;
		if (validaPosicao(posi, posj)) {
			if (verificaPosicaoMarcada(posi, posj, posicaoMinas)) {
				jogo[posi][posj] = campo[posi][posj];
				imprimirCampo(jogo);
				//cout << endl << "GG";
				contador++;
				if (contador >= ((LINHA*COLUNA)-(N-1))) {
					cout << endl << "Voce venceu!!!!" << endl;
					system("pause");
					menu();
				}
			}
			else {
				preencherPosicaoMinas(jogo, posicaoMinas);
				imprimirCampo(jogo);
				cout << endl << "GAME OVER!" << endl;
				system("pause");
				menu();
			}
		}
		else {
			system("cls");
			cout << endl << "Posição invalida! Selecione novamente..." << endl;

		}
	} while (estadoJogo);
}

/**
* Funcao que zera a tabela de jogo
* @param jogo atualizado que é recebido para como deve ser zerado
*/
void zerarJogo(char jogo[LINHA][COLUNA]) {
	for (int i = 0; i < LINHA; i++) {
		for (int j = 0; j < COLUNA; j++) {
			jogo[i][j] = ' ';
		}
	}
}

/**
* Funcao que guarda as posicoes das minas
* @param jogo[LINHA][COLUNA] parametro do jogo que sera recebido para ser zerado
* @param posicaoMinas[IM][JM] posição das minas que serão preenchidas na tabela
*/
void preencherPosicaoMinas(char jogo[LINHA][COLUNA], char posicaoMinas[IM][JM]) {
	zerarJogo(jogo);
	for (int i = 0; i < LINHA; i++) {
		jogo[posicaoMinas[i][0]][posicaoMinas[i][1]] = '*';
	}
}

/**
* Funcao que valida se a posicao digitada foi correta
* @param posicaoLinha   recebe posição da linha
* @param posicaoColuna  recebe posilão da coluna
* @return validaPosicao retorna se valor é valido dentro do campo
*/
bool validaPosicao(int posicaoLinha, int posicaoColuna) {
	if (posicaoLinha >= 0 && posicaoLinha <= LINHA-1 && posicaoColuna >= 0 && posicaoColuna <= COLUNA-1) return true;
	else return false;
}

/**
* Funcao que verifica se a posicao marcada tem ou não minas
* @param posicaoLinha posição da linha selecionada
* @param posicaoColuna posição da coluna selecionada
* @param posicaoMinas[IM][JM] matriz de posição das minas
* @return verificaPosicaoMarcada retorna se a posição selecionada é a de uma mina
*/
bool verificaPosicaoMarcada(int posicaoLinha, int posicaoColuna, char posicaoMinas[IM][JM]){
	for (int i = 0; i < IM; i++) {
		if (posicaoMinas[i][0] == posicaoLinha && posicaoMinas[i][1] == posicaoColuna) return false;
	}

	return true;
}
