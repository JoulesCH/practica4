#include<bits/stdc++.h> 
using namespace std; 

#define TURNO_COMPUTADORA 1 
#define TURNO_PERSONA 2 

#define LARGO_TABLERO 3 //Largo del tablero 

// Computadora movera con O
// y el usuario con X
#define SIMBOLO_COMPUTADORA 'O' 
#define SIMBOLO_PERSONA 'X' 



// Muestra las instrucciones al usuario
void imprimirInstrucciones() 
{ 
	printf("\nAsi deberas elegir tu movimiento: \n\n"); 
	
	printf("\t\t 1 | 2 | 3 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 4 | 5 | 6 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 7 | 8 | 9 \n\n"); 
} 


// Muestra el estado del tablero actual
void imprimirTablero(char tablero[][LARGO_TABLERO]) 
{ 
	
	printf("\t\t %c | %c | %c \n", tablero[0][0], tablero[0][1], tablero[0][2]); 
	printf("\t\t-----------\n"); 
	printf("\t\t %c | %c | %c \n", tablero[1][0], tablero[1][1], tablero[1][2]); 
	printf("\t\t-----------\n"); 
	printf("\t\t %c | %c | %c \n\n", tablero[2][0], tablero[2][1], tablero[2][2]);  
} 

// Declara el ganador
void mostrarGanador(int turno) 
{ 
	if (turno == TURNO_COMPUTADORA) 
		printf("La computadora ha ganado\n"); 
	else
		printf("tu has ganado\n"); 
} 

