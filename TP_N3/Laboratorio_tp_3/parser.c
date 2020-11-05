#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
		int retornoFscanf;
		Employee* pBuffer;
		char auxNombre[LONG_NAME];
		char auxHoras[LONG_NAME];
		char auxSueldo[LONG_NAME];
		char auxId[LONG_NAME];
		if(pFile != NULL && pArrayListEmployee != NULL)
		{
			retorno = 0;
			do
			{
				pBuffer = employee_new();
				retornoFscanf = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxHoras, auxSueldo);
				if(retornoFscanf == 4)
				{
					pBuffer = employee_newParametros(auxId, auxNombre, auxHoras, auxSueldo);
					ll_add(pArrayListEmployee, pBuffer);
				}
			}while(!feof(pFile));
		}
		return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
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
					ll_add(pArrayListEmployee, pBuffer);
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
