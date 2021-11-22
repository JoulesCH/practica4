#include<bits/stdc++.h> 
using namespace std; 

#define TURNO_COMPUTADORA 1 
#define TURNO_PERSONA 2 

#define LARGO_TABLERO 3 // Length of the tablero 

// Computer will move with 'O' 
// and human with 'X' 
#define SIMBOLO_COMPUTADORA 'O' 
#define SIMBOLO_PERSONA 'X' 

// A function to show the current tablero status 
void imprimirTablero(char tablero[][LARGO_TABLERO]) 
{ 
	
	printf("\t\t %c | %c | %c \n", tablero[0][0], tablero[0][1], tablero[0][2]); 
	printf("\t\t-----------\n"); 
	printf("\t\t %c | %c | %c \n", tablero[1][0], tablero[1][1], tablero[1][2]); 
	printf("\t\t-----------\n"); 
	printf("\t\t %c | %c | %c \n\n", tablero[2][0], tablero[2][1], tablero[2][2]);  
} 

// A function to show the instructions 
void imprimirInstrucciones() 
{ 
	printf("\nAsi deberas elegir tu movimiento: \n\n"); 
	
	printf("\t\t 1 | 2 | 3 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 4 | 5 | 6 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 7 | 8 | 9 \n\n"); 
} 



// A function to declare the winner of the game 
void mostrarGanador(int turno) 
{ 
	if (turno == TURNO_COMPUTADORA) 
		printf("La computadora ha ganado\n"); 
	else
		printf("tu has ganado\n"); 
} 

