/*
	Practica 1:
	Ejercicio 1:
	Apartado 1: Cree un programa en C que Cree un abanico de procesos. Visualice en la salida el ID o PID de cada proceso y el de su padre.
	Pida el número de procesos totales "n" por la entrada estándar del sistema.
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
void main(int argc, char ** argv){
	int nProcesos; //Numero de procesos
	int i; //Variable auxiliar para los bucles for
	pid_t procesosHijo;//Variable para la creación de procesos
	int flag;//Variable para guardar el estado del proceso hijo
	int valor;// valor del estado del proceso hijo
	if(argc != 2){
		perror("Error en la sintaxis");
		printf("\nERROR: %d, La sintaxis es incorrecta: ./ejer1a <numeroProcesos>\n", errno);
		exit(EXIT_FAILURE);
	}
	nProcesos = atoi(argv[1]);
	//Creación de procesos
	for(i=0;i<nProcesos; i++){
		procesosHijo=fork(); //si procesosHijo vale -1 ha habido un error con la creación, y si vale 0 estamos en alguno de los hijos
		if(procesosHijo == -1){
			perror("Error al crear el proceso hijo");
			printf("\nERROR: %d, no se ha podido crear un proceso hijo\n",errno);
			exit(EXIT_FAILURE);
		}else{
			if(procesosHijo == 0){
				printf("Hijo nº: %d, numero de proceso: %d, numero de proceso padre: %d\n", i, getpid(),getppid());
				exit(EXIT_SUCCESS);
			}
			while ((flag = wait(&valor)) > 0){
				if (WIFEXITED(valor)) {
					printf("child exited, status=%d\n", WEXITSTATUS(valor));
				} else if (WIFSIGNALED(valor)) {
	  				printf("child killed (signal %d)\n", WTERMSIG(valor));
				} else if (WIFSTOPPED(valor)) {
				   printf("child stopped (signal %d)\n", WSTOPSIG(valor));
				}
			}	
		}
		
	}
}
