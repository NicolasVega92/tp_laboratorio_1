/*
 * Informes.c
 *
 *  Created on: 25 nov. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Ventas.h"
#include "Controller.h"
#include "parser.h"
#include "utn.h"
#include "Informes.h"
/*
 *\brief Crea una lista Auxiliar donde almacenara los clientes que vendieron mas afiches
 *			dependiendo el filtro mayor o menor
 *\param LinkedList* thisCliente
 *\param LinkedList* thisVentas
 *\param int filtro
 *\return int -1 ERROR
 *\return int 0 ok
 */
int informes_findMaxAndMin(LinkedList* thisCliente, LinkedList* thisVentas, int filtro)
{
	int retorno = -1;
	Cliente* pCliente;
	int length = ll_len(thisCliente);
	int i;
	int contadorVentas, auxVentas;
	int idClienteListaCliente;
	int idAuxiliar;
	int flag = TRUE;
	LinkedList* listaClientesConVentasMaximas = ll_newLinkedList();
	if(thisCliente != NULL && thisVentas != NULL && (filtro == 0 || filtro == 1) && length >= 0)
	{
		retorno = 0;
		for(i=0; i < length; i++)
		{
			pCliente = ll_get(thisCliente, i);
			if(pCliente != NULL)
			{
				cliente_getId(pCliente, &idClienteListaCliente);
				contadorVentas = ll_reduceIntDual(thisVentas, contadorAfiches, &idClienteListaCliente);
				if(flag == TRUE)
				{
					auxVentas = contadorVentas;
					cliente_getId(pCliente, &idAuxiliar);
					ll_add(listaClientesConVentasMaximas, pCliente);
					flag = FALSE;
				}
				else
				{
					if(	(filtro == 0 && contadorVentas > auxVentas ) 	||
						(filtro == 1 && contadorVentas < auxVentas )	)
					{
						ll_clear(listaClientesConVentasMaximas);
						ll_add(listaClientesConVentasMaximas, pCliente);
						auxVentas = contadorVentas;
					}
					else if(contadorVentas == auxVentas)
					{
						ll_add(listaClientesConVentasMaximas, pCliente);
					}
				}
			}

		}
		if(filtro == 0)
		{
			printf("Cliente con mas afiches vendidos\n");
		}
		else
		{
			printf("Cliente con menos afiches vendidos\n");
		}
		ll_map(listaClientesConVentasMaximas, cliente_imprimir);
		//ll_mapComparar(thisCliente, cliente_imprimirPorId, &idAuxiliar);
		printf("Cantidad de afiches: %d\n\n",auxVentas );

	}
	return retorno;
}
/*
 *\brief 	compara el id parametro con el idCliente de la venta y en estado COBRADA retorna esa cantidad
 *\param 	void* pElemento
 *\param 	void* id
 *\return	int -2 ERROR VALIDACIONES
 *\return	int 0 OK
 *\return	int cantidadAfiches si encontro coincidencia
 */
int contadorAfiches(void* pElemento, void* id)
{
	int retorno = -2;
	Ventas* pVentas = (Ventas*)pElemento;
	int* idParametro = (int*)id;
	int auxEstado;
	int auxIdClientePorVentas;
	int auxCantidadAfiches;
	if(pVentas != NULL && *idParametro >= 0)
	{
		retorno = 0;
		if(	(ventas_getACobrar(pVentas, &auxEstado)==0) &&
			(ventas_getIdCliente(pVentas, &auxIdClientePorVentas) == 0))
		{
			if(auxEstado == 0 && auxIdClientePorVentas == *idParametro)
			{
				ventas_getCantidadAfiches(pVentas, &auxCantidadAfiches);
				retorno = auxCantidadAfiches;
			}
		}
	}
	return retorno;
}
/*
 *\brief 	compara el id parametro con el id de la venta y en estado COBRADA retorna esa cantidad
 *\param 	void* pElemento
 *\param 	void* id
 *\return	int -2 ERROR VALIDACIONES
 *\return	int 0 OK
 *\return	int cantidadAfiches si encontro coincidencia
 */
