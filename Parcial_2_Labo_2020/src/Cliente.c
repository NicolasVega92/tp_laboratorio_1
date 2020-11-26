/*
 * Cliente.c
 *
 *  Created on: 23 nov. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Cliente.h"
/*
 * \brief 	Crea una direccion de memoria con el tamaño indicado en malloc
 * \return	Una direccion de memoria con el tamaño de CLIENTE
 */
Cliente* cliente_new(void)
{
	return (Cliente*)malloc(sizeof(Cliente));
}
/*
 * \brief	Agrega los valores pasados como parametros a la direccion de memoria creada por new
 * \param	char* nombre
 * \param 	char* apellido
 * \param	char* cuit
 * \param	char* id
 * \return	auxPuntero pudiendo ser = NULL o = la direccion creada por new con los valores agregados
 */
Cliente* cliente_newParametrosTxt(char* nombre, char* apellido, char* cuit, char* id)
{
	Cliente* this = cliente_new();
	if(this != NULL)
	{
		if(
			cliente_setNombre(this, nombre) 		== -1 	||
			cliente_setApellido(this, apellido) 		== -1 	||
			cliente_setCuit(this, cuit) 		== -1 	||
			cliente_setIdTxt(this, id) 		== -1 )
		{
			cliente_delete(this);
			this = NULL;
		}
	}
	//printf("%s - %s - %s - %d", this->nombre, this->apellido, this->cuit, this->id);
	return this;
}
/*
 * \brief	Agrega los valores pasados como parametros a la direccion de memoria creada por new
 * \param	char* nombre
 * \param 	char* apellido
 * \param	char* cuit
 * \param	int* id
 * \return	auxPuntero pudiendo ser = NULL o = la direccion creada por new con los valores agregados
 */
Cliente* cliente_newParametros(char* nombre, char* apellido, char* cuit, int* id )
{
	Cliente* this = cliente_new();
	if(this != NULL)
	{
		if(
			cliente_setNombre(this, nombre) 		!= -1 	&&
			cliente_setApellido(this, apellido) 		!= -1 	&&
			cliente_setCuit(this, cuit) 		!= -1 	&&
			cliente_setId(this, id) 		!= -1 	)
		{
			return this;
		}
	}
	return NULL;
}
/*
 * \brief 	Libera la direccion de memoria del elemento pasado como parametro
 */
void cliente_delete(Cliente* this)
{
	if(this != NULL)
	{
		free(this);
	}
}
/*
 * \brief 	Obtiene el valor de nombre del elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* nombre
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_getNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombre, LONG_NAME);
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de nombre para el elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* nombre
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_setNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && isValidNombre(nombre) == 1)
	{
		strncpy(this->nombre, nombre, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}

int isValidNombre(char* nombre)
{
	return 1;
}
/*
 * \brief 	Obtiene el valor de apellido del elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* apellido
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_getApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		retorno = 0;
		strncpy(apellido, this->apellido, LONG_NAME);
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de apellido para el elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* apellido
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_setApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && isValidApellido(apellido) == 1)
	{
		strncpy(this->apellido, apellido, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}

int isValidApellido(char* apellido)
{
	return 1;
}
/*
 * \brief 	Obtiene el valor de cuit del elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* cuit
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_getCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL)
	{
		retorno = 0;
		strncpy(cuit, this->cuit, LONG_NAME);
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de cuit para el elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* cuit
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_setCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && isValidCuit(cuit) == 1)
	{
		strncpy(this->cuit, cuit, LONG_NAME);
		retorno = 0;
	}
	return retorno;
}

int isValidCuit(char* cuit)
{
	return 1;
}
/*
 * \brief 	Obtiene el valor de id del elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	int* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_getId(Cliente* this, int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de id para el elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	int* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_setId(Cliente* this, int* id)
{
	int retorno = -1;
	if(this != NULL && isValidId(id) == 1)
	{
		this->id = *id;
		retorno = 0;
	}
	return retorno;
}

int isValidId(int* id)
{
	int retorno = 1;
	return retorno;
}

/*
 * \brief 	Obtiene el valor de id del elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_getIdTxt(Cliente* this, char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		sprintf(id, "%d" , this->id);
	}
	return retorno;
}
/*
 * \brief 	Setea el valor de id para el elemento pasado como parametro (this)
 * \param 	Cliente* this
 * \param	char* id
 * \return	int -1 ERROR this == NULL || parametro == NULL
 * 			int 0 OK
 */
