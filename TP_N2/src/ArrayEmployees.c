/*
 * ArrayEmployees.c
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "ArrayEmployees.h"

static int employee_generarIdNuevo(void);
/*
* \brief Inicializa todas las posiciones del array en empty (TRUE).
* \param Employee* pArray puntero al array recibido
* \param int length limite del array
* \return int Retorna (-1) si se encuentra un error / (0)  Ok
*/
int employee_init(Employee* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Busca dentro de los indices del array Employee el primer indice donde el valor de isEmpty == TRUE para
 * 			retornar ese valor de (i) como espacio valido para dar un alta
 * \param Employee* pArray puntero al array
 * \param int limite, es el limite del array
 * \return retorna el valor de ( i ) OK / devuelve (-1) para indicar que no hay espacio a completar
 */
int employee_findFirstValidPosition(Employee* pArray, int length)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length;i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retorno = i;
				return retorno;
			}
		}
	}
	return retorno;
}
/**
* \brief Agrega en el array de la estructura los valores pasados como parametros dentro del indice devuelto por la funcion searchFirstValidPosition
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \param int id Id recibido
* \param char name[], array que contiene chars
* \param char lastName[], array que contiene chars
* \param float salary salario recibido
* \param int sector sector recibido
* \return int Return (-1) Error / (0) Ok
*/
int employee_add(Employee* pArray, int length, int id, char name[], char lastName[], float salary, int sector)
{
	int retorno = -1;
	int indiceLibre;
	if(pArray!=NULL && length > 0 && id >= 0 && name != NULL && lastName != NULL && salary >= MIN_SALARY && salary <= MAX_SALARY && sector > 0)
	{
		indiceLibre = employee_findFirstValidPosition(pArray, QTY_EMPLOYEES);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{
			pArray[indiceLibre].id = id;
			pArray[indiceLibre].salary = salary;
			pArray[indiceLibre].sector = sector;
			pArray[indiceLibre].isEmpty = FALSE;
			strncpy(pArray[indiceLibre].lastName, lastName, sizeof(pArray[indiceLibre].lastName)-1);
			strncpy(pArray[indiceLibre].name, name, sizeof(pArray[indiceLibre].lastName)-1);
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Imprime el array pasado como parametro, si el campo isEmpty == FALSE
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int employee_print(Employee* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && length > 0)
	{
		printf("\n Id          Nombre        Apellido      Salary     Sector\n");
		for(i=0; i< length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("%3d %15s %15s %11.2f %10d\n", pArray[i].id, pArray[i].name, pArray[i].lastName, pArray[i].salary, pArray[i].sector);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief encuentra el Employee por ID y retorna el indice de la posicion en el array
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \param int idValue ID recibido a buscar
* \return int Return (-1) Error / devuelve (i) como retorno informando EXITO
* */
int employee_findById(Employee* pArray, int length, int idValue)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && length > 0 && idValue > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == idValue)
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
* \brief Modifica un campo de un Employee, dicho empleado es el indicado por el Indice pasado como parametro
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \param int indice Int buscado en el array para modificar algún campo
* \return int Return (-1) Error / (0) Ok
 */
int employee_modifyEmployeeByIndex(Employee* pArray, int length, int id)
{
	int retorno = -1;
	int opcionModificar;
	int indiceById;
	Employee bufferEmployee;
	if(pArray != NULL && length > 0  && id >= 0 && id < length)
	{
		indiceById = employee_findById(pArray, QTY_EMPLOYEES, id);
		if(indiceById != -1)
		{
			bufferEmployee = pArray[indiceById];
			if(utn_getNumberInt("Que desea modificar en el Empleado:\n"
								"1- Nombre\n"
								"2- Apellido\n"
								"3- Salario\n"
								"4- Sector\n", "Error, ingrese una opción correcta. (1 - 4)\n", &opcionModificar, 3, 1, 4)==0)
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
				bufferEmployee.id = pArray[indiceById].id;
				pArray[indiceById] = bufferEmployee;
				retorno = 0;
			}
		}
		else
		{
			printf(	"El ID: %d no puede \"modificarse\" debido a que no existe\n"
					"Puede consultar los ID de los empleados en la opción 4\n\n", id);
		}
	}
	return retorno;
}
/**
* \brief crea los valores para los campos del employee, que luego se agregaran al array
* 		por la funcion employee_add()
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \param int* pId puntero de Id
* \param char aName[], array que contiene chars
* \param char aLastName[], array que contiene chars
* \param float* pSalary puntero al salario recibido
* \param int* pSector puntero al sector recibido
* \return int Return (-1) Error / (0) Ok
 */
int employee_alta(int length, int* pId, char aName[], char aLastName[], float* pSalary, int* pSector)
{
	int retorno = -1;
	if(pId!= NULL && aName!=NULL && aLastName!=NULL && pSalary != NULL && pSector != NULL && length > 0)
	{
		if(	(utn_getName("Ingresa el Nombre del empleado:\n", "Error, por favor reintentelo con un nombre válido\n\n", aName , 3, LONG_NAME)==0) &&
			(utn_getName("Ingresa el Apellido del empleado:\n", "Error, por favor reintentelo con un apellido válido\n\n", aLastName, 3, LONG_NAME)==0) &&
			(utn_getNumberFloat("Ingrese el sueldo del empleado:\n", "Error, por favor reintentelo con un valor entre (0 - 1000000)\n\n", pSalary, 3, MIN_SALARY, MAX_SALARY)==0) &&
			(utn_getNumberInt("Ingrese el Numero del sector donde trabaja el empleado: \n", "Error, ingrese un sector válido (1 - 10)\n\n", pSector, 3,MIN_SECTOR, MAX_SECTOR)==0))
		{

			*pId = employee_generarIdNuevo();
			retorno = 0;
		}
	}
	return retorno;
}
/*
 *	\brief Cada vez que es llamada devuelve un ID nuevo. Que nunca devolvio antes.
 */
static int employee_generarIdNuevo(void)
{
	static int id=0;//es global pero solo la fnc puede usarla
	id = id + 1;
	return id;
}
/*
* \brief Remueve un employee del array poniendo a isEmpty == TRUE
* \param Employee* pArray puntero al array recibida
* \param int length limite del array
* \param int indice indice recibido a buscar en el array
* \return int Return (-1) Error / (0) Ok
*/
int employee_remove(Employee* pArray, int length, int id)
{
	int retorno = -1;
	int indiceById;
	if(pArray != NULL && length > 0 && id >= 0)
	{
		indiceById = employee_findById(pArray, QTY_EMPLOYEES, id);
		if(indiceById != -1)
		{
			pArray[indiceById].isEmpty = TRUE;
			retorno = 0;
		}
		else
		{
			printf(	"El ID: %d no puede \"darse de baja\" debido a que no existe.\n"
					"Puede consultar los ID de los empleados en la opción 4\n\n", id);
		}
	}
	return retorno;
}
/**
* \brief Utilizando las funciones "alta" y "add", crea un employee valido en el array de la structura.
* \param Employee* pArray, array recibida para crear el employee
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int employee_create(Employee* pArray, int length)
{
	int retorno = -1;
	int id;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	float salary;
	int sector;
	if(pArray != NULL && length > 0)
	{
		if(employee_alta(length, &id, name, lastName, &salary, &sector)==0)
		{
			if(employee_add(pArray, length, id, name, lastName, salary, sector)==0)
			{
				printf("Carga del empleado exitosa!\n\n");
				retorno = 0;
			}
			else
			{
				printf("No se pudo cargar el empleado\n\n");
			}
		}
		else
		{
			printf("No se pudieron obterner los datos del empleado de manera correcta\n");
		}
	}
	return retorno;
}
/*
* \brief Ordena las filas del array de dos maneras: order = 1 -> de forma ascendente. order = 2 -> de forma descendente
* 		Compara por apellido y luego por sector.
* \param Employee* pArray, array recibida para crear el employee
* \param int length limite del array
* \param order parametro que determina el orden del array
* \return int Return (-1) Error / (0) Ok
 */

int employee_sortByLastName(Employee* pArray, int length, int order)
{
	int retorno = -1;
	int i;
	int flagSwap;
	int nuevoLimite = length - 1;
	Employee bufferAlumno;
	if(pArray!=NULL && length > 0 && (order == 1 || order == 2))
	{
		do
		{
			flagSwap = 0;
			for(i=0; i < nuevoLimite; i++)
			{
					if(	(order == 1 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) > 0)
							||
						(order == 2 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) < 0)
							||
						((order == 1 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) == 0)
						&& (pArray[i].sector > pArray[i+1].sector))
							||
						((order == 2 && strncmp(pArray[i].lastName, pArray[i+1].lastName, sizeof(pArray[i].lastName)) == 0)
						&& (pArray[i].sector < pArray[i+1].sector)))
					{
						bufferAlumno = pArray[i];
						pArray[i] = pArray[i+1];
						pArray[i+1] = bufferAlumno;
						flagSwap = 1;
					}
			}
			nuevoLimite--;
		}while(flagSwap);
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula el salario promedio de todos los empleados en el array, obteniendo la suma de la funcion calculateSumaSalary
* \param Employee* pArray, array recibida para crear el employee
* \param int length limite del array
* \param int contadorEmpleadosCargados, valor de la cantidad de empleados que tienen isEmpty=FALSE
* \param float* pAverageSalary puntero al promedio de los salarios
* \param float* pSumaTotal puntero a la suma de los salarios
* \return int Return (-1) Error / (0) Ok
 */
int employee_averageSalary(Employee* pArray, int length, int contadorEmpleadosCargados, float* pAverageSalary, float* pSumaTotal)
{
	int retorno = -1;
	float promedio;
	if(pArray != NULL && length > 0 && contadorEmpleadosCargados >= 0 && pAverageSalary != NULL && pSumaTotal != NULL)
	{
		if(employee_sumaSalary(pArray, length, pSumaTotal)==0)
		{
			promedio = *pSumaTotal / contadorEmpleadosCargados;
		}
		*pAverageSalary = promedio;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula la suma de SALARIOS de los empleados validando el isEmpty==FALSE.
* \param Employee* pArray, array recibida para crear el employee
* \param int length limite del array
* \param float* pResultado, puntero a devolver el valor de los salarios
* \return int Return (-1) Error / (0) Ok
 */
int employee_sumaSalary(Employee* pArray, int length, float* pResultado)
{
	int retorno = -1;
	int i;
	float sumaSalary = 0;
	if(pArray != NULL && length > 0 && pResultado != NULL)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				sumaSalary += pArray[i].salary;
			}
		}
		*pResultado = sumaSalary;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief calcula la cantidad de empleados que ganan más del promedio y valida el flag isEmpty==FALSE
* \param Employee* pArray, array recibida para crear el employee
* \param int length limite del array
* \param float average recibe el promedio de salarios a evaluar
* \param int* pEmployeeGainMore puntero de la cantidad de empleados que ganan mas
* \return int Return (-1) Error / (0) Ok
 */
int employee_gainMoreThanAverage(Employee* pArray, int length, float average, int* pEmployeeGainMore)
{
	int retorno = -1;
	int i;
	int contador = 0;
	if(pArray != NULL && length > 0 && average > MIN_SALARY && average < MAX_SALARY && pEmployeeGainMore != NULL)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].salary > average && pArray[i].isEmpty == 0)
			{
				contador++;
			}
		}
		*pEmployeeGainMore = contador;
		retorno = 0;
	}
	return retorno;
}

