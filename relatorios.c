#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios.h"
#include "gerenciamento.h"
#include "storage.h"
#include <time.h>

/*RELATÓRIOS*/

/*R1*/
/*Objetivo: apresentar dados da categoria escolhida pelo usuario
Parâmetros: nenhum 
Retorno: nenhum */

void pesquisaDados(){
	
	char opcao,opcao2,siglaEquipe[4];
	piloto *pilotos;
	equipe *equipes;
	volta *voltas;
	circuito *circuitos;
	int qtdCircuitos=0,qtdEquipes=0,qtdPilotos=0,qtdVoltas=0,i=0,idPiloto=0,aux=0,idCircuito=0,j=0;
	data dataVolta;
	FILE *fpiloto, *fequipe, *fcircuito, *fvoltas;
	
	do{
		cabecalho("MENU RELATORIOS(1)");printf("\n");
		printf("(1) - Dados gerais dos pilotos;\n");
		printf("(2) - Dados gerais das equipes;\n");
		printf("(3) - Dados gerais dos circuitos;\n");
		printf("(4) - Dados gerais das voltas;\n");
		printf("(R) - Retornar ao menu de relatorios.\n");
		scanf(" %c", &opcao);opcao=toupper(opcao);
		
		qtdCircuitos=0;qtdEquipes=0;qtdPilotos=0;qtdVoltas=0;
		switch(opcao){
			/*PILOTOS*/
			case '1':
				leValidaChar(&opcao2,'T','F',"\nSelecione T para todos os dados ou F para filtrar: ");system("cls");
				if((fpiloto = fopen("pilotos.dat", "rb+")) == NULL) {
					ERRO_DB_PILOTO
					exit(EXIT_FAILURE);
				}
				
				pilotos = coletaDadosPiloto(&qtdPilotos,fpiloto);
				
				if(qtdPilotos == 0){
					fclose(fpiloto);	
					free(pilotos);		
					printf("Nenhum piloto cadastrado ate o momento\n");
					getch();system("cls");return;
				}
				
				cabecalho("PILOTOS");printf("\n");
					switch(opcao2){
						case 'T':
							printf("NOME                EQUIPE NASCIMENTO  ID SEXO PAIS\n");
							for(i=0;i<qtdPilotos;i++){
								printf("%-20s %4s  %2d/%2d/%-4d ",pilotos[i].nome,pilotos[i].equipePiloto.sigla,pilotos[i].dataNascimento.dia,pilotos[i].dataNascimento.mes,pilotos[i].dataNascimento.ano);
								printf("%3d  %-3c %s\n", pilotos[i].id,pilotos[i].sexo,pilotos[i].paisPiloto.nome);
							}
							break;
						case 'F':
							for(i=0;i<qtdPilotos;i++){
								printf("ID - %d\n", pilotos[i].id);
							}
							leValidaInt(&idPiloto,1,100,"\nId Piloto: ");system("cls");
							printf("PILOTO              EQUIPE NASCIMENTO  ID SEXO PAIS\n");
							for(i=0;i<qtdPilotos;i++){
								if(pilotos[i].id == idPiloto){
									printf("%-20s %4s  %2d/%2d/%-4d ",pilotos[i].nome,pilotos[i].equipePiloto.sigla,pilotos[i].dataNascimento.dia,pilotos[i].dataNascimento.mes,pilotos[i].dataNascimento.ano);
									printf("%3d  %-3c %s\n", pilotos[i].id,pilotos[i].sexo,pilotos[i].paisPiloto.nome);
									aux=1;
									break;
								}else{
									aux=0;
								}
							}
							if(aux!=1){
								printf("Nenhum piloto encontrado\n");
							}
							break;
						}	
				fclose(fpiloto);	
				free(pilotos);			
				break;
				/*EQUIPES*/
			case '2':
				leValidaChar(&opcao2,'T','F',"\nSelecione T para todos os dados ou F para filtrar: ");system("cls");
				if ((fequipe = fopen("equipes.dat", "rb+")) == NULL) {
					ERRO_DB_EQUIP
					exit(EXIT_FAILURE);
				}
				equipes = coletaDadosEquipe(&qtdEquipes,fequipe);
				
				if(qtdEquipes == 0){
					fclose(fequipe);
					free(equipes);	
					printf("Nenhuma equipe cadastrada ate o momento\n");
					getch();system("cls");return;
				}
				
				cabecalho("EQUIPES");printf("\n");
				switch(opcao2){
					case 'T':
						printf("NOME           SIGLA  PAIS\n");
						for(i=0;i<qtdEquipes;i++){
							printf("%-15s %-5s %s\n", equipes[i].nome,equipes[i].sigla,equipes[i].paisEquipe.nome);
						}
						break;
					case 'F':
						for(i=0;i<qtdEquipes;i++){
							printf("Sigla - %s\n", equipes[i].sigla);
						}
						
						leValidaNome("Escolha Equipe: ", siglaEquipe);system("cls");
						
						for(j=0;j<strlen(siglaEquipe);j++){
							siglaEquipe[j] = toupper(siglaEquipe[j]);
						}
						
						printf("NOME           SIGLA  PAIS\n");
						for(i=0;i<qtdEquipes;i++){
							for(j=0;j<strlen(equipes[j].sigla);j++){
								equipes[i].sigla[j] = toupper(equipes[i].sigla[j]);
							}
							
							if(strstr(siglaEquipe,equipes[j].sigla)!=NULL){
								printf("%-15s %-5s %s\n", equipes[i].nome,equipes[i].sigla,equipes[i].paisEquipe.nome);
							}	
						}	
						
						fclose(fequipe);
						free(equipes);
					break;	
				}
				fclose(fequipe);
				free(equipes);
				break;
				/*CIRCUITOS*/
			case '3':
				leValidaChar(&opcao2,'T','F',"\nSelecione T para todos os dados ou F para filtrar: ");system("cls");
				if ((fcircuito = fopen("circuitos.dat", "rb+")) == NULL) {
					ERRO_DB_CIRCUITO
					exit(EXIT_FAILURE);
				}
				circuitos = coletaDadosCircuito(&qtdCircuitos,fcircuito);
				
				if(qtdCircuitos == 0){
					fclose(fcircuito);
					free(circuitos);	
					printf("Nenhum circuito cadastrado ate o momento\n");getch();system("cls");return;
				}
				
				cabecalho("CIRCUITOS");printf("\n");
				switch(opcao2){
					case 'T':
						printf("Circuito       ID  Pais	Tam(Km)	 Menor Tempo Piloto Menor Tempo\n");
						for(i=0;i<qtdCircuitos;i++){
							printf("%-15s	%-3d %-3s ", circuitos[i].nome,circuitos[i].id,circuitos[i].paisCircuito.sigla);
							printf("%-7.2f %3d:%2d:%3.1f ", circuitos[i].quilometros,circuitos[i].menorTempo.minutos,circuitos[i].menorTempo.segundos,circuitos[i].menorTempo.milisegundos);
							printf(" %-10s\n", circuitos[i].pilotoMenorTempo);
						}
						break;
					case 'F':
						for(i=0;i<qtdCircuitos;i++){
							printf("ID - %d\n",circuitos[i].id);
						}	
						leValidaInt(&idCircuito,1,1000,"ID Circuito: ");system("cls");
						printf("Circuito       ID  Pais	Tam(Km)	 Menor Tempo Piloto Menor Tempo\n");
						for(i=0;i<qtdCircuitos;i++){
							if(circuitos[i].id == idCircuito){
								printf("%-15s	%-3d %-3s ", circuitos[i].nome,circuitos[i].id,circuitos[i].paisCircuito.sigla);
								printf("%-7.2f %3d:%2d:%3.1f ", circuitos[i].quilometros,circuitos[i].menorTempo.minutos,circuitos[i].menorTempo.segundos,circuitos[i].menorTempo.milisegundos);
								printf(" %-10s\n", circuitos[i].pilotoMenorTempo);
								aux = 1;
								break;		
							}else{
								aux = 0;
							}
						}
						
						if(aux!=1){
							printf("Nenhum circuito encontrado\n");
						}		
						break;
				}
				fclose(fcircuito);
				free(circuitos);	
				break;
				/*VOLTAS*/
			case '4':
				leValidaChar(&opcao2,'T','F',"\nSelecione T para todos os dados ou F para filtrar: ");system("cls");
				if ((fvoltas = fopen("voltas.dat", "rb+")) == NULL) {
					ERRO_DB_VOLTAS;
					exit(EXIT_FAILURE);
				}
				voltas = coletaDadosVolta(&qtdVoltas,fvoltas);	
				
				if(qtdVoltas == 0){
					fclose(fvoltas);
					free(voltas);
					printf("Nenhuma volta cadastrada ate o momento\n");getch();system("cls");
					return;
				}
				
				cabecalho("VOLTAS");printf("\n");
					switch(opcao2){
						case 'T':
							printf("ID Piloto ID Circuito  Equipe    Data	   Tempo\n");
							for(i=0;i<qtdVoltas;i++){
								printf("%7d %9d %9s ", voltas[i].piloto,voltas[i].circuito,voltas[i].equipePiloto.sigla);
								printf("%5d/%2d/%4d ", voltas[i].dataVolta.dia,voltas[i].dataVolta.mes,voltas[i].dataVolta.ano);
								printf("%3d:%2d:%4.1f\n", voltas[i].melhorVolta.minutos,voltas[i].melhorVolta.segundos,voltas[i].melhorVolta.milisegundos);
							}
							break;
						case 'F':
							for(i=0;i<qtdVoltas;i++){
								printf("ID - %d\n", voltas[i].piloto);
							}
							leValidaInt(&idPiloto,1,100,"\nID Piloto: ");
		
							printf("ID Piloto	ID Circuito	 Equipe  Data	Tempo\n");
							for(i=0;i<qtdVoltas;i++){
								if(idPiloto == voltas[i].piloto){
									printf("%7d %9d %9s ", voltas[i].piloto,voltas[i].circuito,voltas[i].equipePiloto.sigla);
									printf("%5d/%2d/%4d ", voltas[i].dataVolta.dia,voltas[i].dataVolta.mes,voltas[i].dataVolta.ano);
									printf("%3d:%2d:%4.1f\n", voltas[i].melhorVolta.minutos,voltas[i].melhorVolta.segundos,voltas[i].melhorVolta.milisegundos);
									aux = 1;
									break;
								}else{
									aux = 0;
								}
							}
							
							if(aux!=1){
								printf("Nenhuma volta encontrada\n");
							}
						break;		
					}
				fclose(fvoltas);
				free(voltas);	
			break;
			case 'R':
				return;
			default:
				MSG_MENU_ERRO							
		}	
		getch();system("cls");
	}while(opcao!='R');
	
}

