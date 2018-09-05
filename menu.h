//Arquivo cabeçalho das funções de menu

#ifndef _MENU_h
#define _MENU_h

#define EXIT_SUCCESS 0
#define OPCOES printf("\nOpcoes:\n");
#define MSG_MENU_ERRO printf("Opcao invalida! Escolha de acordo com o menu.\n");

void apresentaEscolheMenuPrincipal(char *opcao);
void apresentaEscolheMenuPiloto(char *opcao);
void apresentaEscolheMenuEquipe(char *opcao);
void apresentaEscolheMenuCircuito(char *opcao);
void apresentaEscolheMenuVolta(char *opcao);
void apresentaEscolheMenuRelatorio(char *opcao);
void apresentaEscolheMenuRelatorios1(char *opcao);
void apresentaEscolheMenuRepete(char *opcao);
void chamaFuncoesMenuPrincipal(char *opcao);
void chamaFuncoesMenuPiloto(char *opcao);
void chamaFuncoesMenuEquipe(char *opcao);
void chamaFuncoesMenuCircuito(char *opcao);
void chamaFuncoesMenuVolta(char *opcao);
void chamaFuncoesMenuRelatorio(char *opcao);
void chamaFuncoesMenuRelatorios1(char *opcao);
#endif
