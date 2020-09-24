/*
 * ArrayEmployees.c
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "utn_math.h"
#include "ArrayEmployees.h"

#define QTY_EMPLOYEES 5
#define LONG_NAME 51
#define MAX_SALARY 100000
#define MIN_SALARY 0.01
#define TRUE 1
#define FALSE 0

/*
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
* \param Employee* pListEmployees Pointer to array of employees
* \param int length Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] / (0) if Ok
*/
int Employees_init(Employee* pListEmployees, int length)
{
	int retorno = -1;
	int i;
	if(pListEmployees != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pListEmployees[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/*
* \brief To initialize the id of the employees from 1
* \param Employee* pListEmployees Pointer to array of employees
* \param int length Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] / (0) if Ok
 */
int Employees_id(Employee* pListEmployees, int length)
{
	int retorno = -1;
	int i;
	if(pListEmployees!=NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			pListEmployees[i].id = i + 1;
		}
		retorno = 0;
	}
	return retorno;
}

/*
* \brief add in a existing list of employees the values received as parameters in the first empty position
* \param Employee* pListEmployees Pointer to array of employees
* \param int length Array length
* \param int id
* \param char name[]
* \param char lastName[]
* \param float salary
* \param int sector
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
*/
int Employee_add(Employee* pListEmployees, int length, int index)
{
	int retorno = 0;
	Employee bufferEmployee;
	if(	pListEmployees != NULL && length > 0 && index >= 0 && index < length && pListEmployees[index].isEmpty == TRUE)
	{
		if(	(utn_getName("Ingresa el Nombre del empleado:\n", "Error, por favor reintentelo con un nombre válido\n", bufferEmployee.name , 3, LONG_NAME)==0) &&
			(utn_getName("Ingresa el Apellido del empleado:\n", "Error, por favor reintentelo con un apellido válido\n", bufferEmployee.lastName, 3, LONG_NAME)==0) &&
			(utn_getNumberFloat("Ingrese el sueldo del empleado:\n", "Error, por favor reintentelo con un valor mayor a 0\n", &bufferEmployee.salary, 3, MIN_SALARY, MAX_SALARY)==0) &&
			(utn_getNumberInt("Ingrese el Numero del sector donde trabaja el empleado: \n", "Error, ingrese un sector válido\n", &bufferEmployee.sector, 3, 1, 5)==0))
		{
			bufferEmployee.isEmpty = FALSE;
			pListEmployees[index] = bufferEmployee;
			retorno = 0;
		}

	}
	return retorno;
}

int Employee_print(Employee* pListEmployee, int length)
{
	int retorno = -1;

	return retorno;
}

