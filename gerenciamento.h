/* Arquivo Cabeçalho - Gerenciamento de Dados Cadastrais */

#ifndef _GERENCIAMENTO_h
#define _GERENCIAMENTO_h

#define TAM_NOME 30
#define TAM_SIGLA 4
#define TAM_DATA 11
#define QTD_NUM 3
#define ERRO_PILOTOS printf("Nenhum piloto foi encontrado.\nVolte ao menu e cadastre um.\n");
#define ERRO_EQUIPES printf("Nenhuma equipe foi encontrada.\nRetorne ao menu e cadastre uma equipe.\n");
#define ERRO_CIRCUITOS printf("Nenhum circuito foi encontrado.\nVolte ao menu e cadastre um.\n");
#define ERRO_VOLTAS printf("Nenhuma volta cadastrada.\nRetorne ao menu e cadastre uma.\n");
#define ERRO_EXCLUIR_PILOTO printf("Nao e possivel excluir nenhum piloto.\nVoce sera mandado de volta ao menu.\n");
#define ERRO_EXCLUIR_EQUIPE printf("Nao e possivel excluir nenhuma equipe.\nVoce sera mandado de volta ao menu.\n");
#define ERRO_AUXILIAR printf("Arquivo ""auxiliar.dat"" indisponivel.");
#define ERRO_DB_PILOTO printf("Arquivo ""pilotos.dat"" indisponivel.");
#define ERRO_DB_PAIS printf("Arquivo ""paises.txt"" indisponivel.");
#define ERRO_DB_EQUIP printf("Arquivo ""equipes.dat"" indisponivel.");
#define ERRO_DB_CIRCUITO printf("Arquivo ""circuitos.dat"" indisponivel.");
#define ERRO_DB_VOLTAS printf("Arquivo ""voltas.dat"" indisponivel.");
#define ERRO_DB_PAIS_VAZIO printf("O Banco de Dados de Paises esta vazio.\nPortanto, preencha manualmente.\n");
#define ERRO_CAD_PILOT printf("Piloto invalido! Este piloto ja esta cadastrado!\n");
#define ERRO_CAD_EQUIP printf("Equipe Invalida! Esta equipe ja esta cadastrada!\n");
#define ERRO_DB_EQUIPE_VAZIO printf("Arquivo ""equipes.dat"" vazio.");
#define MIN_DIA 4
#define MIN_MES 6
#define MIN_ANO 2017

typedef struct{
	int dia;
	int mes;
	int ano;
}data;

typedef struct Tempo{
	int minutos;
	int segundos;
	float milisegundos;
} tempo;

typedef struct Pais{
	char sigla[TAM_SIGLA];
	char nome[TAM_NOME];
} pais;

typedef struct Equipe{
	char nome[TAM_NOME];
	char sigla[TAM_SIGLA];
	pais paisEquipe;
} equipe;

typedef struct Piloto{
	int id;
	char nome[TAM_NOME];
	equipe equipePiloto;
	data dataNascimento;
	char sexo;
	pais paisPiloto;
	int idade;
	int qtdMelhoresVoltas;
} piloto;

typedef struct Circuito{
	int id;
	char nome[TAM_NOME];
	pais paisCircuito;
	float quilometros;
	tempo menorTempo;
	char pilotoMenorTempo[TAM_NOME];
} circuito;

typedef struct Volta{
	int piloto;
	int circuito;
	equipe equipePiloto;
	data dataVolta;
	tempo melhorVolta;
} volta;

void bubbleSortIdade(piloto *pilotos, int *qtdPilotos, char tipo);
void bubbleSortQtdVoltas(piloto *pilotos, int *qtdPilotos, char tipo);
void bubbleSortNome(piloto *pilotos, int *qtdPilotos, char tipo);
int calculaIdade(data *dataNascimento);
void geraNumerosPiloto(int *numeros, piloto *pPiloto, int *qtdPiloto);
void inclusaoPilotos();
void alterarPilotos();
void excluirPilotos();
void inclusaoEquipes();
void excluirEquipes();
void inclusaoCircuitos();
void alterarCircuitos();
void inclusaoVoltas();
void alterarVoltas();
void excluirVoltas();
#endif
