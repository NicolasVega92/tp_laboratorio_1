#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include "utn.h"
#include "LinkedList.h"
#define QTY_EMPLOYEE 100
#define ERROR_NOT_LOADED_LIST "\n	Primero debe cargar un archivo.\n	Intente opcion 1 o 2 en el Menú\n"
typedef struct
{
    int id;
    char nombre[LONG_NAME];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);
int employee_setIdTxt(Employee* this, char* id);
int employee_setIdTxtStaticValue(Employee* this, char* id);
int employee_getIdTxt(Employee* this, char* id);

int employee_setNombre(Employee* this, char* nombre);
int employee_getNombre(Employee* this, char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int employee_setHorasTrabajadasTxt(Employee* this, char* horasTrabajadas);
int employee_getHorasTrabajadasTxt(Employee* this, char* horasTrabajadas);

int employee_setSueldoTxt(Employee* this, char* sueldo);
int employee_setSueldo(Employee* this, int sueldo);
int employee_getSueldoTxt(Employee* this, char* sueldo);
int employee_getSueldo(Employee* this, int* sueldo);

int emp_borrarById(LinkedList* pArrayListEmployee, int length, int id);
int emp_buscarId(LinkedList* pArrayListEmployee, int length, int id);
int employee_compararNombre(void* thisA, void* thisB);
int employee_compararSueldo(void* thisA, void* thisB);
int employee_compararId(void* thisA, void* thisB);
int employee_compararHoras(void* thisA, void* thisB);
#endif // employee_H_INCLUDED

