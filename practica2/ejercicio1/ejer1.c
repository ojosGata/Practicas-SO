//ejer1.c
/*
	Practica 2:
		Ejercicio 4.1:
			Implemente un programa que cree dos hebras. Cada hebra ejecutará una función a la que se le pasará
			como parametor un cadena, concretamente a la primera hebra se le pasará la cadena "hola" y a la segunda "mundo"
			La función que deben ejecutar ambas debe imprimir carácter a carácter la cadena recibida, haciendo un sleep(1) entre 
			cada impresión de carácter.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

void *imprimeCaracter(void *arg);

int  main(){
	pthread_t hilo1;
	pthread_t hilo2;
	
	char *cadena1="hola";
	char *cadena2="MUNDO";
	
	//Creamos los hilos
	pthread_create(&hilo1, NULL, imprimeCaracter, (void*)cadena1);
	pthread_create(&hilo2, NULL, imprimeCaracter, (void*)cadena2);
	//Esperamos a que los hilos terminen
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	printf("\n");
	//Salimos
	pthread_exit(NULL);
}
void *imprimeCaracter(void *arg){
	char* cad=(char*)arg;
	int i;
	for(i=0;i<strlen(cad);i++){
		printf("%c\n",cad[i]);
		sleep(2);
	}

}
