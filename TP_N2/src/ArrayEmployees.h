/*
 * ArrayEmployees.h
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

	#define QTY_EMPLOYEES 1000
	#define LONG_NAME 101
	#define MAX_SALARY 100000
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
	int employee_searchFirstValidPosition(Employee* pArrayAlumno, int length);
	int employee_altaEmployee(Employee* pListEmployees, int length, int index);
	int employee_print(Employee* pListEmployee, int length);
	int employee_add(Employee* listEmployee, int length, int id, char name[], char lastName[], float salary, int sector);

	int employee_PRUEBAaltaEmployee(int* pId, char aName[], char aLastName[], float* pSalary, int* pSector, int length);
	int employee_findById(Employee* pListEmployee, int length, int idValue);
	int employee_modifyEmployeeByIndex(Employee* pListEmployee, int length, int indice);
	int employee_remove(Employee* pListEmployee, int length, int indice);
	int employee_createEmployee(Employee* pListEmployee, int length);

	int employee_addEmployee(Employee* pListEmployee, int length, int id, char name[], char lastName[], float salary, int sector);





#endif /* ARRAYEMPLOYEES_H_ */
