/*
 * ArrayEmployees.h
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */
#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_
	#define QTY_EMPLOYEES 1000
	#define LONG_NAME 1001
	#define MAX_SECTOR 10
	#define MIN_SECTOR 1
	#define MAX_SALARY 1000000
	#define MIN_SALARY 0.01
	#define TRUE 1
	#define FALSE 0
	typedef struct
	{
		int id;
		char name[LONG_NAME];
		char lastName[LONG_NAME];
		float salary;
		int sector;
		int isEmpty;
	}Employee;
	int employee_init(Employee* pListEmployees, int length);
	int employee_add(Employee* listEmployee, int length, int id, char name[], char lastName[], float salary, int sector);
	int employee_findFirstValidPosition(Employee* pArrayAlumno, int length);
	int employee_remove(Employee* pListEmployee, int length, int indice);
	int employee_sortByLastName(Employee* pArray, int length, int order);
	int employee_print(Employee* pListEmployee, int length);
	int employee_modifyEmployeeByIndex(Employee* pListEmployee, int length, int indice);
	int employee_findById(Employee* pListEmployee, int length, int idValue);
	int employee_altaEmployee(int length, int* pId, char aName[], char aLastName[], float* pSalary, int* pSector);
	int employee_createEmployee(Employee* pListEmployee, int length);
	int employee_sumaSalary(Employee* pListEmployee, int length, float* pResultado);
	int employee_averageSalary(Employee* pListEmployee, int length, int contadorEmpleadosCargados, float* pAverageSalary);
	int employee_gainMoreThanAverage(Employee* pListEmployee, int length, float average, int* pEmployeeGainMore);
	void employee_menuOptions();
#endif /* ARRAYEMPLOYEES_H_ */
