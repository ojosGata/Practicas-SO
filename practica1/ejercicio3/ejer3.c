#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>

void main(int argc, char **argv){
	pid_t idProceso;
	int i,n1,n2,valor, flag,estado;
	
	if (argc != 3){
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s Numero de processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}
	n1=atoi(argv[1]);
	n2=atoi(argv[2]);
	for(i=0;i<2;i++){
		idProceso=fork();
		switch(idProceso){
			case -1:
				perror("Error del fork()");
				printf("errno value:%d",errno);
				exit(EXIT_FAILURE);
			case 0:
				printf("\nProceso Hijo %d:\tNumero: %d\tNumero Proceso Padre: %d\n",i,getpid(),getppid());
				sleep(1);
				if(execl("a.out",".",argv[(i+1)],NULL)==-1){
					perror("Falla en la ejecucion exec de ./a.out n");
					printf("errno value= %d\n", errno);
					exit(EXIT_FAILURE);
				} 	
				exit(EXIT_SUCCESS);
		}
	
	}
	while ((flag = wait(&valor)) > 0);
	exit(EXIT_SUCCESS); //return 0;
}	

