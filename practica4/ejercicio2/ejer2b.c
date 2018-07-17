//El problema del baño público en la universidad
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>

#define AFORO 3
#define HOMBRES 10
#define MUJERES 10

//Definición de semaforos
sem_t turno;
sem_t estaVacio; /*Inicializado a 1 controla el acceso si el baño esta vacio totalmente*/
sem_t semHombre; /*Inicializado a 1 controla el acceso de los hombres*/
sem_t semMujer; /*Inicializado a 1 controla el acceso de las mujeres*/
sem_t semContHom; /*Inicializado a 3 controla el acceso al baño para 3 hombres*/
sem_t semContMuj; /*Inicializado a 3 controla el acceso de solo tres mujeres*/

//Variable globales
int usHom=0;
int usMuj=0;
void *mujeres( void *arg);
void *hombres(void *arg);


int main(){
	srand(time(NULL));
	int i;
	int j;
	int idM[MUJERES]={20,21,22,23,24,25,26,27,28,29};
	int idH[HOMBRES]={10,11,12,13,14,15,16,17,18,19};
	//Iniciamos semaforos
	sem_init(&turno,0,1);
	sem_init(&estaVacio, 0,1);
	sem_init(&semHombre, 0, 1);
	sem_init(&semMujer,0,1);
	sem_init(&semContHom,0,AFORO);
	sem_init(&semContMuj,0,AFORO);
	//Definición de los hilos para la mujeres y los hombres
	pthread_t hiloMujeres[MUJERES];
	pthread_t hiloHombres[HOMBRES];
	//Creación de los hilos para mujeres y hombres
	for(i=0; i<MUJERES; i++){
		pthread_create(&hiloMujeres[i],NULL,mujeres,(void*)&idM[i]);
	}
	for(j=0;j<HOMBRES;j++){
		pthread_create(&hiloHombres[j],NULL, hombres,(void*)&idH[j]);
	}
	//Espera de los hilos
	for(i=0;i<MUJERES;i++){
		pthread_join(hiloMujeres[i],NULL);
	}
	for(j=0;j<HOMBRES;j++){
		pthread_join(hiloHombres[j],NULL);
	}
	//destruir semaforos 
	sem_destroy(&turno);
	sem_destroy(&estaVacio);
	sem_destroy(&semHombre);
	sem_destroy(&semMujer);
	sem_destroy(&semContHom);
	sem_destroy(&semContMuj);
}
void *mujeres(void *arg){
	sem_wait(&turno);
	 printf("\nId Mujer %d esperando en cola\n",*(int*)arg);
	 sem_wait(&semMujer);
	  usMuj++;
	  if(usMuj == 1){
		  sem_wait(&estaVacio);
	  }
	  sem_post(&semMujer);
	sem_post(&turno);
	sem_wait(&semContMuj);//INiciamos sección critica
	 printf("\nIdM %d, Hay %d mujeres en el servicio...",*(int*)arg,usMuj);
	 sleep((rand()%3));
	sem_post(&semContMuj); //finalizamos la seccion critica
	
	sem_wait(&semMujer);
	 usMuj--;
	 printf("\nIdMUJER: %d saliendo del baño...",*(int*)arg);
	 if(usMuj==0){
	 	 sem_post(&estaVacio);
	 }
	 sem_post(&semMujer);
}
void *hombres(void *arg){
	sem_wait(&turno);
	printf("\nId Hombre %d esperando en cola",*(int*)arg);
	 sem_wait(&semHombre);
	  usHom++;
	  if(usHom == 1){
		  sem_wait(&estaVacio);
	  }
	  sem_post(&semHombre);
	sem_post(&turno);
	sem_wait(&semContHom);//INiciamos sección critica
	 printf("\nidH %d, Hay %d hombres en el servicio..\n.",*(int*)arg,usHom);
	 sleep((rand()%3));
	sem_post(&semContHom); //finalizamos la seccion critica
	sem_wait(&semHombre);
	 usHom--;
	 printf("\nIdHOMBRE: %d saliendo del baño...",*(int*)arg);
	 if(usHom==0){
	 	 sem_post(&estaVacio);
	 }
	 sem_post(&semHombre);
}

