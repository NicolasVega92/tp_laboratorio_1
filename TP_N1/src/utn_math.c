/*
 * utn_math.c
 *      Author: Nico
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Suma dos operadores ingresados
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param float operador1, primer operador obtenido
 * \param float operador2, segundo operador obtenido
 * \return (-1) Error / (0) Ok
 */
int utn_sumar(float* pResultado, float operador1, float operador2)
{
	int retorno = -1;
	float suma;
	if(pResultado != NULL)
	{
		suma = operador1 + operador2;
		*pResultado = suma;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Rest dos operadores ingresados
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param float operador1, primer operador obtenido
 * \param float operador2, segundo operador obtenido
 * \return (-1) Error / (0) Ok
 */
int utn_restar(float* pResultado, float operador1, float operador2)
{
	int retorno = -1;
	float resta;
	if(pResultado != NULL)
	{
		resta = operador1 - operador2;
		*pResultado = resta;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Divide dos operadores ingresados
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param float operador1, primer operador obtenido
 * \param float operador2, segundo operador obtenido
 * \return (-1) Error  / (0) Ok
 */
int utn_dividir(float *pResultado, float operador1, float operador2)
{
	int retorno = -1;
	float division;
	if(pResultado != NULL && operador2 != 0)
	{
		if(operador1 == 0)
		{
			//Debido a que la division de 0 con un numero negativo da como resultado (-0)
			division = 0;
			*pResultado = division;
		}
		else
		{
			division = operador1 / operador2;
			*pResultado = division;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Multiplica dos operadores ingresados
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param float operador1, primer operador obtenido
 * \param float operador2, segundo operador obtenido
 * \return (-1) Error / (0) Ok
 */
int utn_multiplicar(float* pResultado, float operador1, float operador2)
{
	int retorno = -1;
	float multiplicacion;
	if(pResultado != NULL)
	{
		if(operador1 == 0 || operador2 == 0)
		{
			//Debido a que la multiplicacion de 0 con un numero negativo da como resultado (-0)
			*pResultado  = 0;
		}
		else
		{
			multiplicacion = operador1*operador2;
			*pResultado = multiplicacion;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Factorial de un operador ingresado
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param float operador1, operador obtenido
 * \return (-1) Error / (0) Ok
 */
int utn_factorial(float* pResultado, float operador1)
{
	int retorno = -1;
	float factorial = 1;
	int i;
	if(pResultado != NULL && operador1 >= 0)
	{
		if(operador1 == 0)
		{
			*pResultado = 1;
			retorno = 0;
		}
		else
		{
			for(i = operador1; i > 0; i--)
			{
				factorial  *= i;
			}
		}
		*pResultado = factorial;
		retorno = 0;
	}
	return retorno;
}
