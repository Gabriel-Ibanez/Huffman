#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include <locale.h>
#include <time.h>


struct X {
	char letra = '.';
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
	printf("\nIMPORTANTE: Somente foram usadas letras maíusculas, sem qualquer acento ou outro símbolo.\n");

    printf("Pseudo código utilizado:\n\n");
    
	printf("enquanto tamanho(alfabeto) > 1:\n");
	printf("S0 := retira_menor_probabilidade(alfabeto)\n");
	printf("S1 := retira_menor_probabilidade(alfabeto)\n");
	printf("X  := novo_nó\n");
	printf("X.filho0 := S0\n");
	printf("X.filho1 := S1\n");
	printf("X.probabilidade := S0.probabilidade + S1.probabilidade\n");
	printf("insere(alfabeto, X)\n");
	printf("fim enquanto\n");
	printf("\n");
	printf("X = retira_menor_símbolo(alfabeto) # nesse ponto só existe um símbolo.\n");
	printf("\n");
	printf("para cada folha em folhas(X):\n");
	printf("código[folha] := percorre_da_raiz_até_a_folha(folha)\n");
	printf("fim para\n");
	printf("\n");
	
	file = fopen("S1.txt","r"); // abre o arquivo desejado
    
    if (file == NULL) {
    	printf("\nArquivo não existe!\n");
	}
	int cont = 0;
    tempoTotal = 0;
    
	X alfabeto[60];
	
	char letras[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};    
    char caractere [60] = {0};
    int i = 0, freq[60] = {0};
	clock_t inicio, fim;
	inicio = clock(); //começa a marcar o tempo
	
 
    	// copia para "texto" grupos de 1 de
		// caracter do arquivo (o segundo é o espaço para \0)
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
		printf("Frequência de '%c': %i\n",letras[i], freq[i]);
	}
	
	for (i = 0; i < 27; i++){
		alfabeto[i].letra = letras[i];
		alfabeto[i].f = freq[i];
		alfabeto[i].filho0 = 0; // se filho0 e filho1 são 0, então indica que são indica que são folhas
		alfabeto[i].filho1 = 0; // 
	//	printf("Frequência de '%c': %i\n",letras[i], freq[i]);
	}
	
	int freqTotal = 0;
	for (i = 0; i < 27; i++){
		freqTotal += freq[i];
	}
	
	printf("\nFrequência Total: %i",freqTotal);
	int s0 = 0, s1 = 0, pos1 = -1, pos2 = -1, contAlfabeto = 27;

	//while (freqTotal>1) {
		
		s0 = freqTotal;
		for (i=0; i< 27;i++){
			if (freq[i]<s0 && freq[i]>1) s0 = freq[i];
		}
		
		for (i=0; i< 27;i++){
			if (freq[i] == s0) {
			freq[i] = 0;
			pos1 = i;
			}
		}
		
		s1 = freqTotal;
		for (i=0; i< 27;i++){
			if (freq[i]<s1 && freq[i]>1) s1 = freq[i];
		}
		
		for (i=0; i< 27;i++){
			if (freq[i] == s1){
			freq[i] = 0;
			pos2 = i;
			}
		}
		
		freqTotal = 0;
		for (i = 0; i < 27; i++){
		freqTotal += freq[i];
		}
		
		printf("\n\nS0: %i\ts1:%i\n\n",s0,s1);
		printf("\nFrequência Total: %i\n",freqTotal);
		
		X x;
		x.filho0 = s0;
		x.filho1 = s1;
		x.f = s0+s1;
		x.letra = '.';
		alfabeto[contAlfabeto++] = x;

		
		//x.letra = 
	//}


	for (i = 0; i < 60; i++){
		printf("Frequência de '%c': %i\n",alfabeto[i].letra, alfabeto[i].f);
	}

 	fim = clock(); //termina de marcar o tempo
	printf("\nTempo: %lf segundos\n", ((double)( fim - inicio ) / ((double)CLOCKS_PER_SEC )));
    
    fclose(file);
    printf("\nFim do programa!");

    return 0;
}


