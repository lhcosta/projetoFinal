/* Menus */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "menu.h"
#include "ui.h"
#include "gerenciamento.h"
#include "relatorios.h"

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu principal.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuPrincipal(char *opcao) {
	int flag = 1;
	do {
		system("cls");
		cabecalho("Menu Principal");
		OPCOES
		printf("(1) - Piloto;\n");
		printf("(2) - Equipe;\n");
		printf("(3) - Circuito;\n");
		printf("(4) - Volta;\n");
		printf("(5) - Relatorios;\n");
		printf("(S) - Sair do programa.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 53) && (*opcao != 's')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}		
	} while(!flag);
}

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu de pilotos.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuPiloto(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Menu dos Pilotos");
		OPCOES
		printf("(1) - Inclusao de pilotos;\n");
		printf("(2) - Alteracao de pilotos;\n");
		printf("(3) - Exclusao de pilotos;\n");
		printf("(R) - Retornar para o menu principal.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 51) && (*opcao != 'r')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);
}

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu de equipes.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuEquipe(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Menu das Equipes");
		OPCOES
		printf("(1) - Inclusao de equipes;\n");
		printf("(2) - Exclusao de equipes;\n");
		printf("(R) - Retornar para o menu principal.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 50) && (*opcao != 'r')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);
}

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu de circuitos.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuCircuito(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Menu dos Circuitos");
		OPCOES
		printf("(1) - Inclusao de circuitos;\n");
		printf("(2) - Alteracao de circuitos;\n");
		printf("(R) - Retornar para o menu principal.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 50) && (*opcao != 'r')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);
}

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu de voltas.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuVolta(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Menu das Voltas");
		OPCOES
		printf("(1) - Inclusao de volta;\n");
		printf("(2) - Alteracao de dados das voltas;\n");
		printf("(3) - Exclusao de voltas;\n");
		printf("(R) - Retornar para o menu principal.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 51) && (*opcao != 'r')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);
}

/*
Objetivo: Apresentar as opções e realizar o processo de escolha no menu de relatórios.
Entrada: Ponteiro do char da escolha.
Saída: Nenhuma.
*/

void apresentaEscolheMenuRelatorio(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Menu de Relatorios");
		OPCOES
		printf("(1) - Relacionar dados de acordo com o tipo escolhido;\n");
		printf("(2) - Pesquisar pelo nome do piloto;\n");
		printf("(3) - Pesquisar pelo circuito ou data;\n");
		printf("(4) - Relacionar todos os circuitos;\n");
		printf("(5) - Relacionar pilotos por equipe;\n");
		printf("(6) - Pesquisar pelo tempo da volta;\n");
		printf("(7) - Relacionar pilotos, equipes ou circuitos sem melhor volta;\n");
		printf("(8) - Relatorio Sintetico e Analitico;\n");
		printf("(9) - Exibir ultimo relatorio sintetico;\n");
		printf("(R) - Retornar ao menu principal.\n");
		scanf(" %c", opcao);system("cls");
		*opcao = tolower(*opcao);
		if ((*opcao < 49 || *opcao > 57) && (*opcao != 'r')) {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);
}

/*Objetivo: Apresentar e realizar a escolha de repetições.
Entrada: Ponteiro da opção escolhida.
Saída: Nenhuma.*/

void apresentaEscolheMenuRepete(char *opcao) {
	int flag = 1;
	
	do {
		cabecalho("Repetir?");
		OPCOES
		printf("(S) - Sim;\n");
		printf("(N) - Nao.\n");
		scanf(" %c", opcao);
		*opcao = tolower(*opcao);
		if (*opcao != 's' && *opcao != 'n') {
			system("cls");
			MSG_MENU_ERRO
			flag = 0;
		} else {
			flag = 1;
		}
	} while(!flag);	
}

/*
Objetivo: Chamar as funções do menu principal.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuPrincipal(char *opcao) {
	char opcaoDentroMenu = '\0';
	
	switch(*opcao) {
		case '1':
			do {
				system("cls");
				apresentaEscolheMenuPiloto(&opcaoDentroMenu);
				chamaFuncoesMenuPiloto(&opcaoDentroMenu);
			} while(opcaoDentroMenu != 'r');
			break;
		case '2':
			do {
				system("cls");
				apresentaEscolheMenuEquipe(&opcaoDentroMenu);
				chamaFuncoesMenuEquipe(&opcaoDentroMenu);
			} while(opcaoDentroMenu != 'r');
			break;
		case '3':
			do {
				system("cls");
				apresentaEscolheMenuCircuito(&opcaoDentroMenu);
				chamaFuncoesMenuCircuito(&opcaoDentroMenu);
			} while(opcaoDentroMenu != 'r');
			break;
		case '4':	
			do {
				system("cls");
				apresentaEscolheMenuVolta(&opcaoDentroMenu);
				chamaFuncoesMenuVolta(&opcaoDentroMenu);
			} while(opcaoDentroMenu != 'r');
			break;
		case '5':
			do {
				system("cls");
				apresentaEscolheMenuRelatorio(&opcaoDentroMenu);
				chamaFuncoesMenuRelatorio(&opcaoDentroMenu);
			} while(opcaoDentroMenu != 'r');
			break;
		case 's':
			exit(EXIT_SUCCESS);
	}
}

/*
Objetivo: Chamar as funções do menu de pilotos.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuPiloto(char *opcao) {
	switch(*opcao) {
		case '1':
			inclusaoPilotos();
			break;
		case '2':
			alterarPilotos();
			break;
		case '3':
			excluirPilotos();
			break;
		default:
			return;
	}
}

/*
Objetivo: Chamar as funções do menu de equipes.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuEquipe(char *opcao) {
	switch(*opcao) {
		case '1':
			inclusaoEquipes();
			break;
		case '2':
			excluirEquipes();
			break;
		default:
			return;
	}
}

/*
Objetivo: Chamar as funções do menu de circuitos.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuCircuito(char *opcao) {
	switch(*opcao) {
		case '1':
			inclusaoCircuitos();
			break;
		case '2':
			alterarCircuitos();
			break;
		default:
			return;
	}
}

/*
Objetivo: Chamar as funções do menu de voltas.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuVolta(char *opcao) {
	switch(*opcao) {
		case '1':
			inclusaoVoltas();
			break;
		case '2':
			alterarVoltas();
			break;
		case '3':
			excluirVoltas();
			break;
		default:
			return;
	}
}

/*
Objetivo: Chamar as funções do menu de relatórios.
Entrada: Ponteiro de char da escolha feita pelo usuário.
Saída: Nenhuma.
*/

void chamaFuncoesMenuRelatorio(char *opcao) {
	char opcaoDentroMenu = '\0';
	switch(*opcao) {
		case '1':
			pesquisaDados();
			break;
		case '2':
			pesquisaPilotos();
			break;
		case '3':
			pesquisaCircuitos();
			break;
		case '4':
			apresentaCircuitosCadastrados();
			break;
		case '5':
			apresentaPilotosData();
			break;
		case '6':
			apresentaDadosTempo();
			break;
		case '7':
			apresentaDadosSem_melhorVolta();
			break;
		case '8':	
			apresentaPilotosR8R9(0);
			break;
		case '9':
			apresentaPilotosR8R9(1);	
		default:
			return;
	}
}


