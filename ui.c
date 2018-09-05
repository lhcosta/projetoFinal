#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void cabecalho(char texto[TAM_TEXTO]) {
	int i;
	int j,tam=0;
	
	tam = ((80 - strlen(texto)))/2;
	
	for(j=1;j<tam;j++){
		printf(" ");
	}
	CSE
	for (i = 1; i <= (strlen(texto) + 2); i++) {
		HOR
	}
	CSD
	for(j=1;j<tam;j++){
		printf(" ");
	}
	VEE
	printf(" %s ", texto); 
	VED
	for(j=1;j<tam;j++){
		printf(" ");
	}
	CIE
	for (i = 1; i <= (strlen(texto) + 2); i++) {
		HOR
	}
	CID

	
} 

void telaEntrada(){
	
	system("mode con:cols=80 lines=25"); //Define o tamanho da console
	
    printf("||||||      |||||| |||||||||||||||||| |||||||||||||||||| ||||||||||||||||||\n");sleep(0.5);system("color F0");
	printf("||| ||      || ||| |||            |||        ||||        |||            |||\n");sleep(0.5);system("color 0F");
	printf("|||  ||    ||  ||| |||            |||        ||||        |||            |||\n");sleep(0.5);system("color F0");
	printf("|||   ||  ||   ||| |||            |||        ||||        |||            |||\n");sleep(0.5);system("color 0F");
	printf("|||    ||||    ||| |||            |||        ||||        |||            |||\n");sleep(0.5);system("color F0");
	printf("|||     ||     ||| |||            |||        ||||        |||            |||\n");sleep(0.5);system("color 0F");
	printf("|||            ||| ||||||||||||||||||        ||||        ||||||||||||||||||\n");sleep(0.5);system("color F0");
	printf("                                                                           \n");sleep(0.5);system("color 0F");
	printf("                   |||||||||||||||||| |||||||||||||||||                    \n");sleep(0.5);system("color F0");
    printf("                   |||                |||           |||                    \n");sleep(0.5);system("color 0F");
    printf("                   |||                |||           |||                    \n");sleep(0.5);system("color F0");
    printf("                   |||       |||||||| |||||||||||||||||                    \n");sleep(0.5);system("color 0F");
    printf("                   |||            ||| |||                   _   _   _   _  \n");sleep(0.5);system("color F0");
    printf("                   |||            ||| |||                   _| | | / | |_| \n");sleep(0.5);system("color 0F");
    printf("                   |||||||||||||||||| |||                  |_  |_|   | |_| \n");sleep(0.5);system("color F0");
    printf("\n");
    printf("\n");
    printf("\n");
    system("pause");
}
