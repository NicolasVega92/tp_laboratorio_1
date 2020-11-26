/*
 * Ventas.c
 *
 *  Created on: 23 nov. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Ventas.h"
#include "Cliente.h"
#include "Informes.h"
Ventas* ventas_new(void)
{
	return (Ventas*)malloc(sizeof(Ventas));
}

Ventas* ventas_newParametrosTxt(char* id, char* aCobrar, char* idCliente, char* cantidadAfiches, char* nombre, char* zona)
{
	Ventas* this = ventas_new();
	if(this != NULL)
	{
		if(	ventas_setIdTxt(this, id) == -1 ||
			ventas_setACobrarTxt(this, aCobrar) == -1 ||
			ventas_setIdClienteTxt(this, idCliente) 		== -1 	||
			ventas_setCantidadAfichesTxt(this, cantidadAfiches) 		== -1 	||
			ventas_setNombre(this, nombre) 		== -1 	||
			ventas_setZona(this, zona) == -1)
		{
			ventas_delete(this);
			this = NULL;
		}
	}
	return this;
}
Ventas* ventas_newParametros(int* id, int* aCobrar, int* idCliente, int* cantidadAfiches, char* nombre, char* zona)
{
	Ventas* this = ventas_new();
	if(this != NULL)
	{
		if(	ventas_setId(this, id) != -1 &&
			ventas_setACobrar(this, aCobrar) != -1 &&
			ventas_setIdCliente(this, idCliente) 		!= -1 	&&
			ventas_setCantidadAfiches(this, cantidadAfiches) 		!= -1 	&&
			ventas_setNombre(this, nombre) 		!= -1 	&&
			ventas_setZona(this, zona) != -1)
		{
			return this;
		}
	}
	return NULL;
}
void ventas_delete(Ventas* this)
{
	if(this != NULL)
	{
		free(this);
	}
}
int ventas_getId(Ventas* this, int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

int ventas_setId(Ventas* this, int* id)
{
	int retorno = -1;
	if(this != NULL && isValidIdCliente(id) == 1)
	{
		this->id = *id;
		retorno = 0;
	}
	return retorno;
}
int ventas_getIdTxt(Ventas* this, char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		sprintf(id, "%d" , this->id);
	}
	return retorno;
}

int ventas_setIdTxt(Ventas* this, char* id)
{
	int retorno = -1;
	if(this != NULL)
	{
		this->id = atoi(id);
		retorno = 0;
	}
	return retorno;
}
int ventas_getACobrar(Ventas* this, int* aCobrar)
{
	int retorno = -1;
	if(this != NULL && aCobrar != NULL)
	{
		retorno = 0;
		*aCobrar = this->aCobrar;
	}
	return retorno;
}

int ventas_setACobrar(Ventas* this, int* aCobrar)
{
	int retorno = -1;
	if(this != NULL && isValidIdCliente(aCobrar) == 1)
	{
		this->aCobrar = *aCobrar;
		retorno = 0;
	}
	return retorno;
}
int ventas_getACobrarTxt(Ventas* this, char* aCobrar)
{
	int retorno = -1;
	if(this != NULL && aCobrar != NULL)
	{
		retorno = 0;
		sprintf(aCobrar, "%d" , this->aCobrar);
	}
	return retorno;
}

int ventas_setACobrarTxt(Ventas* this, char* aCobrar)
{
	int retorno = -1;
	if(this != NULL)
	{
		this->aCobrar = atoi(aCobrar);
		retorno = 0;
	}
	return retorno;
}
int ventas_getIdCliente(Ventas* this, int* idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente != NULL)
	{
		retorno = 0;
		*idCliente = this->idCliente;
	}
	return retorno;
}

int ventas_setIdCliente(Ventas* this, int* idCliente)
{
	int retorno = -1;
	if(this != NULL && isValidIdCliente(idCliente) == 1)
	{
		this->idCliente = *idCliente;
		retorno = 0;
	}
	return retorno;
}

int isValidIdCliente(int* idCliente)
{
	int retorno = 1;
	return retorno;
}

int ventas_getCantidadAfiches(Ventas* this, int* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches != NULL)
	{
		retorno = 0;
		*cantidadAfiches = this->cantidadAfiches;
	}
	return retorno;
}

int ventas_setCantidadAfiches(Ventas* this, int* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && isValidCantidadAfiches(cantidadAfiches) == 1)
	{
		this->cantidadAfiches = *cantidadAfiches;
		retorno = 0;
	}
	return retorno;
}

int isValidCantidadAfiches(int* cantidadAfiches)
{
	int retorno = 1;
	return retorno;
}

int ventas_getNombre(Ventas* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombre, LONG_NAME);
	}
	return retorno;
}

int ventas_setNombre(Ventas* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && isValidNombreAfiche(nombre) == 1)
	{
		strncpy(this->nombre, nombre, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}

int isValidNombreAfiche(char* nombre)
{
	int retorno = 1;
	return retorno;
}

int ventas_getZona(Ventas* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		retorno = 0;
		strncpy(zona, this->zona, LONG_NAME);
	}
	return retorno;
}

int ventas_setZona(Ventas* this, char* zona)
{
	int retorno = -1;
	if(this != NULL && isValidZona(zona) == 1)
	{
		strncpy(this->zona, zona, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}

int isValidZona(char* zona)
{
	int retorno = 1;
	return retorno;
}

int ventas_getIdClienteTxt(Ventas* this, char* idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente != NULL)
	{
		retorno = 0;
		sprintf(idCliente, "%d" , this->idCliente);
	}
	return retorno;
}

int ventas_setIdClienteTxt(Ventas* this, char* idCliente)
{
	int retorno = -1;
	if(this != NULL)
	{
		this->idCliente = atoi(idCliente);
		retorno = 0;
	}
	return retorno;
}

int ventas_getCantidadAfichesTxt(Ventas* this, char* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL && cantidadAfiches != NULL)
	{
		retorno = 0;
		sprintf(cantidadAfiches, "%d" , this->cantidadAfiches);
	}
	return retorno;
}

int ventas_setCantidadAfichesTxt(Ventas* this, char* cantidadAfiches)
{
	int retorno = -1;
	if(this != NULL )
	{
		this->cantidadAfiches = atoi(cantidadAfiches);
		retorno = 0;
	}
	return retorno;
}
int ventas_buscarIdCliente(LinkedList* this, int length, char* idCliente)
{
	int retorno = -1;
	int i;
	char auxIdClienteBuscado[LONG_NAME];
	Cliente* pCliente;
	if(this != NULL && length > 0 && idCliente != NULL)
	{
		for(i = 0; i < length; i++)
		{
			retorno = -1;
			pCliente = (Cliente*)ll_get(this, i);
			cliente_getIdTxt(pCliente, auxIdClienteBuscado);
			if(strcmp(idCliente, auxIdClienteBuscado) == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
int ventas_imprimirListaACobrar(void* this)
{
	int retorno = -2;
	Ventas* thisA = (Ventas*)this;
	char auxNombre[LONG_NAME];
	char auxIdCliente[LONG_NAME];
	char auxCantAfiches[LONG_NAME];
	char auxId[LONG_NAME];
	char auxZona[LONG_NAME];
	char auxEstado[LONG_NAME];
	//printf("entre aca antes del IF EN LA FUNCION IMPRIMIR\n");
	if(thisA != NULL)
	{
		retorno = -1;
		if(	ventas_getACobrarTxt(thisA, auxEstado) == 0	)
		{
			if(strcmp(auxEstado, "1") == 0)
			{
				if(	ventas_getIdTxt(thisA, auxId) == 0 &&
					ventas_getNombre(thisA, auxNombre)== 0 &&
					ventas_getIdClienteTxt(thisA, auxIdCliente)== 0 &&
					ventas_getCantidadAfichesTxt(thisA, auxCantAfiches)== 0 &&
					ventas_getZona(thisA, auxZona)== 0 )
				{
					printf("%3s|%15s|%10s|%12s|%12s|%10s\n", auxId, auxNombre, auxIdCliente, auxCantAfiches, ZONA[atoi(auxZona)], ESTADO[atoi(auxEstado)]);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}
/*
 *
 */
