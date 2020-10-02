/*
 * ArrayEmployees.h
 *
 *  Created on: 24 sep. 2020
 *      Author: Nico
 */
#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_
	#define QTY_EMPLOYEES 1000
	#define LONG_NAME 51
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
	int employee_init(Employee* pArray, int length);
	int employee_add(Employee* pArray, int length, int id, char name[], char lastName[], float salary, int sector);
	int employee_findById(Employee* pArray, int length, int idValue);
	int employee_modifyEmployeeByIndex(Employee* pArray, int length, int indice);
	int employee_remove(Employee* pArray, int length, int indice);
	int employee_sortByLastName(Employee* pArray, int length, int order);
	int employee_print(Employee* pArray, int length);
	int employee_findFirstValidPosition(Employee* pArray, int length);
	int employee_alta(int length, int* pId, char aName[], char aLastName[], float* pSalary, int* pSector);
	int employee_create(Employee* pArray, int length);
	int employee_sumaSalary(Employee* pArray, int length, float* pResultado);
	int employee_averageSalary(Employee* pArray, int length, int contadorEmpleadosCargados, float* pAverageSalary, float* pSumaTotal);
	int employee_gainMoreThanAverage(Employee* pArray, int length, float average, int* pEmployeeGainMore);
#endif /* ARRAYEMPLOYEES_H_ */
