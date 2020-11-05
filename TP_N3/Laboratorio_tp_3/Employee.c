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
#include "Validaciones.h"
#include "LinkedList.h"
#include "Controller.h"
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
 * \pram 	char* apellido
 * \param	float altura
 * \param	int id
 * \return	auxPuntero pudiendo ser = NULL o = la direccion creada por new con los valores agregados
 */
Employee* emp_newParametros(char* nombre, int horasTrabajadas, float sueldo, int id)
{
	Employee* this;
	this = employee_new();
	if(this != NULL && nombre != NULL && horasTrabajadas > 0 && sueldo > 0L && id > 0)
	{
		if(	employee_setNombre(this, nombre)==-1					||
			employee_setHorasTrabajadas(this, horasTrabajadas)==-1	||
			employee_setId(this, id)==-1							||
			employee_setSueldo(this, sueldo)==-1					)
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
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
 *
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}
/*
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
 */
int employee_setSueldoTxt(Employee* this, char* sueldo)
{
	int retorno = -1;
	float auxSueldo;
	if(this != NULL && sueldo != NULL)
	{
		if(isNumberFloat(sueldo))
		{
			auxSueldo = atof(sueldo);
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
 *
 */
int employee_setSueldo(Employee* this, float sueldo)
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
 *
 */
int employee_getSueldoTxt(Employee* this, char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		sprintf(sueldo, "%.2f", this->sueldo);
		retorno = 0;
	}
	return retorno;
}
/*
 *
 */
int employee_getSueldo(Employee* this, float* sueldo)
{
	int retorno=-1;
	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		retorno = 0;
	}
	return retorno;
}
/*
 *
 */
int emp_guardarArrayEnArchivo(Employee* arrayPunteros[], int length, char* pathArchivo)
{
	int retorno = -1;
	int i;
	FILE* fpArchivo;
	char auxNombre[LONG_NAME];
	char auxHoras[LONG_NAME];
	char auxSueldo[LONG_NAME];
	char auxId[LONG_NAME];
	if(arrayPunteros != NULL && pathArchivo != NULL && length > 0)
	{
		fpArchivo = fopen(pathArchivo, "w");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			for(i=0; i < length; i++)
			{
				if(arrayPunteros[i] != NULL)
				{
					if(	employee_getIdTxt(arrayPunteros[i], auxId) == 0)
					{
						if(employee_getNombre(arrayPunteros[i], auxNombre) == 0)
						{
							if(employee_getHorasTrabajadasTxt(arrayPunteros[i], auxHoras)==0)
							{
								if(employee_getSueldoTxt(arrayPunteros[i], auxSueldo) == 0)
								{
									fprintf(fpArchivo, "%s,%s,%s,%s\n",auxId, auxNombre, auxHoras, auxSueldo );
									//printf("%s,%s,%s,%s\n",auxId, auxNombre, auxApellido, auxSueldo );
								}
								else
								{
									printf("NO SUELDO\n");
								}
							}
							else
							{
								printf("NO HORAS\n");
							}
						}
						else
						{
							printf("NO NOMBRE\n");
						}
					}
					else
					{
						printf("NO ID\n");
					}
				}
			}
			fclose(fpArchivo);
		}
		else
		{
			printf("No se pudo crear el archivo\n\n");
		}
	}

	return retorno;
}
/*
 *
 */
int emp_leerArchivoParaVolcarloAlArray(Employee* arrayPunteros[], int length, char* pathArchivo, int* proximoId)
{
	int retorno = -1;
	int retornoFscanf;
	char auxNombre[LONG_NAME];
	char auxHoras[LONG_NAME];
	char auxSueldo[LONG_NAME];
	char auxId[LONG_NAME];
	FILE* fpArchivo;
	if(arrayPunteros != NULL && pathArchivo != NULL && length > 0)
	{
		fpArchivo = fopen(pathArchivo, "r");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			do
			{
				retornoFscanf = fscanf(fpArchivo, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxHoras, auxSueldo);
				if(retornoFscanf == 4)
				{
					//printf("\n%s-%s-%s-%s\n", auxId, auxNombre, auxApellido, auxAltura);
					if(emp_agregarArrayPunterosTxt(arrayPunteros, length, auxId, auxNombre, auxHoras, auxSueldo) != -1)
					{
						//printf("ALTA OK\n");

						if(atoi(auxId) > *proximoId)
						{
							*proximoId = atoi(auxId) + 1;
						}
					}
				}
			}while(!feof(fpArchivo));
			fclose(fpArchivo);
		}
		else
		{
			printf("No se pudo leer el archivo\n\n");
		}
	}
	return retorno;
}
/*
 *
 */
