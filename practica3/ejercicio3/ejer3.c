#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NELEMENTOS 5
pthread_mutex_t mtx=	PTHREAD_MUTEX_INITIALIZER;
int miArray[NELEMENTOS];
void* consumirNumero(void * num);
void* producirNumero(void * num);

int main(){
	
	//Declaracion de hilos
 	pthread_t hiloConsumidor;
 	pthread_t hiloProductor;
 	
 	//Creación de hilos
 	pthread_create(&hiloConsumidor,NULL, consumirNumero,(void*)miArray);
 	pthread_create(&hiloProductor,NULL, producirNumero,(void*)miArray);
 
 	//Esperamos a los hilos	
	pthread_join(hiloConsumidor,NULL);
	pthread_join(hiloProductor,NULL);
	
	//Destruccion del mutex
	pthread_mutex_destroy(&mtx);
}

void* consumirNumero(void * num){
	//vamos a sacar numeros del arrray
}
void* producirNumero(void * num){
	//vamos a introducir numeros en el array
}

