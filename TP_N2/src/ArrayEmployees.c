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

#define QTY_EMPLOYEES 1000
#define LONG_NAME 101
#define MAX_SALARY 100000
#define MIN_SALARY 0.01
#define TRUE 1
#define FALSE 0

static int employee_generarIdNuevo(void);

/*
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
* \param Employee* pListEmployees Pointer to array of employees
* \param int length Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] / (0) if Ok
*/
int employee_init(Employee* pListEmployees, int length)
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

/**
 * \brief Busca dentro de los indices del array ALUMNO el primer indice donde el valor de isEmpty == TRUE para
 * 			retornar ese valor de I como espacio valido para dar un alta
 * \param Employee* pListEmployees puntero a la struct EMPLOYEE
 * \param int limite, es el limite del array
 * \return retorna el valor de I OK / devuelve -1 para indicar que no hay espacio a completar
 */
int employee_searchFirstValidPosition(Employee* pListEmployees, int length)
{
	int i;
	int retorno = -1;
	if(pListEmployees!=NULL && length > 0)
	{
		for(i=0; i < length;i++)
		{
			if(pListEmployees[i].isEmpty == TRUE)
			{
				retorno = i;
				return retorno;
			}
		}
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
int employee_altaEmployee(Employee* pListEmployees, int length, int index)
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


/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param Employee* listEmployee
* \param length int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
*/
int employee_add(Employee* listEmployee, int length, int id, char name[], char lastName[], float salary, int sector)
{
	int retorno = -1;
	int indiceLibre;
	//Employee bufferEmployee;
	if(listEmployee!=NULL && length > 0 && id >= 0 && name != NULL && lastName != NULL && salary >= MIN_SALARY && salary <= MAX_SALARY && sector > 0)
	{
		indiceLibre = employee_searchFirstValidPosition(listEmployee, QTY_EMPLOYEES);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{

			listEmployee[indiceLibre].id = id;
			listEmployee[indiceLibre].salary = salary;
			listEmployee[indiceLibre].sector = sector;
			listEmployee[indiceLibre].isEmpty = FALSE;
			printf("empty%d - %d\n", listEmployee[indiceLibre].isEmpty, listEmployee[indiceLibre+1].isEmpty );
			strncpy(listEmployee[indiceLibre].lastName, lastName, sizeof(listEmployee[indiceLibre].lastName-1));
			strncpy(listEmployee[indiceLibre].name, name, sizeof(listEmployee[indiceLibre].name-1));
			printf("empty%d - %d\n", listEmployee[indiceLibre].isEmpty, listEmployee[indiceLibre+1].isEmpty );

		}
		retorno = 0;
	}
	return retorno;
}

/*
int employee_addEmployee(Employee* pListEmployee, int length, int id, char name[], char lastName[], float salary, int sector)
{
	int retorno = -1;
	int indiceLibre;
	if(pListEmployee != NULL && length > 0 && id > 0 && name != NULL && lastName != NULL && salary >= MIN_SALARY && salary <= MIN_SALARY && sector > 0)
	{
		indiceLibre = employee_searchFirstValidPosition(pListEmployee, length);
		if(indiceLibre == -1)
		{
			printf("No quedan indices\n");
		}
		else
		{
			pListEmployee[in
		}
	}
	return retorno;
}
*/
/**
 *
 */
int employee_print(Employee* pListEmployee, int length)
{
	int retorno = -1;
	int i;
	if(pListEmployee!=NULL && length > 0)
	{
		for(i=0; i< length; i++)
		{
			if(pListEmployee[i].isEmpty == FALSE)
			{
				printf("Id: %d - Nombre: %s - Apellido: %s - Salary: %.2f - Sector: %d -  isEmpty:%d - Indice:%d\n", pListEmployee[i].id, pListEmployee[i].name, pListEmployee[i].lastName, pListEmployee[i].salary, pListEmployee[i].sector, pListEmployee[i].isEmpty, i);
			}
		}
		retorno = 0;
	}
	return retorno;
}


/** \brief find an Employee by Id en returns the index position in array.
*
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int employee_findById(Employee* pListEmployee, int length, int idValue)
{
	int retorno = -1;
	int i;
	if(pListEmployee!=NULL && length > 0 && idValue > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pListEmployee[i].isEmpty == FALSE)
			{
				if(pListEmployee[i].id == idValue)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
 *
 */
int employee_modifyEmployeeByIndex(Employee* pListEmployee, int length, int indice)
{
	int retorno = -1;
	int opcionModificar;
	Employee bufferEmployee = pListEmployee[indice];
	if(pListEmployee != NULL && length > 0  && indice >= 0)
	{
		/*
		if(	(utn_getName("Ingrese el nuevo Nombre del empleado:\n", "Error, ingrese un nombre válido\n", bufferEmployee.name, 3, LONG_NAME)==0) &&
			(utn_getName("Ingrese el nuevo Apellido del empleado:\n", "Error, ingrese un apellido válido\n", bufferEmployee.lastName, 3, LONG_NAME)==0) &&
			(utn_getNumberFloat("Ingrese el nuevo Sueldo del empleado:\n", "Error, ingrese un sueldo válido\n", &bufferEmployee.salary, 3, MIN_SALARY, MAX_SALARY)==0) &&
			(utn_getNumberInt("Ingrese el nuevo sector del empleado\n", "Error, no existe ese sector\n", &bufferEmployee.sector, 3, 1, 10)==0))


			bufferEmployee.isEmpty = FALSE;
			bufferEmployee.id = pListEmployee[indice].id;
			pListEmployee[indice] = bufferEmployee;
			retorno = 0;
			*/
		if(utn_getNumberInt("Que desea modificar en el Empleado:\n1- Nombre\n2- Apellido\n3- Salario\n4- Sector\n", "Error, ingrese una opción correcta. (1 - 4)", &opcionModificar, 3, 1, 4)==0)
		{
			switch(opcionModificar)
			{
				case 1:
					if(utn_getName("Ingrese el nuevo Nombre del empleado:\n", "Error, ingrese un nombre válido\n", bufferEmployee.name, 3, LONG_NAME)==0)
					{
						printf("Nombre modificado correctamente\n");
					}
					break;
				case 2:
					if(utn_getName("Ingrese el nuevo Apellido del empleado:\n", "Error, ingrese un apellido válido\n", bufferEmployee.lastName, 3, LONG_NAME)==0)
					{
						printf("Apellido modificado correctamente\n");
					}
					break;
				case 3:
					if(utn_getNumberFloat("Ingrese el nuevo Sueldo del empleado:\n", "Error, ingrese un sueldo válido\n", &bufferEmployee.salary, 3, MIN_SALARY, MAX_SALARY)==0)
					{
						printf("Salario modificado correctamente\n");
					}
					break;
				case 4:
					if(utn_getNumberInt("Ingrese el nuevo sector del empleado\n", "Error, no existe ese sector\n", &bufferEmployee.sector, 3, 1, 10)==0)
					{
						printf("Sector modificado correctamente\n");
					}
					break;
			}
			bufferEmployee.isEmpty = FALSE;
			bufferEmployee.id = pListEmployee[indice].id;
			pListEmployee[indice] = bufferEmployee;
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *
 *
 */
int employee_PRUEBAaltaEmployee(int* pId, char aName[], char aLastName[], float* pSalary, int* pSector, int length)
{
	int retorno = -1;
	//Employee bufferEmployee;
	if(pId!= NULL && aName!=NULL && aLastName!=NULL && pSalary != NULL && pSector != NULL && length > 0)
	{
		if(	(utn_getName("Ingresa el Nombre del empleado:\n", "Error, por favor reintentelo con un nombre válido\n", aName , 3, LONG_NAME)==0) &&
			(utn_getName("Ingresa el Apellido del empleado:\n", "Error, por favor reintentelo con un apellido válido\n", aLastName, 3, LONG_NAME)==0) &&
			(utn_getNumberFloat("Ingrese el sueldo del empleado:\n", "Error, por favor reintentelo con un valor mayor a 0\n", pSalary, 3, MIN_SALARY, MAX_SALARY)==0) &&
			(utn_getNumberInt("Ingrese el Numero del sector donde trabaja el empleado: \n", "Error, ingrese un sector válido\n", pSector, 3, 1, 5)==0))
		{

			*pId = employee_generarIdNuevo();
			/*
			strcpy(bufferEmployee.name, aName);
			strcpy(bufferEmployee.lastName, aLastName);
			bufferEmployee.salary = *pSalary;
			bufferEmployee.sector = *pSector;
			bufferEmployee.id = *pId;
			*/
			//printf("PRINTF : %s - %s - %.2f - %d - %d\n\n", bufferEmployee.name, bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector, bufferEmployee.id );
			retorno = 0;
		}
	}
	return retorno;
}

/*
 *	\brief Cada vez que llamo me devuelve un ID nuevo que nunca devolvio antes
 */
static int employee_generarIdNuevo(void)
{
	static int id=0;//es global pero solo la fnc puede usarla

	id = id + 1;
	return id;

}


/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int employee_remove(Employee* pListEmployee, int length, int indice)
{
	int retorno = -1;
	if(pListEmployee != NULL && length > 0 && indice >= 0)
	{
		pListEmployee[indice].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}


/**
 *
 */
int employee_createEmployee(Employee* pListEmployee, int length)
{
	int retorno = -1;
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	if(pListEmployee != NULL && length > 0)
	{
		if(employee_PRUEBAaltaEmployee(&id, name, lastName, &salary, &sector, length)==0)
		{
			if(employee_add(pListEmployee, length, id, name, lastName, salary, sector)==0)
			{
				//FOR PARA VER EL ERROR
				printf("Carga del empleado exitosa!\n\n");
				retorno = 0;
			}
			else
			{
				printf("NO SE AÑADIO EL EMPLOYEE\n\n");
			}
		}
	}
	return retorno;
}

/*
 *
 */
int employee_sortByLastNameAndSector(Employee* pListEmployee, int length, int order)
{
	int retorno = -1;
	int nuevoLimite;
	int i;
	int flagSwamp = 1;
	Employee bufferEmployee;
	if(pListEmployee != NULL && length > 0 && order > 0 && order < 3)
	{

		do
			{
				nuevoLimite = length -1;
				flagSwamp = 0;
				for(i = 0; i < nuevoLimite; i++)
				{
					if(order == 1)
					{
						if(pListEmployee[i].isEmpty == 0)
						{
							if(strncmp(pListEmployee[i].lastName, pListEmployee[i+1].lastName, sizeof(pListEmployee[i].lastName)-1) > 0)
							{
								flagSwamp = 1;
								bufferEmployee = pListEmployee[i];
								pListEmployee[i] = pListEmployee[i + 1];
								pListEmployee[i + 1] = bufferEmployee;
							}
							else if(strncmp(pListEmployee[i].lastName, pListEmployee[i+1].lastName, sizeof(pListEmployee[i].lastName)-1) == 0 && pListEmployee[i].sector > pListEmployee[i+1].sector)
							{
								bufferEmployee = pListEmployee[i];
								pListEmployee[i] = pListEmployee[i + 1];
								pListEmployee[i + 1] = bufferEmployee;
							}
						}
					}
					else
					{
						if(pListEmployee[i].isEmpty == 0)
						{
							if(strncmp(pListEmployee[i].lastName, pListEmployee[i+1].lastName, sizeof(pListEmployee[i].lastName)-1) < 0)
							{
								flagSwamp = 1;
								bufferEmployee = pListEmployee[i];
								pListEmployee[i] = pListEmployee[i + 1];
								pListEmployee[i + 1] = bufferEmployee;
							}
							else if(strncmp(pListEmployee[i].lastName, pListEmployee[i+1].lastName, sizeof(pListEmployee[i].lastName)-1) == 0 && pListEmployee[i].sector < pListEmployee[i+1].sector)
							{
								bufferEmployee = pListEmployee[i];
								pListEmployee[i] = pListEmployee[i + 1];
								pListEmployee[i + 1] = bufferEmployee;
							}
						}
					}

				}
				nuevoLimite--;
				retorno = 0;
			}while(flagSwamp);
	}
	return retorno;
}

/*
 *
 */
int employee_calculateAverageSalary(Employee* pListEmployee, int length, int contadorEmpleadosCargados, float* pAverageSalary)
{
	int retorno = -1;
	float sumaTotal;
	float promedio;
	if(pListEmployee != NULL && length > 0)
	{
		if(employee_calculateSumaSalary(pListEmployee, length, &sumaTotal)==0)
		{
			promedio = sumaTotal / contadorEmpleadosCargados;
		}
		*pAverageSalary = promedio;
		retorno = 0;
	}
	return retorno;
}


/*
 *
 */
int employee_calculateSumaSalary(Employee* pListEmployee, int length, float* pResultado)
{
	int retorno = -1;
	int i;
	float sumaSalary = 0;
	if(pListEmployee != NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pListEmployee[i].isEmpty == 0)
			{
				sumaSalary += pListEmployee[i].salary;
			}
		}
		*pResultado = sumaSalary;
		printf("El total de los salarios es: %f\n", *pResultado);
		retorno = 0;
	}
	return retorno;
}

/*
 *
 */
int employee_calculateEmployeeGainMoreThanAverage(Employee* pListEmployee, int length, float average, int* pEmployeeGainMore)
{
	int retorno = -1;
	int i;
	int contador = 0;
	if(pListEmployee != NULL && length > 0 && average > MIN_SALARY && average < MAX_SALARY && pEmployeeGainMore != NULL)
	{
		for(i=0; i < length; i++)
		{
			if(pListEmployee[i].salary > average && pListEmployee[i].isEmpty == 0)
			{
				contador++;
			}
		}
		*pEmployeeGainMore = contador;
		retorno = 0;
	}


	return retorno;
}
