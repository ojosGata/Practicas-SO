#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
void main(int argc, char **argv){
	pid_t idProceso;
	int i,n,valor, flag;
	
	if (argc != 2){
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s Numero de processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}
	n=atoi(argv[1]);
	
	for(i=0;i<n;i++){
		idProceso=fork();	
	
		switch(idProceso){
			case -1:
				perror("Error del fork()");
				printf("errno value:%d",errno);
				exit(EXIT_FAILURE);
			case 0:
				printf("\nProceso Hijo:\tNumero: %d\tNumero Proceso Padre: %d",getpid(),getppid());		
			/*default:
				printf("\nProceso Padre:\tNumero: %d\tNumero Proceso Padre: %d",getpid(),getppid());
			*/
		}
		while ((flag = wait(&valor)) > 0){
			if (WIFEXITED(valor)) {
     		 	printf("\nchild exited, status=%d\n", WEXITSTATUS(valor));
  			} else if (WIFSIGNALED(valor)) {
  			  	printf("\nchild killed (signal %d)\n", WTERMSIG(valor));
  			} else if (WIFSTOPPED(valor)) {
      		printf("\nchild stopped (signal %d)\n", WSTOPSIG(valor));
      	}
		}
	}		
	
	if (flag==-1 && errno==ECHILD)
		printf("\nNo hay más hijos que esperar\n");
	else{
		printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS); //return 0;
}
