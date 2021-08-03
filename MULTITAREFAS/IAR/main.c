#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "multitarefas.h"

#define TAM_BUFFER	10
/*
 * Prototipos das tarefas
 */
void thread1(void);
void thread2(void);
void thread3(void);
void thread4(void);
void thread5(void);
void fim(void);

uint32_t count1 = 0, count2 =0, count3 = 0, count4 = 0, count5 = 0, soma = 0;

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6     (TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_1[TAM_PILHA_1];
uint32_t PILHA_2[TAM_PILHA_2];
uint32_t PILHA_3[TAM_PILHA_3];
uint32_t PILHA_4[TAM_PILHA_4];
uint32_t PILHA_5[TAM_PILHA_5];
uint32_t PILHA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];


/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(thread1, "Thread 1", PILHA_1, TAM_PILHA_1, 5);

	CriaTarefa(thread2, "Thread 2", PILHA_2, TAM_PILHA_2, 4);

	CriaTarefa(thread3, "Thread 3", PILHA_3, TAM_PILHA_3, 3);

	CriaTarefa(thread4, "Thread 4", PILHA_4, TAM_PILHA_4, 2);
	
	CriaTarefa(thread5, "Thread 5", PILHA_5, TAM_PILHA_5, 1);

	CriaTarefa(fim, "Soma", PILHA_6, TAM_PILHA_6, 6);


	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	 	    TCB[1].estado = ESPERA;
	        TCB[2].estado = ESPERA;
	        TCB[3].estado = ESPERA;
	        TCB[4].estado = ESPERA;
	        TCB[5].estado = ESPERA;

	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}



/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */

void thread5(void){

	for(;;){
		count5++;
		TarefaContinua(4);
	}
}

void thread4(void){

	for(;;){
		count4++;
		TarefaContinua(3);
		TarefaSuspende(4);
	}
}

void thread3(void){

	for(;;){
		count3++;
		TarefaContinua(2);
		TarefaSuspende(3);
	}
}

void thread2(void){

	for(;;){
		count2++;
		 TarefaContinua(1);
		 TarefaSuspende(2);
	}
}

void thread1(void){

	for(;;){
		count1++;
		 TarefaSuspende(1);
	}
}

void fim(void){

	for(;;){
		soma = count1 + count2 + count3 + count4 + count5;
		TarefaEspera(30);
	}
}

