#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NHILOS 3
#define NCARACTERES 5
pthread_mutex_t mtx=	PTHREAD_MUTEX_INITIALIZER;
char eligeCaracter(int valor);
void *escribePantalla(void *args);

int main(){
	int i;
	int estadoHilo, estadoHiloJ;
	int  s;
	char c;//Caracter que va a imprimir cada hilo
	//Declaracion de hilos
	pthread_t hilo[NHILOS];
	for(i=0;i<NHILOS;i++){
		c=eligeCaracter(i);
		estadoHilo=pthread_create(&hilo[i], NULL, escribePantalla, (void*)&c);
		
		if(estadoHilo!=0){
			perror("Error al crear el hilo");
			printf("Error con la creacion del hilo:%d\n", errno);
			exit(EXIT_FAILURE);
		}
	}
	////impresion de ---- por parte del programa principal
	s=pthread_mutex_lock(&mtx); //bloquea el semaforo
	if(s!=0){
			perror("Error al cerrar el semaforo");
			printf("Error cerrando el semaforo :%d\n", errno);
			exit(EXIT_FAILURE);
	}
	//Sección crítica
	for(i=0; i< NCARACTERES; i++){
		printf("%c",'-');
	}
	s=pthread_mutex_unlock(&mtx); //desbloquea el semaforo	
	
	for(i=0;i<NHILOS;i++){
		estadoHiloJ=pthread_join(hilo[i],NULL);
		if(estadoHiloJ!=0){
			perror("Error al esperar el hilo");
			printf("Error con el join del hilo:%d\n", errno);
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_destroy(&mtx);
}
void *escribePantalla(void *args){
	int i, s;
	char *caracter=(char *)args;
	s=pthread_mutex_lock(&mtx); //bloquea el semaforo
	if(s!=0){
			perror("Error al cerrar el semaforo");
			printf("Error cerrando el semaforo :%d\n", errno);
			exit(EXIT_FAILURE);
	}
	//Sección crítica
	for(i=0; i< NCARACTERES; i++){
		printf("%c",(*caracter));
	}
	s=pthread_mutex_unlock(&mtx); //desbloquea el semaforo	
	pthread_exit(NULL);
}

//Funcion que devuelve un caracter segun sea el valor del parametro
char eligeCaracter(int valor){
	if(valor==0) 
		return '*';
	else	if(valor==1)
		return '+';
	else	if(valor==2)
		return '?';
	else
		return '0';					
}

