/* Arquivo Cabeçalho - Funções de Armazenamento */

#ifndef _STORAGE_h
#define _STORAGE_h

#define EXIT_FAILURE 1

int existeArquivo(char *nomeArquivo, char *tipo);
void criaArquivo(char *nomeArquivo, char *tipo);
equipe* coletaDadosEquipe(int *qtdEquipCad, FILE *f);
piloto* coletaDadosPiloto(int *qtdPiloto, FILE *f);
circuito* coletaDadosCircuito(int *qtdCircuito, FILE *f);
volta* coletaDadosVolta(int *qtdVolta, FILE *f);
pais* coletaDadosPais(int *qtdPaisCad, FILE *p);
#endif
