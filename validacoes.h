/*Arquivo de Cabeçalho - Fuções de Validação*/
#ifndef _VALIDACOES_h
#define _VALIDACOES_h

#include "gerenciamento.h"

#define TAM_DATA 11

void leValidaFloat(float *pValor, float valorMin, float valorMax, char *texto);
void leValidaNome(char *texto, char *nome);
void leValidaChar(char *pChar, char X, char Y, char *titulo);
void leValidaInt(int *pValor,int valorMin, int valorMax, char *texto);
void leValidaData(data *data, char *texto);
void leValidaSigla(char *texto, char *sigla);
void leValidaTempo(int *minutos, int *segundos, float *milissegundos, char *texto);
int qtdDiasAniversario(data *dataAniversario);
int calculaDiaSemana(data *dataVolta);

#endif
