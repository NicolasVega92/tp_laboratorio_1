/*
 * Employee.c
 *
 *  Created on: 1 nov. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"
#include "LinkedList.h"
#include "Controller.h"
static int isAValidName(char array[], int limite);
static int isLettersSpaceGuion(char array[]);
static int isNumber(char array[]);
/*
 * \brief 	Crea una direccion de memoria con el tamaño indicado en malloc
 * \return	Una direccion de memoria con el tamaño de Employee
 */
Employee* employee_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}
/*
 * \brief	Agrega los valores pasados como parametros a la direccion de memoria creada por new
 * \param	char* nombre
 * \param 	char* apellido
 * \param	char* altura
 * \param	char* id
 * \return	auxPuntero pudiendo ser = NULL o = la direccion creada por new con los valores agregados
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this;
	this = employee_new();
	if(this != NULL && nombreStr != NULL && sueldoStr != NULL && idStr != NULL && horasTrabajadasStr != NULL)
	{
		if(	employee_setNombre(this, nombreStr)==-1							||
			employee_setHorasTrabajadasTxt(this, horasTrabajadasStr) == -1 	||
			employee_setIdTxt(this, idStr)==-1								||
			employee_setSueldoTxt(this, sueldoStr)==-1						)
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}
/*
 * \brief 	Libera la direccion de memoria del elemento pasado como parametro
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}
/*
 * \brief 	Setea el valor de nombre para el elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	char* nombre
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(isAValidName(nombre, LONG_NAME))
		{
			strncpy(this->nombre, nombre, LONG_NAME);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de nombre del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	char* nombre
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre, this->nombre, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de ID como INT en el elemento pasado como parametro (this)
 * 			El id se pasa como char* en el parametro de la función
 * \param 	Employee* this
 * \param	char* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setIdTxt(Employee* this, char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		if(isNumber(id))
		{
			this->id = atoi(id);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * A REHACER ....
 */
