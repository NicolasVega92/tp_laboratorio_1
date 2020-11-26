/*
 * Cliente.h
 *
 *  Created on: 23 nov. 2020
 *      Author: Nico
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#include "LinkedList.h"
#include "utn.h"
	typedef struct{
		char nombre[LONG_NAME];
		char apellido[LONG_NAME];
		char cuit[LONG_NAME];
		int id;
	}Cliente;
	Cliente* cliente_new(void);
	Cliente* cliente_newParametrosTxt(char* nombre, char* apellido, char* cuit, char* id);
	Cliente* cliente_newParametros(char* nombre, char* apellido, char* cuit, int* id );
	void cliente_delete(Cliente* this);
	int cliente_getNombre(Cliente* this, char* nombre);
	int cliente_setNombre(Cliente* this, char* nombre);
	int isValidNombre(char* nombre);
	int cliente_getApellido(Cliente* this, char* apellido);
	int cliente_setApellido(Cliente* this, char* apellido);
	int isValidApellido(char* apellido);
	int cliente_getCuit(Cliente* this, char* cuit);
	int cliente_setCuit(Cliente* this, char* cuit);
	int isValidCuit(char* cuit);
	int cliente_getId(Cliente* this, int* id);
	int cliente_setId(Cliente* this, int* id);
	int isValidId(int* id);
	int cliente_getIdTxt(Cliente* this, char* id);
	int cliente_setIdTxt(Cliente* this, char* id);
	int cliente_borrarById(LinkedList* this, int length, int id);
	int cliente_buscarId(LinkedList* this, int length, int id);
	int cliente_buscarCuit(LinkedList* this, int length, char* cuit);
	int cliente_imprimirClientePorIdClienteVentas(void* this, void* elemento);
	int cliente_imprimir(void* this);
	int cliente_buscarIdPorParametro(void* this, void* elemento);
	int cliente_imprimirPorId(void* this, void* elemento);
#endif /* CLIENTE_H_ */
