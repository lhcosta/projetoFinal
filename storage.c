/* Armazenamento(storage) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"
#include "storage.h"

/* Objetivo: Verificar a existência de um arquivo.
Entrada: Nome do arquivo a ser verificada a existência.
Saída: Inteiro com o valor lógico referente a existência do arquivo. */

int existeArquivo(char *nomeArquivo, char *tipo) {
	FILE *f;
	if((f = fopen(nomeArquivo, tipo)) == NULL) {
		return 0;
	} else {
		fclose(f);
		return 1;
	}
}

/* Objetivo: Criar um arquivo binário.
Entrada: Nome do arquivo a ser criado.
Saída: Nenhuma. */

void criaArquivo(char *nomeArquivo, char *tipo) {
	FILE *f = NULL;
	if((f = fopen(nomeArquivo, tipo)) == NULL) {
		printf("Nao foi possivel criar o arquivo %s.\n", nomeArquivo);
		getch();
		exit(EXIT_FAILURE);
	} else {
		fclose(f);
	}
}

/* Objetivo: Coletar os dados das equipes do arquivo e armazená-los em uma alocação dinâmica.
Entrada: Ponteiro da quantidade das equipes, do arquivo onde estão as esquipes.
Saída: Ponteiro da alocação dinâmica das equipes. */

equipe* coletaDadosEquipe(int *qtdEquipe, FILE *f) {
	equipe aux, *pEquipe = NULL;
	int i = 0;
	
	fseek(f, 0, SEEK_SET);
	while(fread(&aux, sizeof(equipe), 1, f) == 1) {
		*qtdEquipe += 1;
	}
	if (*qtdEquipe != 0) {
		if((pEquipe = (equipe*) calloc(*qtdEquipe, sizeof(equipe))) == NULL) {
			printf("Nao foi possivel alocar para as equipes.\n");
			getch();
			exit(EXIT_FAILURE);
		}
		fseek(f, 0, SEEK_SET);
		while(fread((pEquipe+i), sizeof(equipe), 1, f) == 1) {
			i++;
		}
	}
	return pEquipe;
}

/* Objetivo: Coletar os dados dos pilotos do arquivo e armazená-los em uma alocação dinâmica.
Entrada: Ponteiro da quantidade dos pilotos, do arquivo onde estão os pilotos.
Saída: Ponteiro da alocação dinâmica dos pilotos. */

piloto* coletaDadosPiloto(int *qtdPiloto, FILE *f) {
	piloto aux, *pPiloto = NULL;
	int i = 0;
	
	fseek(f, 0, SEEK_SET);
	while(fread(&aux, sizeof(piloto), 1, f) == 1) {
		*qtdPiloto += 1;
	}
	if (*qtdPiloto != 0) {
		if ((pPiloto = (piloto*) calloc(*qtdPiloto,sizeof(piloto))) == NULL) {
			printf("Nao foi possivel alocar para os pilotos.\n");
			getch();
			exit(EXIT_FAILURE);
		}
		fseek(f, 0, SEEK_SET);
		while(fread((pPiloto+i), sizeof(piloto), 1, f) == 1) {
			i++;
		}
	}
	return pPiloto;
}

/* Objetivo: Coletar os dados dos circuitos do arquivo e armazená-los em uma alocação dinâmica.
Entrada: Ponteiro da quantidade dos circuitos, do arquivo onde estão os circuitos.
Saída: Ponteiro da alocação dinâmica dos circuitos. */

circuito* coletaDadosCircuito(int *qtdCircuito, FILE *f) {
	circuito aux, *pCircuito = NULL;
	int i = 0;
	
	fseek(f, 0, SEEK_SET);
	while(fread(&aux, sizeof(circuito), 1, f) == 1) {
		*qtdCircuito += 1;
	}
	if (*qtdCircuito != 0) {
		if ((pCircuito = (circuito*) calloc(*qtdCircuito, sizeof(circuito))) == NULL) {
			printf("Nao foi possivel alocar para os circuitos.\n");
			getch();
			exit(EXIT_FAILURE);
		}
		fseek(f, 0, SEEK_SET);
		while(fread((pCircuito+i), sizeof(circuito), 1, f) == 1) {
			i++;
		}
	}
	return pCircuito;
}

/* Objetivo: Coletar os dados de voltas do arquivo e armazená-los em uma alocação dinâmica.
Entrada: Ponteiro da quantidade das voltas, do arquivo onde estão as voltas.
Saída: Ponteiro da alocação dinâmica das voltas. */

volta* coletaDadosVolta(int *qtdVolta, FILE *f) {
	volta aux, *pVolta = NULL;
	int i = 0;
	
	fseek(f, 0, SEEK_SET);
	while(fread(&aux, sizeof(volta), 1, f) == 1) {
		*qtdVolta += 1;
	}
	if (*qtdVolta != 0) {
		if ((pVolta = (volta*) calloc(*qtdVolta, sizeof(volta))) == NULL) {
			printf("Nao foi possivel alocar para as voltas.\n");
			getch();
			exit(EXIT_FAILURE);
		}
		fseek(f, 0, SEEK_SET);
		while(fread((pVolta+i), sizeof(volta), 1, f) == 1) {
			i++;
		}
	}
	return pVolta;
}

/* Objetivo: Coletar os dados dos paises do arquivo e armazená-los em uma alocação dinâmica.
Entrada: Ponteiro da quantidade dos paises, do arquivo onde estão os paises.
Saída: Ponteiro da alocação dinâmica dos paises. */

pais* coletaDadosPais(int *qtdPais, FILE *f) {
	pais aux, *pPais = NULL;
	int i = 0;
	
	fseek(f, 0, SEEK_SET);
	while(!feof(f)) {
		fscanf(f, "%s", &aux.sigla);
		fseek(f, (long) sizeof(char), SEEK_CUR);
		fscanf(f, "%[^\n]s\n", &aux.nome);
		*qtdPais += 1;
	}
	if (*qtdPais != 0) {
		if ((pPais = (pais*) calloc(*qtdPais, sizeof(pais))) == NULL) {
			printf("Nao foi possivel alocar para os paises.\n");
			getch();
			exit(EXIT_FAILURE);
		}
		fseek(f, 0, SEEK_SET);
		while(!feof(f)) {
			fscanf(f, "%s", (pPais+i)->sigla);
			fseek(f, (long) sizeof(char), SEEK_CUR);
			fscanf(f, "%[^\n]s\n", (pPais+i)->nome);
			i++;
		}
	}
	return pPais;
}