int employee_setIdTxtStaticValue(Employee* this, char* id)
{
	int retorno = -1;
	static int maximoId = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		if(atoi(id) < 0)
		{
			maximoId++;
			this->id = maximoId;
		}
		else
		{
			if(atoi(id) > maximoId)
			{
				maximoId = atoi(id);
			}
			this->id = atoi(id);
		}
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de ID como INT en el elemento pasado como parametro (this)
 * 			El id se pasa como int en el parametro de la función
 * \param 	Employee* this
 * \param	int id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setId(Employee* this, int id)
{
	int retorno = -1;
	if(this != NULL && id > 0)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de ID como CHAR del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	char* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getIdTxt(Employee* this, char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		sprintf(id, "%d", this->id);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de ID como INT del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	int* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getId(Employee* this, int* id)
{
	int retorno=-1;
	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de HORASTRABAJADAS como INT en el elemento pasado como parametro (this)
 * 			HORASTRABAJADAS se pasa como char* en el parametro de la función
 * \param 	Employee* this
 * \param	char* horasTrabajadas
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		if(isNumber(horasTrabajadas))
		{
			this->horasTrabajadas = atoi(horasTrabajadas);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de HORASTRABAJADAS como INT en el elemento pasado como parametro (this)
 * 			HORASTRABAJADAS se pasa como int en el parametro de la función
 * \param 	Employee* this
 * \param	int horasTrabajadas
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas > 0)
	{
		this->id = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de HORASTRABAJADAS como CHAR del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	char* horasTrabajadas
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getHorasTrabajadasTxt(Employee* this, char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		sprintf(horasTrabajadas, "%d", this->horasTrabajadas);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de HORASTRABAJADAS como INT del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	int* horasTrabajadas
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
	int retorno=-1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de SUELDO como INT en el elemento pasado como parametro (this)
 * 			SUELDO se pasa como char* en el parametro de la función
 * \param 	Employee* this
 * \param	char* sueldo
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
	int retorno = -1;
	float auxSueldo;
	if(this != NULL && sueldo != NULL)
	{
		if(isNumber(sueldo))
		{
			auxSueldo = atoi(sueldo);
			if(auxSueldo >= 0)
			{
				this->sueldo = auxSueldo;
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de SUELDO como INT en el elemento pasado como parametro (this)
 * 			SUELDO se pasa como int en el parametro de la función
 * \param 	Employee* this
 * \param	int sueldo
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_setSueldo(Employee* this, int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de SUELDO como CHAR del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	char* sueldo
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getSueldoTxt(Employee* this, char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		sprintf(sueldo, "%d", this->sueldo);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Obtiene el valor de SUELDO como INT del elemento pasado como parametro (this)
 * \param 	Employee* this
 * \param	int sueldo
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int employee_getSueldo(Employee* this, int* sueldo)
{
	int retorno=-1;
	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		retorno = 0;
	}
	return retorno;
}
/**********************************************************************************************************/
/*
 * \brief	Recorre la lista pasada como parametro y verifica en cada elemento el campo ID
 * 			y lo compara con el id pasado como parametro.
 * 			Hasta encontrar una coincidencia o llegar al final y no encontrarla.
 * \param	Employee* pArrayListEmployee
 * \param	int length
 * \param	int id
 * \return	int -1 ERROR pArrayListEmployee == NULL || length <= 0 || id <= 0 /
 * 			int -2 ERROR No encontro ID /
 * 			int i OK indice del elemento cargado en la lista con el mismo valor del ID pasado como parametro
 */
int emp_buscarId(LinkedList* pArrayListEmployee, int length, int id)
{
	int retorno = -1;
	int i;
	int auxId;
	Employee* pEmployee;
	if(pArrayListEmployee != NULL && length > 0 && id > 0)
	{
		retorno = -2;
		for(i = 0; i < length; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			employee_getId(pEmployee, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief	Elimina de la lista un elemento con el id pasado como parametro.
 * 			Mediante la funcion emp_buscarId() obtiene el indice y luego lo elimina.
 * \param	Employee* pArrayListEmployee
 * \param	int length
 * \param	int id
 * \return	int -1 ERROR pArrayListEmployee == NULL || length <= 0 || id <= 0 /
 * 			int -1 indiceBorrar <= -1 /
 * 			int i OK indice del elemento cargado en la lista con el mismo valor del ID pasado como parametro
 */
int emp_borrarById(LinkedList* pArrayListEmployee, int length, int id)
{
	int retorno = -1;
	int indiceBorrar;
	Employee* pEmployee;
	char auxNombre[LONG_NAME];
	char auxSueldo[LONG_NUMBER_VALUE];
	char auxHoras[LONG_NUMBER_VALUE];
	if(pArrayListEmployee != NULL && length > 0 && id > 0)
	{
		indiceBorrar = emp_buscarId(pArrayListEmployee, length, id);
		if(indiceBorrar > -1)
		{
			pEmployee = ll_get(pArrayListEmployee, indiceBorrar);
			employee_getNombre(pEmployee, auxNombre);
			employee_getSueldoTxt(pEmployee, auxSueldo);
			employee_getHorasTrabajadasTxt(pEmployee, auxHoras);
			printf("\nAcaba de eliminar de la lista el id: %d\n", id);
			printf("Nombre: %s - Horas Trabajadas: %s - Sueldo: %s\n",auxNombre,auxHoras,auxSueldo);
			if(ll_remove(pArrayListEmployee, indiceBorrar)==0)
			{
				retorno = 0;
				employee_delete(pEmployee);
			}
		}
		else if(indiceBorrar == -1)
		{
			printf("Error en la validación de datos en BuscarByIdArrayPunteros\n");
		}
		else
		{
			printf("No existe el ID a ser removido\n\n");
		}
	}
	return retorno;
}
/*
 * \brief	Compara dos elementos pasados como parametros
 * \param	void* thisA
 * \param	void* thisB
 * \return	int 1 el elementoA es mayor que el elementoB
 * 			int -1 el elementoB es mayor que el elementoA
 * 			int 0 iguales
 * 			int -2 ERROR thisA == NULL || thisB == NULL
 */
int employee_compararNombre(void* thisA, void* thisB)
{
	int retorno = -2;
	Employee* pEmployeeA = (Employee*)thisA;
	Employee* pEmployeeB = (Employee*)thisB;
	int respuestaStrncmp;
	char bufferNombreA[LONG_NAME];
	char bufferNombreB[LONG_NAME];
	if(thisA != NULL && thisB != NULL)
	{
		employee_getNombre(pEmployeeA, bufferNombreA);
		employee_getNombre(pEmployeeB, bufferNombreB);
		respuestaStrncmp = strncmp(bufferNombreA, bufferNombreB, LONG_NAME);
		if(respuestaStrncmp > 0)
		{
			retorno = 1;
		}
		else if(respuestaStrncmp < 0)
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief	Compara dos elementos pasados como parametros
 * \param	void* thisA
 * \param	void* thisB
 * \return	int 1 el elementoA es mayor que el elementoB
 * 			int -1 el elementoB es mayor que el elementoA
 * 			int 0 iguales
 * 			int -2 ERROR thisA == NULL || thisB == NULL
 */
int employee_compararSueldo(void* thisA, void* thisB)
{
	int retorno = -2;
	Employee* pEmployeeA = (Employee*)thisA;
	Employee* pEmployeeB = (Employee*)thisB;
	char bufferSueldoA[LONG_NUMBER_VALUE];
	char bufferSueldoB[LONG_NUMBER_VALUE];
	if(thisA != NULL && thisB != NULL)
	{
		employee_getSueldoTxt(pEmployeeA, bufferSueldoA);
		employee_getSueldoTxt(pEmployeeB, bufferSueldoB);
		if(atoi(bufferSueldoA) > atoi(bufferSueldoB))
		{
			retorno = 1;
		}
		else if(atoi(bufferSueldoA) < atoi(bufferSueldoB))
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief	Compara dos elementos pasados como parametros
 * \param	void* thisA
 * \param	void* thisB
 * \return	int 1 el elementoA es mayor que el elementoB
 * 			int -1 el elementoB es mayor que el elementoA
 * 			int 0 iguales
 * 			int -2 ERROR thisA == NULL || thisB == NULL
 */
int employee_compararId(void* thisA, void* thisB)
{
	int retorno = -2;
	Employee* pEmployeeA = (Employee*)thisA;
	Employee* pEmployeeB = (Employee*)thisB;
	char bufferIdA[LONG_NUMBER_VALUE];
	char bufferIdB[LONG_NUMBER_VALUE];
	if(thisA != NULL && thisB != NULL)
	{
		employee_getIdTxt(pEmployeeA, bufferIdA);
		employee_getIdTxt(pEmployeeB, bufferIdB);
		if(atoi(bufferIdA) > atoi(bufferIdB))
		{
			retorno = 1;
		}
		else if(atoi(bufferIdA) < atoi(bufferIdB))
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief	Compara dos elementos pasados como parametros
 * \param	void* thisA
 * \param	void* thisB
 * \return	int 1 el elementoA es mayor que el elementoB
 * 			int -1 el elementoB es mayor que el elementoA
 * 			int 0 iguales
 * 			int -2 ERROR thisA == NULL || thisB == NULL
 */
int employee_compararHoras(void* thisA, void* thisB)
{
	int retorno = -2;
	Employee* pEmployeeA = (Employee*)thisA;
	Employee* pEmployeeB = (Employee*)thisB;
	char bufferHorasA[LONG_NUMBER_VALUE];
	char bufferHorasB[LONG_NUMBER_VALUE];
	if(thisA != NULL && thisB != NULL)
	{
		employee_getHorasTrabajadasTxt(pEmployeeA, bufferHorasA);
		employee_getHorasTrabajadasTxt(pEmployeeB, bufferHorasB);
		if(atoi(bufferHorasA) > atoi(bufferHorasB))
		{
			retorno = 1;
		}
		else if(atoi(bufferHorasA) < atoi(bufferHorasB))
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
/*
* \brief 	Verifica una cadena como parametro para determinar si es nombre valido
* \param 	char array[], array a analizar
* \param 	int limite indica la cantidad maxima del nombre
 * return 	(1) Es válido / (0) No es un nombre valido
 */
static int isAValidName(char array[], int limite)
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
 * \brief 	Verifica si la cadena ingresada son letras
 * \param 	char array de caracteres a ser analizada
 * \return 	1 EXITO / (0) ERROR
 */
static int isLettersSpaceGuion(char array[])
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
 * \brief 	Verifica si la cadena ingresada es numerica
 * \param 	char array de caracteres a ser analizada
 * \return 	1 EXITO / (0) ERROR
 */
static int isNumber(char array[])
{
	int retorno = 1;
	int i = 0;
	for( i=0; array[i] != '\0'; i++)
	{
		if(array[i] < '0' || array[i] > '9')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}










































