/* Gerenciamento e controle dos dados cadastrais */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "validacoes.h"
#include "ui.h"
#include "gerenciamento.h"
#include "storage.h"

/******PILOTOS*******/
/* Objetivo: incluir um piloto 
Parâmetros: Nenhum
Retorno: nenhum */

void inclusaoPilotos(){	
	FILE *f = NULL, *p = NULL, *q = NULL;
	char opcao = '\0';
	int qtdEquipCad = 0, qtdPilotCad = 0, qtdPaisCad = 0, flag, numeros[QTD_NUM] = {0}, opcaoId = 0, opcaoEquipe = 0, opcaoPais = 0, i = 0;
	equipe *pEquip = NULL;
	pais *pPais = NULL;
	piloto *pPiloto = NULL, pilotoCadastro;
	
	if (!existeArquivo("pilotos.dat", "rb")) {
		criaArquivo("pilotos.dat", "wb+");
	}
	if ((f = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("paises.txt", "rt")) {
		criaArquivo("paises.txt", "wt+");
	}
	if ((p = fopen("paises.txt", "rt+")) == NULL) {
		ERRO_DB_PAIS
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("equipes.dat", "rb")) {
		criaArquivo("equipes.dat", "wb+");
	}
	if ((q = fopen("equipes.dat", "rb+")) == NULL) {
		ERRO_DB_EQUIP
		exit(EXIT_FAILURE);
	}
	do {
		flag = 1;
		qtdEquipCad = 0;
		qtdPilotCad = 0;
		qtdPaisCad = 0;
		
		pEquip = coletaDadosEquipe(&qtdEquipCad, q);
		pPiloto = coletaDadosPiloto(&qtdPilotCad, f);
		pPais = coletaDadosPais(&qtdPaisCad, p);
		
		system("cls");
		cabecalho("Cadastro de Piloto");
			if (qtdEquipCad == 0) {
			free(pEquip); free(pPiloto); free(pPais);
			fclose(f); fclose(p); fclose(q);
			ERRO_EQUIPES
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		strcpy(pilotoCadastro.nome, "");
		strcpy(pilotoCadastro.equipePiloto.nome, "");
		strcpy(pilotoCadastro.equipePiloto.sigla, "");
		strcpy(pilotoCadastro.equipePiloto.paisEquipe.nome, "");
		strcpy(pilotoCadastro.equipePiloto.paisEquipe.sigla, "");
		strcpy(pilotoCadastro.paisPiloto.nome, "");
		strcpy(pilotoCadastro.paisPiloto.sigla, "");
		pilotoCadastro.sexo = '\0';
		pilotoCadastro.id = -1;
		
		do {
			leValidaNome("Digite o nome do piloto: ", pilotoCadastro.nome);
			if (qtdPilotCad != 0) {
				for (i = 0; i < qtdPilotCad; i++) {
					if (stricmp(pilotoCadastro.nome, pPiloto[i].nome) == 0) {
						ERRO_CAD_PILOT
						getch();
						flag = 0;
						break;
					} else {
						flag = 1;
					}
				}
			}
		} while(!flag);
		
		LINHA

		leValidaData(&pilotoCadastro.dataNascimento,"Digite a data de nascimento do piloto [dd/mm/aaaa]: ");
		
		LINHA
		
		leValidaChar(&pilotoCadastro.sexo, 'm', 'f', "Digite o sexo do piloto [m/f]: ");
		
		LINHA
		
		geraNumerosPiloto(numeros, pPiloto, &qtdPilotCad);
		printf("Escolha um ID para o piloto dos numeros abaixo:\n");
		for (i = 0; i < QTD_NUM; i++) {
			printf("(%2d) - %3d\n", i+1, numeros[i]);
		}
		leValidaInt(&opcaoId, 1,QTD_NUM,"Digite de acordo com o indice: ");
		pilotoCadastro.id = numeros[opcaoId-1];
		
		LINHA
		
		if (qtdPaisCad != 0) {
			printf("Escolha o pais do piloto:\n");
			for (i = 0; i < qtdPaisCad; i++) {
				printf("(%2d) - Pais: %-15s Sigla: %3s\n", i+1, pPais[i].nome, pPais[i].sigla);
			}
			leValidaInt(&opcaoPais, 1, i+1, "Digite de acordo com o indice: ");
			pilotoCadastro.paisPiloto = pPais[opcaoPais-1];
		} else {
			ERRO_DB_PAIS_VAZIO
		}
		
		LINHA
		
		if (qtdEquipCad != 0) {
			printf("Escolha a equipe do piloto:\n");
			for (i = 0; i < qtdEquipCad; i++) {
				printf("(%2d) - Sigla: %3s Nome: %-15s\n", i+1, pEquip[i].sigla, pEquip[i].nome);
			}
			leValidaInt(&opcaoEquipe, 1, i+1, "Digite de acordo com o indice: ");
			pilotoCadastro.equipePiloto = pEquip[opcaoEquipe-1];
		} else {
			ERRO_DB_EQUIPE_VAZIO
		}
		
		fwrite(&pilotoCadastro, sizeof(piloto), 1, f);

		apresentaEscolheMenuRepete(&opcao);
		if (qtdPaisCad != 0) {
			free(pPais);
		}
		if (qtdEquipCad != 0) {
			free(pEquip);
		}
		if (qtdPilotCad != 0) {
			free(pPiloto);
		}
	} while(opcao == 's');
	
	fclose(f);
	fclose(p);
	fclose(q);
	free(pPais);free(pEquip);free(pPiloto);
}

/* Objetivo: alterar um piloto cadastrado
Parâmetros: nenhum
Retorno: nenhum */
void alterarPilotos(){
	FILE *a = NULL, *b = NULL, *c = NULL, *d = NULL;
	char opcao = '\0', continuar = '\0';
	int flag, qtdPilotos, qtdPaises, qtdEquipes, i, alteraPiloto, numeros[QTD_NUM] = {0}, opcaoId, opcaoEquipe, opcaoPais;
	piloto *pPiloto = NULL;
	pais *pPais = NULL;
	equipe *pEquipe = NULL;
	
	do {
		qtdPilotos = 0;
		qtdPaises = 0;
		qtdEquipes = 0;
		
		if (!existeArquivo("pilotos.dat", "rb")) {
			criaArquivo("pilotos.dat", "wb+");
		}
		if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
			ERRO_DB_PILOTO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("paises.txt", "rt")) {
			criaArquivo("paises.txt", "wt+");
		}
		if ((b = fopen("paises.txt", "rt+")) == NULL) {
			ERRO_DB_PAIS
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("equipes.dat", "rb")) {
			criaArquivo("equipes.dat", "wb+");
		}
		if ((c = fopen("equipes.dat", "rb+")) == NULL) {
			ERRO_DB_EQUIP
			exit(EXIT_FAILURE);
		}
		
		pPiloto = coletaDadosPiloto(&qtdPilotos, a);
		pPais = coletaDadosPais(&qtdPaises, b);
		pEquipe = coletaDadosEquipe(&qtdEquipes, c);
		
		fclose(a);
		fclose(b);
		fclose(c);
		
		system("cls");
		cabecalho("ALTERACAO DE PILOTOS");
		if (qtdPilotos == 0) {
			free(pPiloto); free(pPais); free(pEquipe);
			ERRO_PILOTOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		if (qtdEquipes == 0) {
			free(pPiloto); free(pPais); free(pEquipe);
			ERRO_EQUIPES
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		printf("Escolha um piloto para alterar:\n");
		for (i = 0; i < qtdPilotos; i++) {
			printf("(%2d) - Nome: %-15s ID: %3d Equipe: %-3s\n", i+1, pPiloto[i].nome, pPiloto[i].id, pPiloto[i].equipePiloto.sigla);
		}
		leValidaInt(&alteraPiloto, 1, i+1, "Digite sua escolha abaixo:\n");
		
		LINHA
		
		pPiloto[alteraPiloto-1].id = -1;
		
		do {
			leValidaNome("Digite o novo nome do piloto: ", pPiloto[alteraPiloto-1].nome);
			for (i = 0; i < qtdPilotos; i++) {
				if (stricmp(pPiloto[alteraPiloto-1].nome, pPiloto[i].nome) == 0 && (alteraPiloto-1) != i) {
					ERRO_CAD_PILOT
					getch();
					flag = 0;
					break;
				} else {
					flag = 1;
				}
			}						
		} while(!flag);
		
		LINHA
		
		leValidaData(&pPiloto[alteraPiloto-1].dataNascimento, "Digite a data de nascimento do piloto [dd/mm/aaaa]: ");
		
		LINHA
		
		leValidaChar(&(pPiloto[alteraPiloto-1].sexo), 'm', 'f', "Digite o sexo do piloto [m/f]: ");
		
		LINHA
		
		geraNumerosPiloto(numeros, pPiloto, &qtdPilotos);
		printf("Escolha um ID para o piloto dos numeros abaixo:\n");
		for (i = 0; i < QTD_NUM; i++) {
			printf("(%2d) - %3d\n", i+1, numeros[i]);
		}
		leValidaInt(&opcaoId, 1, QTD_NUM, "Digite de acordo com o indice: ");
		pPiloto[alteraPiloto-1].id = numeros[opcaoId-1];
		
		LINHA
		
		if (qtdPaises != 0) {
			printf("Escolha o pais do piloto:\n");
			for (i = 0; i < qtdPaises; i++) {
				printf("(%2d) - Pais: %-15s Sigla: %3s\n", i+1, pPais[i].nome, pPais[i].sigla);
			}
			leValidaInt(&opcaoPais, 1, i+1, "Digite de acordo com o indice: ");
			pPiloto[alteraPiloto-1].paisPiloto = pPais[opcaoPais-1];
		} else {
			ERRO_DB_PAIS_VAZIO
			exit(EXIT_FAILURE);
		}
		
		LINHA
		
		printf("Escolha a equipe do piloto:\n");
		for (i = 0; i < qtdEquipes; i++) {
			printf("(%2d) - Sigla: %3s Nome: %-15s\n", i+1, pEquipe[i].sigla, pEquipe[i].nome);
		}
		leValidaInt(&opcaoEquipe, 1, i+1, "Digite de acordo com o indice: ");
		pPiloto[alteraPiloto-1].equipePiloto = pEquipe[opcaoEquipe-1];
		
		criaArquivo("auxiliar.dat", "wb");
		if ((d = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdPilotos; i++) {
			fwrite((pPiloto+i), sizeof(piloto), 1, d);
		}
		fclose(d);
		remove("pilotos.dat");
		rename("auxiliar.dat", "pilotos.dat");
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdPilotos != 0) {
			free(pPiloto);
		}
		if (qtdEquipes != 0) {
			free(pEquipe);
		}
		if (qtdPaises != 0) {
			free(pPais);
		}
	} while(opcao == 's');
}


/* Objetivo: excluir um piloto cadastrado
Parâmetros: nenhum 
Retorno: nenhum */

void excluirPilotos(){	
	FILE *a = NULL, *b = NULL, *c = NULL;
	int qtdPilotos = 0, qtdVoltas = 0, i, j, cont1, cont2, excluiPiloto;
	char opcao = '\0', continuar = '\0';
	piloto *pPiloto = NULL;
	volta *pVolta = NULL;
	
	
	do {
		qtdPilotos = 0;
		qtdVoltas = 0;
		cont1 = 0;
		cont2 = 0;
		if (!existeArquivo("pilotos.dat", "rb")) {
			criaArquivo("pilotos.dat", "wb+");
		}
		if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
			ERRO_DB_PILOTO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("voltas.dat", "rb")) {
			criaArquivo("voltas.dat", "wb+");
		}
		if ((b = fopen("voltas.dat", "rb+")) == NULL) {
			ERRO_DB_EQUIP
			exit(EXIT_FAILURE);
		}
		
		system("cls");
		cabecalho("EXCLUSAO DE PILOTOS");
		pPiloto = coletaDadosPiloto(&qtdPilotos, a);
		pVolta = coletaDadosVolta(&qtdVoltas, b);
		fclose(a);
		fclose(b);
		
		if (qtdPilotos == 0) {
			free(pPiloto); free(pVolta);
			ERRO_PILOTOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		int pilotosValidos[qtdPilotos], apareceu;
		for (i = 0; i < qtdPilotos; i++) {
			pilotosValidos[i] = -1;
		}
		
		for (i = 0; i < qtdPilotos; i++) {
			apareceu = 0;
			for (j = 0; j < qtdVoltas; j++) {
				if (pPiloto[i].id == pVolta[j].piloto) {
					apareceu = 1;
					break;
				} 
			}
			if (!apareceu) {
				pilotosValidos[cont2++] = i;
			}
		}	
		
		for (i = 0; i < qtdPilotos; i++) {
			if (pilotosValidos[i] != -1) {
				cont1++;
			}
		}
		
		if (cont1 == 0) {
			free(pPiloto); free(pVolta);
			ERRO_EXCLUIR_PILOTO
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		cont2 = 0;
		printf("Escolha o piloto a ser excluido:\n");
		for (i = 0; i < qtdPilotos; i++) {
			if (i == pilotosValidos[i]) {
				printf("(%2d) - Nome: %-15s ID: %3d\n", ++cont2, pPiloto[i].nome, pPiloto[i].id);
			}
		}
		leValidaInt(&excluiPiloto, 1, cont2, "Digite sua opcao abaixo:\n");
		leValidaChar(&continuar, 's', 'n', "Deseja mesmo excluir este piloto? [s/n]\n");
		
		if (continuar == 'N') {
			free(pPiloto); free(pVolta);
			printf("Voce sera mandado de volta ao menu.\n");
			printf("Aperte ENTER para volta.\n");
			getch();
			return;
		}
		
		for (i = 0; i < qtdPilotos; i++) {
			if (excluiPiloto-1 == i) {
				excluiPiloto = pilotosValidos[i];
				break;
			}
		}
		
		criaArquivo("auxiliar.dat", "wb");
		if ((c = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdPilotos; i++) {
			if (i != excluiPiloto) {
				fwrite((pPiloto+i), sizeof(piloto), 1, c);
			}
		}
		fclose(c);
		free(pPiloto);
		free(pVolta);
		remove("pilotos.dat");
		rename("auxiliar.dat", "pilotos.dat");
		
		qtdPilotos--;
		if (qtdPilotos == 0) {
			ERRO_EXCLUIR_PILOTO
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		apresentaEscolheMenuRepete(&opcao);
	} while(opcao == 's');
}

/******EQUIPES******/
/* Objetivo: incluir uma equipe 
Parâmetros: nenhum
Retorno: nenhum */

void inclusaoEquipes(){
	FILE *f = NULL, *p = NULL;
	int qtdEquipCad = 0, qtdPaisCad = 0, i = 0, flag = 1;
	char opcao = '\0';
	int opcaoPais = 0;
	equipe equipeCadastro, *pEquipe = NULL;
	pais *pPais = NULL;
	
	if (!existeArquivo("equipes.dat", "rb")) {
		criaArquivo("equipes.dat", "wb+");
	}
	if((f = fopen("equipes.dat", "rb+")) == NULL) {
		printf("Arquivo ""equipes.dat"" indisponivel.\n");
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("paises.txt", "rt")) {
		criaArquivo("paises.txt", "wt+");
	}
	if ((p = fopen("paises.txt", "rt+")) == NULL) {
		printf("Arquivo ""paises.txt"" indisponivel.\n");
		exit(EXIT_FAILURE);
	}
	
	do {
		qtdEquipCad = 0;
		qtdPaisCad = 0;
		
		pEquipe = coletaDadosEquipe(&qtdEquipCad, f);
		pPais = coletaDadosPais(&qtdPaisCad, p);
		
		do {
			flag = 1;
			system("cls");
			cabecalho("CADASTRO DE EQUIPES");
			
			strcpy(equipeCadastro.nome, "");
			strcpy(equipeCadastro.paisEquipe.nome, "");
			strcpy(equipeCadastro.paisEquipe.sigla, "");
			strcpy(equipeCadastro.sigla, "");
			
			leValidaNome("Digite o nome da equipe: ", equipeCadastro.nome);
			
			LINHA
			
			leValidaSigla("Digite a sigla da equipe [SSS]: ", equipeCadastro.sigla);
			
			LINHA
			
			if (qtdPaisCad != 0) {
				printf("Escolha um pais para a equipe:\n");
				for (i = 0; i < qtdPaisCad; i++) {
					printf("(%2d) - [%s] %s\n", i+1, pPais[i].sigla, pPais[i].nome);
				}
				leValidaInt(&opcaoPais, 1, i+1, "Digite o pais escolhido:\n");
				equipeCadastro.paisEquipe = pPais[opcaoPais-1];
			} else {
				free(pEquipe); free(pPais);
				fclose(f); fclose(p);
				ERRO_DB_PAIS_VAZIO
				exit(EXIT_FAILURE);
			}
			
			LINHA
			
			if (qtdEquipCad != 0) {
				for (i = 0; i < qtdEquipCad; i++) {
					if (stricmp(pEquipe[i].sigla, equipeCadastro.sigla) == 0) {
						ERRO_CAD_EQUIP
						getch();
						flag = 0;
						break;
					} else {
						flag = 1;
					}
				}
			}
			
			if (flag) {
				fseek(f, 0, SEEK_END);
				fwrite(&equipeCadastro, sizeof(equipe), 1, f);
			}
		} while(!flag);
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdEquipCad != 0) {
			free(pEquipe);
		}
		if (qtdPaisCad != 0) {
			free(pPais);
		}
	} while(opcao == 's');
	fclose(p);
	fclose(f);
}

/* Objetivo: excluir uma equipe
Parâmetros: nenhum
Retorno: nenhum */

void excluirEquipes(){
	FILE *a = NULL, *b = NULL, *c = NULL;
	int qtdEquipes = 0, qtdPilotos = 0, i = 0, j = 0, cont1, cont2, excluiEquipe;
	char opcao = '\0', continuar = '\0';
	piloto *pPiloto = NULL;
	equipe *pEquipe = NULL;
	
	do {
		qtdPilotos = 0;
		qtdEquipes = 0;
		cont1 = 0; 
		cont2 = 0;
		
		if (!existeArquivo("pilotos.dat", "rb")) {
			criaArquivo("pilotos.dat", "wb");
		}
		if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
			ERRO_DB_PILOTO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("equipes.dat", "rb")) {
			criaArquivo("equipes.dat", "wb");
		}
		if ((b = fopen("equipes.dat", "rb+")) == NULL) {
			ERRO_DB_EQUIP
			exit(EXIT_FAILURE);
		}
		
		system("cls");
		cabecalho("EXCLUSAO DE EQUIPES");
		pPiloto = coletaDadosPiloto(&qtdPilotos, a);
		pEquipe = coletaDadosEquipe(&qtdEquipes, b);
		
		fclose(a);
		fclose(b);
		
		if (qtdEquipes == 0) {
			free(pPiloto); free(pEquipe);
			ERRO_EQUIPES
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		int equipesValidas[qtdEquipes], apareceu;
		for (i = 0; i < qtdEquipes; i++) {
			equipesValidas[i] = -1;
		}
		
		for (i = 0; i < qtdEquipes; i++) {
			apareceu = 0;
			for (j = 0; j < qtdPilotos; j++) {
				if (stricmp(pEquipe[i].sigla, pPiloto[j].equipePiloto.sigla) == 0) {
					apareceu = 1;
					break;
				}
			}
			if (!apareceu) {
				equipesValidas[cont2++] = i;
			}
		}	
		
		for (i = 0; i < qtdEquipes; i++) {
			if (equipesValidas[i] != -1) {
				cont1++;
			}
		}
		
		if (cont1 == 0) {
			free(pPiloto); free(pEquipe);
			ERRO_EXCLUIR_EQUIPE
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
				
		cont2 = 0;
		printf("Escolha a equipe a ser excluida:\n");
		for (i = 0; i < qtdEquipes; i++) {
			if (i == equipesValidas[i]) {
				printf("(%2d) - Nome: %-15s Sigla: %-3s\n", ++cont2, pEquipe[i].nome, pEquipe[i].sigla);
			}
		}
		leValidaInt(&excluiEquipe, 1, cont2, "Digite sua opcao abaixo:\n");
		leValidaChar(&continuar, 's', 'n', "Deseja mesmo excluir esta equipe? [s/n]\n");
		
		if (continuar == 'N') {
			free(pPiloto); free(pEquipe);
			printf("Voce sera mandado de volta ao menu.\n");
			printf("Aperte ENTER para volta.\n");
			getch();
			return;
		}
		
		for (i = 0; i < qtdEquipes; i++) {
			if (excluiEquipe-1 == i) {
				excluiEquipe = equipesValidas[i];
				break;
			}
		}
		
		criaArquivo("auxiliar.dat", "wb");
		if ((c = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdEquipes; i++) {
			if (i != excluiEquipe) {
				fwrite((pEquipe+i), sizeof(equipe), 1, c);
			}
		}
		fclose(c);
		free(pEquipe);
		free(pPiloto);
		remove("equipes.dat");
		rename("auxiliar.dat", "equipes.dat");
		
		qtdEquipes--;
		if (qtdEquipes == 0) {
			ERRO_EXCLUIR_EQUIPE
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		apresentaEscolheMenuRepete(&opcao);
	} while(opcao == 's');
}

/******CIRCUITOS*******/
/* Objetivo: incluir um circuito 
ParÃ¢metros: nenhum
Retorno: nenhum */

void inclusaoCircuitos(){
	FILE *a = NULL, *b = NULL, *c = NULL;
	char opcao = '\0';
	int flag = 1, qtdPilotoCad = 0, qtdPaisCad = 0, qtdCircuitCad = 0, opcaoPais = 0, opcaoPiloto = 0, i = 0;
	piloto *pPiloto = NULL;
	pais *pPais = NULL;
	circuito *pCircuito = NULL, circuitoCadastro;
	
	if (!existeArquivo("pilotos.dat", "rb")) {
		criaArquivo("pilotos.dat", "wb+");
	}
	if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("paises.txt", "rt")) {
		criaArquivo("paises.txt", "wt+");
	}
	if ((b = fopen("paises.txt", "rt+")) == NULL) {
		ERRO_DB_PAIS
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("circuitos.dat", "rb")) {
		criaArquivo("circuitos.dat", "wb+");
	}
	if ((c = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO
		exit(EXIT_FAILURE);
	}
	
	do {
		flag = 1;
		qtdPilotoCad = 0;
		qtdPaisCad = 0;
		qtdCircuitCad = 0;
		pPiloto = coletaDadosPiloto(&qtdPilotoCad, a);
		pPais = coletaDadosPais(&qtdPaisCad, b);
		pCircuito = coletaDadosCircuito(&qtdCircuitCad, c);
		
		system("cls");
		cabecalho("CADASTRO DE CIRCUITOS");
		if (qtdPilotoCad == 0) {
			fclose(a); fclose(b); fclose(c);
			free(pPiloto); free(pPais); free(pCircuito);
			ERRO_PILOTOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		strcpy(circuitoCadastro.nome, "");
		strcpy(circuitoCadastro.pilotoMenorTempo, "");
		circuitoCadastro.id = -1;
		circuitoCadastro.quilometros = -1;
		strcpy(circuitoCadastro.paisCircuito.nome, "");
		strcpy(circuitoCadastro.paisCircuito.sigla, "");
		circuitoCadastro.menorTempo.minutos = -1;
		circuitoCadastro.menorTempo.segundos = -1;
		circuitoCadastro.menorTempo.milisegundos = -1;
		
		circuitoCadastro.id = qtdCircuitCad + 1;
		
		do {
			leValidaNome("Digite o nome do circuito: ", circuitoCadastro.nome);
			for (i = 0; i < qtdCircuitCad; i++) {
				if (stricmp(circuitoCadastro.nome, pCircuito[i].nome) == 0) {
					printf("Circuito invalido! Este circuito ja esta cadastrado.\n");
					flag = 0;
					break;
				} else {
					flag = 1;
				}
			}
		} while(!flag);
		
		LINHA
		
		if (qtdPaisCad != 0) {
			printf("Escolha o pais do circuito:\n");
			for (i = 0; i < qtdPaisCad; i++) {
				printf("(%2d) - Pais: %-15s Sigla: %3s\n", i+1, pPais[i].nome, pPais[i].sigla);
			}
			leValidaInt(&opcaoPais, 1, i+1, "Digite de acordo com o indice: ");
			circuitoCadastro.paisCircuito = pPais[opcaoPais-1];
		} else {
			fclose(a); fclose(b); fclose(c);
			free(pPiloto); free(pPais); free(pCircuito);
			ERRO_DB_PAIS_VAZIO
			exit(EXIT_FAILURE);
		}
		
		LINHA
		
		leValidaFloat(&circuitoCadastro.quilometros, 3000, 29000, "Digite o tamanho do circuito (em Km): ");
		
		LINHA
		
		leValidaTempo(&circuitoCadastro.menorTempo.minutos, &circuitoCadastro.menorTempo.segundos, &circuitoCadastro.menorTempo.milisegundos, "Digite o menor tempo do circuito [min:seg:mili]: ");
		
		LINHA
		
		printf("Escolha o piloto com o menor tempo no circuito:\n");
		for (i = 0; i < qtdPilotoCad; i++) {
			printf("(%2d) - Piloto: %-15s Equipe %s\n", i+1, pPiloto[i].nome, pPiloto[i].equipePiloto.sigla);
		}
		leValidaInt(&opcaoPiloto, 1, qtdPilotoCad, "Digite sua opcao abaixo: ");
		strcpy(circuitoCadastro.pilotoMenorTempo, pPiloto[opcaoPiloto-1].nome);
		
		fwrite(&circuitoCadastro, sizeof(circuito), 1, c);
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdPaisCad != 0) {
			free(pPais);
		}
		if (qtdPilotoCad != 0) {
			free(pPiloto);
		}
		if (qtdCircuitCad != 0) {
			free(pCircuito);
		}
	} while(opcao == 's');
	fclose(a);
	fclose(b);
	fclose(c);
}

/* Objetivo: alterar um circuito
Parâmetros: nenhum
Retorno: nenhum */

void alterarCircuitos(){
	FILE *a = NULL, *b = NULL, *c = NULL, *d = NULL;
	char opcao = '\0';
	int qtdPilotos, qtdPaises, qtdCircuitos, i, alteraCircuito, opcaoPais, opcaoPiloto, flag;
	piloto *pPiloto = NULL;
	pais *pPais = NULL;
	circuito *pCircuito = NULL;
		
	do {
		qtdPilotos = 0;
		qtdPaises = 0;
		qtdCircuitos = 0;
		
		if (!existeArquivo("pilotos.dat", "rb")) {
		criaArquivo("pilotos.dat", "wb+");
		}
		if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
			ERRO_DB_PILOTO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("paises.txt", "rt")) {
			criaArquivo("paises.txt", "wt+");
		}
		if ((b = fopen("paises.txt", "rt+")) == NULL) {
			ERRO_DB_PAIS
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("circuitos.dat", "rb")) {
			criaArquivo("circuitos.dat", "wb+");
		}
		if ((c = fopen("circuitos.dat", "rb+")) == NULL) {
			ERRO_DB_CIRCUITO
			exit(EXIT_FAILURE);
		}
		
		pPiloto = coletaDadosPiloto(&qtdPilotos, a);
		pPais = coletaDadosPais(&qtdPaises, b);
		pCircuito = coletaDadosCircuito(&qtdCircuitos, c);
		
		fclose(a);
		fclose(b);
		fclose(c);
		
		system("cls");
		cabecalho("ALTERACAO DE CIRCUITOS");
		if (qtdCircuitos == 0) {
			free(pPiloto); free(pPais); free(pCircuito);
			ERRO_CIRCUITOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		printf("Escolha o circuito a ser alterado:\n");
		for (i = 0; i < qtdCircuitos; i++) {
			printf("(%2d) - Nome: %-15s ID: %3d Pais: %-3s\n", i+1, pCircuito[i].nome, pCircuito[i].id, pCircuito[i].paisCircuito.sigla);
		}
		leValidaInt(&alteraCircuito, 1, i+1, "Digite sua escolha abaixo:\n");
		
		LINHA
		
		do {
			leValidaNome("Digite o novo nome do circuito: ", pCircuito[alteraCircuito-1].nome);
			for (i = 0; i < qtdCircuitos; i++) {
				if (stricmp(pCircuito[alteraCircuito-1].nome, pCircuito[i].nome) == 0 && i != alteraCircuito-1) {
					printf("Circuito invalido! Este circuito ja esta cadastrado.\n");
					flag = 0;
					break;
				} else {
					flag = 1;
				}
			}
		} while(!flag);
		
		LINHA
		
		if (qtdPaises != 0) {
			printf("Escolha o pais do circuito:\n");
			for (i = 0; i < qtdPaises; i++) {
				printf("(%2d) - Pais: %-15s Sigla: %3s\n", i+1, pPais[i].nome, pPais[i].sigla);
			}
			leValidaInt(&opcaoPais, 1, i+1, "Digite de acordo com o indice: ");
			pCircuito[alteraCircuito-1].paisCircuito = pPais[opcaoPais-1];
		} else {
			ERRO_DB_PAIS_VAZIO
			exit(EXIT_FAILURE);
		}
		
		LINHA
		
		leValidaFloat(&(pCircuito[alteraCircuito-1].quilometros), 3000, 29000, "Digite o tamanho do circuito (em Km): ");
		
		LINHA
		
		leValidaTempo(&pCircuito[alteraCircuito-1].menorTempo.minutos, &pCircuito[alteraCircuito-1].menorTempo.segundos, &pCircuito[alteraCircuito-1].menorTempo.milisegundos, "Digite o menor tempo do circuito [min:seg:mili]: ");
		
		LINHA
		
		printf("Escolha o piloto com o menor tempo no circuito:\n");
		for (i = 0; i < qtdPilotos; i++) {
			printf("(%2d) - Piloto: %-15s Equipe %s\n", i+1, pPiloto[i].nome, pPiloto[i].equipePiloto);
		}
		leValidaInt(&opcaoPiloto, 1, i+1, "Digite sua opcao abaixo: ");
		strcpy(pCircuito[alteraCircuito-1].pilotoMenorTempo, pPiloto[opcaoPiloto-1].nome);
		
		criaArquivo("auxiliar.dat", "wb");
		if ((d = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdCircuitos; i++) {
			fwrite((pCircuito+i), sizeof(circuito), 1, d);
		}
		fclose(d);
		remove("circuitos.dat");
		rename("auxiliar.dat", "circuitos.dat");
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdPaises != 0) {
			free(pPais);
		}
		if (qtdPilotos != 0) {
			free(pPiloto);
		}
		if (qtdCircuitos != 0) {
			free(pCircuito);
		}
	} while(opcao == 's');
}

/*****VOLTAS*****/
/* Objetivo: incluir uma volta 
Parâmetros: nenhum
Retorno: nenhum */

void inclusaoVoltas(){
	FILE *a, *b, *c, *d;
	char opcao = '\0';
	int flag, qtdPilotoCad = 0, qtdCircuitoCad = 0, qtdVoltaCad = 0, i, opcaoPiloto, opcaoCircuito, diaSemana=0,dataAux=0,flag2=0;
	float tempoSegundosVolta, melhorVoltaSegundos;
	piloto *pPiloto = NULL; 
	circuito *pCircuito = NULL; 
	volta *pVolta = NULL, voltaCadastro;
	
	if (!existeArquivo("pilotos.dat", "rb")) {
		criaArquivo("pilotos.dat", "wb+");
	}
	if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("circuitos.dat", "rb")) {
		criaArquivo("circuitos.dat", "wb+");
	}
	if ((b = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO
		exit(EXIT_FAILURE);
	}
	if (!existeArquivo("voltas.dat", "rb")) {
		criaArquivo("voltas.dat", "wb+");
	}
	if ((c = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS
		exit(EXIT_FAILURE);
	}
	
	do {
		flag = 1;
		qtdPilotoCad = 0;
		qtdCircuitoCad = 0;
		qtdVoltaCad = 0;
		pPiloto = coletaDadosPiloto(&qtdPilotoCad, a);
		pCircuito = coletaDadosCircuito(&qtdCircuitoCad, b);
		pVolta = coletaDadosVolta(&qtdVoltaCad, c);
		
		system("cls");
		cabecalho("CADASTRO DE VOLTAS");
		if (qtdCircuitoCad == 0) {
			fclose(a); fclose(b); fclose(c);
			free(pPiloto); free(pCircuito); free(pVolta);
			ERRO_CIRCUITOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		if (qtdPilotoCad == 0) {
			fclose(a); fclose(b); fclose(c);
			free(pPiloto); free(pCircuito); free(pVolta);
			ERRO_PILOTOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		voltaCadastro.piloto = -1;
		voltaCadastro.circuito = -1;
		strcpy(voltaCadastro.equipePiloto.nome, "");
		strcpy(voltaCadastro.equipePiloto.sigla, "");
		strcpy(voltaCadastro.equipePiloto.paisEquipe.nome, "");
		strcpy(voltaCadastro.equipePiloto.paisEquipe.sigla, "");
		voltaCadastro.melhorVolta.minutos = -1;
		voltaCadastro.melhorVolta.segundos = -1;
		voltaCadastro.melhorVolta.milisegundos = -1;
		
		do {
			printf("Escolha o piloto da volta abaixo:\n");
			for (i = 0; i < qtdPilotoCad; i++) {
				printf("(%2d) - ID: %3d Nome: %-15s\n", i+1, pPiloto[i].id, pPiloto[i].nome);
			}
			leValidaInt(&opcaoPiloto, 1, i+1, "Digite sua escolha abaixo:\n");
			voltaCadastro.piloto = pPiloto[opcaoPiloto-1].id;
			voltaCadastro.equipePiloto = pPiloto[opcaoPiloto-1].equipePiloto;
			
			LINHA
			
			do{	
				do{
					fflush(stdin);
					leValidaData(&voltaCadastro.dataVolta, "Digite a data da volta [dd/mm/aaaa]: ");
					dataAux = (MIN_DIA + (MIN_MES * 30) + (MIN_ANO * 365));
					
					if((voltaCadastro.dataVolta.dia + (voltaCadastro.dataVolta.mes * 30) + (voltaCadastro.dataVolta.ano * 365)) < dataAux){
						printf("A data minima para cadastro e %d/%d/%d\n", MIN_DIA,MIN_MES,MIN_ANO);getch();system("cls");
						flag2=1;
					}else{
						flag2=0;
					}
				}while(flag2==1);
				
				diaSemana = calculaDiaSemana(&voltaCadastro.dataVolta);
				if(diaSemana!=0){
					printf("O dia da semana deve ser domingo\n");getch();system("cls");
				}
			}while(diaSemana!=0);
		
			
			if (qtdVoltaCad != 0) {
				for (i = 0; i < qtdVoltaCad; i++) {
					if (voltaCadastro.dataVolta.dia == pVolta[i].dataVolta.dia && voltaCadastro.dataVolta.mes == pVolta[i].dataVolta.mes && voltaCadastro.dataVolta.ano == pVolta[i].dataVolta.ano && voltaCadastro.piloto == pVolta[i].piloto) {
						printf("Volta invalida! Este piloto ja esta cadastrado neste dia.\n");
						flag = 0;
						break;
					} else {
						flag = 1;
					}
				}
			}
		} while(flag==0);
		
		LINHA
		
		printf("Escolha o circuito da volta abaixo:\n");
		for (i = 0; i < qtdCircuitoCad; i++) {
			printf("(%2d) - ID: %3d Nome: %-15s\n", i+1, pCircuito[i].id, pCircuito[i].nome);
		}
		leValidaInt(&opcaoCircuito, 1, i+1, "Digite sua escolha abaixo:\n");
		voltaCadastro.circuito = pCircuito[opcaoCircuito-1].id;
		
		LINHA
		
		leValidaTempo(&voltaCadastro.melhorVolta.minutos, &voltaCadastro.melhorVolta.segundos, &voltaCadastro.melhorVolta.milisegundos, "Digite o tempo da volta [min:seg:mili]: ");
		tempoSegundosVolta = (voltaCadastro.melhorVolta.minutos * 60) + voltaCadastro.melhorVolta.segundos + (voltaCadastro.melhorVolta.milisegundos * 0.001);
		melhorVoltaSegundos = (pCircuito[opcaoCircuito-1].menorTempo.minutos * 60) + pCircuito[opcaoCircuito-1].menorTempo.segundos + (pCircuito[opcaoCircuito-1].menorTempo.milisegundos * 0.001);

		if (tempoSegundosVolta < melhorVoltaSegundos) {
			pCircuito[opcaoCircuito-1].menorTempo.minutos = voltaCadastro.melhorVolta.minutos;
			pCircuito[opcaoCircuito-1].menorTempo.segundos = voltaCadastro.melhorVolta.segundos;
			pCircuito[opcaoCircuito-1].menorTempo.milisegundos = voltaCadastro.melhorVolta.milisegundos;

			criaArquivo("auxiliar.dat", "wb");
			if ((d = fopen("auxiliar.dat", "rb+")) == NULL) {
				ERRO_AUXILIAR
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < qtdCircuitoCad; i++) {
				fwrite((pCircuito+i), sizeof(circuito), 1, d);
			}
			fclose(d);
			remove("circuitos.dat");
			rename("auxiliar.dat", "circuitos.dat");
		}
		
		fwrite(&voltaCadastro, sizeof(volta), 1, c);
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdPilotoCad != 0) {
			free(pPiloto);
		}
		if (qtdCircuitoCad != 0) {
			free(pCircuito);
		}
		if (qtdVoltaCad != 0) {
			free(pVolta);
		}
	} while(opcao == 's');
	fclose(a);
	fclose(b);
	fclose(c);
}

/* Objetivo: alterar uma volta
Parâmetros: nenhum
Retorno: nenhum */

void alterarVoltas(){
	FILE *a, *b, *c, *d, *e;
	char opcao = '\0';
	int qtdPilotos, qtdCircuitos, qtdVoltas, i, alteraVolta, opcaoPiloto, opcaoCircuito, flag, diaSemana=0;
	float tempoSegundosVolta, melhorVoltaSegundos;
	piloto *pPiloto;
	circuito *pCircuito;
	volta *pVolta;
	
	do {
		qtdPilotos = 0;
		qtdCircuitos = 0;
		qtdVoltas = 0;
		
		if (!existeArquivo("pilotos.dat", "rb")) {
			criaArquivo("pilotos.dat", "wb+");
		}
		if ((a = fopen("pilotos.dat", "rb+")) == NULL) {
			ERRO_DB_PILOTO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("circuitos.dat", "rb")) {
			criaArquivo("circuitos.dat", "wb+");
		}
		if ((b = fopen("circuitos.dat", "rb+")) == NULL) {
			ERRO_DB_CIRCUITO
			exit(EXIT_FAILURE);
		}
		if (!existeArquivo("voltas.dat", "rb")) {
			criaArquivo("voltas.dat", "wb+");
		}
		if ((c = fopen("voltas.dat", "rb+")) == NULL) {
			ERRO_DB_VOLTAS
			exit(EXIT_FAILURE);
		}
		
		pPiloto = coletaDadosPiloto(&qtdPilotos, a);
		pCircuito = coletaDadosCircuito(&qtdCircuitos, b);
		pVolta = coletaDadosVolta(&qtdVoltas, c);
		
		fclose(a);
		fclose(b);
		fclose(c);
		
		system("cls");
		cabecalho("ALTERACAO DE VOLTAS");
		if (qtdVoltas == 0) {
			free(pPiloto); free(pCircuito); free(pVolta);
			ERRO_VOLTAS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		if (qtdCircuitos == 0) {
			free(pPiloto); free(pCircuito); free(pVolta);
			ERRO_CIRCUITOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		if (qtdPilotos == 0) {
			free(pPiloto); free(pCircuito); free(pVolta);
			ERRO_PILOTOS
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		printf("Escolha a volta a ser alterada:\n");
		for (i = 0; i < qtdVoltas; i++) {
			printf("(%2d) - Circuito: %3d Data: %-10s", i+1, pVolta[i].circuito, pVolta[i].dataVolta);
			printf(" Equipe: %-3s Piloto: %3d", pVolta[i].equipePiloto.sigla, pVolta[i].piloto);
			printf(" Tempo: %2d:%2d:%4d\n", pVolta[i].melhorVolta.minutos, pVolta[i].melhorVolta.segundos, pVolta[i].melhorVolta.milisegundos);
		}
		leValidaInt(&alteraVolta, 1, i+1, "Digite sua escolha abaixo:\n");
		
		LINHA
		
		do {
			printf("Escolha o piloto da volta abaixo:\n");
			for (i = 0; i < qtdPilotos; i++) {
				printf("(%2d) - ID: %3d Nome: %-15s\n", i+1, pPiloto[i].id, pPiloto[i].nome);
			}
			leValidaInt(&opcaoPiloto, 1, i+1, "Digite sua escolha abaixo:\n");
			pVolta[alteraVolta-1].piloto = pPiloto[opcaoPiloto-1].id;
			pVolta[alteraVolta-1].equipePiloto = pPiloto[opcaoPiloto-1].equipePiloto;
			
			LINHA
			
			do{
				leValidaData(&pVolta[alteraVolta-1].dataVolta, "Digite a data da volta [dd/mm/aaaa]: ");
				diaSemana = calculaDiaSemana(&pVolta[alteraVolta-1].dataVolta);
				if(diaSemana!=0){
					printf("O dia da semana deve ser domingo\n");getch();system("cls");
				}
			}while(diaSemana!=0);
			
			if (qtdVoltas != 0) {
				for (i = 0; i < qtdVoltas; i++) {
					if (pVolta[alteraVolta-1].dataVolta.dia == pVolta[i].dataVolta.dia && pVolta[alteraVolta-1].dataVolta.mes == pVolta[i].dataVolta.mes && pVolta[alteraVolta-1].dataVolta.ano == pVolta[i].dataVolta.ano && pVolta[alteraVolta-1].piloto == pVolta[i].piloto && i != alteraVolta-1) {
						printf("Volta invalida! Este piloto ja esta cadastrado neste dia.\n");
						flag = 0;
						break;
					} else {
						flag = 1;
					}
				}
			}		
		} while(flag!=1);

		LINHA
		
		printf("Escolha o circuito da volta abaixo:\n");
		for (i = 0; i < qtdCircuitos; i++) {
			printf("(%2d) - ID: %3d Nome: %-15s\n", i+1, pCircuito[i].id, pCircuito[i].nome);
		}
		leValidaInt(&opcaoCircuito, 1, i+1, "Digite sua escolha abaixo:\n");
		pVolta[alteraVolta-1].circuito = pCircuito[opcaoCircuito-1].id;
		
		LINHA
		
		leValidaTempo(&pVolta[alteraVolta-1].melhorVolta.minutos, &pVolta[alteraVolta-1].melhorVolta.segundos, &pVolta[alteraVolta-1].melhorVolta.milisegundos, "Digite o tempo da volta [min:seg:mili]: ");
		tempoSegundosVolta = (pVolta[alteraVolta-1].melhorVolta.minutos * 60) + pVolta[alteraVolta-1].melhorVolta.segundos + (pVolta[alteraVolta-1].melhorVolta.milisegundos * 0.001);
		melhorVoltaSegundos = (pCircuito[opcaoCircuito-1].menorTempo.minutos * 60) + pCircuito[opcaoCircuito-1].menorTempo.segundos + (pCircuito[opcaoCircuito-1].menorTempo.milisegundos * 0.001);
		
		if (tempoSegundosVolta < melhorVoltaSegundos) {
			pCircuito[opcaoCircuito-1].menorTempo.minutos = pVolta[alteraVolta-1].melhorVolta.minutos;
			pCircuito[opcaoCircuito-1].menorTempo.segundos = pVolta[alteraVolta-1].melhorVolta.segundos;
			pCircuito[opcaoCircuito-1].menorTempo.milisegundos = pVolta[alteraVolta-1].melhorVolta.milisegundos;

			criaArquivo("auxiliar.dat", "wb");
			if ((d = fopen("auxiliar.dat", "rb+")) == NULL) {
				ERRO_AUXILIAR
				exit(EXIT_FAILURE);
			}
			for (i = 0; i < qtdCircuitos; i++) {
				fwrite((pCircuito+i), sizeof(circuito), 1, d);
			}
			fclose(d);
			remove("circuitos.dat");
			rename("auxiliar.dat", "circuitos.dat");
		}
		
		criaArquivo("auxiliar.dat", "wb");
		if ((e = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdVoltas; i++) {
			fwrite((pVolta+i), sizeof(volta), 1, e);
		}
		fclose(e);
		remove("voltas.dat");
		rename("auxiliar.dat", "voltas.dat");
		
		apresentaEscolheMenuRepete(&opcao);
		if (qtdPilotos != 0) {
			free(pPiloto);
		}
		if (qtdCircuitos != 0) {
			free(pCircuito);
		}
		if (qtdVoltas != 0) {
			free(pVolta);
		}
	} while(opcao == 's');
}

/* Objetivo: excluir uma volta
Parâmetros: nenhum
Retorno: nenhum */

void excluirVoltas(){
	FILE *a, *e;
	int qtdVoltas = 0, excluiVolta, i;
	char continuar = '\0', opcao = '\0';
	volta *pVolta = NULL;
	
	do {
		qtdVoltas = 0;
		if (!existeArquivo("voltas.dat", "rb")) {
			criaArquivo("voltas.dat", "wb+");
		}
		if ((a = fopen("voltas.dat", "rb+")) == NULL) {
			ERRO_DB_VOLTAS
			exit(EXIT_FAILURE);
		}
		
		system("cls");
		cabecalho("EXCLUSAO DE VOLTAS");
		pVolta = coletaDadosVolta(&qtdVoltas, a);
		fclose(a);
		
		if (qtdVoltas == 0) {
			free(pVolta);
			ERRO_VOLTAS
			printf("Aperte ENTER para voltar ao menu.\n");
			getch();
			return;
		}
		
		printf("Escolha a volta para excluir:\n");
		for (i = 0; i < qtdVoltas; i++) {
			printf("(%2d) - Circuito: %3d Data: %-10s", i+1, pVolta[i].circuito, pVolta[i].dataVolta);
			printf(" Equipe: %-3s Piloto: %3d", pVolta[i].equipePiloto.sigla, pVolta[i].piloto);
			printf(" Tempo: %2d:%2d:%4d\n", pVolta[i].melhorVolta.minutos, pVolta[i].melhorVolta.segundos, pVolta[i].melhorVolta.milisegundos);
		}
		leValidaInt(&excluiVolta, 1, i+1, "Digite sua opcao abaixo:\n");
		leValidaChar(&continuar, 's', 'n', "Deseja mesmo excluir esta volta? [s/n]\n");
		
		if (continuar == 'N') {
			free(pVolta);
			printf("Voce sera mandado de volta ao menu.\n");
			printf("Aperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		criaArquivo("auxiliar.dat", "wb"); 
		if ((e = fopen("auxiliar.dat", "rb+")) == NULL) {
			ERRO_AUXILIAR
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < qtdVoltas; i++) {
			if (i != excluiVolta-1) {
				fwrite((pVolta+i), sizeof(volta), 1, e);
			}
		}
		fclose(e);
		free(pVolta);
		remove("voltas.dat");
		rename("auxiliar.dat", "voltas.dat");
		
		qtdVoltas--;
		if (qtdVoltas == 0) {
			printf("Nao e possivel excluir mais voltas.\n");
			printf("Voce sera mandado de volta para o menu.\nAperte ENTER para voltar.\n");
			getch();
			return;
		}
		
		apresentaEscolheMenuRepete(&opcao);
	} while(opcao == 's');
}

/* Objetivo: gerar os números de ID dos pilotos
Entrada: vetor dos números que serão apresentados, números cadastrados, quantidade de pilotos cadastrados
Saída: nenhuma */

void geraNumerosPiloto(int *numeros, piloto *pPiloto, int *qtdPiloto) {
	int i, j, flag = 1;
	
	srand(time(NULL));
	do {
		for (i = 0; i < QTD_NUM; i++) {
			*(numeros+i) = rand() % 100;
		}
		if (*qtdPiloto != 0) {
			for (i = 0; i < *qtdPiloto; i++) {
				for (j = 0; j < QTD_NUM; j++) {
					if (*(numeros+j) == (pPiloto+i)->id) {
						flag = 0;
						break;
					} else {
						flag = 1;
					}
				}
				if (!flag) {
					break;
				}
			}			
		}
	} while(!flag);
}

/*
Objetivo: ordenar pelo nome
Parâmetros: ponteiro de pilotos, ponteiro quantidade de atletas e o tipo
Retorno: nenhum
*/

void bubbleSortNome(piloto *pilotos, int *qtdPilotos, char tipo){
	
	int i,j;
	piloto aux;
	
	if(tipo == 'C'){
		/*CRESCENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if((stricmp(pilotos[i].nome,pilotos[j].nome) > 0 && stricmp(pilotos[i].nome,""))!=0){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else if(tipo == 'D'){
		/*DESCRECENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if((stricmp(pilotos[i].nome,pilotos[j].nome) < 0 && stricmp(pilotos[i].nome,""))!=0){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else{
		printf("Parametro tipo Invalido\nOs dados nao foram ordenados\n");getch();system("cls");
		return;
	}
}

/*
Objetivo: ordenar pela idade
Parâmetros: ponteiro de pilotos, ponteiro quantidade de pilotos e o tipo
Retorno: nenhum
*/

void bubbleSortIdade(piloto *pilotos, int *qtdPilotos, char tipo){
	
	int i,j;
	piloto aux;
	
	if(tipo == 'C'){
		/*CRESCENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if(pilotos[i].idade > pilotos[j].idade){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else if(tipo == 'D'){
		/*DESCRECENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if(pilotos[i].idade < pilotos[j].idade){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else{
		printf("Parametro tipo Invalido\nOs dados nao foram ordenados\n");getch();system("cls");
		return;
	}
}

/*
Objetivo: ordenar pela quantidade de melhores voltas
Parâmetros: ponteiro de pilotos, ponteiro quantidade de pilotos e o tipo
Retorno: nenhum
*/

void bubbleSortQtdVoltas(piloto *pilotos, int *qtdPilotos, char tipo){
	
	int i,j;
	piloto aux;
	
	if(tipo == 'C'){
		/*CRESCENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if(pilotos[i].qtdMelhoresVoltas > pilotos[j].qtdMelhoresVoltas){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else if(tipo == 'D'){
		/*DESCRECENTE*/
		for(i=0;i<*qtdPilotos;i++){
			for(j=i+1;j<*qtdPilotos;j++){
				if(pilotos[i].qtdMelhoresVoltas < pilotos[j].qtdMelhoresVoltas){
					aux = pilotos[i];
					pilotos[i] = pilotos[j];
					pilotos[j] = aux;
				}	
			}
		}
	}else{
		printf("Parametro tipo Invalido\nOs dados nao foram ordenados\n");getch();system("cls");
		return;
	}
}
/*Objetivo: calcular idade
Parâmetros: data de nascimento
Retorno: idade*/

int calculaIdade(data *dataNascimento){
	
	struct tm *local;
	time_t t;
	t = time(NULL);
	local=localtime(&t);
	int idade;
	
	int anoAtual = local->tm_year+1900;
	int mesAtual = local->tm_mon+1;
	int diaAtual = local->tm_mday;	
	
	
	if(dataNascimento->mes > mesAtual){
		idade = (anoAtual - dataNascimento->ano) - 1;
	}else if(dataNascimento->mes == mesAtual){
		if(dataNascimento->dia > diaAtual){
			idade = (anoAtual - dataNascimento->ano) - 1;
		}else{
			idade = (anoAtual - dataNascimento->ano);
		}
	}else{
		idade = (anoAtual - dataNascimento->ano);
	}
	
	return idade;
}
