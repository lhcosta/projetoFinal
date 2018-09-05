/*Síntese - Projeto Final - Lucas Henrique - UC17201125 - Ramón Dias - UC14201004
Objetivo: Gestão dos testes do Campeonato de Moto GP, auxiliando o usuário com diversas opções de menu
Entrada: piloto, equipe, circuito, melhor volta
Saída: de acordo com o menu de opções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main() {
	//Declarações
	char opcao = '\0';
	
	//Instruções
	
	telaEntrada();
	do {
		apresentaEscolheMenuPrincipal(&opcao);
		chamaFuncoesMenuPrincipal(&opcao);
	} while(opcao != 's');
	
	return EXIT_SUCCESS;
}


