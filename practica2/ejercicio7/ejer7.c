#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

struct estructura{
	char cadena[1024];
	int entero;
};

void *cambioCadena(void *arg);

void main(int argc, char** argv){
	struct estructura st;
	pthread_t hilo;
	int i;
	strcpy(st.cadena ,"Este es el mensaje Original");
	st.entero=0;
	for(i=0;i<10;i++){
		pthread_create(&hilo, NULL, cambioCadena,(void *)&st);
		pthread_join(hilo, NULL);
	}
	printf("\nMostramos el mensaje después de los cambios:\n");
	printf("valor entero:%d y valor cadena:%s\n",st.entero,st.cadena);
	
}
void *cambioCadena(void *arg){
	struct estructura *aux=(struct estructura *)arg;
	aux->cadena[aux->entero]='9';
	sleep(1);
	(aux->entero)++;
	
}