/*R2*/
/*Objetivo: pesquisar pilotos de acordo com o nome
Parâmetros: nenhum 
Retorno: nenhum */

void pesquisaPilotos(){
	
	char nome[TAM_NOME];	
	char aux[TAM_NOME]={""};
	char *pAux;
	int i=0,flag=0,qtdPilotos=0,j=0;
	piloto *pilotos;
	FILE *fpilotos = NULL;
	
	if ((fpilotos = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO
		exit(EXIT_FAILURE);
	}
	
	pilotos = coletaDadosPiloto(&qtdPilotos,fpilotos);
	
	if(qtdPilotos == 0){
		free(pilotos);fclose(fpilotos);
		printf("Nenhum piloto cadastrado ate o momento\n");
		getch();system("cls");return;
	}
	
	cabecalho("PESQUISA PILOTOS");
	leValidaNome("Digite o nome do piloto: ",nome);	system("cls");
	
	for(i=0;i<strlen(nome);i++){
		nome[i] = toupper(nome[i]);
	}
	
	bubbleSortNome(pilotos,&qtdPilotos,'C');
	cabecalho("PILOTOS");printf("\n");
	printf("NOME                EQUIPE NASCIMENTO  ID SEXO PAIS\n");
	
	for(i=0;i<qtdPilotos;i++){
		strcpy(aux,pilotos[i].nome);
		
		for(j=0;j<strlen(aux);j++){
			aux[j] = toupper(aux[j]);
		}
		
		pAux = strstr(aux,nome);
		if(pAux){
			printf("%-20s %4s  %2d/%2d/%-4d ",pilotos[i].nome,pilotos[i].equipePiloto.sigla,pilotos[i].dataNascimento.dia,pilotos[i].dataNascimento.mes,pilotos[i].dataNascimento.ano);
			printf("%3d  %-3c %s\n", pilotos[i].id,pilotos[i].sexo,pilotos[i].paisPiloto.nome);
			flag=1;	
		}
	}
	
	if(flag!=1){
		printf("Nenhum piloto encontrado\n\n");
	}
	getch();system("cls");
	free(pilotos);fclose(fpilotos);
}


/*R3
Objetivo: apresentar os pilotos de um determinado circuito  
Parâmetros: nenhum
Retorno: nenhum 
*/

void pesquisaCircuitos(){
	
	FILE *fcircuitos=NULL,*fvolta=NULL,*fpilotos=NULL;
	int i=0,j=0,idCircuito=0,qtdVoltas=0,qtdPilotos=0,qtdCircuitos=0;
	data data;
	volta *voltas;
	piloto *pilotos;
	circuito *circuitos;
	
	int flag=0;
	char aux;
		
	cabecalho("PESQUISA CIRCUITOS");printf("\n");

	if ((fcircuitos = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO;
		exit(EXIT_FAILURE);
	}
	circuitos = coletaDadosCircuito(&qtdCircuitos,fcircuitos);
	
	if(qtdCircuitos == 0){
		fclose(fcircuitos);free(circuitos);
		printf("Nenhum circuito cadastrado ate o momento\n");getch();system("cls");
		return;
	}

	if ((fvolta = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS;
		exit(EXIT_FAILURE);
	}
	voltas = coletaDadosVolta(&qtdVoltas,fvolta);
	
	pilotos = coletaDadosPiloto(&qtdPilotos,fpilotos);
	if ((fpilotos = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO;
		exit(EXIT_FAILURE);
	}
	pilotos = coletaDadosPiloto(&qtdPilotos,fpilotos);
	
	for(i=0;i<qtdCircuitos;i++){
		printf("Nome: %s - (ID): %d\n", circuitos[i].nome, circuitos[i].id);
	}
	
	leValidaInt(&idCircuito,1,100,"\nDigite o ID do Circuito: ");
	leValidaChar(&aux,'S','N',"Deseja adicionar uma data - (S/N): ");
	
	if(aux == 'S'){
		leValidaData(&data,"Digite uma data - [dd/mm/aaaa]: ");	system("cls");
		cabecalho("CIRCUITO");printf("\n");
		printf("Pilotos\n");
		printf("NOME           EQUIPE TEMPO\n");
		for(i=0;i<qtdVoltas;i++){
			if(voltas[i].dataVolta.dia == data.dia && voltas[i].dataVolta.mes == data.mes && voltas[i].dataVolta.ano == data.ano){
					if(voltas[i].circuito == idCircuito){
						for(j=0;j<qtdPilotos;j++){
							if(voltas[i].piloto == pilotos[j].id){
								printf("%-15s %-5s", pilotos[j].nome,pilotos[j].equipePiloto.sigla);
								printf("%3d:%2d:%3.1f\n", voltas[i].melhorVolta.minutos,voltas[i].melhorVolta.segundos,voltas[i].melhorVolta.milisegundos);
								flag=1;
						}
					}	
				}	
			}
		}	
		if(flag!=1){
			printf("\nNenhum dado encontrado\n");
		}	
	}else{	
		cabecalho("CIRCUITO");printf("\n");
		printf("Pilotos\n");
		printf("NOME           EQUIPE TEMPO\n");
		for(i=0;i<qtdVoltas;i++){
			if(voltas[i].circuito == idCircuito){
				for(j=0;j<qtdPilotos;j++){
					if(voltas[i].piloto == pilotos[j].id){
							printf("%-15s %-5s", pilotos[j].nome,pilotos[j].equipePiloto.sigla);
							printf("%3d:%2d:%3.1f\n", voltas[i].melhorVolta.minutos,voltas[i].melhorVolta.segundos,voltas[i].melhorVolta.milisegundos);
							flag=1;
					}
				}	
			}
		}
		
		if(flag!=1){
			printf("Nenhum dado encontrado\n");
		}	
	}	
	getch();system("cls");
	fclose(fcircuitos);free(circuitos);
	fclose(fpilotos);free(pilotos);
	fclose(fvolta);free(voltas);
}

/*R4
Objetivo: apresentar circuitos cadastrados de acordo com codigo ou nome
Parâmetros: 
Retorno: nenhum 
*/

void apresentaCircuitosCadastrados(){
	
	char opcao;
	char nome[TAM_NOME],aux[TAM_NOME]={""};
	circuito *circuito=NULL;
	int qtdCircuitos,idCircuito,j=0,i=0,flag=0;
	FILE *fcircuitos;

	if ((fcircuitos = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO;
		exit(EXIT_FAILURE);
	}
	free(circuito);
	circuito = coletaDadosCircuito(&qtdCircuitos,fcircuitos);
	
	if(qtdCircuitos == 0){
		free(circuito);fclose(fcircuitos);
		printf("Nenhum circuito cadastrado\n");getch();system("cls");
		return;
	}
	
	cabecalho("CIRCUITOS");printf("\n");
	printf("(1) - Consultar por nome\n");
	printf("(2) - Consultar por codigo\n");
	scanf(" %c", &opcao);opcao=toupper(opcao);system("cls");
	cabecalho("CIRCUITOS");printf("\n");
	
	switch(opcao){
		case '1':
			leValidaNome("Digite o nome do circuito: ", nome);system("cls");
			cabecalho("CIRCUITOS");printf("\n");
			printf("NOME           ID   Pais Tam(Km)  Menor Tempo  Piloto com Menor Tempo\n");
			for(i=0;i<strlen(nome);i++){
				nome[i] = toupper(nome[i]);
			}
			
			for(i=0;i<qtdCircuitos;i++){
				strcpy(aux,circuito[i].nome);
				
				for(j=0;j<strlen(aux);j++){
					aux[j] = toupper(aux[j]);
				}
			
				if(strstr(aux,nome)!=NULL){
					printf("%-15s %-3d %4s ", circuito[i].nome,circuito[i].id,circuito[i].paisCircuito.sigla);
					printf("%7.2f %3d:%2d:%3.2f ", circuito[i].quilometros,circuito[i].menorTempo.minutos,circuito[i].menorTempo.segundos,circuito[i].menorTempo.milisegundos);
					printf(" %s\n", circuito[i].pilotoMenorTempo);
					flag = 1;
				}else{
					flag = 0;
				}
			}
			
			if(flag != 1){
				printf("Nenhum circuito encontrado\n");getch();system("cls");
			}
			break;
		case '2':
			for(i=0;i<qtdCircuitos;i++){
				printf("ID %d - %s\n", circuito[i].id,circuito[i].nome);		
			}
			leValidaInt(&idCircuito,1,1000,"\nID Circuito: ");system("cls");
			printf("NOME           ID   Pais Tam(Km)  Menor Tempo  Piloto com Menor Tempo\n");
			for(i=0;i<qtdCircuitos;i++){
				if(circuito[i].id == idCircuito){
					printf("%-15s %-3d %4s ", circuito[i].nome,circuito[i].id,circuito[i].paisCircuito.sigla);
					printf("%7.2f %3d:%2d:%3.2f ", circuito[i].quilometros,circuito[i].menorTempo.minutos,circuito[i].menorTempo.segundos,circuito[i].menorTempo.milisegundos);
					printf(" %s\n", circuito[i].pilotoMenorTempo);
					flag = 1;
				}else{
					flag = 0;
				}
			}	
			
			if(flag!=1){
				printf("Nenhum circuito encontrado\n");
			}
		break;	
	}
	getch();system("cls");
	free(circuito);fclose(fcircuitos);
	
}

/*R5
Objetivo: apresentar pilotos de acordo com um intervalo de datas 
Parâmetros: nenhum
Retorno: nenhum*/

void apresentaPilotosData(){
	
	data dataInicial;
	data dataFinal;
	char auxEquipe[4];
	FILE *fvolta,*fcircuito,*fpiloto, *fequipes;
	int flag=0,qtdVoltas=0,qtdPilotos=0,qtdCircuitos=0,qtdEquipes=0,i=0,j=0,k=0,l=0;
	int dataFim,dataInit,aux,flag2=0;
	volta *voltas;
	piloto *pilotos;
	circuito *circuitos;
	equipe *equipes;
	
	if ((fequipes = fopen("equipes.dat", "rb+")) == NULL) {
		ERRO_DB_EQUIP;
		exit(EXIT_FAILURE);
	}
	equipes = coletaDadosEquipe(&qtdEquipes,fequipes);
	
	if(qtdEquipes==0){
		free(equipes);fclose(fequipes);
		printf("Nenhuma equipe cadastrada ate o momento\n");getch();system("cls");return;
	}
	
	if ((fpiloto = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO;
		exit(EXIT_FAILURE);
	}
	pilotos = coletaDadosPiloto(&qtdPilotos,fpiloto);
	
	
	if ((fcircuito = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO;
		exit(EXIT_FAILURE);
	}
	circuitos = coletaDadosCircuito(&qtdCircuitos,fcircuito);
	
	if ((fvolta = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS;
		exit(EXIT_FAILURE);
	}
	voltas = coletaDadosVolta(&qtdVoltas,fvolta);

	bubbleSortNome(pilotos,&qtdPilotos,'C');
	
	/*Validação do intervalo de data*/
	do{
		fflush(stdin);
		cabecalho("PILOTOS - DATA");printf("\n");
		
		for(i=0;i<qtdEquipes;i++){
			printf("(%d) - %s", i+1, equipes[i].sigla);
		}
		
		leValidaSigla("\nDigite a sigla da equipe: ", &auxEquipe);
		leValidaData(&dataInicial,"Data Inicial - [dd/mm/aaaa]: ");
		leValidaData(&dataFinal,"Data Final - [dd/mm/aaaa]: ");
		system("cls");
		
		/*REGRA PRA VERIFICAR INTERVALOS DE TEMPO*/
		dataInit = (dataInicial.dia + (dataInicial.mes * 30) + ((dataInicial.ano - 2016) * 365));
		dataFim = (dataFinal.dia + (dataFinal.mes * 30) + ((dataFinal.ano - 2016) * 365));
	
		if(dataInit > dataFim){
			printf("Intervalos entre datas invalido\nDigite Novamente\n");getch();system("cls");
			flag=1;
		}else{
			flag=0;
		}
	}while(flag!=0);
	
	flag=0;
	cabecalho("PILOTOS");printf("\n");
	printf("NOME            ID EQUIPE  DATA        CIRCUITO\n");

	for(k=0;k<qtdEquipes;k++){
		if(stricmp(auxEquipe,equipes[k].sigla)==0){
			flag2=1;
				for(j=0;j<qtdPilotos;j++){
					if(stricmp(pilotos[j].equipePiloto.sigla,auxEquipe)==0){
						for(i=0;i<qtdVoltas;i++){
							aux = (voltas[i].dataVolta.dia + (voltas[i].dataVolta.mes*30) + ((voltas[i].dataVolta.ano-2016)*365));
							if(aux >= dataInit && aux <= dataFim){
								flag=1;
								if(pilotos[j].id == voltas[i].piloto){
									printf("%-15s %-3d %-5s ", pilotos[j].nome, pilotos[j].id, pilotos[j].equipePiloto.sigla);
									printf("%2d/%2d/%4d ", voltas[i].dataVolta.dia,voltas[i].dataVolta.mes,voltas[i].dataVolta.ano);
									for(l=0;l<qtdCircuitos;l++){
										if(voltas[i].circuito == circuitos[l].id){
											printf("%15s\n", circuitos[l].nome);
											break;
										}
									break;
								}	
							}
						}
					}
				}
			}
		}
	}
	
	if(flag2!=1){
		printf("Nenhuma equipe encontrada\n");
	}	
				
	if(flag!=1){
		printf("Nao foi encontrado nenhum dado com as datas selecionadas\n");
	}
		
	getch();system("cls");
	free(voltas);free(circuitos);free(pilotos);free(equipes);
	fclose(fpiloto);fclose(fcircuito);fclose(fvolta);fclose(fequipes);	
}

/*R6
Objetivo: apresentar dados de acordo com o tempo desejado
Parâmetros: nenhum 
Retorno: nenhum */

void apresentaDadosTempo(){
	
	tempo tempo;
	volta *volta;
	int qtdVoltas=0,aux=0,i=0;
	float tempoAux;
	FILE *fvoltas=NULL;
	
	if ((fvoltas = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS;
		exit(EXIT_FAILURE);
	}
	
	volta = coletaDadosVolta(&qtdVoltas,fvoltas);
	
	if(qtdVoltas==0){
		printf("Nenhuma volta cadastrada ate o momento\n");
		getch();system("cls");return;
	}
	
	cabecalho("PESQUISA TEMPO");printf("\n");
	leValidaTempo(&tempo.minutos,&tempo.segundos,&tempo.milisegundos,"Tempo desejado - [min:seg:mil]: ");system("cls");
	cabecalho("PESQUISA TEMPO");printf("\n");
	tempoAux = (tempo.minutos * 60) + tempo.segundos + (tempo.milisegundos/1000);
	printf("ID Piloto ID Circuito  Equipe    Data	   Tempo\n");
	for(i=0;i<qtdVoltas;i++){
		if(((volta[i].melhorVolta.minutos * 60) + volta[i].melhorVolta.segundos + (volta[i].melhorVolta.milisegundos/1000))<=tempoAux){
			printf("%7d %9d %9s ", volta[i].piloto,volta[i].circuito,volta[i].equipePiloto.sigla);
			printf("%5d/%2d/%4d ", volta[i].dataVolta.dia,volta[i].dataVolta.mes,volta[i].dataVolta.ano);
			printf("%3d:%-2d:%4.1f\n", volta[i].melhorVolta.minutos,volta[i].melhorVolta.segundos,volta[i].melhorVolta.milisegundos);
			aux=1;
		}
	}
	
	if(aux!=1){
		printf("Nenhuma volta encontrada\n");
	}
	
	getch();system("cls");
	free(volta);fclose(fvoltas);

}

/*R7
Objetivo: apresentar dados que não estão cadastrados em melhores voltas 
Parâmetros: nenhum
Retorno: nenhum */

void apresentaDadosSem_melhorVolta(){

	char opcao;
	piloto *pilotos;
	equipe *equipes;
	circuito *circuitos;
	volta *voltas;
	int contador=0,i=0,j=0,flag=0;
	int qtdVoltas=0,aux=0;
	FILE *fvoltas, *fcircuitos,*fequipes,*fpilotos;
	
	if ((fvoltas = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS;
		exit(EXIT_FAILURE);
	}
	voltas = coletaDadosVolta(&qtdVoltas,fvoltas);
		
	do{	
		cabecalho("Cadastros Sem Melhores Voltas");printf("\n");
		printf("(1) - Pilotos\n");
		printf("(2) - Equipes\n");
		printf("(3) - Circuitos\n");
		printf("(4) - Retornar ao Menu\n");
		scanf(" %c", &opcao);system("cls");
		cabecalho("Cadastros Sem Melhores Voltas");printf("\n");
		contador=0;
		switch(opcao){
			case '1':
				if ((fpilotos = fopen("pilotos.dat", "rb+")) == NULL) {
					ERRO_DB_PILOTO;
					exit(EXIT_FAILURE);
				}
				pilotos = coletaDadosPiloto(&contador,fpilotos);
				flag=0;
				for(i=0;i<contador;i++){
					for(j=0;j<qtdVoltas;j++){
						if(pilotos[i].id != voltas[j].piloto){
							aux++;				
						}
					}
					
					if(aux == qtdVoltas){
						printf("Piloto %s nao esta cadastrado em nenhuma melhor volta\n", pilotos[i].nome);getch();
						flag=1;
						aux=0;
					}
				}
					
				if(flag!=1){
					printf("Nenhum dado encontrado\n");getch();
				}
				free(pilotos);fclose(fpilotos);
				break;
			case '2':
				flag=0;
				if ((fequipes = fopen("equipes.dat", "rb+")) == NULL) {
					ERRO_DB_EQUIP;
					exit(EXIT_FAILURE);
				}
				equipes = coletaDadosEquipe(&contador,fequipes);
				for(i=0;i<contador;i++){
					for(j=0;j<qtdVoltas;j++){
						aux=0;
						if(stricmp(equipes[i].sigla,voltas[j].equipePiloto.sigla)!=0){
							aux++;				
						}
					}
					if(aux == qtdVoltas){
						printf("Equipe %s nao esta cadastrada em nenhuma melhor volta\n", equipes[i].nome);getch();
						flag=1;
						aux=0;
					}
				}
				
				if(flag!=1){
					printf("Nenhum dado encontrado\n");getch();
				}
				free(equipes);fclose(fequipes);
				break;
			case '3':
					flag=0;
					if ((fcircuitos = fopen("circuitos.dat", "rb+")) == NULL) {
						ERRO_DB_CIRCUITO;
						exit(EXIT_FAILURE);
					}
					circuitos = coletaDadosCircuito(&contador,fcircuitos);
					for(i=0;i<contador;i++){
						for(j=0;j<qtdVoltas;j++){
							aux=0;
							if(circuitos[i].id != voltas[j].circuito){
								aux++;				
							}	
						}
						if(aux == qtdVoltas){
							printf("Circuito %s nao esta cadastrado em nenhuma melhor volta\n", circuitos[i].nome);getch();
							flag=1;
							aux=0;
						}
					}
				if(flag!=1){
					printf("Nenhum dado encontrado\n");getch();
				}
				free(circuitos);fclose(fcircuitos);
				break;
			case '4':
				free(voltas);fclose(fvoltas);
				return;
			default:
				printf("\nOpcao Invalida\nDigite Novamente\n");getch();			
		}
		system("cls");
	}while(opcao!='4');
	
	free(voltas);fclose(fvoltas);
}


/*R8
Objetivo: apresentar relatorios dos pilotos sintetico e analitico 
Parâmetros: o tipo - 1 para exibir ultimo relatorio sintetico ou 0
Retorno: nenhum 
*/

void apresentaPilotosR8R9(int tipo){
	
	piloto *pilotos, *auxPiloto;
	circuito *circuitos;
	equipe *equipes;
	int i=0,j=0,k=0,qtdPilotos=0,qtdVoltas=0,idPiloto=0,qtdCircuitos=0,qtdEquipes=0;
	char siglaEquipe[4],opcao,opcao2,opcao3; 
	volta *voltas;
	int auxQtdPilotos=0,flag=0,flag2=0;
	FILE *fParametro;
	FILE *fcircuitos, *fequipes, *fpilotos, *fvoltas;
	int qtdAniversario=0;

	
	if(tipo==1){
		if((fParametro = fopen("r8.txt","rt"))==NULL){
			printf("Arquivo nao disponivel\nRealize uma primeira busca\n");getch();system("cls");
			return;
		}
	}
	
	if ((fequipes = fopen("equipes.dat", "rb+")) == NULL) {
		ERRO_DB_EQUIP;
		exit(EXIT_FAILURE);
	}
	equipes = coletaDadosEquipe(&qtdEquipes,fequipes);
	
	if ((fcircuitos = fopen("circuitos.dat", "rb+")) == NULL) {
		ERRO_DB_CIRCUITO;
		exit(EXIT_FAILURE);
	}
	circuitos = coletaDadosCircuito(&qtdCircuitos,fcircuitos);
	
	if ((fpilotos = fopen("pilotos.dat", "rb+")) == NULL) {
		ERRO_DB_PILOTO;
		exit(EXIT_FAILURE);
	}
	pilotos = coletaDadosPiloto(&qtdPilotos,fpilotos);
	
	if ((fvoltas = fopen("voltas.dat", "rb+")) == NULL) {
		ERRO_DB_VOLTAS;
		exit(EXIT_FAILURE);
	}
	voltas = coletaDadosVolta(&qtdVoltas,fvoltas);
	
	if(tipo == 0){
		cabecalho("EQUIPES");printf("\n");
		for(i=0;i<qtdEquipes;i++){
			printf("Sigla - %s\n", equipes[i].sigla);
		}
		
		leValidaNome("Sigla da Equipe: ", siglaEquipe);system("cls");
		
		for(i=0;i<qtdEquipes;i++){
			if(stricmp(siglaEquipe,equipes[i].sigla)==0){
				flag=1;
			}
		}
		
		if(flag!=1){
			printf("Nenhuma equipe encontrada\n");getch();system("cls");
			return;
		}
	}else{
		fscanf(fParametro,"%c %c %s",&opcao,&opcao2,&siglaEquipe);
		fclose(fParametro);
	}

	do{
		//Tipo 1 Para exibir relatorio imediatamente
			auxPiloto = (piloto *) calloc(qtdPilotos,sizeof(piloto));
			if(auxPiloto == NULL){
				printf("Erro na alocacao de memoria\n");getch();system("cls");
				return;
			}
			
			for(i=0;i<qtdPilotos;i++){
				if(stricmp(siglaEquipe,pilotos[i].equipePiloto.sigla)==0){
				 	auxPiloto[j] = pilotos[i]; 
				 	auxPiloto[j].idade = calculaIdade(&auxPiloto[j].dataNascimento);
					j+=1;	
				}
			}
			
			if(j==0){
				printf("Nenhum piloto cadastrado nesta equipe\n");getch();system("cls");
				return;
			}
			
			auxQtdPilotos = j;
			
			for(i=0;i<auxQtdPilotos;i++){
				auxPiloto[i].qtdMelhoresVoltas = 0;
			}
			
			//CONTANDO QUANTIDADE DE MELHORES VOLTAS DOS PILOTOS DA EQUIPE
			for(i=0;i<auxQtdPilotos;i++){
				for(k=0;k<qtdVoltas;k++){
					if(auxPiloto[i].id == voltas[k].piloto){
						auxPiloto[i].qtdMelhoresVoltas+=1;
					}
				}
			}
			
		if(tipo==1){
			cabecalho("ULTIMO RELATORIO SINTETICO");printf("\n");
		}else{	
			cabecalho("FORMATO APRESENTACAO");printf("\n");
			printf("(1) - Apresentar ordenando idade\n");
			printf("(2) - Apresentar ordenando numero de voltas\n");
			printf("(3) - Apresentar ordenando nome do piloto\n");
			printf("(4) - Retornar ao menu principal\n");
			scanf(" %c", &opcao);
			leValidaChar(&opcao2,'C','D',"\nOrdenacao - C - Crescente ou D - Decrescente: ");system("cls");
		}
		cabecalho("PILOTOS");printf("\n");
		switch(opcao){
			case '1':
				bubbleSortIdade(auxPiloto,&auxQtdPilotos,opcao2);
				printf("Idade  Nome		Quantidade Melhores Voltas\n");
				for(i=0;i<auxQtdPilotos;i++){
					printf("%-5d  %-15s	 %12d\n", auxPiloto[i].idade, auxPiloto[i].nome, auxPiloto[i].qtdMelhoresVoltas);
				}
				break;
			case '2':
				bubbleSortQtdVoltas(auxPiloto,&auxQtdPilotos,opcao2);
				printf("Idade  Nome		Quantidade Melhores Voltas\n");
				for(i=0;i<auxQtdPilotos;i++){
					printf("%-5d  %-15s	 %12d\n", auxPiloto[i].idade, auxPiloto[i].nome, auxPiloto[i].qtdMelhoresVoltas);
				}
				break;	
			case '3':
				bubbleSortNome(auxPiloto,&auxQtdPilotos,opcao2);
				printf("Idade  Nome		Quantidade Melhores Voltas\n");
				for(i=0;i<auxQtdPilotos;i++){
					printf("%-5d  %-15s	 %12d\n", auxPiloto[i].idade, auxPiloto[i].nome, auxPiloto[i].qtdMelhoresVoltas);
				}
				break;
			case '4':
				return;
			default:
				printf("Opcao Invalida\nDigite Novamente\n");	
		}
	
		if(tipo == 1){
			free(voltas);free(pilotos);free(auxPiloto);free(circuitos);
			fclose(fvoltas);fclose(fcircuitos);fclose(fpilotos);fclose(fequipes);
			getch();system("cls");
			return;
		}
		
		if(opcao!='4'){
			fParametro = fopen("r8.txt","wt");
			if(fParametro == NULL){
				printf("Erro na criacao do arquivo\n");
				return;
			}
			
			fprintf(fParametro,"%c %c %s",opcao,opcao2,siglaEquipe);
			fclose(fParametro);
		}
		
		//Relatório R9
			leValidaChar(&opcao3,'S','N',"\nDeseja apresentar o relatorio de melhores voltas - (S/N): ");system("cls");	
		do{		
			if(opcao3 == 'S'){
				cabecalho("ID PILOTOS");printf("\n");
				for(i=0;i<auxQtdPilotos;i++){
					printf("ID %-3d - %s\n", auxPiloto[i].id,auxPiloto[i].nome);
				}
				leValidaInt(&idPiloto,0,1000000,"\nId do Piloto: ");	
			}else{
				free(voltas);free(pilotos);free(auxPiloto);free(circuitos);
				fclose(fvoltas);fclose(fcircuitos);fclose(fpilotos);fclose(fequipes);
				return;
			}
			
			system("cls");
			cabecalho("MELHORES VOLTAS DO PILOTO");printf("\n");
			for(i=0;i<auxQtdPilotos;i++){
				if(idPiloto == pilotos[i].id){
					qtdAniversario = qtdDiasAniversario(&pilotos[i].dataNascimento);
					flag=1;
					printf("PILOTO - %s == ", pilotos[i].nome);
					printf("Dias Aniversario: ");
						if(qtdAniversario<0){
							printf("Aniversario ja comemorado\n");
						}else if(qtdAniversario==0){
							printf("Feliz Aniversario!!\n");
						}else{
							printf("%d Dias\n", qtdAniversario);
						}
					printf("CIRCUITO         DATA\n");
					for(j=0;j<qtdVoltas;j++){
						if(pilotos[i].id == voltas[j].piloto){
							flag2=1;
							for(k=0;k<qtdCircuitos;k++){
								if(voltas[j].circuito == circuitos[k].id){
									printf("%-15s ",circuitos[k].nome);	
								}
							}
								printf("%2d/%2d/%4d\n", voltas[j].dataVolta.dia,voltas[j].dataVolta.mes,voltas[j].dataVolta.ano);
							}
						}
					}	
				}
					
			if(flag!=1){
				printf("Nenhum piloto encontrado com este id\n");
			}
			
			if(flag2!=1){
				printf("\nPiloto nao possui nenhuma melhor volta\n");
			}
			
			leValidaChar(&opcao,'R','C',"\nR - Retornar ao menu ou C - continuar: ");system("cls");
			if(opcao == 'R'){
				return;
			}
		}while(opcao == 'C');
			
	}while(opcao != '4');

	free(voltas);free(pilotos);free(auxPiloto);free(circuitos);
	fclose(fvoltas);fclose(fcircuitos);fclose(fpilotos);fclose(fequipes);
}




