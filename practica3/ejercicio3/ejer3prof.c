/*
Includes y defines
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define MAX_BUFFER 5 /* tamanio del buffer */ 
#define DATOS_A_PRODUCIR 20 /* cantidad de datos a producir, puede ser mayor que MAX_BUFFER */ 
//funciones
void* consumidor(void * arg);
void* productor(void * arg);
void mostrarVector(int* vector);

//Global
pthread_mutex_t mutex=	PTHREAD_MUTEX_INITIALIZER; /* mutex para controlar el acceso al buffer compartido */ 
pthread_cond_t no_lleno=	PTHREAD_COND_INITIALIZER; /* controla el llenado del buffer */
pthread_cond_t no_vacio=	PTHREAD_COND_INITIALIZER; /* controla el vaciado del buffer */
int n_elementos; /* numero de elementos en el buffer */
int buffer[MAX_BUFFER]; /* buffer comun, seccion critica */ 





int main(){
	//Iniciar hebras productora y consumidora
	pthread_t hiloProductor;
	pthread_t hiloConsumidor;
	//Lanzar hebras productora y consumidora
	pthread_create(&hiloProductor, NULL, productor,NULL);
	pthread_create(&hiloConsumidor,NULL, consumidor, NULL);
	//	Esperar las hebras
	pthread_join(hiloProductor,NULL);
	pthread_join(hiloConsumidor,NULL);
	//Destruir los semaforos y variables de condicion
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&no_lleno);
	pthread_cond_destroy(&no_vacio);

}
void *productor(void * arg){
	int dato, i, pos=0;
	int s;
	for(i=0; i<DATOS_A_PRODUCIR;i++){
		dato = i; /* producir dato */ 
		s=pthread_mutex_lock(&mutex); /* acceder al buffer */ 
		if(s!=0){
			printf("Error al cerrar el mutex");
			exit(EXIT_FAILURE);
		}
		while(n_elementos == MAX_BUFFER){ /* si buffer lleno */ 
			s=pthread_cond_wait(&no_lleno,&mutex); /* se bloquea */ 
			if(s!=0){
				printf("Error al bloquear la condicion: no_lleno");
				exit(EXIT_FAILURE);
			}

		}
		buffer[pos] = i; 
		pos = (pos + 1) % MAX_BUFFER; 
		n_elementos ++; 
		s=pthread_cond_signal(&no_vacio); /* buffer no vacio */ 
		printf("\nProduciendo...\n");
		mostrarVector(buffer);
		if(s!=0){
			printf("Error al desbloquear la condicion: no vacio");
			exit(EXIT_FAILURE);
		}

		s=pthread_mutex_unlock(&mutex); 
		if(s!=0){
			printf("Error al abrir el mutex");
			exit(EXIT_FAILURE);
		}

	}
}


void *consumidor(void *arg){  /* codigo del consumidor */ 
	int dato, i, pos=0;
	int s;
	for(i=0;i < DATOS_A_PRODUCIR; i++){ 
		s=pthread_mutex_lock(&mutex);  /* acceder al buffer */ 
		if(s!=0){
			printf("Error al cerrar el mutex");
			exit(EXIT_FAILURE);
		}
		while(n_elementos == 0){ /* si buffer vacio */ 
			s=pthread_cond_wait(&no_vacio,&mutex); /* se bloquea */ 
			if(s!=0){
				printf("Error al bloquear la condicion: no_vacio");
				exit(EXIT_FAILURE);
			}
		}
		dato = buffer[pos]; 
		pos = (pos + 1) % MAX_BUFFER; 
		n_elementos --; 
		printf("\nConsumiendo...\n");
		mostrarVector(buffer);
		s=pthread_cond_signal(&no_lleno); /* buffer no lleno */ 
	  	if(s!=0){
			printf("Error al desbloquear la condicion: no_lleno");
			exit(EXIT_FAILURE);
		}
		s=pthread_mutex_unlock(&mutex); 
		if(s!=0){
		  	printf("Error al abrir el mutex");
			exit(EXIT_FAILURE);
		}
	}
}
void mostrarVector(int* vector){
	int i;
	for(i=0;i<MAX_BUFFER;i++){
		printf("\t%d",vector[i]);
	}
	printf("\n");
}

