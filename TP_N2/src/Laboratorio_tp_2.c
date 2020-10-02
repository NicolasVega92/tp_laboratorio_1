/*
 ============================================================================
 Name        : Laboratorio_tp_2.c
 Author      : Nicolás Martín Vega Gangemi
 Comisión    : 1°H
 Docentes    : Mauricio Davila y Ernesto Gigliotti
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "ArrayEmployees.h"

int main(void) {
	setbuf(stdout,NULL);
	int opcion;
	int contadorCargaEmpleados = 0;
	int id;
	int order;
	float sumaTotal;
	float averageSalary;
	int employeeGainMore;

	Employee arrayEmployees[QTY_EMPLOYEES];
	employee_init(arrayEmployees, QTY_EMPLOYEES);
	printf(	"Bienvenido al sistema de carga de Empleados 2020\n"
			"*************************************************\n");
	do
	{
		if(utn_getNumberInt("Ingrese una de las siguientes opciones:\n"
							"1- Dar de alta un empleado\n"
							"2- Modificar algún empleado por ID\n"
							"3- Dar de baja un empleado\n"
							"4- Informar la lista de empleados y promedio sueldos\n"
							"5- Salir\n", "Error, opción inválida\n", &opcion, 3, 1, 5)==0)
		{
			switch(opcion)
			{
			case 1: //ALTA
				if(employee_create(arrayEmployees, QTY_EMPLOYEES)==0)
				{
					contadorCargaEmpleados++;
				}
				break;
			case 2: //MODIFICAR
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del empleado que desea modificar:\n", "Error, ingrese un ID entre 1 - 100\n", &id, 3, 1, 100)==0)
					{
						if(employee_modifyEmployeeByIndex(arrayEmployees, QTY_EMPLOYEES, id)==0)
						{
							printf("Modificación exitosa!\n\n");
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder modificar.\nIntente opción 1.\n\n");
				}
				break;
			case 3: // BAJA
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese el ID del empleado que desea remover:\n", "Error, ingrese un ID entre 1 - 100\n", &id, 3, 1, 100)==0)
					{
						if(employee_remove(arrayEmployees, QTY_EMPLOYEES, id)==0)
						{
							printf("Id removido exitosamente!\n\n");
							contadorCargaEmpleados--;
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder dar de baja.\nIntente opción 1.\n\n");
				}
				break;
			case 4: //PRINT - ORDENAR
				if(contadorCargaEmpleados > 0)
				{
					if(utn_getNumberInt("Ingrese:\n"
										"1- Si desea ver la lista ordenada de forma ASCENDENTE.\n"
										"2- Si desea ver la lista ordenada de forma DESCENDENTE\n", "ERROR, ingrese 1 o 2 segun corresponda\n", &order, 3, 1, 2)==0)
					{
						if(	(employee_sortByLastName(arrayEmployees, QTY_EMPLOYEES, order)==0) &&
							(employee_print(arrayEmployees, QTY_EMPLOYEES)==0) &&
							(employee_averageSalary(arrayEmployees, QTY_EMPLOYEES, contadorCargaEmpleados, &averageSalary, &sumaTotal)==0) &&
							(employee_gainMoreThanAverage(arrayEmployees, QTY_EMPLOYEES, averageSalary, &employeeGainMore)==0))
						{
							printf(	"\n- El \"total de los salarios\" es: $ %.2f\n"
									"- El \"promedio de los salarios\" es de: $ %.2f\n"
									"- La \"cantidad de Empleados\" que superan el salario medio es: %d\n\n", sumaTotal, averageSalary, employeeGainMore);
						}
					}
				}
				else
				{
					printf("Se debe dar de alta al menos un empleado para poder imprimir la lista.\nIntente opción 1.\n\n");
				}
				break;
			}
		}
	}while(opcion!=5);
	printf("\nGracias por haber utilizado mi proyecto.\n"
			"Espero que tenga un buen día!\n");
	return EXIT_SUCCESS;
}
