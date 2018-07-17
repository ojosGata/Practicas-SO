/*
	Practica 1:
	Ejercicio 1:
	Apartado 2: Cree un programa en C que Cree un hilera de procesos. Visualice en la salida el ID o PID de cada proceso y el de su padre.
	Pida el número de procesos totales "n" por la entrada estándar del sistema.
*/
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void main(int argc, char **argv){
	int nProcesos; //Numero de procesos
	int i=0; //Variable auxiliar para los bucles for
	pid_t procesosHijo;//Variable para la creación de procesos
	int flag;//Variable para guardar el estado del proceso hijo
	int valor;// valor del estado del proceso hijo
	
	if(argc != 2){
		perror("Error con la sintaxis")
		printf("ERROR: %d, La sintaxis correcta es: ./ejer1b <NumeroProcesos>");
		exit(EXIT_FAILURE);
	}
	nProcesos = atoi(argv[1]);
	while(i!=nProcesos){
		//creación de procesos
		procesosHijo = fork
	
	}

}


