/*
 * utn.h
 *      Author: Nico
 */
#ifndef UTN_H_
#define UTN_H_
	int utn_getNumberInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo);
	int utn_getNumberFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo);
	int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_sortMin(int pArray[], int limite);
	int utn_getName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
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
#endif /* UTN_H_ */
