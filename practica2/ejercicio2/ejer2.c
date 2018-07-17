/*	
	Practica 2:
	Ejercicio 4.2:
		Implementa un programa que cree un numero N de  hebras. Cada hebra creará 2 números aleatorios y guardará sus suma en una variable para ello, que será devuelta a la hebra llamadora.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void *crearDosNumerosAleatorios(void *arg);

int main(){
	int numHilos=5;
	int i,acu=0,s;
	int *suma=0,auxsum;
	pthread_t hilo;
	for(i=0;i<numHilos;i++){
		pthread_create(&hilo,NULL,crearDosNumerosAleatorios,NULL);
		s=pthread_join(hilo,(void**)&suma);
		if(s!=0){
			perror("Fallos en el join\n");
			exit(EXIT_FAILURE);
		}else{
			auxsum=*(int *)suma;
			printf("suma %d= %d\n",i,auxsum);
			acu+= auxsum;
		}
	}
	printf("La suma total es: %d\n",acu);
}
void *crearDosNumerosAleatorios(void *arg){
	int num1,num2;
	int *sum=malloc(sizeof(int));
	srand(time(NULL));
	sleep(1);
	num1= ((rand()%10) + 1);
	num2=((rand()%10) + 1);
	(*sum)=num1+num2;
	arg=sum;
	pthread_exit((void*)sum);
}