int emp_guardarArrayEnArchivoBinario(Employee* arrayPunteros[], int length, char* pathArchivo)
{
	int retorno = -1;
	int i;
	FILE* fpArchivoBinario;
	if(arrayPunteros != NULL && pathArchivo != NULL && length > 0)
	{
		fpArchivoBinario = fopen(pathArchivo, "wb");
		if(fpArchivoBinario != NULL)
		{
			retorno = 0;
			for(i = 0; i < length;i++)
			{
				fwrite(arrayPunteros[i], sizeof(Employee), 1, fpArchivoBinario);
			}
			fclose(fpArchivoBinario);
		}
		else
		{
			printf("No se pudo crear el archivo\n\n");
		}
	}

	return retorno;
}
/*
 *
 */
int emp_leerArchivoParaVolcarloAlArrayBinario(Employee* arrayPunteros[], int length, char* pathArchivo, int* proximoId)
{
	int retorno = -1;
	int i=0;
	int fin = 1;
	int auxId;
	//char auxNombre[LONG_NAME];
	//char auxApellido[LONG_NAME];
	//float auxAltura;
	FILE* fpArchivoBinario;
	Employee auxEmployee;
	//pasar el parser bynaria
	if(arrayPunteros != NULL && length > 0 && pathArchivo != NULL)
	{
		fpArchivoBinario = fopen(pathArchivo, "rb");
		if(fpArchivoBinario != NULL)
		{
			retorno = 0;
			do
			{
				fin = fread(&auxEmployee, sizeof(Employee), 1, fpArchivoBinario);
				if(fin == 1)
				{
					//printf("%s-%s-%.2f.%d\n",auxEmployee.name, auxEmployee.lastName, auxEmployee.altura, auxEmployee.id);
					if(emp_agregarArrayPunteros(arrayPunteros, length, auxEmployee.nombre, auxEmployee.horasTrabajadas, auxEmployee.sueldo, auxEmployee.id) != -1)
					{
						printf("Entro\n");
						i++;
						auxId = auxEmployee.id;
						if(auxId > *proximoId)
						{
							*proximoId = auxId + 1;
						}
					}
					else
					{
						printf("NO AGREGO AL ARRAY LO QUE LEYO\n");
					}
				}
			}while(!feof(fpArchivoBinario));
			fclose(fpArchivoBinario);
		}
		else
		{
			printf("No se pudo leer el archivo\n\n");
		}
	}
	return retorno;
}

/**********************************************************************************************************/


/*
 * \brief	Recorre el array de punteros poniendo sus posiciones en NULL
 * \param	Employee* arrayPunteros
 * \param	int length
 * \return	-1 ERROR / 0 OK
 *
 */
