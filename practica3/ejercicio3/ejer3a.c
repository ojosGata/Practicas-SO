#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


#define NELEMENTOS 5
pthread_mutex_t mtx=	PTHREAD_MUTEX_INITIALIZER;
int miArray[NELEMENTOS];
void* consumirNumero(void * vector);
void* producirNumero(void * vector);
void mostrarVector(int* vector);

int main(){
	int estadoHiloC, estadoHiloP;
	srand(time(NULL));
	//Declaracion de hilos
 	pthread_t hiloConsumidor;
 	pthread_t hiloProductor;
 	
 	
 //	miArray[0]=2;
 //	miArray[1]=4;
 //	miArray[2]=6;
 	//Creación de hilos
 	estadoHiloC=pthread_create(&hiloConsumidor,NULL, consumirNumero,(void*)miArray);
 	if(estadoHiloC!=0){
		perror("Error al crear el hilo");
		printf("Error con la creacion del hilo:%d\n", errno);
		exit(EXIT_FAILURE);
	}
 	estadoHiloP=pthread_create(&hiloProductor,NULL, producirNumero,(void*)miArray);
 	if(estadoHiloP!=0){
		perror("Error al crear el hilo");
		printf("Error con la creacion del hilo:%d\n", errno);
		exit(EXIT_FAILURE);
	}
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
