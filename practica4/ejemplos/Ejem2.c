/*
Programa de sincronización entre hilos que suma los números impares entre 0 y 20, es decir,
los números 1+3+5+7+9+11+13+15+17+19 = 100. El primer hilo comprueba que el número es
impar, si lo es deja que el segundo hilo lo sume, sino comprueba el siguiente número. Cópielo
y ejecútelo para comprobar su salida. Haga una traza en papel de su funcionamiento teniendo
en cuenta varios casos en los que el procesador da rodaja de tiempo al hilo P1 o al hilo P2.*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//Semáforo s1 para lo impares y s2 para los pares.
sem_t s1, s2;
//Sección crítica
int num=0, suma=0;
//Prototipos de funciones
void *p1 ();
void *p2 ();
int main(){
	int error1, error2;
	pthread_t h1, h2;
	sem_init (&s2, 0, 0); //Semáforo inicializado a 0
	sem_init (&s1, 0, 1); //Semáforo inicializado a 1
	error1 = pthread_create (&h1, NULL, p1, NULL);
	error2 = pthread_create (&h2, NULL, p2, NULL);
	//Complete el control de errores
	// ...
	pthread_join (h1, NULL);
	pthread_join (h2, NULL);
	//Complete el control de errores
 	// ...
	printf ("Mai() - La suma es %d\n", suma);
	return 0;
} 

 void *p1(){
	int i;
	for (i=0; i<20; i++){
		sem_wait (&s1); //Cuando haya que sumar un impar se bloqueará aquí.
		if (i%2){ //Si el resultado del modulo es distinto de cero es que es impar. Incrementa semáforo 2.
			num=i;
			printf ("HILO1: Número impar %d. Desbloqueando a HILO 2\n", i);
			sem_post (&s2); //Si p2() está esperando en s2, P2 se desbloqueará.
		}
		else //Si el resultado del modulo es cero es par. Si es impar incrementa semáforo 1.
			sem_post (&s1); //Incrementa s1, el siguiente numero será impar y debe entrar en seccióncrit.
	}
	pthread_exit(NULL);
} 
void *p2(){
	int i;
	for (i=0; i<10; i++){
		/*Se queda esperando cuando el número es par y lo tiene que desbloquear P1 cuando encuentre un impar.*/
		sem_wait (&s2);
		printf ("HILO2: Suma actual = %d + %d\n", suma, num);
		suma = suma+num;
		/*Cuando haya sumado un impar desbloqueará a P1() incrementando s1 para
		que busque el siguiente par. P1 se encontrará esperando a que P2 haga la
		suma antes de poder volver a entrar en la sección crítica*/
		sem_post (&s1);
	}
	pthread_exit(NULL);
}
