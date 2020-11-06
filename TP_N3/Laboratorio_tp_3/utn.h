/*
 * utn.h
 *      Author: Nico
 */
#ifndef UTN_H_
#define UTN_H_
	#define LONG_NAME 100
	#define LONG_NUMBER_VALUE 8
	#define MAX_SALARY 1000000
	#define MIN_SALARY 0.01
	#define MAX_SECTOR 10
	#define MIN_SECTOR 1
	#define TRUE 1
	#define FALSE 0
	//#define LONG_CUIT 14
	int utn_getNumberInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo);
	int utn_getNumberFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo);
	int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_sortMin(int pArray[], int limite);
	int utn_getName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getSueldoTxt(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getHorasTxt(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_calculateMaximum(int pArray[], int cantidadElementos, int* pResultado);
	int utn_calculateMinimum(int pArray[], int cantidadElementos, int* pResultado);
	int utn_calculateAverage(int pArray[], int cantidadElementos, float* pResultado);
	int utn_printArrayInt(int pArray[], int limite);
	int utn_sortArrayInt(int pArray[], int limite);
	int utn_countInt(int pArray[], int limite, int numero);
	int utn_countIntByReference(int pArray[], int limite, int numero, int* pDireccion);
	int utn_countCharByReference(char pArray[], char elemento, int* pElemento);
	int utn_getPhone(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getAlphaNum(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getCuit(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getDni(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getText(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
#endif /* UTN_H_ */
