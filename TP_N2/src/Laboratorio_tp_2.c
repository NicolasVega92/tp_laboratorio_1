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
		1. Listado de los empleados ordenados alfab�ticamente por Apellido y Sector.
		2. Total y promedio de los salarios, y cu�ntos empleados superan el salario promedio.

	NOTA: Se deber� realizar el men� de opciones y las validaciones a trav�s de funciones.
	Tener en cuenta que no se podr� ingresar a los casos 2, 3 y 4; sin antes haber realizado la
	carga de alg�n empleado.

 ============================================================================
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

int main(void) {
	setbuf(stdout,NULL);

	int opcion;
	int indice = 0; // ESTO ESTA MAL CAMBIARLO DESPUES
	Employee arrayEmployees[QTY_EMPLOYEES];

	//FUNCION INIT isEmpty TRUE
	Employees_init(arrayEmployees, QTY_EMPLOYEES);
	Employees_id(arrayEmployees, QTY_EMPLOYEES);

	do
	{
		if(utn_getNumberInt("Ingrese una opci�n\n1- Dar de alta un empleado\n2- Modificar alg�n empleado por ID\n3- Dar de baja un empleado\n4- Informar la lista de empleados\n5- Salir\n ", "Error, opci�n inv�lida\n", &opcion, 3, 1, 5)==0)
		{

			switch(opcion)
			{
			case 1: //ALTA
				if(Employee_add(arrayEmployees, QTY_EMPLOYEES, indice)==0)
				{
					printf("************");
				}
				indice++;
				break;
			case 2: //MODIFICAR
				break;
			case 3: // BAJA
				break;
			case 4: //ORDENAR POR A - Z
				Employee_print(arrayEmployees, QTY_EMPLOYEES);
				break;
			}
			printf("//////////");
		}
	}while(opcion!=5);

	return EXIT_SUCCESS;
}
