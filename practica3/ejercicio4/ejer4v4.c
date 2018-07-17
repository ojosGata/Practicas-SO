//ejer4v4
//Includes y defines
 #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void *lector(void * arg);
void *escritor(void * arg);
//Seccion critica
int dato = 4; /* Puede ser cualquier otro tipo de recurso */ 
int n_lectores = 0; /* numero de lectores */ 
pthread_mutex_t mutex =	PTHREAD_MUTEX_INITIALIZER;/* semaforoBinario mutex; controlar el acceso a dato */ 
pthread_mutex_t mutex_lectores = PTHREAD_MUTEX_INITIALIZER; /* semaforoBinario mutex_lectores; controla la variable n_lectores */


int main(){ 
	//Iniciar hebras escritoras y lectoras
	pthread_t hiloEscritor;
	pthread_t hiloLector;
	//Lanzar hebras escritoras y lectoras
	pthread_create(&hiloLector, NULL, lector,NULL);
	pthread_create(&hiloEscritor,NULL, escritor, NULL);
	//	Esperar las hebras
	pthread_join(hiloLector,NULL);
	pthread_join(hiloEscritor,NULL);
	//Destruir los semaforos 
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex_lectores);
}

void *escritor(void * arg){ /* codigo del escritor */
	while(1){
		pthread_mutex_lock(&mutex);
		printf("\nescribiendo...");
	   dato = dato + 2; /* modificar el recurso */ 
      pthread_mutex_unlock(&mutex); 
   }
}
void *lector(void *arg){  /* codigo del lector */ 
   while(1){
	  pthread_mutex_lock(&mutex_lectores);
	  n_lectores++; 
	  if (n_lectores == 1){
	  	   pthread_mutex_lock(&mutex);
	  }
	  pthread_mutex_unlock(&mutex_lectores);
	  printf("Leyendo: %d\n", dato); /* leer dato */ 
	  pthread_mutex_lock(&mutex_lectores); 
	  n_lectores--; 
	  if (n_lectores == 0){
		   pthread_mutex_unlock(&mutex);
     }
     pthread_mutex_unlock(&mutex_lectores);
   }
}

