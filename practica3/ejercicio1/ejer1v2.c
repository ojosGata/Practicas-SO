// Soluci�n al problema de la secci�n cr�tica para 2 procesos
// Algoritmo de Peterson

// Variables globales compartidas
typedef enum {
    PRIMERO, SEGUNDO
} TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

// Inicializaci�n de variables
P1QuiereEntrar = P2QuiereEntrar = FALSE;
TurnoProceso = PRIMERO;

void Proceso1()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P1QuiereEntrar = TRUE;
	TurnoProceso = SEGUNDO;
	while (P2QuiereEntrar && TurnoProceso == SEGUNDO);

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

	P1QuiereEntrar = FALSE;

	// Secci�n residual
    }
}

void Proceso2()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P2QuiereEntrar = TRUE;
	TurnoProceso = PRIMERO;
	while (P1QuiereEntrar && TurnoProceso == PRIMERO);

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

	P2QuiereEntrar = FALSE;

	// Secci�n residual
    }
}