int cliente_setIdTxt(Cliente* this, char* id)
{
	int retorno = -1;
	if(this != NULL)
	{
		this->id = atoi(id);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief	Recorre la lista pasada como parametro y verifica en cada elemento el campo ID
 * 			y lo compara con el id pasado como parametro.
 * 			Hasta encontrar una coincidencia o llegar al final y no encontrarla.
 * \param	Cliente* this
 * \param	int length
 * \param	int id
 * \return	int -1 ERROR this == NULL || length <= 0 || id <= 0 /
 * 			int -2 ERROR No encontro ID /
 * 			int i OK indice del elemento cargado en la lista con el mismo valor del ID pasado como parametro
 */
int cliente_buscarId(LinkedList* this, int length, int id)
{
	int retorno = -1;
	int i;
	int auxId;
	Cliente* pCliente;
	if(this != NULL && length > 0 && id > 0)
	{
		retorno = -2;
		for(i = 0; i < length; i++)
		{
			pCliente = (Cliente*)ll_get(this, i);
			cliente_getId(pCliente, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief	Recorre y busca el CUIT pasado como parametro
 * \param	Cliente* this
 * \param	int length
 * \param	char* cuit
 * \return	int -2 ERROR en validaciones
 * \return  int -1 Si encontro el CUIT (ya existe)
 * \return  int  0 NO ENCONTRO COINCIDENCIA
 */
int cliente_buscarCuit(LinkedList* this, int length, char* cuit)
{
	int retorno = -2;
	int i;
	char auxCuitBuscado[LONG_NAME];
	Cliente* pCliente;
	if(this != NULL && length > 0 && cuit != NULL)
	{
		for(i = 0; i < length; i++)
		{
			retorno = 0;
			pCliente = (Cliente*)ll_get(this, i);
			cliente_getCuit(pCliente, auxCuitBuscado);
			if(strcmp(cuit, auxCuitBuscado) == 0)
			{
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief	Elimina de la lista un elemento con el id pasado como parametro.
 * 			Mediante la funcion emp_buscarId() obtiene el indice y luego lo elimina.
 * \param	Cliente* this
 * \param	int length
 * \param	int id
 * \return	int -1 ERROR this == NULL || length <= 0 || id <= 0 /
 * 			int -1 indiceBorrar <= -1 /
 * 			int i OK indice del elemento cargado en la lista con el mismo valor del ID pasado como parametro
 */
int cliente_borrarById(LinkedList* this, int length, int id)
{
	int retorno = -1;
	int indiceBorrar;
	Cliente* pCliente;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	if(this != NULL && length > 0 && id > 0)
	{
		indiceBorrar = cliente_buscarId(this, length, id);
		if(indiceBorrar > -1)
		{
			pCliente = ll_get(this, indiceBorrar);
			cliente_getNombre(pCliente, auxNombre);
			cliente_getApellido(pCliente, auxApellido);
			cliente_getCuit(pCliente, auxCuit);
			printf("\nAcaba de eliminar de la lista el id: %d\n", id);
			printf("Nombre: %s - Apellido: %s - CUIT: %s\n",auxNombre,auxApellido,auxCuit);
			if(ll_remove(this, indiceBorrar)==0)
			{
				retorno = 0;
				cliente_delete(pCliente);
			}
		}
		else if(indiceBorrar == -1)
		{
			printf("Error en la validación de datos en BuscarByIdArrayPunteros\n");
		}
		else
		{
			printf("No existe el ID a ser removido\n\n");
		}
	}
	return retorno;
}
/*
 * \brief	Imprime el cliente obtenido del this pasado como parametro
 * 			Comparandolo con el elemento del parametro
 * \param	void* this
 * \param 	void* elemento
 * \return	int -2 ERROR en validaciones
 * 			int -1 No encuentra
 * 			int id cliente OK
 */
int cliente_imprimirClientePorIdClienteVentas(void* this, void* elemento)
{
	int retorno = -2;
	Cliente* thisA = (Cliente*)this;
	int* idClienteParametro = (int*)elemento;
	char auxId[LONG_NAME];
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	if(thisA != NULL)
	{
		retorno = -1;
		if(	cliente_getIdTxt(thisA, auxId) == 0)
		{
			if(atoi(auxId) ==  *idClienteParametro)
			{
				if(	cliente_getNombre(thisA, auxNombre) == 0 &&
					cliente_getApellido(thisA, auxApellido) == 0 &&
					cliente_getCuit(thisA, auxCuit)==0)
				{
					printf("Nombre: %s - Apellido: %s - CUIT: %s\n", auxNombre, auxApellido, auxCuit);
				}
				retorno = atoi(auxId);
			}
		}
	}
	return retorno;
}
/*
 * \brief	Imprime el cliente obtenido del this pasado como parametro
 * \param	void* this
 * \return	int -2 ERROR en validaciones
 * 			int -1 No encuentra
 * 			int 0 OK
 */
int cliente_imprimir(void* this)
{
	int retorno = -2;
	Cliente* thisA = (Cliente*)this;
	char auxId[LONG_NAME];
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	if(thisA != NULL)
	{
		retorno = -1;
		if(	cliente_getIdTxt(thisA, auxId) == 0				&&
			cliente_getNombre(thisA, auxNombre) == 0 		&&
			cliente_getApellido(thisA, auxApellido) == 0 	&&
			cliente_getCuit(thisA, auxCuit)==0)
		{
			printf("Id: %s - Nombre: %s - Apellido: %s - CUIT: %s\n", auxId, auxNombre, auxApellido, auxCuit);
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \brief	Compara el elemento parametro con el id del cliente
 * \param	void* this
 * \param	void* elemento
 * \return	int -2 ERROR en validaciones
 * 			int -1 No encuentra
 * 			int id del cliente OK
 */
int cliente_buscarIdPorParametro(void* this, void* elemento)
{
	int retorno = -2;
	Cliente* thisA = (Cliente*)this;
	char* idClienteParametro = (char*)elemento;
	int auxIdClienteInt;
	if(thisA != NULL && idClienteParametro != NULL)
	{
		retorno = -1;
		if(cliente_getId(thisA, &auxIdClienteInt)==0)
		{
			if(auxIdClienteInt == atoi(idClienteParametro))
			{
				retorno = auxIdClienteInt;
			}
		}

	}
	return retorno;
}
/*
 * \brief	Imprime el cliente obtenido del this pasado como parametro
 * 			Comparandolo con el elemento pasado
 * \param	void* this
 * \return	int -2 ERROR en validaciones
 * 			int -1 No encuentra
 * 			int 0 OK
 */
int cliente_imprimirPorId(void* this, void* elemento)
{
	int retorno = -2;
	Cliente* thisA = (Cliente*)this;
	int* idClienteParametro = (int*)elemento;
	char auxId[LONG_NAME];
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	if(thisA != NULL)
	{
		retorno = 0;
		if(	cliente_getIdTxt(thisA, auxId) == 0)
		{
			if(atoi(auxId) ==  *idClienteParametro)
			{
				if(	cliente_getNombre(thisA, auxNombre) == 0 &&
					cliente_getApellido(thisA, auxApellido) == 0 &&
					cliente_getCuit(thisA, auxCuit)==0)
				{
					printf("Nombre: %s - Apellido: %s - CUIT: %s\n", auxNombre, auxApellido, auxCuit);
				}
				retorno = atoi(auxId);
			}
		}
	}
	return retorno;
}









