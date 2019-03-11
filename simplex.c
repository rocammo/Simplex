/**
 * Autor: Rodrigo Casamayor <alu.89657@usj.es>
 * Fecha: 09 de Febrero de 2018
 *
 * Programa: Resolution of linear programming problems by the Simplex method.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j, k; // iteradores

char objective;
int variables, restrictions;
int ROWS, COLS, b, FO;

void inputMatrix  (float matrix[ROWS][COLS]);
void solveMatrix  (float matrix[ROWS][COLS]);
void outputMatrix (float matrix[ROWS][COLS]);

int main (void)
{
    char running = 'S';

    printf("%c", 218);
    for (i = 0; i < 49; i++)
    {
        printf("%c", 196);
    }
    printf("%c\n", 191);
    printf("|Solucionador Programacion Lineal (Metodo Simplex)|\n");
    printf("|  (Autor: Rodrigo Casamayor <alu.89657@usj.es>)  |\n");
    printf("%c", 192);
    for (i = 0; i < 49; i++)
    {
        printf("%c", 196);
    }
    printf("%c\n\n", 217);


    while (running == 'S' || running == 's')
    {
        printf("Introduzca el objetivo ([M]aximizar o [m]inimizar): ");
        scanf(" %c", &objective);
        printf("Introduzca el numero de variables (x, y, z): ");
        scanf("%d", &variables);
        printf("Introduzca el numero de restricciones: ");
        scanf("%d", &restrictions);

        // ROWS: restricciones + FO; COLS: variables iniciales + variables de holgura + b;
        ROWS = restrictions + 1, COLS = variables + restrictions + 1, b = COLS - 1, FO = restrictions;
        float matrix[ROWS][COLS];

        inputMatrix (matrix);
        solveMatrix (matrix);
        outputMatrix(matrix);


        // Regenerar?
        do
        {
            printf("%cDesea introducir otro problema? <S/n>: ", 168);
            scanf(" %c", &running);
        } while ((running != 'S' && running != 's') &&
                 (running != 'n' && running != 'N'));
        if (running == 'S' || running == 's') printf("\n\n");
    }



    return(0);
}

void inputMatrix (float matrix[ROWS][COLS])
{
    for (i = 0; i < restrictions; i++)
    {
        printf("Introduzca la restriccion %d (-ax by cz = d): ", i + 1);
        for (j = 0; j < variables; j++) {
            scanf("%f%*c ", &matrix[i][j]);
        }
        scanf("%*c %f", &matrix[i][b]);
    }
    printf("Introduzca la F.O. (F = t -> t -[F] = 0): ");
    for (j = 0; j < variables; j++) {
        if (j == (variables - 1)) scanf("%f%*c", &matrix[FO][j]);
        else scanf("%f%*c ", &matrix[FO][j]);
    }
    for (i = 0, j = restrictions; j >= 1; i++, j--) {
        switch (objective) {
        case 'M':
            matrix[i][b - j] = (float) 1;
            break;
        case 'm':
            matrix[i][b - j] = (float) -1;
            break;
        }
        for (k = 0; k <= FO; k++) {
            if (matrix[k][b - j] != 1) matrix[k][b - j] = (float) 0;
        }
    }
    matrix[FO][b] = (float) 0;
}

void solveMatrix (float matrix[ROWS][COLS])
{
    int solution = 0, counter = 0;
    int n, m;
    float smaller, higher, pivot;

    while (!solution && counter <= 8)
    {
        if (objective == 'M') {
            // Determina el numero menor de la F.O.
            smaller = 0, n = 0, m = 0, pivot = 0;
            for (j = 0; j < b; j++) {
                if (matrix[FO][j] < smaller) {
                    smaller = matrix[FO][j];
                    n = j;
                }
            }
            // Determina el numero menor de la b
            smaller = 0;
            for (i = 0; i < FO; i++) {
                if (matrix[i][n] > 0) {
                    if (smaller == 0) {
                        smaller = matrix[i][b] / matrix[i][n];
                        m = i;
                    } else if ((matrix[i][b] / matrix[i][n]) < smaller) {
                        smaller = matrix[i][b] / matrix[i][n];
                        m = i;
                    }
                }
            }
            // Realiza las operaciones pertinentes
            pivot = matrix[m][n];
            for (j = 0; j < COLS; j++) {
                matrix[m][j] /= pivot;
            }
            for (i = 0; i < ROWS; i++) {
                pivot = matrix[i][n];
                for (j = 0; j < COLS; j++) {
                    if (i != m) matrix[i][j] += (-pivot * matrix[m][j]);
                }
            }
            // Comprueba si existe solucion basica factible
            smaller = 0;
            for (k = 0; k < b; k++) {
                if (matrix[FO][k] < 0) smaller = matrix[FO][k];
            }
            if (smaller < 0) solution = 0;
            else solution = 1;
            counter++;
        } else {
            // SOLVE FOR mINIMIZATION
            // Determina el numero mayor de la F.O.
            higher = 0, n = 0, m = 0, pivot = 0;
            for (j = 0; j < b; j++) {
                if (matrix[FO][j] > higher) {
                    higher = matrix[FO][j];
                    n = j;
                }
            }
            // Determina el numero mayor de la b
            higher = 0;
            for (i = 0; i < FO; i++) {
                if (matrix[i][n] > 0) {
                    if (higher == 0) {
                        higher = matrix[i][b] / matrix[i][n];
                        m = i;
                    } else if ((matrix[i][b] / matrix[i][n]) > higher) {
                        higher = matrix[i][b] / matrix[i][n];
                        m = i;
                    }
                }
            }
            // Realiza las operaciones pertinentes
            pivot = matrix[m][n];
            for (j = 0; j < COLS; j++) {
                matrix[m][j] /= pivot;
            }
            for (i = 0; i < ROWS; i++) {
                pivot = matrix[i][n];
                for (j = 0; j < COLS; j++) {
                    if (i != m) matrix[i][j] += (-pivot * matrix[m][j]);
                }
            }
            // Comprueba si existe solucion basica factible
            higher = 0;
            for (k = 0; k < b; k++) {
                if (matrix[FO][k] > 0) higher = matrix[FO][k];
            }
            if (higher > 0) solution = 0;
            else solution = 1;
            counter++;
        }
    }
}

void outputMatrix (float matrix[ROWS][COLS])
{
    // Comprobacion por consola
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("|");
        for (j = 0; j < COLS; j++) {
            printf(" %8.2f |", matrix[i][j]);
            if (j == (b)) printf("\n");
        }
    }


    // Matriz resultado
    char varXYZ[50], varH[50], aux[50];
    printf("\nS.B.F.O.  : (");
    if (variables == 2) {
        strcpy(varXYZ, " x y");
    } else {
        strcpy(varXYZ, " x y z");
    }
    strcpy(varH,   " ");
    for (i = 1, k = variables; k < b; i++, k++) {
        strcat(varH, "x");
        sprintf(aux, "%d ", i);
        strcat(varH, aux);
    }
    printf("%s%s", varXYZ, varH);

    printf(") = ( ");

    int count;
    for (j = 0; j < b; j++) {
        count = 0, k = 0;
        for (i = 0; i < ROWS; i++) {
            switch ((int) matrix[i][j]) {
                case 0:
                    count++;
                    break;
                case 1:
                    count++;
                    k = i;
                    break;
            }
        }
        if (count == ROWS) printf("%.f ", matrix[k][b]);
        else printf("0 ");
    }
    printf(")\n");

    printf("Valor F.O.: [%.f]\n\n", matrix[FO][b]);
}
