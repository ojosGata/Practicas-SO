#include <stdio.h>
#include <pthread.h>

void* message_print(void* ptr){
	int error=0;
	char *msg;
	
	/* Desconexión del hilo cuando finalice. pthread_self() devuelve el ID de la hebra que invoca esta función. Se estudiará a continuacion.*/
	
	error=pthread_detach(pthread_self());
	
	/* Manejar el error*/
	//....
	
	msg = (char*)ptr;
	sleep(5);
	printf("THREAD: This is the Message %s\n", msg);
	pthread_exit(NULL);

}

int main(void){
	int error=0;
	size_t i=0;
	char mess[]="This is a test";
	
	/* Creación de un conjunto de hebras*/
	pthread_t th[5];//Array de hebras
	for(i=0;i<thread_no;i++){
		error=pthread_create(&(th[i]),NULL, message_print,(void*)mess);
		/* Manejar el error */
		//....
	}
	printf("MAIN: Thread Message: %s\n",mess);
	pthread_exit(NULL);
}
