/* El siguiente programa crea dos hilos. Cada hilo hace exactamente lo mismo, incrementar una
variable global un numero de veces. El resultado final debe ser el doble del numero de veces
que se incrementa la variable, ya que cada hilo la incrementa el mismo número de veces. Si no
hubiera semáforo general, el resultado podría ser inconsistente. Pruebe a ejecutarlo con
semáforos y quitando los semáforos.*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
//Cada hilo incrementará 100 veces la variable global.
#define NITER 100
//Variables globales
int count = 0;
sem_t mutex;
void * ThreadAdd(void * a){
	int i, tmp;
	for(i = 0; i < NITER; i++){
		sem_wait(&mutex);
		tmp = count; /* copy the global count locally */
		tmp = tmp+1; /* increment the local copy */
		count = tmp; /* store the local value into the global count */
		sem_post(&mutex);
	}
}
int main(int argc, char * argv[]){
	//inicializamos nuestro semáforo a 1
	//y el cero indica que el semáforo solo
	//estara disponible para este main() y sus hilos().
	sem_init(&mutex, 0, 1);
	pthread_t tid1, tid2;
	//Note que podría hacer esto con un bucle for()
	if(pthread_create(&tid1, NULL, ThreadAdd, NULL)){
		printf("\n ERROR creating thread 1");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&tid2, NULL, ThreadAdd, NULL)){
		printf("\n ERROR creating thread 2");
		exit(EXIT_FAILURE);
	}
	//Note que podría hacer esto con un bucle for()
	if(pthread_join(tid1, NULL)){/* wait for the thread 1 to finish */ 
		printf("\n ERROR joining thread");
		exit(EXIT_FAILURE);
	}
	if(pthread_join(tid2, NULL)){ /* wait for the thread 2 to finish */
		printf("\n ERROR joining thread");
		exit(EXIT_FAILURE);
	}
	if ( (count< (2 * NITER)) || (count>(2 * NITER)) )
		printf("\n BOOM! count is [%d], should be %d\n", count, 2*NITER);
	else
		printf("\n OK! count is [%d] \n", count);
	pthread_exit(NULL);
}
