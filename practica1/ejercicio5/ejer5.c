#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>

void main(int argc, char **argv){
	pid_t idProceso;
	int tiempo,flag;
	int estado;
	if(argc != 3){
	 	printf("Uso: %s Tiempo ValorEstado\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	tiempo=atoi(argv[1]);
	estado=atoi(argv[2]);
	idProceso=fork();
	switch(idProceso){
		case -1:
			perror("Error del fork()");
			printf("errno value:%d",errno);
			exit(EXIT_FAILURE);
		case 0:
			printf("\nProceso Hijo:\tNumero: %d\tNumero Proceso Padre: %d\n",getpid(),getppid());
			sleep(tiempo);	
			exit(EXIT_SUCCESS);
		//default:
			//while ((flag = wait(&valor)) > 0);		
	}
	while(idProceso!=wait(&estado));
	printf("\nEl estado actual es: %d\n",estado);
	exit(EXIT_SUCCESS);

}
