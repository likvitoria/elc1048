#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "multitarefas.h"

#define TAM_BUFFER	10
/*
 * Prototipos das tarefas
 */
void produtor(void);
void consumidor(void);


/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_PRODUTOR[TAM_PILHA_1];
uint32_t PILHA_CONSUMIDOR[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];


semaforo_t cheio = {0, NULL};
semaforo_t vazio = {TAM_BUFFER, NULL};
int buffer[TAM_BUFFER];
int i = 0, j =  0, valor;
/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(produtor, "Produtor", PILHA_PRODUTOR, TAM_PILHA_1, 1);
	
	CriaTarefa(consumidor, "Consumidor", PILHA_CONSUMIDOR, TAM_PILHA_2, 2);


	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
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

void produtor(void){

	while(1){
		SemaforoAguarda(&vazio);
		buffer[i]=rand()%20;	//produz();

		i = (i+1)%TAM_BUFFER;
		SemaforoLibera(&cheio);

	}
}

void consumidor(void){

	while(1){
		SemaforoAguarda(&cheio);
		valor = buffer[j]; //consome

		j = (j+1)%TAM_BUFFER;
		SemaforoLibera(&vazio);

	}
}