int emp_initArrayPunteros(Employee* arrayPunteros[], int length)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && length > 0)
	{
		for(i = 0; i < length; i++)
		{
			arrayPunteros[i] = NULL;
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief	Recorre el array de punteros buscando un indice con NULL
 * \param	Employee* arrayPunteros
 * \param	int length
 * \return	-1 ERROR en validacion / -2 no encontro posición libre / i OK, posición con NULL cargado en el array
 *
 */
int emp_buscarLibreArrayPunteros(Employee* arrayPunteros[], int length)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && length > 0)
	{
		retorno = -2;
		for(i = 0; i < length; i++)
		{
			if(arrayPunteros[i] == NULL)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief	Recorre el array de punteros imprimiendo los indices con != NULL
 * \param	Employee* arrayPunteros
 * \param	int length
 * \return	-1 ERROR / 0 OK
 *
 */
int emp_imprimirArrayPunteros(Employee* arrayPunteros[], int length)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && length > 0)
	{
		printf("\n-----------LISTA EMPLEADOS--------------\n");
		for(i = 0; i < length; i++)
		{
			if(arrayPunteros[i] != NULL)
			{
				printf("ID: %d - Nombre: %s - Horas trabajadas: %d - Sueldo: %.2f\n\n", arrayPunteros[i]->id, arrayPunteros[i]->nombre, arrayPunteros[i]->horasTrabajadas, arrayPunteros[i]->sueldo);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief	Libera la posicion en el arrayPunteros del indice pasado y luego coloca un NULL en esa posicion
 * \param	Employee* arrayPunteros
 * \param	int indice
 * \return	-1 ERROR / 0 OK
 *
 */
int emp_deleteByIndiceArrayPunteros(Employee* arrayPunteros[], int length ,int indice)
{
	int retorno = -1;
	if(arrayPunteros != NULL && indice < length && indice > -1 && arrayPunteros[indice] != NULL)
	{
		employee_delete(arrayPunteros[indice]);
		arrayPunteros[indice] = NULL;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief	Recorre el array de punteros buscando un indice !=NULL y con el mismo valor en el campo Id que el pasado como parametro
 * \param	Employee* arrayPunteros
 * \param	int length
 * \param	int id
 * \return	-1 ERROR en validacion / -2 no encontro posición libre / i OK, posición con NULL cargado en el array
 *
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
 * \brief	agrega los valores pasados como parametros al array de punteros mediante la utilizacion de la funcion
 * 			buscarLibre y luego newParametros
 * \param	Employee* arrayPunteros
 * \param	int length
 * \param	char* nombre
 * \param	float altura
 * \param	int id
 * \return	-1 ERROR en validacion / OK retorno el valor del indice donde se agrego el Employee
 *
 */
int emp_agregarArrayPunteros(Employee* arrayPunteros[], int length, char* nombre, int horasTrabajadas, float sueldo, int id)
{
	int retorno = -1;
	int indiceLibre;
	Employee* punteroAuxEmployee;
	if(arrayPunteros != NULL && length > 0 && nombre != NULL && horasTrabajadas >= 0 && id > 0 && sueldo > 0)
	{
		indiceLibre = emp_buscarLibreArrayPunteros(arrayPunteros, length);
		if(indiceLibre > -1)
		{
			punteroAuxEmployee = emp_newParametros(nombre, horasTrabajadas, sueldo, id);
			if(punteroAuxEmployee != NULL)
			{
				arrayPunteros[indiceLibre] = punteroAuxEmployee;
				retorno = indiceLibre;
			}
		}
	}
	return retorno;
}
/*
 * \brief	agrega los valores pasados como parametros al array de punteros mediante la utilizacion de la funcion
 * 			buscarLibre y luego newParametros
 * \param	Employee* arrayPunteros
 * \param	int length
 * \param   char* id
 * \param	char* nombre
 * \param	char* apellido
 * \param	char* altura
 * \return	-1 ERROR en validacion / OK retorno el valor del indice donde se agrego el Employee
 *
 */
int emp_agregarArrayPunterosTxt(Employee* arrayPunteros[], int length, char* id, char* nombre, char* horasTrabajadas, char* sueldo)
{
	int retorno = -1;
	int indiceLibre;
	Employee* punteroAuxEmployee;
	if(arrayPunteros != NULL && length > 0 && nombre != NULL && horasTrabajadas != NULL && id != NULL && sueldo != NULL)
	{
		indiceLibre = emp_buscarLibreArrayPunteros(arrayPunteros, length);
		if(indiceLibre > -1)
		{
			punteroAuxEmployee = employee_newParametros(nombre, horasTrabajadas, sueldo, id);
			if(punteroAuxEmployee != NULL)
			{
				arrayPunteros[indiceLibre] = punteroAuxEmployee;
				retorno = indiceLibre;
			}
		}
	}
	return retorno;
}
/*
 * \brief	Recorre el array de punteros buscando un indice !=NULL y con el mismo valor en el campo Id que el pasado como parametro
 * \param	Employee* arrayPunteros
 * \param	int length
 * \param	int id
 * \return	-1 ERROR en validacion / -2 no encontro posición libre / i OK, posición con NULL cargado en el array
 */
int emp_borrarById(LinkedList* pArrayListEmployee, int length, int id)
{
	int retorno = -1;
	int indiceBorrar;
	if(pArrayListEmployee != NULL && length > 0 && id > 0)
	{
		indiceBorrar = emp_buscarId(pArrayListEmployee, length, id);
		if(indiceBorrar > -1)
		{
			if(ll_remove(pArrayListEmployee, indiceBorrar)==0)
			{
				retorno = 0;
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
 *
 */
int emp_ordenarArrayPunteros(Employee* arrayPunteros[], int length)
{
	int retorno = -1;
	int i;
	int flagSwap;
	Employee* bufferPuntero;
	int nuevoLimite = length - 1;
	if(arrayPunteros!= NULL && length > 0)
	{
		retorno=0;
		do
		{
			flagSwap=0;
			for(i=0; i < nuevoLimite;i++)
			{
				if(	arrayPunteros[i] != NULL && arrayPunteros[i+1] != NULL &&
					strncmp(arrayPunteros[i]->nombre, arrayPunteros[i+1]->nombre, LONG_NAME) > 1)
				{
					bufferPuntero = arrayPunteros[i];
					arrayPunteros[i] = arrayPunteros[i+1];
					arrayPunteros[i+1] = bufferPuntero;
					flagSwap = 1;
				}
			}
			nuevoLimite--;
		}while(flagSwap);
	}
	return retorno;
}
/*
 *
 */
int emp_promediarSueldo(Employee* arrayPunteros[], int length, float* promedio)
{
	int retorno = -1;
	int i;
	int cantidadEmployee = 0;
	float acumulador = 0;
	if(arrayPunteros != NULL && length > 0 && promedio != NULL)
	{
		for(i=0; i < length;i++)
		{
			if(arrayPunteros[i] != NULL)
			{
				acumulador = arrayPunteros[i]->sueldo + acumulador;
				cantidadEmployee++;
			}
		}
		*promedio = acumulador / cantidadEmployee;
		retorno = 0;
	}

	return retorno;
}
/*
 *
 */
int emp_calcularSueldoMax(Employee* arrayPunteros[], int length, int* indice)
{
	int retorno = -1;
	int i;
	float maxSueldo;
	int indiceMaxSueldo;
	int flag = 0;
	if(arrayPunteros != NULL && length > 0 && indice != NULL)
	{
		for(i=0; i < length;i++)
		{
			if(arrayPunteros[i] != NULL)
			{
				if(flag == 0)
				{
					indiceMaxSueldo = i;
					maxSueldo = arrayPunteros[i]->sueldo;
					flag = 1;
				}
				else
				{
					if(arrayPunteros[i]->sueldo > maxSueldo)
					{
						indiceMaxSueldo = i;
						maxSueldo = arrayPunteros[i]->sueldo;
					}
				}

			}
		}
		*indice = indiceMaxSueldo;
		retorno = 0;
	}
	return retorno;
}

/*
 *
 */
int employee_compararNombre(void* thisA, void* thisB)
{
	int retorno = 0;
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












































