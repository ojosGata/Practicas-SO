#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


#define NELEMENTOS 5

typedef enum{FALSE=0; TRUE=1}booleano;
pthread_mutex_t semS =	PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semN = 	PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semE =	PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;1

int miArray[NELEMENTOS];

void* consumirNumero(void * vector);
void* producirNumero(void * vector);
void mostrarVector(int* vector);

int main(){
	srand(time(NULL));
	//Declaracion de hilos
 	pthread_t hiloConsumidor;
 	pthread_t hiloProductor;
 	
 	//Inicio de condicion 
 	pthread_cond_init(&cond,NULL);
 	//Inicio de semaforos
 	pthread_mutex_init(&mtxS,NULL);
 	pthread_mutex_init(&mtxN,NULL);
 	pthread_mutex_init(&mtxE,NULL);
 	
 	//Creación de hilo
 	pthread_create(&hiloConsumidor,NULL, consumirNumero,(void*)miArray);
 	pthread_create(&hiloProductor,NULL, producirNumero,(void*)miArray);
 	mostrarVector(miArray);
 	//Esperamos a los hilos	
	pthread_join(hiloConsumidor,NULL);
	pthread_join(hiloProductor,NULL);
	
	//Destruccion del mutex
	pthread_mutex_destroy(&mtx);
}

void* consumirNumero(void * vector){
	//vamos a sacar numeros del arrray
	int i, s,encontrado=0,pos;
	int *vec;
	
	vec=(int *)vector;
	//contralar error de cerrar semaforo	
	s=pthread_mutex_lock(&mtx); //bloquea el semaforo
	
	while(1){
		
		for(i=0;i<NELEMENTOS && !encontrado ;i++){
			if(vec[i]!=0){
				encontrado=1;
				pos=i;
			}	
		}
		//sleep(1);
		if(encontrado){
			vec[pos]=0;
		}
		printf("\nConsumiendo.....\n");
		mostrarVector(vec);
		
		
		s=pthread_mutex_unlock(&mtx); //desbloquea el semaforo
		encontrado=0;//para ver si hay hueco en el vector para escribir un numero
		
	}
}
void* producirNumero(void * vector){
	//vamos a introducir numeros en el array
	int i, s,pos,encontrado=0;
	int *vec;
	vec=(int *)vector;
	s=pthread_mutex_lock(&mtx); //bloquea el semaforo
		
	while(1){
		for(i=0;i<NELEMENTOS && !encontrado;i++){
			if(vec[i]==0){
				encontrado=1;
				pos=i;
			}
		}
		//sleep(1);
		if(encontrado){
			vec[pos]=(rand()%100) + 1;
		}
		printf("\nProduciendo.....\n");
		mostrarVector(vec);
		
		s=pthread_mutex_unlock(&mtx); //desbloquea el semaforo
		s=pthread_cond_signal(&cond);
		encontrado=0;//para ver si hay hueco en el vector para escribir un numero
	}
	pthread_exit(NULL);
}

void mostrarVector(int* vector){
	int i;
	for(i=0;i<NELEMENTOS;i++){
		printf("\t%d",vector[i]);
	}
	printf("\n");
}
