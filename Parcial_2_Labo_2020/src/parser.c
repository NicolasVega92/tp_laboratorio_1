

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "utn.h"
#include "Cliente.h"
#include "Ventas.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param this LinkedList*
 * \return int
 *
 */
int parser_ClienteFromText(FILE* pFile , LinkedList* this)
{
	int retorno = -1;
		int retornoFscanf;
		Cliente* pBuffer;
		char auxNombre[LONG_NAME];
		char auxApellido[LONG_NAME];
		char auxCuit[LONG_NAME];
		char auxId[LONG_NAME];
		char buffer[4][LONG_NAME];
		if(pFile != NULL && this != NULL)
		{
			retorno = 0;
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
			do
			{
				pBuffer = cliente_new();
				retornoFscanf = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxApellido, auxCuit);
				if(retornoFscanf == 4)
				{
					pBuffer = cliente_newParametrosTxt(auxNombre, auxApellido, auxCuit, auxId);
					ll_add(this, pBuffer);
				}
				else
				{
					printf("Fijate el retorno del fscanf\n");
				}
			}while(!feof(pFile));
		}
		return retorno;
}
/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param this LinkedList*
 * \return int
 *
 */
int parser_ventasFromText(FILE* pFile , LinkedList* this)
{
	int retorno = -1;
	int retornoFscanf;
	Ventas* pBuffer;
	char auxNombre[LONG_NAME];
	char auxIdCliente[LONG_NAME];
	char auxCantAfiches[LONG_NAME];
	char auxId[LONG_NAME];
	char auxZona[LONG_NAME];
	char auxEstado[LONG_NAME];
	char buffer[6][LONG_NAME];
	if(pFile != NULL && this != NULL)
	{
		retorno = 0;
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
		do
		{
			pBuffer = ventas_new();
			retornoFscanf = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxCantAfiches, auxNombre, auxZona, auxEstado,auxIdCliente );
			if(retornoFscanf == 6)
			{
				pBuffer = ventas_newParametrosTxt(auxId, auxEstado, auxIdCliente, auxCantAfiches, auxNombre, auxZona);
				ll_add(this, pBuffer);
			}
			else
			{
				printf("Fijate el retorno del fscanf\n");
			}
		}while(!feof(pFile));
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param this LinkedList*
 * \return int
 *
 */
/*
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* this)
{
	int retorno = -1;
	Employee* pBuffer;
	int retornoRead;
	if(pFile != NULL)
	{
		retorno = 0;
		do
		{
			pBuffer = employee_new();
			if(pBuffer != NULL)
			{
				retornoRead = fread(pBuffer, sizeof(Employee), 1, pFile);
				if(retornoRead == 1)
				{
					ll_add(this, pBuffer);
				}
				else
				{
					employee_delete(pBuffer);
					break;
				}
			}
		}while(!feof(pFile));
	}
	else
	{
		printf("No se pudo leer el archivo\n\n");
	}
	return retorno;
}
*/
