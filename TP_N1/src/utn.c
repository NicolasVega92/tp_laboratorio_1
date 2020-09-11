/*
 * utn.c
 *      Author: Nico
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Imprime un menú al usuario
 * \param float operador1, recibe un dato del operador
 * \param float operador2, recibe un dato del operador
 * \param int flagOperador1, recibe un dato del operador
 * \param int flagOperador2, recibe un dato del operador
 * \return void
 */
void utn_menuOptions(float operador1, float operador2, int flagOperador1, int flagOperador2)
{
	printf("\n1 para ingresar el primer operador: A\n");
	printf("2 para ingresar el segundo operador: B\n");
	printf("3 para calcular todas las operaciones \n");
	printf("4 para mostrar los resultados\n");
	printf("5 Salir de la calculadora\n");
	if(flagOperador1 == 0 && flagOperador2 == 0)
	{
		printf("A = %.2f\n", operador1);
		printf("B = %.2f\n", operador2);
	}
	else
	{
		if(flagOperador1 == 0 && flagOperador2 == (-1))
		{
			printf("A = %.2f\n", operador1);
			printf("B = Sin ingresar\n");
		}
		else
		{
			if(flagOperador1 == (-1) && flagOperador2 == 0)
			{
				printf("A = Sin ingresar\n");
				printf("B = %.2f\n", operador2);
			}
			else
			{
				printf("A = Sin ingresar\n");
				printf("B = Sin ingresar\n");
			}
		}
	}
}


/**
 * \brief Solicita un entero al usuario
 * \param char* pMensaje, Es el mensaje mostrado al usuario
 * \param char* pMensajeError, Es el mensaje de error a ser mnostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int maximo, valor maximo admitido
 * \return (-1) Error / (0) Ok
 */
int utn_getInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo)
{
	int retorno = -1;
	int bufferInt;

	if(		pMensaje != NULL &&
			pMensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			minimo <= maximo)
	{
		do
		{
			printf("%s", pMensaje);
			fflush(stdin);
			if(scanf("%d", &bufferInt) == 1 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break; //Para terminar el bucle del do while
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}
		while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}

/**
* \brief Solicita un float al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mnostrado al usuario
* \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param float minimo, valor minimo admitido
* \param float maximo, valor maximo admitido
* \return (-1) Error / (0) Ok
*/
int utn_getFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo)
{
	int retorno = -1;
	float bufferFloat;
	int resultadoScanf;

	if(pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s\n", pMensaje);
			fflush(stdin);
			resultadoScanf = scanf("%f" , &bufferFloat);
			if(resultadoScanf == 1 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s\n", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}


