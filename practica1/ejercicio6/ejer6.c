#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void main(int argc, char **argv){
	pid_t idProceso;
	int i,valor, flag,estado;
	
	
	for(i=0;i<2;i++){
		idProceso=fork();
		switch(idProceso){
			case -1:
				perror("Error del fork()");
				printf("errno value:%d",errno);
				exit(EXIT_FAILURE);
			case 0:
				printf("\nProceso Hijo %d:\tNumero: %d\tNumero Proceso Padre: %d\n",i,getpid(),getppid());
				if(i==0){
					if(execlp(argv[1],argv[1],NULL)==-1){
						perror("Falla en la ejecucion de la calculadora");
						printf("errno value= %d\n", errno);
						exit(EXIT_FAILURE);
				
					}
				}else{
					if(execvp(argv[2],&argv[2])<0){
						perror("Falla en la ejecucion del editor gedit");
						printf("errno value= %d\n", errno);
						exit(EXIT_FAILURE);
					}
				} 	
				sleep(1);
				exit(EXIT_SUCCESS);
		}
	
	}
	while ((flag = wait(&valor)) > 0);
	exit(EXIT_SUCCESS); //return 0;
}	

