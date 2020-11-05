/*
 * Validaciones.c
 *
 *  Created on: 2 nov. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"
#include "Validaciones.h"
/*
* \brief Verifica una cadena como parametro para determinar si es nombre valido
* \param char cadena[], cadena a analizar
* \param limite indica la cantidad maxima del nombre
 * return (1) Es válido / (0) No es un nombre valido
 */
int isAValidName(char array[], int limite)
{
	int retorno = 1; //TODO OK
	int i=0;
	if(array[i]=='\0')
	{
		retorno = 0;
	}
	else
	{
		for(i = 0; i <= limite && array[i] != '\0'; i++)
		{
			if(isLettersSpaceGuion(array) == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada son letras
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
int isLettersSpaceGuion(char array[])
{
	int retorno = 1;
	int i=0;
	int flagSpace = FALSE;
	if(array[i]==' ')
	{
		retorno = 0;
	}
	else
	{
		for( ; array[i] != '\0'; i++)
		{
			if(flagSpace == TRUE)
			{
				if(array[i] == ' ')
				{
					retorno = 0;
					break;
				}
				else
				{
					flagSpace = FALSE;
				}
			}
			if((array[i] < 'A' || array[i] > 'Z') &&
				(array[i] < 'a' || array[i] > 'z') &&
				(array[i] != ' ') &&
				(array[i] != '-') &&
				(array[i] < 'á' || array[i] > 'ú') &&
				(array[i] != 'é'))
			{
				retorno = 0;
				break;
			}
			if(array[i] == ' ')
			{
				flagSpace = TRUE;
			}

		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
int isNumber(char array[])
{
	int retorno = 1;
	int i = 0;

	if(array[0] == '-')
	{
		i = 1;
	}
	for( ; array[i] != '\0'; i++)
	{
		if(array[i] < '0' || array[i] > '9')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica y puede contener signo en el primer indice o ningun o 1 punto.
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
int isNumberFloat(char array[])
{
	int retorno = 1;
	int i = 0;
	int contadorPuntos = 0;

	if(array != NULL && strlen(array) > 0)
	{
		for(i=0; array[i] != '\0'; i++)
		{
			if(i==0 && (array[i] == '-' || array[i] == '+'))
			{
				continue;
			}
			if(array[i] < '0' || array[i] > '9')
			{
				if(array[i] == '.' && contadorPuntos==0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	else
	{
		retorno = 0;
	}
	return retorno;
}



























