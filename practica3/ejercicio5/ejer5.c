//ejer4v4
//Includes y defines
 #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void *leerFichero(void * arg);
void *escribirFichero(void * arg);
//Seccion critica
int buffer[1024]; /* Buffer en el que se va a escribir parte del fichero*/ 
int n_copias = 0; /* contador de copias que se van realizando */
int n_hilos=0; /* Contador de hilos que han realizado una copia*/ 
pthread_mutex_t mutex =	PTHREAD_MUTEX_INITIALIZER;/*Semafora para controlar el acceso */ 
pthread_cond_t no_leer = PTHREAD_COND_INITIALIZER; /* condicion para que no lea */
pthread_cond_t no_escribir=PTHREAD_COND_INITIALIZER; /*Condicion para que no escriba*/

void main(int argc, char **argv){
	if(argc =!3){
		printf("\nError en la sintaxis: ./ejer5 <nombreFichero> nºcopias\n");
		exit(EXIT_FAILURE);
	} 
	int nCopias = atoi(argv[2]);
	int i;
	n_hilos = nCopias;
	//Iniciar hebras escritoras y lectoras
	pthread_t hiloEscribirBuffer;
	pthread_t hiloCopias[nCopias];
	
	//Lanzar hebras escritoras y lectoras
	char *nombreFich;
	strcpy(nombreFich, argv[1]);
	pthread_create(&EscribirBuffer, NULL,leerFichero,(void*)nombreFich);
	
	for(i=0;i<nCopias;i++){
		char *ext;
		ext=itoa(i);
		strcat(ext,".txt");
		strcat(nombreFich, ext);
		pthread_create(&hiloCopias[i],NULL, hacerCopia, (void*)nombreFich);
	}
	//	Esperar las hebras
	pthread_join(hiloEscribirBuffer,NULL);
	for(i=0;i<nCopias;i++){
		pthread_join(hiloCopias[i],NULL);
	}
	//Destruir los semaforos 
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&no_leer);
	pthread_cond_destroy(&no_escribir);
}

void *escribirFichero(void * arg){ /* codigo del escritor */
	FILE fichero;
	int i;
	pthread_cond_wait(&no_leer,&mutex);
	fichero=fopen(arg,"r");
	if(fichero==NULL){
		perror();
		printf("Error al abrir el fichero %s", arg);
		exit(EXIT_FAIURE);
	
	}
	while((fgets(buffer,1024,fichero))!=NULL){
					
	}
	
  	//Entrando en la seccion critica de escribir fichero
  	//Leer una linea del fichero
  	//Guardar en el buffer
  	//Desbloquear la condicion de NOLEER
  	
      pthread_mutex_unlock(&mutex); 
   
}
void *hacerCopia(void *arg){  /* codigo del lector */ 
   
   if(strcmp(buffer,"")==0){ //El buffer esta vacio y no puedo empezar a copiar
   	pthread_mutex_lock(&mutexLeer);
   }else{
   	n_copias++;
   	if(n_copias==n_hilos){
   		pthread_cond
   	}
   
   }
   //Bloquear la condicion de NOLEER
   //Aumentar el numero de copias
   //si la copia es uno
   	//bloquear la condicion de Escribir
   //desbloquear la condicion de Noleer
   //Guardar en el fichero pasado como argumento el contenido del buffer
   	//abrir fichero en modo añadir
   	//añadir la cadena
   	//cerrar el fichero
   //bloquear la condicion de NOleer
   //aumentar el numero de hebras//distinto al numero de copias
   //Si el numero de copias coincide con el numero de hebras
   	//desbloquear la condicion de escribir
   //desbloquear la condicion de NOLEER
   
}
