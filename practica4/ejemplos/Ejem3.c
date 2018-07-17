/*Problema lectores-escritores donde hay 2 lectores y 2 escritores (prioridad a los lectores). Un
buffer con un solo dato que se va incrementando. Compílelo, ejecútelo y observe su salida.
Haga varias trazas del comportamiento del programa para poder entender los semáforos.*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
/* datos a leer y escribir. Podría usar también un while(){} */
#define DATOS_A_ESCRIBIR 10
/* Recurso. No hay buffer solo se puede escribir en o leer de una variable. Una mejora interesante sería hacer un buffer
donde pudieran escribir y leer los escritores y lectores sin causar incoherencia en los datos*/
int dato = 0;
int n_lectores = 0; /* numero de lectores */ 
sem_t sem_lec; /* controlar el acceso n_lectores */
sem_t mutex; /* controlar el acceso a dato */
void * Lector(void * arg){
	//Complete el manejo de errores
	//....
	int i=0;
	for(i=0; i < DATOS_A_ESCRIBIR; i++ ){
		sem_wait(&sem_lec);
		n_lectores = n_lectores + 1;
		if (n_lectores == 1)
			sem_wait(&mutex);
		sem_post(&sem_lec);
		printf("Lector %u y leo %d\n", (unsigned int)pthread_self(), dato); /* leer dato */
		sem_wait(&sem_lec);
		n_lectores = n_lectores - 1;
		if (n_lectores == 0)
			sem_post(&mutex);
		sem_post(&sem_lec);
	}
	pthread_exit(NULL); 
}
void * Escritor(void * arg){
	//Complete el manejo de errores
	//....
	int i=0;
	for(i=0; i < DATOS_A_ESCRIBIR; i++ ){
		sem_wait(&mutex); //No más de un escritor a la vez
		dato = dato + 1; /* modificar el recurso */
		printf("Escritor %u y escribo %d\n", (unsigned int)pthread_self(), dato);
		sem_post(&mutex);
	}
	pthread_exit(NULL);
}
void main(void){
	//Complete el manejo de errores en el main()
	//....
	pthread_t th1, th2, th3, th4;
	sem_init(&mutex, 0, 1);
	sem_init(&sem_lec, 0, 1);
	//Mejorable con un for()...
	pthread_create(&th1, NULL, Lector, NULL);
	pthread_create(&th2, NULL, Escritor, NULL); 
	pthread_create(&th3, NULL, Lector, NULL);
	pthread_create(&th4, NULL, Escritor, NULL);
	//Mejorable con un for()...
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL); 
	pthread_join(th4, NULL);
	/* eliminar todos los semaforos */
	sem_destroy(&mutex);
	sem_destroy(&sem_lec);
}
