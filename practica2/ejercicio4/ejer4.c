//ejer4.c
/*
	Practica 2:
		Ejercicio 4.4:
			usar dos ficheros .mp4. Crear un programa que de forma paralela convierta dichos ficheros a .mp3 con el programa "ffmpeg".
			Los nombre de los ficheros .mp4 se pediran por linea de argumentos. Usar system()

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void*convertirMP4aMP3(void *arg);

void main(int argc, char **argv){
	
	pthread_t hilo1, hilo2;
	
	if(argc!=2){
		perror("Error en la sintaxis");
		printf("\nError en la sintaxis: ./ejer4 <nombreVideo1> <nombreVideo2>\n" );
		exit(EXIT_FAILURE);
	}
	//crear los hilos
	pthread_create(&hilo1, NULL, convertirMP4aMP3,(void*)argv[1]);
	pthread_create(&hilo2, NULL, convertirMP4aMP3,(void*)argv[2]);
	//esperar hilos
	pthread_join(hilo1,NULL);
	pthread_join(hilo2,NULL);	
	
	//finalizar hilos
	pthread_exit(NULL);

}
void*convertirMP4aMP3(void *arg){
	char *video=(char *)arg;
	char comando[1024]="ffmpeg -i "+arg+".mp4 -f mp3 -ab 192000 -ar 48000 -vn "+arg+"MP3.mp3";
	
	system(comando);
}