int ventas_imprimirListaACobrarParametro(void* this, void* pArgumento)
{
	int retorno = -2;
	Ventas* thisA = (Ventas*)this;
	int* ACobrar = (int*)pArgumento;
	char auxNombre[LONG_NAME];
	char auxIdCliente[LONG_NAME];
	char auxCantAfiches[LONG_NAME];
	char auxId[LONG_NAME];
	char auxZona[LONG_NAME];
	//char auxEstado[LONG_NAME];
	int ACobrarInt;
	//printf("entre aca antes del IF EN LA FUNCION IMPRIMIR\n");
	if(thisA != NULL)
	{
		retorno = -1;
		if(	ventas_getACobrar(thisA, &ACobrarInt) == 0	)
		{
			if(ACobrarInt == *ACobrar)
			{
				if(	ventas_getIdTxt(thisA, auxId) == 0 &&
					ventas_getNombre(thisA, auxNombre)== 0 &&
					ventas_getIdClienteTxt(thisA, auxIdCliente)== 0 &&
					ventas_getCantidadAfichesTxt(thisA, auxCantAfiches)== 0 &&
					ventas_getZona(thisA, auxZona)== 0 )
				{
					printf("%3s|%15s|%10s|%12s|%12s|%10s\n", auxId, auxNombre, auxIdCliente, auxCantAfiches, ZONA[atoi(auxZona)], ESTADO[ACobrarInt]);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}
int ventas_obtenerIdCliente(void* this, void* elemento)
{
	int retorno = -1;
	Ventas* thisA = (Ventas*)this;
	int* idVentaParametro = (int*)elemento;
	//char auxIdCliente[LONG_NAME];
	int auxIdClienteInt;
	char auxId[LONG_NAME];
	char auxEstado[LONG_NAME];
	if(thisA != NULL)
	{
		retorno = 0;
		if(	ventas_getACobrarTxt(thisA, auxEstado) == 0	)
		{
			if(strcmp(auxEstado, "1") == 0)
			{
				if(	ventas_getIdTxt(thisA, auxId) == 0)
				{
					if(atoi(auxId) ==  *idVentaParametro)
					{
						//ventas_getIdClienteTxt(thisA, auxIdCliente);
						//printf("id cliente - %s -  del id de la venta - %s - \n",auxIdCliente, auxId);
						ventas_getIdCliente(thisA, &auxIdClienteInt);
						printf("id cliente - %d -  del id de la venta - %s - \n",auxIdClienteInt, auxId);
						retorno = auxIdClienteInt;
					}
				}
			}
		}

	}
	return retorno;
}
