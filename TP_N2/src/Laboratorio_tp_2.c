/*
 ============================================================================
 Name        : Laboratorio_tp_2.c
 Author      : Nicolás Martín Vega Gangemi

El sistema deberá tener el siguiente menú de opciones:
	1. ALTAS: Se debe permitir ingresar un empleado calculando automáticamente el número
	de Id. El resto de los campos se le pedirá al usuario.

	2. MODIFICAR: Se ingresará el Número de Id, permitiendo modificar: o Nombre o Apellido
	o Salario o Sector

	3. BAJA: Se ingresará el Número de Id y se eliminará el empleado del sistema.

	4. INFORMAR:
		1. Listado de los QTY_EMPLOYEES ordenados alfabéticamente por Apellido y Sector.
		2. Total y promedio de los salarios, y cuántos QTY_EMPLOYEES superan el salario promedio.

	NOTA: Se deberá realizar el menú de opciones y las validaciones a través de funciones.
	Tener en cuenta que no se podrá ingresar a los casos 2, 3 y 4; sin antes haber realizado la
	carga de algún empleado.
 ============================================================================
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

int main(void) {
	setbuf(stdout,NULL);

	int opcion;
	int indiceById;
	int id;
	int contadorCargaEmpleados = 0;
	//int salariosTotal;
	float averageSalary;
	int employeeGainMore=0;
	int order;

	Employee arrayEmployees[QTY_EMPLOYEES];

	//FUNCION INIT isEmpty TRUE
	employee_init(arrayEmployees, QTY_EMPLOYEES);
	do
	{
		if(utn_getNumberInt("Ingrese una opción\n1- Dar de alta un empleado\n2- Modificar algún empleado por ID\n3- Dar de baja un empleado\n4- Informar la lista de empleados y promedio sueldos\n5- Salir\n", "Error, opción inválida\n", &opcion, 3, 1, 5)==0)
		{
			switch(opcion)
			{
			case 1: //ALTA
				if(employee_createEmployee(arrayEmployees, QTY_EMPLOYEES)==0)
				{
					printf("TODO OK\n");
					contadorCargaEmpleados++;
				}
				else
				{
					printf("ERRRRRRRRRRRRRRRRROORR\n");
				}
				break;
			case 2: //MODIFICAR
				// CAMBIAR A SOLO UNA SOLO OPCION
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del empleado que desea modificar:\n", "Error, ingrese un ID entre 1 - 100\n", &id, 3, 1, 100)==0)
					{
						indiceById = employee_findById(arrayEmployees, QTY_EMPLOYEES, id);
						if(employee_modifyEmployeeByIndex(arrayEmployees, QTY_EMPLOYEES, indiceById)==0)
						{
							printf("modificado exitosamente!\n");
						}
						else
						{
							printf("No existe ese ID para ser modificado\n");
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder modificar.\n");
				}
				break;
			case 3: // BAJA
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del empleado que desea remover:\n", "Error, ingrese un ID entre 1 - 100\n", &id, 3, 1, 100)==0)
					{
						indiceById = employee_findById(arrayEmployees, QTY_EMPLOYEES, id);
						if(employee_remove(arrayEmployees, QTY_EMPLOYEES, indiceById)==0)
						{
							printf("Id removido exitosamente!\n");
							contadorCargaEmpleados--;
						}
						else
						{
							printf("No existe ID cargado para remover\n");
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder modificar.\n");
				}
				break;
			case 4: //ORDENAR POR A - Z
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese:\n1- Si desea ver la lista ordenada de forma ascendente.\n2- Si desea ver la lista de forma desendente\n", "ERROR, ingrese 1 o 2 segun corresponda\n", &order, 3, 1, 2)==0)
					{
						if(employee_sortByLastNameAndSector(arrayEmployees, QTY_EMPLOYEES, order)==0)
						{
							if(employee_print(arrayEmployees, QTY_EMPLOYEES)==0)
							{
								if(employee_calculateAverageSalary(arrayEmployees, QTY_EMPLOYEES, contadorCargaEmpleados, &averageSalary)==0)
								{
									if(employee_calculateEmployeeGainMoreThanAverage(arrayEmployees, QTY_EMPLOYEES, averageSalary, &employeeGainMore)==0)
									{
										printf("PROMEDIO DE LOS SALARIOS: %.2f\nLa cantidad de Empleados que superan el salario medio es: %d\n", averageSalary, employeeGainMore);
									}
								}
							}
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder modificar.\n");
				}
				break;
			}
			printf("//////////\n\n");
		}
	}while(opcion!=5);

	return EXIT_SUCCESS;
}
