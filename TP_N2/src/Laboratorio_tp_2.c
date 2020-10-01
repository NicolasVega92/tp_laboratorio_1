/*
 ============================================================================
 Name        : Laboratorio_tp_2.c
 Author      : Nicol�s Mart�n Vega Gangemi

El sistema deber� tener el siguiente men� de opciones:
	1. ALTAS: Se debe permitir ingresar un empleado calculando autom�ticamente el n�mero
	de Id. El resto de los campos se le pedir� al usuario.

	2. MODIFICAR: Se ingresar� el N�mero de Id, permitiendo modificar: o Nombre o Apellido
	o Salario o Sector

	3. BAJA: Se ingresar� el N�mero de Id y se eliminar� el empleado del sistema.

	4. INFORMAR:
		1. Listado de los QTY_EMPLOYEES ordenados alfab�ticamente por Apellido y Sector.
		2. Total y promedio de los salarios, y cu�ntos QTY_EMPLOYEES superan el salario promedio.

	NOTA: Se deber� realizar el men� de opciones y las validaciones a trav�s de funciones.
	Tener en cuenta que no se podr� ingresar a los casos 2, 3 y 4; sin antes haber realizado la
	carga de alg�n empleado.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

#define QTY_EMPLOYEES 1000
#define LONG_NAME 1001
#define MAX_SALARY 1000000
#define MIN_SALARY 0.01
#define MAX_SECTOR 10
#define MIN_SECTOR 1
#define TRUE 1
#define FALSE 0

int main(void) {
	setbuf(stdout,NULL);
	int opcion;
	int contadorCargaEmpleados = 0;
	int indiceById;
	int id;
	int order;
	float averageSalary;
	int employeeGainMore;

	Employee arrayEmployees[QTY_EMPLOYEES];
	employee_init(arrayEmployees, QTY_EMPLOYEES);
	printf("Bienvenido al sistema de carga de Empleados 2020\n*************************************************\n");
	do
	{
		employee_menuOptions();
		if(utn_getNumberInt("\n", "Error, opci�n inv�lida\n", &opcion, 3, 1, 5)==0)
		{
			switch(opcion)
			{
			case 1: //ALTA
				if(employee_createEmployee(arrayEmployees, QTY_EMPLOYEES)==0)
				{
					contadorCargaEmpleados++;
				}
				break;
			case 2: //MODIFICAR
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del empleado que desea modificar:\n", "Error, ingrese un ID entre 1 - 100\n", &id, 3, 1, 100)==0)
					{
						indiceById = employee_findById(arrayEmployees, QTY_EMPLOYEES, id);
						if(employee_modifyEmployeeByIndex(arrayEmployees, QTY_EMPLOYEES, indiceById)==0)
						{
							printf("Modificaci�n exitosa!\n\n");
						}
						else
						{
							printf(	"El ID: %d no puede \"modificarse\" debido a que no existe\n"
									"Puede consultar los ID de los empleados en la opci�n 4\n\n", id);
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder modificar.\nIntente opci�n 1.\n\n");
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
							printf("Id removido exitosamente!\n\n");
							contadorCargaEmpleados--;
						}
						else
						{
							printf(	"El ID: %d no puede \"darse de baja\" debido a que no existe\n"
									"Puede consultar los ID de los empleados en la opci�n 4\n\n", id);
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder dar de baja.\nIntente opci�n 1.\n\n");
				}
				break;
			case 4: //PRINT - ORDENAR
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese:\n"
										"1- Si desea ver la lista ordenada de forma ascendente.\n"
										"2- Si desea ver la lista ordenada de forma desendente\n", "ERROR, ingrese 1 o 2 segun corresponda\n", &order, 3, 1, 2)==0)
					{
						if(	(employee_sortByLastName(arrayEmployees, QTY_EMPLOYEES, order)==0) &&
							(employee_print(arrayEmployees, QTY_EMPLOYEES)==0) &&
							(employee_averageSalary(arrayEmployees, QTY_EMPLOYEES, contadorCargaEmpleados, &averageSalary)==0) &&
							(employee_gainMoreThanAverage(arrayEmployees, QTY_EMPLOYEES, averageSalary, &employeeGainMore)==0))
						{
							printf("- El \"promedio de los salarios\" es de: $ %.2f\n- La \"cantidad de Empleados\" que superan el salario medio es: %d\n\n", averageSalary, employeeGainMore);
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder imprimir la lista.\nIntente opci�n 1.\n\n");
				}
				break;
			}
		}
	}while(opcion!=5);
	printf("\nGracias por haber utilizado mi proyecto.\nEspero que tenga un buen d�a!\n");
	return EXIT_SUCCESS;
}
