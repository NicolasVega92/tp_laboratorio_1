#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile = fopen(path, "r");
	int retorno = parser_EmployeeFromText(pFile, pArrayListEmployee);
	fclose(pFile);
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pFile = fopen(path, "rb");
	int retorno = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
	fclose(pFile);
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;
	char auxName[LONG_NAME];
	char auxSueldo[LONG_NAME];
	char auxHoras[LONG_NAME];
	char auxid[LONG_NAME];
	int auxIdPorRetorno;
	if(pArrayListEmployee!=NULL)
	{
		if(	(utn_getName("Ingresa el Nombre del empleado:\n", "Error, por favor reintentelo con un nombre válido\n", auxName , 3, LONG_NAME)==0) &&
			(utn_getSueldoTxt("Ingresa el sueldo:\n", "Error, por favor reintentelo con un sueldo válido (solo números)\n", auxSueldo , 3, LONG_NAME)==0) &&
			(utn_getHorasTxt("Ingresa la cantidad de horas trabajadas:\n", "Error, por favor reintentelo con un valor válido (solo números)\n",  auxHoras, 3, LONG_NAME)==0))
		{
			auxIdPorRetorno = controller_encontrarProximoId(pArrayListEmployee);
			sprintf(auxid, "%d", auxIdPorRetorno);
			pEmployee = employee_newParametros(auxid, auxName, auxHoras, auxSueldo);
			if(pEmployee != NULL)
			{
				ll_add(pArrayListEmployee, pEmployee);
				printf("%s - %s - %s - %s\n", auxName, auxSueldo, auxHoras, auxid);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idAModificar;
	Employee* pEmployee;
	char auxName[LONG_NAME];
	char auxSueldo[LONG_NAME];
	char auxHoras[LONG_NAME];
	int indexAModificar;
	int length;
	if(pArrayListEmployee != NULL)
	{
		length = ll_len(pArrayListEmployee);
		if(controller_ListEmployee(pArrayListEmployee)==0)
		{
			if(utn_getNumberInt("**************************************\n"
								"Aca puede ver la lista de empleados.\n"
								"Ingrese el Id del empleado a modificar:\n",
								"Error, Ingrese un Id válido (solo números)\n", &idAModificar, 2, 1, 10000)==0)
			{
				indexAModificar = emp_buscarId(pArrayListEmployee, length, idAModificar);
				if(indexAModificar >= 0)
				{
					pEmployee = (Employee*)ll_get(pArrayListEmployee, indexAModificar);
					if(pEmployee != NULL)
					{
						if(	(utn_getName("Ingresa el Nuevo Nombre del empleado:\n", "Error, por favor reintentelo con un nombre válido\n", auxName , 3, LONG_NAME)==0) &&
							(utn_getSueldoTxt("Ingresa el nuevo sueldo:\n", "Error, por favor reintentelo con un sueldo válido (solo números)\n", auxSueldo , 3, LONG_NAME)==0) &&
							(utn_getHorasTxt("Ingresa la nueva cantidad de horas trabajadas:\n", "Error, por favor reintentelo con un valor válido (solo números)\n",  auxHoras, 3, LONG_NAME)==0))
						{
							employee_setNombre(pEmployee, auxName);
							employee_setSueldoTxt(pEmployee, auxSueldo);
							employee_setHorasTrabajadasTxt(pEmployee, auxHoras);
							retorno = 0;
						}
					}
					else
					{
						printf("Ese id no existe en la lista\n\n");
					}
				}
				else if(indexAModificar == -2)
				{
					printf("No se encontro el ID\n");
				}
				else
				{
					printf("Error validación datos en buscarId\n");
				}
			}

		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idBorrar;
	int length;
	if(pArrayListEmployee != NULL)
	{
		length = ll_len(pArrayListEmployee);
		if(	utn_getNumberInt("Que id desea borrar\n", "Error\n", &idBorrar, 3, 1, 1000)==0	&&
			emp_borrarById(pArrayListEmployee, length, idBorrar)== 0	)
		{
			printf("Baja ok\n");
		}
	}

	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	int length;
	Employee* pBuffer;
	char auxNombre[LONG_NAME];
	int auxHoras;
	float auxSueldo;
	int auxId;
	if(pArrayListEmployee != NULL)
	{
		length = ll_len(pArrayListEmployee);
		printf(	"--------------------------------------------\n"
				"|               LISTA EMPLEADOS            |\n"
				"--------------------------------------------\n"
				"|  ID|           NOMBRE|   HORAS|    SUELDO|\n"
				"--------------------------------------------\n");
		for(i = 0; i < length; i++)
		{
			pBuffer = ll_get(pArrayListEmployee, i);
			if(	employee_getId(pBuffer, &auxId) == 0 					&&
				employee_getNombre(pBuffer, auxNombre) == 0 			&&
				employee_getHorasTrabajadas(pBuffer, &auxHoras)==0 		&&
				employee_getSueldo(pBuffer, &auxSueldo) == 0)
			{
				printf("%5d|%17s|%8d|%10.0f|\n",auxId, auxNombre, auxHoras, auxSueldo );
			}
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int option;
	if(pArrayListEmployee != NULL)
	{
		if(utn_getNumberInt("Como desea ordenar la lista:\n"
							"1-Por NOMBRE (Ascendente )\n"
							"2-Por NOMBRE (Descendente)\n"
							"3-Por SUELDO (Ascendente )\n"
							"4-Por SUELDO (Descendente)\n"
							"5-Por ID     (Ascendente )\n"
							"6-Por HORAS  (Ascendente )\n", "Error, ingrese una opción válida (1 - 5)\n", &option, 3, 1, 6)==0)
		{
			switch(option)
			{
			case 1:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR NOMBRE (A - Z)\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararNombre, 1);
				break;
			case 2:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR NOMBRE (Z - A)\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararNombre, 0);
				break;
			case 3:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR SUELDO (MAYOR A MENOR)\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararSueldo, 0);
				break;
			case 4:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR SUELDO (MENOR A MAYOR)\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararSueldo, 1);
				break;
			case 5:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR ID DE MANERA ASCENDENTE\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararId, 1);
				break;
			case 6:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR MAYOR CANTIDAD DE HORAS TRABAJADAS\n");
				retorno = ll_sort(pArrayListEmployee, employee_compararHoras, 0);
				break;
			}
		}
		if(retorno == 0)
		{
			printf("\n	GRACIAS POR ESPERAR\n"
					"	AHORA PUEDE ENTRAR A LA OPCION 6 PARA VER LA LISTA ORDENADA\n");
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	int length;
	FILE* fpArchivo;
	Employee* pBuffer;
	char auxNombre[LONG_NAME];
	char auxHoras[LONG_NAME];
	char auxSueldo[LONG_NAME];
	char auxId[LONG_NAME];
	if(pArrayListEmployee != NULL && path != NULL)
	{
		length = ll_len(pArrayListEmployee);
		fpArchivo = fopen(path, "w");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			fprintf(fpArchivo,"id,nombre,horasTrabajadas,sueldo\n");
			for(i=0; i < length; i++)
			{
				pBuffer = ll_get(pArrayListEmployee, i);
				if(	employee_getIdTxt(pBuffer, auxId) == 0 					&&
					employee_getNombre(pBuffer, auxNombre) == 0 			&&
					employee_getHorasTrabajadasTxt(pBuffer, auxHoras)==0 	&&
					employee_getSueldoTxt(pBuffer, auxSueldo) == 0)
				{
					fprintf(fpArchivo, "%s,%s,%s,%s\n",auxId, auxNombre, auxHoras, auxSueldo );
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

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	FILE* pFile;
	Employee* pEmployee;
	int length;
	if(pArrayListEmployee != NULL && path != NULL)
	{
		length = ll_len(pArrayListEmployee);
		pFile = fopen(path, "wb");
		if(pFile != NULL)
		{
			retorno = 0;
			for(i = 0; i < length;i++)
			{
				pEmployee = (Employee*) ll_get(pArrayListEmployee, i);
				fwrite(pEmployee, sizeof(Employee), 1, pFile);
			}
			fclose(pFile);
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
int controller_deleteListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int option;
	if(pArrayListEmployee != NULL)
	{
		if(utn_getNumberInt("Ya hay una lista cargada.\n"
							"Desea eliminar la lista cargada?\n"
							"1-SI\n"
							"2-NO\n", "Error, ingrese 1 - 2", &option, 2, 1, 2)==0)
		{
			if(option == 1)
			{
				if(ll_clear(pArrayListEmployee) == 0)
				{
	    			if(ll_deleteLinkedList(pArrayListEmployee)==0)
	    			{
	    				printf(	"Lista eliminada con exito\n"
	    						"Volviendo al MENÚ\n\n"
	    						"Ahora puede cargar otra lista en la opción 1 o 2\n\n");
	    				retorno = 0;
	    			}
					else
					{
						printf("ERROR EN LL_DELETELINKEDLIST\n");
					}
				}
				else
				{
					printf("ERROR EN LL_CLEAR\n");
				}
			}
		}
	}
	return retorno;
}
/*
 * \brief Recorre la lista buscando el id maximo
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_encontrarProximoId(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int auxId;
    int max;
    Employee * empleadoAux;
    int len = ll_len(pArrayListEmployee);
    if (pArrayListEmployee!=NULL)
    {
        for (int i = 0;i<len;i++)
        {
            empleadoAux=ll_get(pArrayListEmployee, i);
            employee_getId(empleadoAux, &auxId);
            if (i==1||auxId>max)
            {
                max = auxId;
                retorno = max+1;
            }
        }
    }
    return retorno;
}


