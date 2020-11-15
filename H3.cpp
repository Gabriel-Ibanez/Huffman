#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include <locale.h>
#include <time.h>


struct X {
	char letra[60] = {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
	//char letra[60] = {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
	int filho0 = 0;
	int filho1 = 0;
	int f = 0;
};

int main(void)
{
	//SetConsoleOutputCP(65001); // faz aparecer em português o texto
	setlocale(LC_ALL,"Portuguese");
	printf("================================================================\n");
	printf("IESB 20201 - Análise de Algoritmos - Professor Felippe Rodrigues\n");
	printf("Programa Compressor Huffman.  Aluno: Gabriel Ibañez - 1812130004\n");
	printf("================================================================\n");
	
    FILE *file;
    
    double t1=0, t2=0;
	float tempo=0, tempoTotal=0;
	char texto [2]; // poderia ser maior mas 2 é suficiente neste caso
	printf("\nIMPORTANTE: Para a resolução deste exercício, somente foram usados \nespaços e letras maiúsculas, sem qualquer acento ou outro símbolo.\n");

    printf("\n------------------  Pseudo código utilizado: ----------------- \n");
	printf("enquanto tamanho(alfabeto) > 1:\n");
	printf("\tS0 := retira_menor_probabilidade(alfabeto)\n");
	printf("\tS1 := retira_menor_probabilidade(alfabeto)\n");
	printf("\tX  := novo_nó\n");
	printf("\tX.filho0 := S0\n");
	printf("\tX.filho1 := S1\n");
	printf("\tX.probabilidade := S0.probabilidade + S1.probabilidade\n");
	printf("\tinsere(alfabeto, X)\n");
	printf("fim enquanto\n");
	printf("\n");
	printf("X = retira_menor_símbolo(alfabeto) # nesse ponto só existe um símbolo.\n");
	printf("\n");
	printf("para cada folha em folhas(X):\n");
	printf("\tcódigo[folha] := percorre_da_raiz_até_a_folha(folha)\n");
	printf("fim para\n");
	printf("-------------------------------------------------------------- \n");
	
	
	file = fopen("S1.txt","r"); // abre o arquivo desejado
    
    if (file == NULL) {
    	printf("\nArquivo não existe!\n");
	}
	int cont = 0;
    tempoTotal = 0;
    
	X alfabeto[60];
	X alfabeto2[60];
	
	char letras[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};    
    char caractere [60] = {0};
    int i = 0, freq[60] = {0};
	clock_t inicio, fim;
	inicio = clock(); //começa a marcar o tempo
	
 
    	// copia para "texto" grupos de 1 de
		// caracter do arquivo (o segundo é o espaço para \0)
	
	    printf("\nLeitura do arquivo texto e apresentação das frequências de cada letra:\n\n");
	while (fgets(texto, 2, file) != NULL) {  
	
	switch (texto[0]) {
		case ' ': freq[0]++; break;
		case 'A': freq[1]++; break;
		case 'B': freq[2]++; break;
		case 'C': freq[3]++; break;
		case 'D': freq[4]++; break;
		case 'E': freq[5]++; break;
		case 'F': freq[6]++; break;
		case 'G': freq[7]++; break;
		case 'H': freq[8]++; break;
		case 'I': freq[9]++; break;
		case 'J': freq[10]++; break;
		case 'K': freq[11]++; break;
		case 'L': freq[12]++; break;
		case 'M': freq[13]++; break;
		case 'N': freq[14]++; break;
		case 'O': freq[15]++; break;
		case 'P': freq[16]++; break;
		case 'Q': freq[17]++; break;
		case 'R': freq[18]++; break;
		case 'S': freq[19]++; break;
		case 'T': freq[20]++; break;
		case 'U': freq[21]++; break;
		case 'V': freq[22]++; break;
		case 'W': freq[23]++; break;
		case 'X': freq[24]++; break;
		case 'Y': freq[25]++; break;
		case 'Z': freq[26]++; break;
	}
}

	for (i = 0; i < 27; i++){
		alfabeto2[i].letra[0]= letras[i];
		alfabeto2[i].f = freq[i];
		alfabeto2[i].filho0 = 0; // se filho0 e filho1 são 0, então indica que são indica que são folhas
		alfabeto2[i].filho1 = 0; // 
	//	printf("Frequência de '%c': %i\n",letras[i], freq[i]);
	}
	
	for (i = 0; i < 27; i++){
		printf("Frequência de '%c': %i\n",alfabeto2[i].letra[0], alfabeto2[i].f);
	}
	
	
	int freqTotal = 0;
	for (i = 0; i < 27; i++){
		freqTotal += freq[i];
	}
	
	printf("\nFrequência Total: %i",freqTotal);
	int s0 = 0, s1 = 0, pos1 = -1, pos2 = -1, contAlfabeto = 27;
	bool dentro = false; int posicaoElemento = 1, p= 0,  contAux1 = 0; int contAux2 = 0;

	while (freqTotal>1) {
		
		s0 = freqTotal;
		for (i=0; i< contAlfabeto;i++){
			if (alfabeto2[i].f<s0 && alfabeto2[i].f>0) s0 = alfabeto2[i].f;
		}
		
		for (i=0; i< contAlfabeto;i++){
			if (alfabeto2[i].f == s0) {
			alfabeto2[i].f = 0;
			pos1 = i;
			}
		}
		
		s1 = freqTotal;
		for (i=0; i< contAlfabeto;i++){
			if (alfabeto2[i].f<s1 && alfabeto2[i].f>0) s1 = alfabeto2[i].f;
		}
		
		for (i=0; i< contAlfabeto;i++){
			if (alfabeto2[i].f == s1){
			alfabeto2[i].f = 0;
			pos2 = i;
			}
		}
		
		freqTotal = 0;
		for (i = 0; i < contAlfabeto; i++){
		freqTotal += alfabeto2[i].f;
		}
		
		printf("\nS0: %i\ts1:%i\n",s0,s1);
		printf("Frequência Total: %i\n",freqTotal);
		
		if (!dentro) {			
			dentro = true;
			printf("Entrou dentro \n");
			X x;
			x.filho0 = -2;
			x.filho1 = -2;
			x.f = s0;
			x.letra[0] = letras[pos1];
			alfabeto2[pos1].f=0;
			alfabeto2[contAlfabeto++] = x;
			
			X y;
			y.filho0 = -3;
			y.filho1 = -3;
			y.f = s1;
			y.letra[0] = letras[pos2];
			alfabeto2[pos2].f=0;
			alfabeto2[contAlfabeto++] = y;
		}
		

		
		X x;
		x.filho0 = s0;
		x.filho1 = s1;
		x.f = s0+s1;
		
		contAux1 = 0; 
		for (i = 0; i< 60; i++){
			if (alfabeto2[contAlfabeto-2].letra[i] == '.') contAux1++;
		}
			
		contAux2 = 0; 
		for (i = 0; i< 60; i++){
			if (alfabeto2[contAlfabeto-1].letra[i] == '.') contAux2++;
		}

		contAux1 = 60 - contAux1;
		contAux2 = 60 - contAux2;
		
		printf("contAux1 = %i , contAux2 = %i , contAlfabeto = %i \n",contAux1,contAux2,contAlfabeto);
		
		for (i = 0; i < contAux1; i++){
			x.letra[i] = alfabeto2[contAlfabeto-2].letra[i];
		}
		x.letra[contAux1] = '+';
		
		for (i = 0; i < contAux2; i++){
			x.letra[contAux1+1] = alfabeto2[contAlfabeto-1].letra[i];
		}
		

		alfabeto2[contAlfabeto++] = x;

	}

	int j,k;
	for (k = 0; k < 60-1; k++){
		printf("Frequência de ");
		
		/*
		for (j = 0; j < 30; j++){
		printf("%c",alfabeto2[i].letra[j]);
		} */
		
		contAux1 = 0; 
		for (i = 0; i< 60; i++){
			if (alfabeto2[k].letra[i] == '.') contAux1++;
		}
		
		contAux2 = 60 - contAux1;
		
		//	printf("contAux2: %i ",contAux2);
		for (j = 0; j < contAux2; j++){
		printf("%c",alfabeto2[k].letra[j]);
		} 
		//printf("Aqui2!\n ");
		printf(": %i\n", alfabeto2[k].f);
	}

 	fim = clock(); //termina de marcar o tempo
	printf("\nTempo: %lf segundos\n", ((double)( fim - inicio ) / ((double)CLOCKS_PER_SEC )));
    
    fclose(file);
    printf("\nFim do programa!");

    return 0;
}


