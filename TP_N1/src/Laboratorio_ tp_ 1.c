/*
 ============================================================================
Nombre: Nicolás Martín Vega Gangemi
Comisión: 1 H
Proyecto: TP N°1
Profesores: Mauricio Davila y Ernesto Gigliotti

Hacer una calculadora. Para ello el programa iniciará y contará con un menú de opciones:
1. Ingresar 1er operando (A=x)
2. Ingresar 2do operando (B=y)
3. Calcular todas las operaciones
	a) Calcular la suma (A+B)
	b) Calcular la resta (A-B)
	c) Calcular la division (A/B)
	d) Calcular la multiplicacion (A*B)
	e) Calcular el factorial (A!)
4. Informar resultados
	a) “El resultado de A+B es: r”
	b) “El resultado de A-B es: r”
	c) “El resultado de A/B es: r” o “No es posible dividir por cero”
	d) “El resultado de A*B es: r”
	e) “El factorial de A es: r1 y El factorial de B es: r2”
5. Salir
• Todas las funciones matemáticas del menú se deberán realizar en una biblioteca aparte,
que contenga las funciones para realizar las cinco operaciones.
• En el menú deberán aparecer los valores actuales cargados en los operandos A y B
(donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado)
• Deberán contemplarse los casos de error (división por cero, etc)
• Documentar todas las funciones
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "utn_math.h"
#include <float.h>

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;
	float operador1;
	float operador2;
	int flagOperador1 = -1;
	int flagOperador2 = -1;
	int flagCalculos = -1;
	float sumaResultado;
	float restaResultado;
	float divisionResultado;
	float multiplicaionResultado;
	float factorialResultado1;
	float factorialResultado2;

	printf("Bienvenido a la Calculadora\n********************");
	do
	{
		utn_menuOptions(operador1, operador2, flagOperador1, flagOperador2);
		utn_getInt("Ingrese una opción:\n\n", "\nERROR: opción no válida\nIntente (1 - 5)\n", &opcion, 3, 1, 5);

		switch(opcion)
		{
		case 1:
			if(utn_getFloat(	"Ingresa el primer operador:",
								"\nERROR: ingresa una opción válida debe ser un numero\n",
								&operador1,
								2,
								-FLT_MAX,
								FLT_MAX) == 0)
			{
				printf("(A = %.2f)\n\n", operador1);
				flagOperador1 = 0;
			}
			break;
		case 2:
			if(utn_getFloat(	"Ingresa el segundo operador:",
								"\nERROR: ingresa una opción válida debe ser un numero\n",
								&operador2,
								2,
								-FLT_MAX,
								FLT_MAX) == 0)
			{
				printf("(B = %.2f)\n\n", operador2);
				flagOperador2 = 0;
			}
			break;
		case 3:
			if(flagOperador1 == 0 && flagOperador2 == 0)
			{
				utn_sumar(&sumaResultado, operador1, operador2);
				utn_restar(&restaResultado, operador1, operador2);
				utn_dividir(&divisionResultado, operador1, operador2);
				utn_multiplicar(&multiplicaionResultado, operador1, operador2);
				utn_factorial(&factorialResultado1, operador1);
				utn_factorial(&factorialResultado2, operador2);
				flagCalculos = 0;
				printf("Se han realizado los calculos con éxito\nIngrese la opción 4 para ver los resultados:\n\n");
			}
			else
			{
				printf("\nDebe ingresar ambos operadores para calcular.\n Intente opcion 1 o 2\n");
			}
			break;
		case 4:
			if(flagCalculos == 0)
			{
				printf("\nLos operadores seleccionados son A = %.2f y B = %.2f\n", operador1, operador2);
				printf("\nEl resultado de la suma de %.2f y %.2f es: %.2f\n", operador1, operador2, sumaResultado);
				printf("\nEl resultado de la resta de %.2f y %.2f es: %.2f\n", operador1, operador2, restaResultado);
				if(utn_dividir(&divisionResultado, operador1, operador2) == 0)
				{
					printf("\nEl resultado de la division de %.2f y %.2f es: %.2f\n", operador1, operador2, divisionResultado);
				}
				else
				{
					printf("\nNo se puede dividir por cero\n");
				}
				printf("\nEl resultado de la multiplicacion de %.2f y %.2f es: %.2f\n", operador1, operador2, multiplicaionResultado);
				if(utn_factorial(&factorialResultado1, operador1) == 0)
				{
					printf("\nEl resultado del factorial de %.2f es: %.2f", operador1, factorialResultado1);
				}
				else
				{
					printf("\nNo existe el factorial de un numero negativo (A = %.2f)", operador1);
				}
				if(utn_factorial(&factorialResultado1, operador2) == 0)
				{
					printf(" y el resultado del factorial de %.2f es: %.2f\n", operador2, factorialResultado2);
				}
				else
				{
					printf(" y no existe el factorial de un numero negativo (B = %.2f)\n", operador2);
				}

			}
			else
			{
				printf("\nDebe primero Calcular (opcion 3) para poder ver los resultados\n");
			}
			break;
		}
	}while(opcion != 5);
	return EXIT_SUCCESS;
}
