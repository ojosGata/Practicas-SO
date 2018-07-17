#include <pthread.h>
#include <stdio.h>

void *thread(void *vargp){
	/*En cuanto se haga el pthread_detach() se eliminará el estado de esta hebra y no se podrán hacer más joins con ella.*/
	sleep(3);
	pthread_detach(pthread_self());
	pthread_exit((void*)42);
	
}

int main(){
	int i=0;
	pthread_t tid;
	
	pthread_create(&tid,NULL, thread, NULL);
	//Recogemos el resultado que devuelve la hebra. Ninguna otra hebra o proceso principal podra hacerle otro join().
	pthread_join(tid, (void**)&i);
	printf("%d\n",i);

}
