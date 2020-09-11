/*
 * utn.h
 *      Author: Nico
 */

#ifndef UTN_H_
#define UTN_H_

	int utn_getFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo);
	int utn_getInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo);
	int utn_menuOptions(float operador1, float operador2, int flagOperador1, int flagOperador2);

#endif /* UTN_H_ */
