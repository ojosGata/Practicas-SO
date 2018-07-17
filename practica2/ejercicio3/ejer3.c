/*
	practica 2:
	ejercicio 4.3: Implementar un programa para realizar la suma en forma paralela de los valores de un vector de 10 números enteros que van de 0 a 9(puede probar con aleatorios).
	Utilizce una cantidad de hilos indicada como parámetro de entrada por la linea de argumentos y reparta la suma del vector entre ellos. La suma debe ser el subtotal devuelto por cada hilo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
struct vectorHilos{
	int vector[10];
	int nHilos;
	int posHilo;
};
void rellenarVector(int *v);
int crearNumeroAleatorio();
//Mi Funcion
void *sumaParcial(void* arg);
void main (int argc, char **argv){
	int v[10], acu=0, auxsum,s,*suma;
	struct vectorHilos vh;
	pthread_t hilo;
	int i,numHilos;
	if(argc != 2){
		perror("Error en la sintaxis");
		printf("Error en la sintaxis: ./ejer3 <numeroHilos>: %d\n",errno);
		exit(EXIT_FAILURE);
	}
	rellenarVector(vh.vector);
	numHilos=atoi(argv[1]);
	vh.nHilos=numHilos;
	for(i=0;i < numHilos;i++){
		vh.posHilo=i;
		pthread_create(&hilo, NULL, sumaParcial, (void*)&vh);
		s=pthread_join(hilo,(void**)&suma);
		if(s!=0){
			perror("Fallos en el join\n");
			exit(EXIT_FAILURE);
		}else{
			auxsum= *(int *)suma;
			printf("suma %d= %d\n",i,auxsum);
			acu+= auxsum;
		}
	}
	printf("La suma total es: %d\n",acu);
}

void rellenarVector(int *v){
	int i;
	for(i=0;i<10;i++){
		v[i]=crearNumeroAleatorio();
	}	

}
int crearNumeroAleatorio(){
	int num1;
	srand(time(NULL));
	num1= ((rand()%10) );
	return num1;
}

void *sumaParcial(void* arg){
	struct vectorHilos *vAux;
	int aux,i;
	int *sum=malloc(sizeof(int));
	vAux=(struct vectorHilos *)arg;
	for(i=(vAux->posHilo)*(vAux->nHilos);i<(vAux->nHilos+vAux->posHilo);i++){
		(*sum)+=vAux->vector[i];
	}

	pthread_exit((void*)sum);
}
