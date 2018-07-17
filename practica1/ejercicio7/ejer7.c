#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void main(int argc, char **argv){
	pid_t idProceso;
	int i, valor, flag,estado;
	FILE *fich;
	char auxiliar[1024];
	char* cadenaHijo="----------------hijo";
	char* cadenaPadre="+++++++++++++++++Padre";
	if(argc !=2){
		perror("Error en la sintaxis: ./ejer7 nombreFichero");
		printf("valor errno: %d.\n", errno);
		exit(EXIT_FAILURE);
	}
	if((fich=fopen(argv[1],"w"))==NULL){
		printf("\nError: Al intentar abrir el fichero\n");
		exit(EXIT_FAILURE);
	}
	idProceso=fork();
	for(i=0;i<2;i++){
		//sleep(1);
		if(idProceso==-1){
			perror("Error del fork()");
			printf("errno value:%d",errno);
			exit(EXIT_FAILURE);
		}else if(idProceso==0){
			sleep(1);
			fprintf(fich, "%s\n",cadenaHijo);
			printf("\nImprimiendo al hijo\n");
			//exit(EXIT_SUCCESS);
		}else{
			sleep(1);
			fprintf(fich, "%s\n",cadenaPadre);
			printf("\nImprimiendo al padre\n");
		}
		
	}
	while ((flag = wait(&valor)) > 0);
	fclose(fich);
	if((fich=fopen(argv[1],"r"))==NULL){
		printf("\nError: Al intentar abrir el fichero\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(auxiliar, 1024, fich)!=NULL ){
		printf("%s",auxiliar);
	}	
	fclose(fich);
	exit(EXIT_SUCCESS); //return 0;
}	

