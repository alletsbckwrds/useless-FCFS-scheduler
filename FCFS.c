//#include <iostream>
#include <stdlib.h>
#include <stdio.h>

struct processes
{
	int num;		//
	int burst_time;		//settate a mano
	int arrival_time;	//
};

void input(struct processes *array_progs, int num_progs); //prototipo di funzione per l'input
void FCFScalc(struct processes *array_progs, int num_progs); //prototipo di funzione per il calcolo FCFS

int main()
{
	printf("Quanti processi vuoi inserire? ");
	int num_progs;
	scanf("%d", &num_progs);
	
	while(num_progs < 2)
	{
		printf("Devi inserire un numero maggiore di 1.\n");
		scanf("%d", &num_progs);
	}
	
	struct processes *array_progs = malloc(num_progs * sizeof(*array_progs)); //array di lunghezza arbitraria di struct per ogni processo
	if(array_progs == NULL)
	{
		printf("Impossibile allocare risorse per l'esecuzione del programma.\n");
		return 1;
	}
	
	input(array_progs, num_progs); //funzione per l'input

	FCFScalc(array_progs, num_progs); //svolge tutti i calcoli e manda in output i risultati

	free(array_progs);
	return 0;
}

void input(struct processes *array_progs, int num_progs)
{
	printf("L\'arrival time deve partire da 0.\n\n");
	for(int i=0; i<num_progs; i++) //ciclo che si ripete tante volte quante le struct nell'array
	{
		array_progs[i].num = i;					//setta il numero del processo
		printf("Burst time per processo P%d: ", i);
		scanf("%d", &(array_progs[i].burst_time)); //std::cin>>array_progs[i].burst_time;	//input per burst time
		
		printf("Arrival time per processo P%d: ", i);
		scanf("%d", &(array_progs[i].arrival_time)); //std::cin>>array_progs[i].arrival_time;	//input per arrival time
	}
}

void FCFScalc(struct processes *array_progs, int num_progs)
{
	for(int i=0; i<(num_progs-1); i++) 						//bubble sort in base al tempo di arrivo
		for(int j=0; j<(num_progs-i-1); j++)					//
			if(array_progs[j].arrival_time > array_progs[j+1].arrival_time)	//
			{								//
				struct processes temp = array_progs[j];			//
				array_progs[j] = array_progs[j+1];			//
				array_progs[j+1] = temp;				//
			}								//

	printf("Processi:\t\t");			//
	for(int i=0; i<num_progs; i++)			//
		printf("%d\t", array_progs[i].num);	//output numero processi
	printf("\n");				//

	printf("Burst time:\t\t");				//
	for(int i=0; i<num_progs; i++)				//
		printf("%d\t", array_progs[i].burst_time);	//output burst time
	printf("\n");						//

	printf("Waiting time:\t\t"); //output tempo di attesa
	int contatore_tempo=0; //tempo usato per esecuzione dei vari processi
	int sommatoria_waitt=0; //sommatoria per la media
	for(int i=0; i<num_progs; i++)
	{
		if(array_progs[i].arrival_time > contatore_tempo) //se il processo arriva dopo che tutti i processi piu vecchi sono finiti
		{
			//std::cout<<contatore_tempo+(array_progs[i].arrival_time - contatore_tempo)<<"\t";
			printf("%d\t", contatore_tempo+(array_progs[i].arrival_time - contatore_tempo));
			sommatoria_waitt += contatore_tempo+(array_progs[i].arrival_time - contatore_tempo);
			contatore_tempo += array_progs[i].burst_time + (array_progs[i].arrival_time - contatore_tempo);
		}
		else
		{
			printf("%d\t", contatore_tempo);
			sommatoria_waitt += contatore_tempo;
			contatore_tempo += array_progs[i].burst_time;
		}
	}
	printf("\n");

	printf("Turn around time:\t"); //output turn around time
	contatore_tempo=0; //tempo usato per esecuzione dei vari processi
	int sommatoria_turnat=0;
	for(int i=0; i<num_progs; i++)
	{
		if(array_progs[i].arrival_time > contatore_tempo) //se il processo arriva dopo che tutti i processi piu vecchi sono finiti
		{
			contatore_tempo += array_progs[i].burst_time + (array_progs[i].arrival_time - contatore_tempo);
			printf("%d\t", contatore_tempo);
			sommatoria_turnat += contatore_tempo;
		}
		else
		{
			contatore_tempo += array_progs[i].burst_time;
			printf("%d\t", contatore_tempo);
			sommatoria_turnat += contatore_tempo;
		}
	}
	printf("\n");

	printf("Average wait time: %f\n", (((float) sommatoria_waitt)/((float) num_progs)));		//output medie
	printf("Average turn around time: %f\n", (((float) sommatoria_turnat)/((float) num_progs)));	//
}

//appunti: (li ho lasciati perche' potrebbero rendere il programma di piu' facile lettura)
//completio time = contatore tempo + burst
//burst time = tempo per eseguire processo x
//tempo attesa = waiting time = quelli di prima		(se arrival time>quelli di prima:	=quelli di prima+(arrival time-quelli di prima)

/*
exit codes:
0: success
1: RAM insufficiente
*/
