#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>

int main(){
	pid_t idProceso;
	int valor, flag,estado;
	idProceso=fork();
	switch(idProceso){
		case -1:
			perror("Error del fork()");
			printf("errno value:%d",errno);
			exit(EXIT_FAILURE);
		case 0:
			printf("\nProceso Hijo:\tNumero: %d\tNumero Proceso Padre: %d\n",getpid(),getppid());	
			exit(33);
		default:
			sleep(30);
			if((flag=wait(&estado))>0)
				{
					if (WIFEXITED(estado) != 0){ //Si se termina bien, "estadoHijo" cogerá  el valor devuelto por éste,33..
						printf ("Padre: Mi hijo ha salido. Devuelve %d\n y flag(su PID) es %d\n", WEXITSTATUS(estado), flag);
					} else if (WIFSIGNALED(estado)) {  //Para seniales como las de finalizar o matar
            			printf("NO ME VAS A MATAR, MI PADRE ES INIT!!!  child killed (signal %d)\n", WTERMSIG(estado));
					}
					/*No entrará nunca porque wait solo se ejecuta una vez(no hay bucle). wait devuelve -1 cuando hay fallo en su llamada o
					 cuando se llama Y no hay datos en el sistema de algun hijo que haya tenido el padre, en cuyo caso "errno" se pone a ECHILD*/
					if(errno==ECHILD) {
						printf("No hay hijos que esperar\n");	
						printf("Padre durmiendo de nuevo....\n");
						sleep(10);
					}
				}
				else
				{
					printf("Fallo al ejecutar el wait()\n");
				}
			
	}
	
	exit(EXIT_SUCCESS); //return 0;
}	

