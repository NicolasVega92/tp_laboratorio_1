/*
 * ArrayEmployees.h
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

	#define QTY_EMPLOYEES 5
	#define LONG_NAME 51
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

	int Employees_init(Employee* pListEmployees, int length);
	int Employees_id(Employee* pListEmployees, int length);
	int Employee_add(Employee* pListEmployees, int length, int index);
	int Employee_print(Employee* pListEmployee, int length);



#endif /* ARRAYEMPLOYEES_H_ */