// Regresa verdadero si hay una fila con 3 simbolos iguales
bool porFila(char tablero[][LARGO_TABLERO]) 
{ 
	for (int i=0; i<LARGO_TABLERO; i++) 
	{ 
		// Si hay una fila con 3 simbolos iguales, regresa verdadero
		if (tablero[i][0] == tablero[i][1] && 
			tablero[i][1] == tablero[i][2] && 
			tablero[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// Regresa verdadero si hay una columna con 3 simbolos iguales
bool porColumna(char tablero[][LARGO_TABLERO]) 
{ 
	for (int i=0; i<LARGO_TABLERO; i++) 
	{ 
		// Si hay una columna con 3 simbolos iguales, regresa verdadero
		if (tablero[0][i] == tablero[1][i] && 
			tablero[1][i] == tablero[2][i] && 
			tablero[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// Regresa verdadero si hay una diagonal con 3 simbolos iguales
bool porDiagonal(char tablero[][LARGO_TABLERO]) 
{ 
	// Si hay una diagonal con 3 simbolos iguales, regresa verdadero
	if (tablero[0][0] == tablero[1][1] && 
		tablero[1][1] == tablero[2][2] && 
		tablero[0][0] != ' ') 
		return(true); 
		
	if (tablero[0][2] == tablero[1][1] && 
		tablero[1][1] == tablero[2][0] && 
		tablero[0][2] != ' ') 
		return(true); 

	return(false); 
} 

// Regresa verdadero si el juego ha terminado
bool terminoJuego(char tablero[][LARGO_TABLERO]) 
{ 
	return(porFila(tablero) || porColumna(tablero) || porDiagonal(tablero) ); 
}

// Funcion para calcular el mejor movimiento (puntaje)
int minimax(char tablero[][LARGO_TABLERO], int espacios, bool turno_compu)
{
	int puntaje = 0;
	int mejor_puntaje = 0;
	if (terminoJuego(tablero) == true)
	{
		// Si el juego ha terminado, regresa el puntaje
		if (turno_compu == true)
			return -1;
		if (turno_compu == false)
			return +1;
	}
	else
	{
		// Si el juego no ha terminado, calcula cuantos espacios quedan
		if(espacios < 9)
		{
			if(turno_compu == true)
			{
				// Si es el turno de la computadora
				mejor_puntaje = -999;
				for(int i=0; i<LARGO_TABLERO; i++)
				{
					for(int j=0; j<LARGO_TABLERO; j++)
					{
						if (tablero[i][j] == ' ')
						{
							// Hace un movimiento en el tablero
							tablero[i][j] = SIMBOLO_COMPUTADORA;

							// Calcula el puntaje
							puntaje = minimax(tablero, espacios + 1, false);

							// Si el puntaje es mejor que el mejor puntaje, lo guarda
							tablero[i][j] = ' ';
							if(puntaje > mejor_puntaje)
							{
								mejor_puntaje = puntaje;
							}
						}
					}
				}
				return mejor_puntaje;
			}
			else
			{
				// si es el turno del usuario
				mejor_puntaje = 999;
				for (int i = 0; i < LARGO_TABLERO; i++)
				{
					for (int j = 0; j < LARGO_TABLERO; j++)
					{
						if (tablero[i][j] == ' ')
						{
							tablero[i][j] = SIMBOLO_PERSONA;
							puntaje = minimax(tablero, espacios + 1, true);
							tablero[i][j] = ' ';
							if (puntaje < mejor_puntaje)
							{
								mejor_puntaje = puntaje;
							}
						}
					}
				}
				return mejor_puntaje;
			}
		}
		else
		{
			return 0;
		}
	}
    return 0;
}

// Funcion para calcular el mejor movimiento 
int calcularMejorMovimiento(char tablero[][LARGO_TABLERO], int indice_movimiento)
{
	int x = -1, y = -1;
	int puntaje = 0, mejor_puntaje = -999;
    printf("\n\n\t\tMOVIMIENTOS POSIBLES:\n\n\n");
	// Recorre el tablero
	for (int i = 0; i < LARGO_TABLERO; i++)
	{
		for (int j = 0; j < LARGO_TABLERO; j++)
		{
			if (tablero[i][j] == ' ')
			{
				// hace un movimiento de prueba
				tablero[i][j] = SIMBOLO_COMPUTADORA;
				// calcula el puntaje
				puntaje = minimax(tablero, indice_movimiento+1, false);
				imprimirTablero(tablero);
				// si el puntaje es mejor que el mejor puntaje, lo guarda
                printf("\nProbabilidad de ganar: %d\n\n", puntaje);
				tablero[i][j] = ' ';
				if(puntaje > mejor_puntaje)
				{
					mejor_puntaje = puntaje;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// Funcion para contar los simbolos en el tablero
int contarSimbolos(char tablero[][LARGO_TABLERO], char simbolo)
{
    int contador = 0;
    for (int i = 0; i < LARGO_TABLERO; i++)
    {
        for (int j = 0; j < LARGO_TABLERO; j++)
        {
            if (tablero[i][j] == simbolo)
            {
                contador++;
            }
        }
    }
    return contador;
}

// Funcion principal para jugar 
void jugar() 
{ 
	// TABLERO INICIAL
	char tablero[LARGO_TABLERO][LARGO_TABLERO]={ 
        {' ', ' ', ' '}, 
        {' ', SIMBOLO_PERSONA, ' '}, 
        {' ', ' ', ' '} 
    }; 
	int turno, x = 0, y = 0, instruct=0;
    char choice;
    
    printf("Tablero inicial (puedes modificarlo en la linea 213):\n\n");
    imprimirTablero(tablero);

    // Cuenta los simbolos para ver a quien le toca
    int num_x = contarSimbolos(tablero, SIMBOLO_PERSONA);
    int num_o = contarSimbolos(tablero, SIMBOLO_COMPUTADORA);
	int indice_movimiento = num_x + num_o;
    if(num_x<num_o)
    {
        turno = TURNO_PERSONA;
    }
    else if(num_o<num_x)
    {
        turno = TURNO_COMPUTADORA;
    }
    else{
        printf("Es tu intento?(s/n) : ");
	    scanf(" %c", &choice);
        if(choice=='n')
            turno = TURNO_COMPUTADORA;
        else if(choice=='s')
            turno = TURNO_PERSONA;
        else{
            printf("Opcion invalida\n"); 
            return;
        }
	}
	// Continuar jugando hasta que alguien gane o haya un empate
	while (terminoJuego(tablero) == false && indice_movimiento != LARGO_TABLERO*LARGO_TABLERO) 
	{ 
		int n;
		if (turno == TURNO_COMPUTADORA) 
		{
			// logica del turno de la computadora
            printf("\nTurno de la computadora\n");
			n = calcularMejorMovimiento(tablero, indice_movimiento);
			// se calcula el indice del tablero
			x = n / LARGO_TABLERO;
			y = n % LARGO_TABLERO;
			tablero[x][y] = SIMBOLO_COMPUTADORA; 
            printf("-------------------------------------------------------\n");
			printf("\tComputadora decidio poner un %c en la celda %d\n\n", SIMBOLO_COMPUTADORA, n+1);
			// muestra el tableor despues del movimiento
			imprimirTablero(tablero);
			indice_movimiento ++; 
			// cambia el turno
			turno = TURNO_PERSONA;
		} 
		
		else if (turno == TURNO_PERSONA) 
		{
            if(instruct==0){
				// solo se muestran las instrucciones una vez
	            imprimirInstrucciones();
                instruct=1;
            } 
            printf("\nTu turno\n");
			printf("Pudes elegir las siguientes: ");
			for(int i=0; i<LARGO_TABLERO; i++)
				for (int j = 0; j < LARGO_TABLERO; j++)
					if (tablero[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			// pide la decision del usuario 
			printf("\n\nIngresa tu decision => ");
			scanf("%d",&n);
			n--;

			// se calcula el indice del tablero
			x = n / LARGO_TABLERO;
			y = n % LARGO_TABLERO; 


			if(tablero[x][y] == ' ' && n<9 && n>=0)
			{
				// ahora se pone el simbolo en el tablero
				tablero[x][y] = SIMBOLO_PERSONA; 
				printf ("\nHas elegido poner %c en la celda %d\n\n", SIMBOLO_PERSONA, n+1); 
				imprimirTablero(tablero); 
				indice_movimiento ++; 
				turno = TURNO_COMPUTADORA;
			}
			else if(tablero[x][y] != ' ' && n<9 && n>=0)
			{
				// si ingresa una posicion ya ocupada
				printf("\nLa posicion esta ocupada, intentalo de nuevo\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("Posicion invalida\n");
			}
		} 
	} 

	// Si hay un empate
	if (terminoJuego(tablero) == false && indice_movimiento == LARGO_TABLERO * LARGO_TABLERO) 
		printf("Es un empate!\n"); 
	else
	{ 
		// Cambiando los turnos
		if (turno == TURNO_COMPUTADORA) 
			turno = TURNO_PERSONA; 
		else if (turno == TURNO_PERSONA) 
			turno = TURNO_COMPUTADORA; 
		
		mostrarGanador(turno); 
	} 
} 


// Funcion principal
int main() 
{ 
	printf("\t\t\t Juego de Gato - Equipo 8\n\n"); 
	char cont='y';
	do {
		jugar();
        
		printf("\nQuieres salir?(s/n) : ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0); 
} 