int contadorAfichesPorVenta(void* pElemento, void* id)
{
	int retorno = -2;
	Ventas* pVentas = (Ventas*)pElemento;
	int* idParametro = (int*)id;
	int auxEstado;
	int auxIdPorVentas;
	int auxCantidadAfiches;
	if(pVentas != NULL && *idParametro >= 0)
	{
		retorno = 0;
		if(	(ventas_getACobrar(pVentas, &auxEstado)==0) &&
			(ventas_getId(pVentas, &auxIdPorVentas) == 0))
		{
			if(auxEstado == 0 && auxIdPorVentas == *idParametro)
			{
				ventas_getCantidadAfiches(pVentas, &auxCantidadAfiches);
				retorno = auxCantidadAfiches;
			}
		}
	}
	return retorno;
}
/*
 *\brief Crea una lista Auxilair donde almacenara las ventas que contengas la mayor cantidad de afiches
 *			dependiendo el filtro
 *\param LinkedList* thisCliente
 *\param LinkedList* thisVentas
 *\param int filtro
 *\return int -1 ERROR
 *\return int 0 ok
 */
int informes_CANTIDADAFICHESMAXIMOSPORVENTA(LinkedList* thisCliente, LinkedList* thisVentas, int filtro)
{
	int retorno = -1;
	Ventas* pVentas;
	Ventas* pVentasMaximas;
	int length = ll_len(thisCliente);
	int lengthVentas = ll_len(thisVentas);
	int lengthVentasMaximas;
	int i;
	int contadorVentas, auxVentas;
	int idVentasListaVentas;
	int idAuxiliarVentasMax;
	int flag = TRUE;
	LinkedList* listaVentasMaximas = ll_newLinkedList();
	if(thisCliente != NULL && thisVentas != NULL && (filtro == 0 || filtro == 1) && length >= 0)
	{
		retorno = 0;
		for(i=0; i < lengthVentas; i++)
		{
			pVentas = ll_get(thisVentas, i);
			if(pVentas != NULL)
			{
				ventas_getId(pVentas, &idVentasListaVentas);
				contadorVentas = ll_reduceIntDual(thisVentas, contadorAfichesPorVenta, &idVentasListaVentas);
				if(flag == TRUE)
				{
					auxVentas = contadorVentas;
					ll_add(listaVentasMaximas, pVentas);
					flag = FALSE;
				}
				else
				{
					if(	(filtro == 0 && contadorVentas > auxVentas ) 	||
						(filtro == 1 && contadorVentas < auxVentas )	)
					{
						ll_clear(listaVentasMaximas);
						ll_add(listaVentasMaximas, pVentas);
						auxVentas = contadorVentas;
					}
					else if(contadorVentas == auxVentas)
					{
						ll_add(listaVentasMaximas, pVentas);
					}
				}
			}

		}
		if(filtro == 0)
		{
			printf("afiche MAS vendidos\n");
		}
		else
		{
			printf("afiches MENOS vendidos\n");
		}
		lengthVentasMaximas = ll_len(listaVentasMaximas);
		for(int j = 0; j < lengthVentasMaximas;j++)
		{
			pVentasMaximas = ll_get(listaVentasMaximas, j);
			if(pVentasMaximas != NULL)
			{
				ventas_getIdCliente(pVentasMaximas, &idAuxiliarVentasMax);
				ll_mapComparar(thisCliente, cliente_imprimirClientePorIdClienteVentas, &idAuxiliarVentasMax);
			}
		}
		printf("Cantidad de afiches: %d\n\n",auxVentas );
	}
	return retorno;
}
/*
 *

int informe_imprimirClienteConMasCobros(LinkedList* thisA, LinkedList* thisB, int filtro)
{
	int retorno = -1;
	int length;
	Cliente* pCliente = cliente_new();
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	int idInt;
	int i;
	int ventasCobradas;
	int ventasMaximasCobradas;
	int ventasMinimasCobradas;
	if( pCliente != NULL && thisA != NULL && thisB != NULL && (filtro == 1 || filtro == 0))
	{
		length = ll_len(thisA);
		for(i= 1; i < length; i++)
		{
			pCliente = ll_get(thisA, i);
			if(	//cliente_getIdTxt(pCliente, auxId) == 0 					&&
				cliente_getId(pCliente, &idInt) == 0 				&&
				cliente_getNombre(pCliente, auxNombre) == 0 			&&
				cliente_getApellido(pCliente, auxApellido) == 0		&&
				cliente_getCuit(pCliente, auxCuit) == 0 )
			{
				if(filtro == 1)
				{

					ventasCobradas = ll_reduceIntDual(thisB, findCobradas, &idInt);
					printf("ventas COBRADAS MAXIMAS: %d por %s\n", ventasCobradas, auxNombre);
					if(i == 1 || ventasCobradas > ventasMaximasCobradas)
					{
						ventasMaximasCobradas = ventasCobradas;
						printf("maximas %d\n", ventasMaximasCobradas);
					}
				}
				else
				{
					if(filtro == 0)
					{
						ventasCobradas = ll_reduceIntDual(thisB, findACobrar, &idInt);
						printf("ventas COBRADAS MINIMAS: %d\n", ventasCobradas);
						if(i == 0 || ventasCobradas < ventasMinimasCobradas)
						{
							ventasMinimasCobradas = ventasCobradas;
							printf("minimas %d\n", ventasMinimasCobradas);
						}
					}
				}
				retorno = 0;
			}
		}

	}
	return retorno;
}
*/
/*
 *

int informes_maxCantAficheEnVenta(LinkedList* thisCliente, LinkedList* thisVentas)
{
	int retorno = -1;
	Ventas* pVentas;
	int length = ll_len(thisVentas);
	int i;
	int contadorVentas, maximaVentas;
	int idClienteListaVentasMaximas;
	int flag = TRUE;
	LinkedList* listaVentasMaximas = ll_newLinkedList();
	int idVenta2;
	if(thisCliente != NULL && thisVentas != NULL )
	{
		retorno = 0;
		for(i=1; i < length+1; i++)
		{
			pVentas = ll_get(thisVentas, i);
			if(pVentas != NULL)
			{
				contadorVentas = ll_reduceIntDual(thisVentas, contadorAfiches, &i);
				if(flag == TRUE)
				{
					maximaVentas = contadorVentas;
					ll_add(listaVentasMaximas, pVentas);
					ventas_getId(pVentas, &idVenta2);
					printf("idVenta: %d - contad: %d \n", idVenta2, contadorVentas);
					flag = FALSE;
				}
				else
				{
					if(contadorVentas > maximaVentas)
					{
						ll_clear(listaVentasMaximas);
						ll_add(listaVentasMaximas, pVentas);
						maximaVentas = contadorVentas;
						ventas_getId(pVentas, &idVenta2);
						printf("idVenta: %d - contad: %d \n", idVenta2, contadorVentas);
					}
					else if(contadorVentas == maximaVentas)
					{
						ll_add(listaVentasMaximas, pVentas);
						ventas_getId(pVentas, &idVenta2);
						printf("idVenta: %d - contad: %d \n", idVenta2, contadorVentas);
					}
				}
			}
		}
		for(int j = 0; j < ll_len(listaVentasMaximas);j++)
		{
			pVentas = ll_get(listaVentasMaximas, j);
			ventas_getIdCliente(pVentas, &idClienteListaVentasMaximas);
			printf("idcliente: %d\n", idClienteListaVentasMaximas);
			ll_mapComparar(thisCliente, cliente_imprimirClientePorIdClienteVentas, &idClienteListaVentasMaximas);
		}
		printf("Cantidad de afiches en una sola venta: %d\n\n",maximaVentas );
	}
	return retorno;
}
*/
/*
 *
Ventas* informes_cantidadAfichesPorVenta(LinkedList* thisVentas, int choice, int* qtyPoster, int estado)
{
	void* returnAux = NULL;
	Ventas* pVentas;
	int cantidad;
	int maximo;
	int minimo;
	int i;
	int stat;

	if(thisVentas != NULL  && qtyPoster != NULL && (estado == 0 || estado == 1))
	{
		for(i = 0; i< ll_len(thisVentas);i++)
		{
			pVentas = ll_get(thisVentas,i);
			if(pVentas != NULL)
			{
				ventas_getCantidadAfiches(pVentas, &cantidad);
				ventas_getACobrar(pVentas, &stat);
				if((i==0 || cantidad > maximo) && choice == 0 && stat == estado)
				{
					maximo = cantidad;
					returnAux = pVentas;
					*qtyPoster = cantidad;
				} else if((i== 0 || cantidad < minimo) && choice == 1 && stat == estado) {
					minimo = cantidad;
					returnAux = pVentas;
					*qtyPoster = cantidad;
				}
			}
		}
	}
	return returnAux;
}
*/








































