#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include "utn.h"
#include "LinkedList.h"
#define QTY_EMPLOYEE 100
#define ERROR_NOT_LOADED_LIST "Primero debe cargar un archivo\nIntente opcion 1 o 2 en el Menú\n"
typedef struct
{
    int id;
    char nombre[LONG_NAME];
    int horasTrabajadas;
    float sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
Employee* emp_newParametros(char* nombre, int horasTrabajadas, float sueldo, int id);
void employee_delete();

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
int employee_setSueldo(Employee* this, float sueldo);
int employee_getSueldoTxt(Employee* this, char* sueldo);
int employee_getSueldo(Employee* this, float* sueldo);

int emp_guardarArrayEnArchivo(Employee* arrayPunteros[], int length, char* pathArchivo);
int emp_leerArchivoParaVolcarloAlArray(Employee* arrayPunteros[], int length, char* pathArchivo, int* proximoId);
int emp_guardarArrayEnArchivoBinario(Employee* arrayPunteros[], int length, char* pathArchivo);
int emp_leerArchivoParaVolcarloAlArrayBinario(Employee* arrayPunteros[], int length, char* pathArchivo, int* proximoId);

int employee_compararNombre(void* thisA, void* thisB);

/*************************************************************************************************/

int emp_initArrayPunteros(Employee* arrayPunteros[], int length);
int emp_buscarLibreArrayPunteros(Employee* arrayPunteros[], int length);
int emp_imprimirArrayPunteros(Employee* arrayPunteros[], int length);
int emp_deleteByIndiceArrayPunteros(Employee* arrayPunteros[], int length ,int indice);
int emp_borrarById(LinkedList* pArrayListEmployee, int length, int id);
int emp_buscarId(LinkedList* pArrayListEmployee, int length, int id);
int emp_agregarArrayPunteros(Employee* arrayPunteros[], int length, char* nombre, int horasTrabajadas, float sueldo, int id);
int emp_agregarArrayPunterosTxt(Employee* arrayPunteros[], int length, char* id, char* nombre, char* horasTrabajadas, char* sueldo);
int emp_ordenarArrayPunteros(Employee* arrayPunteros[], int length);
int emp_promediarSueldo(Employee* arrayPunteros[], int length, float* promedio);
int emp_calcularSueldoMax(Employee* arrayPunteros[], int length, int* indice);

#endif // employee_H_INCLUDED

