#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0;
	int i, n, j, valor, flag;

	if (argc != 2)	{
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);

	for (i = 0; i <n; i++){
		childpid = fork();
		if (childpid == -1){
		 	perror("fork error");
			printf("errno value= %d\n", errno);  
			exit(EXIT_FAILURE);
		}else if(childpid == 0){//Estamos en alguno de los hijos
			printf("process ID:%ld parent ID:%ld\n",(long)getpid(), (long)getppid());
			sleep(i*10);
		}else{
		//En caso contrario el padre espera al hijo
			while ((flag = wait(&valor)) > 0);
			i=n;
		}
	}


	exit(EXIT_SUCCESS); //return 0;
}