// A function that returns true if any of the row 
// is crossed with the same player's move 
bool porFila(char tablero[][LARGO_TABLERO]) 
{ 
	for (int i=0; i<LARGO_TABLERO; i++) 
	{ 
		if (tablero[i][0] == tablero[i][1] && 
			tablero[i][1] == tablero[i][2] && 
			tablero[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the column 
// is crossed with the same player's move 
bool porColumna(char tablero[][LARGO_TABLERO]) 
{ 
	for (int i=0; i<LARGO_TABLERO; i++) 
	{ 
		if (tablero[0][i] == tablero[1][i] && 
			tablero[1][i] == tablero[2][i] && 
			tablero[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the diagonal 
// is crossed with the same player's move 
bool porDiagonal(char tablero[][LARGO_TABLERO]) 
{ 
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

// A function that returns true if the game is over 
// else it returns a false 
bool terminoJuego(char tablero[][LARGO_TABLERO]) 
{ 
	return(porFila(tablero) || porColumna(tablero) || porDiagonal(tablero) ); 
}

// Function to calculate best puntaje
int minimax(char tablero[][LARGO_TABLERO], int espacios, bool turno_compu)
{
	int puntaje = 0;
	int mejor_puntaje = 0;
	if (terminoJuego(tablero) == true)
	{
		if (turno_compu == true)
			return -1;
		if (turno_compu == false)
			return +1;
	}
	else
	{
		if(espacios < 9)
		{
			if(turno_compu == true)
			{
				mejor_puntaje = -999;
				for(int i=0; i<LARGO_TABLERO; i++)
				{
					for(int j=0; j<LARGO_TABLERO; j++)
					{
						if (tablero[i][j] == ' ')
						{
							tablero[i][j] = SIMBOLO_COMPUTADORA;
							puntaje = minimax(tablero, espacios + 1, false);
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

// Function to calculate best move
int calcularMejorMovimiento(char tablero[][LARGO_TABLERO], int indice_movimiento)
{
	int x = -1, y = -1;
	int puntaje = 0, mejor_puntaje = -999;
    printf("\n\n\t\tMOVIMIENTOS POSIBLES:\n\n\n");
	for (int i = 0; i < LARGO_TABLERO; i++)
	{
		for (int j = 0; j < LARGO_TABLERO; j++)
		{
			if (tablero[i][j] == ' ')
			{
				tablero[i][j] = SIMBOLO_COMPUTADORA;
				puntaje = minimax(tablero, indice_movimiento+1, false);
                imprimirTablero(tablero);
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
// A function to play Tic-Tac-Toe 
void jugar() 
{ 
	char tablero[LARGO_TABLERO][LARGO_TABLERO]={ 
        {' ', ' ', ' '}, 
        {' ', SIMBOLO_PERSONA, ' '}, 
        {' ', ' ', ' '} 
    }; 
	int turno, indice_movimiento = 0, x = 0, y = 0, instruct=0;
    char choice;
    
    printf("Tablero inicial (puedes modificarlo en la linea 213):\n\n");
    imprimirTablero(tablero);
    
    int num_x = contarSimbolos(tablero, SIMBOLO_PERSONA);
    int num_o = contarSimbolos(tablero, SIMBOLO_COMPUTADORA);
    if(num_x<num_o)
    {
        turno = TURNO_PERSONA;
    }
    else if(num_o<num_x)
    {
        turno = TURNO_COMPUTADORA;
    }
    else{
        printf("Es tu intento?(y/n) : ");
	    scanf(" %c", &choice);
        if(choice=='n')
            turno = TURNO_COMPUTADORA;
        else if(choice=='y')
            turno = TURNO_PERSONA;
        else{
            printf("Opcion invalida\n"); 
            return;
        }
	}
	// Keep playing till the game is over or it is a draw 
	while (terminoJuego(tablero) == false && indice_movimiento != LARGO_TABLERO*LARGO_TABLERO) 
	{ 
		int n;
		if (turno == TURNO_COMPUTADORA) 
		{
            printf("\nTurno de la computadora\n");
			n = calcularMejorMovimiento(tablero, indice_movimiento);
			x = n / LARGO_TABLERO;
			y = n % LARGO_TABLERO;
			tablero[x][y] = SIMBOLO_COMPUTADORA; 
            printf("-------------------------------------------------------\n");
			printf("\tComputadora decidio poner un %c en la celda %d\n\n", SIMBOLO_COMPUTADORA, n+1);
			imprimirTablero(tablero);
			indice_movimiento ++; 
			turno = TURNO_PERSONA;
		} 
		
		else if (turno == TURNO_PERSONA) 
		{
            if(instruct==0){
	            imprimirInstrucciones();
                instruct=1;
            } 
            printf("\nTu turno\n");
			printf("Pudes elegir las siguientes: ");
			for(int i=0; i<LARGO_TABLERO; i++)
				for (int j = 0; j < LARGO_TABLERO; j++)
					if (tablero[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nIngresa tu decision => ");
			scanf("%d",&n);
			n--;
			x = n / LARGO_TABLERO;
			y = n % LARGO_TABLERO; 
			if(tablero[x][y] == ' ' && n<9 && n>=0)
			{
				tablero[x][y] = SIMBOLO_PERSONA; 
				printf ("\nHas elegido poner %c en la celda %d\n\n", SIMBOLO_PERSONA, n+1); 
				imprimirTablero(tablero); 
				indice_movimiento ++; 
				turno = TURNO_COMPUTADORA;
			}
			else if(tablero[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\nLa posicion esta ocupada, intentalo de nuevo\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("Posicion invalida\n");
			}
		} 
	} 

	// If the game has drawn 
	if (terminoJuego(tablero) == false && indice_movimiento == LARGO_TABLERO * LARGO_TABLERO) 
		printf("Es un empate!\n"); 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (turno == TURNO_COMPUTADORA) 
			turno = TURNO_PERSONA; 
		else if (turno == TURNO_PERSONA) 
			turno = TURNO_COMPUTADORA; 
		
		mostrarGanador(turno); 
	} 
} 

int main() 
{ 
	printf("\t\t\t Juego de Gato - Equipo 8\n\n"); 
	char cont='y';
	do {
		jugar();
        
		printf("\nQuieres salir?(y/n) : ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0); 
} 