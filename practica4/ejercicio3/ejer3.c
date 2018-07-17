//Los filosofos
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>

#define N 5					/*Número de filosofos*/
#define IZQ (i-1)%N		/*Número del vecino izq de i*/
#define DER (i+1)%N		/*Número del vecino der de i*/
#define PENSANDO 0		/*El filósofo esta pensando*/
#define HAMBRIENTO 1    /*El filósofo esta hambriento*/
#define COMIENDO 2      /*El filósofo esta comiendo*/

int estado[N];  //vector para llevar el estado de los filósofo
sem_t exmut;	 //Semaforo para la exclusión mutua
sem_t s[N];		 // Semaforo para los filosofos
void *filosofo(void *i);
void coger_tenedores(int i);
void dejar_tenedores(int i);
void prueba(int i);
void pensar(int i);
void comer(int i);


int main(){
	srand(time(NULL));
	int i;
	int enteros[N]={0,1,2,3,4};
	//Iniciar hilos de los filosofos
	pthread_t hiloFilosofo[5];
	//Iniciar semaforo de exclusion mutua
	sem_init(&exmut, 0,1);
	//Iniciar hilos y semaforos de los filosofos
	for(i=0;i<N;i++){
		//Lanzar hilos filósofos
		pthread_create(&hiloFilosofo[i],NULL,filosofo , (void*)&enteros[i]);//Deberia pasar el entero comov void *
		sem_init(&s[i],0,0);
	}	
	//	Esperar las hilos filosofos
	for(i=0;i<N;i++){
		pthread_join(hiloFilosofo[i],NULL);
	}
	//Destruir los semaforos 
	sem_destroy(&exmut);
	for(i=0;i<N;i++){
		sem_destroy(&s[i]);
	}
}

void *filosofo(void *arg){
	int* num=(int*)arg;
	while(1){
		pensar(*num);
		coger_tenedores(*num);
		comer(*num);
		dejar_tenedores(*num);
	}
}

void coger_tenedores(int i){
	sem_wait(&exmut);
	estado[i]=HAMBRIENTO;	
	prueba(i);
	sem_post(&exmut);
	sem_wait(&s[i]);
}

void dejar_tenedores(int i){
	sem_wait(&exmut);
	estado[i]=PENSANDO;
	prueba(IZQ);
	prueba(DER);
	sem_post(&exmut);
}
void prueba(int i){
	if(estado[i]==HAMBRIENTO && estado[IZQ]!=COMIENDO && estado[DER]!= COMIENDO){
		estado[i]=COMIENDO;
		sem_post(&s[i]);
	}

}
void pensar(int i){
	printf("\nFilosofo %d Pensando...",i);
	sleep((rand()%3));
}
void comer(int i){
	printf("\nFilosofo %d Comiendo....",i);
	sleep((rand()%3));
}

