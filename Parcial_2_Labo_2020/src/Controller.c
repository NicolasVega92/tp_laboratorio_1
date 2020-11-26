

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
 * \brief 	Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param 	char* path, nombre del archivo pasado como parametro
 * \param 	LinkedList* this, lista pasada como parametro
 * \return 	int -1 ERROR en el parser /
 * 			int 0 OK
 */
int controller_loadFromTextCliente(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			retorno = parser_ClienteFromText(pFile, this);
		}
		else
		{
			printf("EMPEZAMOS MAL\n");
		}
		fclose(pFile);
	}
	return retorno;
}
/*
 *
 */
int controller_loadFromTextVentas(char* path , LinkedList* this)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			retorno = parser_ventasFromText(pFile, this);
		}
		else
		{
			printf("EMPEZAMOS MAL\n");
		}
		fclose(pFile);
	}
	return retorno;
}
/*
 * \brief 	Carga los datos de los empleados desde el archivo data-bin.csv (modo binario).
 * \param 	char* path, nombre del archivo pasado como parametro
 * \param 	LinkedList* this, lista pasada como parametro
 * \return 	int -1 ERROR en el parser /
 * 			int 0 OK
 */
/*
int controller_loadFromBinary(char* path , LinkedList* this)
{
	int retorno = -1;
	if(path != NULL)
	{
		FILE* pFile = fopen(path, "rb");
		retorno = parser_ClienteFromBinary(pFile, this);
		fclose(pFile);
	}
	return retorno;
}
*/
/*
 * \brief 	Alta de empleados, agrega un nuevo empleado a la lista con todos sus campos rellenados por el usuario
 * \param 	LinkedList* this
 * \return 	int -1 ERROR si la this == NULL /
 * 			int -1 ERROR si no se pudieron obtener los datos del empleado correctamente /
 * 			int -1 ERROR si el pCliente == NULL
 * 			int 0 OK
 */
int controller_addCliente(LinkedList* this)
{
	int retorno = -1;
	Cliente* pCliente;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	char auxid[LONG_NUMBER_VALUE];
	int auxIdPorRetorno;
	int length;
	if(this!=NULL)
	{
		length = ll_len(this);
		if(	(utn_getName("Ingresa el Nombre del cliente:\n", "Error, por favor reintentelo con un nombre válido\n", auxNombre , 3, LONG_NAME)==0) &&
			(utn_getName("Ingresa el apellido:\n", "Error, por favor reintentelo con un apellido válido\n",  auxApellido, 3, LONG_NAME)==0) &&
			(utn_getCuitTxt("Ingresa el cuit:\n", "Error, por favor reintentelo con un cuit válido (solo números)\n", auxCuit, 3, LONG_NAME)==0))
		{
			//if(ll_map(this, cliente_buscarCuit) == 0)
			if(cliente_buscarCuit(this, length, auxCuit)==0)
			{
				auxIdPorRetorno = controller_encontrarProximoId(this);
				sprintf(auxid, "%d", auxIdPorRetorno);
				pCliente = cliente_newParametrosTxt(auxNombre, auxApellido, auxCuit, auxid);
				if(pCliente != NULL)
				{
					ll_add(this, pCliente);
					printf("\nEmpleado cargado con ID: %s\nNombre: %s - Apellido:%s - CUIT:%s\n", auxid, auxNombre, auxApellido, auxCuit);
					retorno = 0;
				}
			}
			else
			{
				printf("ESE CUIT YA EXISTE\n");
			}
		}
	}
	return retorno;
}
int controller_addVentas(LinkedList* this, LinkedList* thisB)
{
	int retorno = -1;
	Ventas* pVentas;
	char auxNombre[LONG_NAME];
	char auxIdCliente[LONG_NAME];
	char auxCantAfiches[LONG_NAME];
	char auxId[LONG_NAME];
	char auxZona[LONG_NAME];
	char auxEstado[LONG_NAME];
	int auxIdPorRetorno;
	int retornoMap;
	if(this!=NULL && thisB != NULL)
	{
		if(	(utn_getName("Ingresa el Nombre del archivo:\n", "Error, por favor reintentelo con un nombre válido\n", auxNombre , 3, LONG_NAME)==0) 	&&
			(utn_getNumberTxt("Ingrese el Id del Cliente\n", "Error, solo Numeros\n", auxIdCliente, 3, LONG_NAME) == 0 )							&&
			//(utn_getNumberInt("Ingrese el Id del Cliente\n", "Error, solo Numeros\n", &auxIdClienteInt, 3, 1, 100) == 0) &&
			(utn_getNumberTxt("Ingrese la cantidad de afiches que desea: \n", "Error, solo Números\n", auxCantAfiches, 3, LONG_NAME)==0) 			&&
			(utn_getNumberTxt(	"Ingrese el número correspondiente de la zona donde desea colocar los afiches:\n"
								"0-CABA\n"
								"1-ZONA SUR\n"
								"2-ZONA OESTE\n", "Error, ingrese una opción válida\n", auxZona, 3, LONG_NAME)==0))
		{
			//retornoMap = ll_mapComparar(thisB, cliente_buscarIdPorParametro, &idClienteAux);
			retornoMap = ll_mapComparar(thisB, cliente_buscarIdPorParametro, auxIdCliente);
			if(retornoMap > -1)
			//if(ventas_buscarIdCliente(thisB, lengthCliente, auxIdCliente)==0)
			{
				auxIdPorRetorno = controller_encontrarProximoIdVentas(this);
				sprintf(auxId, "%d", auxIdPorRetorno);
				sprintf(auxEstado, "%d", 1);
				pVentas = ventas_newParametrosTxt(auxId, auxEstado, auxIdCliente, auxCantAfiches, auxNombre, auxZona);
				if(pVentas != NULL)
				{
					ll_add(this, pVentas);
					printf("\nLa venta realizada tiene el ID: %s - con el estado: %s -\n"
							"Id Cliente: %s - Una cantidad de afiches de: %s \n"
							"Nombre del afiche: %s - En la zona: %s\n", auxId, ESTADO[atoi(auxEstado)], auxIdCliente, auxCantAfiches, auxNombre, ZONA[atoi(auxZona)]);
					retorno = 0;
				}
			}
			else
			{
				printf("ESE ID CLIENTE NO EXISTE\n");
			}
		}
	}
	return retorno;
}
/*
 * \brief 	Modifica el nombre, sueldo y horas de un empleado, a través del ID pedido al usuario
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 * 			int -1 ERROR pCliente == NULL /
 * 			int -1 ERROR en utn_getNumberInt(); /
 * 			int -1 ERROR no se pueden settear los nuevos datos en el pCliente /
 * 			int -2 ERROR en controller_ListCliente(); /
 * 			int 0 OK
 */
int controller_editCliente(LinkedList* this)
{
	int retorno = -1;
	int idAModificar;
	Cliente* pCliente;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	int indexAModificar;
	int length;
	int option;
	if(this != NULL)
	{
		length = ll_len(this);
		if(controller_ListCliente(this)==0)
		{
			if(utn_getNumberInt("**************************************\n"
								"Aca puede ver la lista de empleados.\n"
								"Ingrese el Id del empleado a modificar:\n",
								"Error, Ingrese un Id válido (solo números)\n", &idAModificar, 2, 1, 99999)==0)
			{
				indexAModificar = cliente_buscarId(this, length, idAModificar);
				if(indexAModificar >= 0)
				{
					pCliente = (Cliente*)ll_get(this, indexAModificar);
					cliente_getNombre(pCliente, auxNombre);
					cliente_getApellido(pCliente, auxApellido);
					cliente_getCuit(pCliente, auxCuit);
					printf(	"\nEl empleado con el ID:%d\n"
							"Nombre: %s - Apellido: %s - Cuit: %s\n", idAModificar, auxNombre, auxApellido, auxCuit);
					if(utn_getNumberInt("\n¿Está seguro de querer modificarlo?\n1-Si\n2-No\n", "Error, ingrese 1 - 2\n", &option, 3, 1, 2)==0)
					{
						if(option == 1 && pCliente != NULL)
						{
							if(	(utn_getName("Ingresa el Nombre del cliente:\n", "Error, por favor reintentelo con un nombre válido\n", auxNombre , 3, LONG_NAME)==0) &&
								(utn_getName("Ingresa el apellido:\n", "Error, por favor reintentelo con un apellido válido\n",  auxApellido, 3, LONG_NAME)==0) &&
								(utn_getCuitTxt("Ingresa el cuit:\n", "Error, por favor reintentelo con un cuit válido (solo números)\n", auxCuit, 3, LONG_NAME)==0))
							{
								if(	cliente_setNombre(pCliente, auxNombre) == 0 		&&
									cliente_setApellido(pCliente, auxApellido) == 0		&&
									cliente_setCuit(pCliente, auxCuit)==0)
								{
									ll_set(this, indexAModificar, pCliente);
									printf(	"\nAcabas de modificar el ID:%d\n"
											"Nombre: %s - Apellido: %s - CUIT: %s\n", idAModificar, auxNombre, auxApellido, auxCuit);
									retorno = 0;
								}
							}
						}
					}
				}
				else if(indexAModificar == -2)
				{
					printf("No se encontro el ID\n");
				}
				else
				{
					printf("Error validación datos en buscarId\n");
				}
			}
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}
int controller_editVentasEstado(LinkedList* thisA, LinkedList* thisB )
{
	int retorno = -1;
	Ventas* pVentas;
	//char auxEstado[LONG_NAME];
	//char estadoACAMBIAR[LONG_NAME];
	//char estadoDespues[LONG_NAME];
	/************/
	int idClienteAImprimir;
	int idVentaPedido;
	int opcion;
	int auxEstadoInt;
	/************/
	//char nombreGet[LONG_NAME];
	//int cantGet;
	//int estadoGet;
	/**/
	if(thisA != NULL && thisB != NULL)
	{
		printf(" ID|         NOMBRE| IDCLIENTE|CANT AFICHES|        ZONA|    ESTADO\n");
    	if(ll_map(thisA, ventas_imprimirListaACobrar)==0)
    	{
    		printf("\nOK PRINT\n");
    		if(utn_getNumberInt("Ingrese el Id de la venta que desea modificar:\n", "Error, ingrese un valor numérico\n", &idVentaPedido, 3, 1, 100)==0)
    		{
    			idClienteAImprimir = ll_mapComparar(thisA, ventas_obtenerIdCliente, &idVentaPedido);
    			if(idClienteAImprimir > -1)
				{
    				printf("\nOK MAP COMPARAR\n");
    				if(ll_mapComparar(thisB, cliente_imprimirClientePorIdClienteVentas, &idClienteAImprimir) > -1)
    				{
    					pVentas = (Ventas*)ll_get(thisA, (idVentaPedido)-1);
    					printf("\nOK MAP COMPARAR CLIENTE\n");
    					if(utn_getNumberInt("¿Desea confirmar el cambio de estado a \"Cobrada\"?\n"
    										"1- Si\n"
    										"2- NO\n", "Error, Ingrese una opción válida (1 - 2)\n", &opcion, 3, 1, 2) == 0)
    					{
    						if(pVentas != NULL && opcion == 1)
    						{
    							auxEstadoInt = 0;
    							//sprintf(auxEstado, "%d", 0);
    							//ventas_getACobrarTxt(pVentas, estadoACAMBIAR);
    							//printf("ESTADO A CAMBIAR   %s --- Y EL ANTEIROR %s \n\n", auxEstado, estadoACAMBIAR);
    							//ventas_getNombre(pVentas, nombreGet);
    							//ventas_getCantidadAfiches(pVentas, &cantGet);
    							//ventas_getACobrar(pVentas, &estadoGet);
    							//printf("-----------%s %d ---- %d ", nombreGet, cantGet, estadoGet);
    							if(ventas_setACobrar(pVentas, &auxEstadoInt) == 0)
    							{
    								//ventas_getACobrarTxt(pVentas, estadoDespues);
    								//printf("aaaaaaaaaaaa %s aaaaa \n", estadoDespues);
    								printf("OK CAMBIO DE ESTADO COBRADA\n");
    								retorno = 0;
    							}
    						}
    					}
    				}
				}
    		}
    	}
	}
	return retorno;
}
int controller_editVentas(LinkedList* thisA, LinkedList* thisB )
{
	int retorno = -1;
	Ventas* pVentas;
	char auxNombre[LONG_NAME];
	char auxZona[LONG_NAME];
	/************/
	int idClienteAImprimir;
	int idVentaPedido;
	int aModificar;
	int auxCantInt;
	//int parametro = 1;
	/************/
	if(thisA != NULL && thisB != NULL)
	{

    	if(ll_map(thisA, ventas_imprimirListaACobrar)==0)
    	//if(ll_mapComparar(thisA, ventas_imprimirListaACobrarParametro, &parametro) == 0)
    	{
    		printf("\nOK PRINT\n");
    		if(utn_getNumberInt("Ingrese el Id de la venta que desea modificar:\n", "Error, ingrese un valor numérico\n", &idVentaPedido, 3, 1, 100)==0)
    		{
    			idClienteAImprimir = ll_mapComparar(thisA, ventas_obtenerIdCliente, &idVentaPedido);
    			if(idClienteAImprimir > -1)
				{
    				printf("\nOK MAP COMPARAR\n");
    				if(ll_mapComparar(thisB, cliente_imprimirClientePorIdClienteVentas, &idClienteAImprimir) > -1)
    				{
    					pVentas = (Ventas*)ll_get(thisA, (idVentaPedido - 1));
    					printf("\nOK MAP COMPARAR CLIENTE\n");
    					if(utn_getNumberInt("Que desea modificar de la venta:\n"
    										"1- Nombre del archivo\n"
    										"2- Cantidad de afiches\n"
    										"3- Zona donde se pegarán\n", "Error, Ingrese una opción válida (1 - 3)\n", &aModificar, 3, 1, 3) == 0)
    					{
    						if(pVentas != NULL && aModificar > 0 && aModificar < 4)
    						{
    							printf("\n\nventa: %s - cant %d - %s\n\n", pVentas->nombre, pVentas->cantidadAfiches, ZONA[atoi(pVentas->zona)]);
        						switch(aModificar)
        						{
    								case 1:
    									if(utn_getName("Ingresa el Nombre del archivo:\n", "Error, por favor reintentelo con un nombre válido\n", auxNombre , 3, LONG_NAME)==0)
    									{
    										if(ventas_setNombre(pVentas, auxNombre) == 0)
    										{
    											//ll_set(thisA, idVentaPedido, pVentas);
    											printf("Ok EDIT NOMBRE VENTA\n");
    											printf("\n\nventa: %s - cant %d - %s\n\n", pVentas->nombre, pVentas->cantidadAfiches, pVentas->zona);
    											retorno = 0;
    										}
    									}
    									break;
    								case 2:
    									if(utn_getNumberInt("Ingrese la cantidad de afiches que desea: \n", "Error, solo Números (1 - 1000)\n", &auxCantInt, 3, 1, 1000)== 0)
    									{
    										if(ventas_setCantidadAfiches(pVentas, &auxCantInt) == 0)
    										{
    											//ll_set(thisA, idVentaPedido, pVentas);
    											printf("Ok EDIT CANT AFICHES VENTA\n");
    											printf("\n\nventa: %s - cant %d - %s\n\n", pVentas->nombre, pVentas->cantidadAfiches, pVentas->zona);
    											retorno = 0;
    										}
    									}
    									break;
    								case 3:
    									if(utn_getNumberTxt("Ingrese el número correspondiente de la zona donde desea colocar los afiches:\n"
    														"0- CABA\n"
    														"1-ZONA SUR\n"
    														"2-Zona OESTE\n", "Error, ingrese una opción válida\n", auxZona, 2, LONG_NAME)==0)
    									{
    										if(ventas_setZona(pVentas, auxZona)==0)
    										{
    											//ll_set(thisA, idVentaPedido, pVentas);
    											printf("Ok EDIT ZONA VENTA\n");
    											printf("\n\nventa: %s - cant %d - %s\n\n", pVentas->nombre, pVentas->cantidadAfiches, pVentas->zona);
    											retorno = 0;
    										}
    									}
    									break;
        						}
    						}
    					}
    				}
				}
    		}
    	}
	}
	return retorno;
}
/*
 * \brief 	Baja de empleado de la lista, por medio del ID pedido al usuario
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 * 			int -2 ERROR en utn_getNumberInt(); /
 * 			int -2 ERROR en emp_borrarById();
 * 			int 0 OK
 *
 */
int controller_removeCliente(LinkedList* this)
{
	int retorno = -1;
	int idBorrar;
	int length;
	if(this != NULL)
	{
		length = ll_len(this);
		controller_ListCliente(this);
		if(	utn_getNumberInt("\nQue id desea borrar:\n", "Error, ingrese un valor numérico de ID (1 - 99999)\n", &idBorrar, 3, 1, 99999)==0	&&
			cliente_borrarById(this, length, idBorrar) == 0)
		{
			retorno = 0;
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}

/*
 * \brief 	Listar empleados con sus campos.
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 *			int 0 OK
 */
int controller_ListCliente(LinkedList* this)
{
	int retorno = -1;
	int i;
	int length;
	Cliente* pBuffer;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	int auxId;
	if(this != NULL)
	{
		length = ll_len(this);
		printf(	"--------------------------------------------\n"
				"|               LISTA EMPLEADOS            |\n"
				"--------------------------------------------\n"
				"|  ID|           NOMBRE|   APELLIDO|    CUIT|\n"
				"--------------------------------------------\n");
		for(i = 0; i < length; i++)
		{
			pBuffer = ll_get(this, i);
			if(	cliente_getId(pBuffer, &auxId) == 0 					&&
				cliente_getNombre(pBuffer, auxNombre) == 0 			&&
				cliente_getApellido(pBuffer, auxApellido) == 0		&&
				cliente_getCuit(pBuffer, auxCuit) == 0 )
			{
				printf("%5d|%17s|%15s|%15s|\n",auxId, auxNombre, auxApellido, auxCuit );
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief 	Ordenar empleados según los criterios del switch
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 * 			int 0 OK
 */
int controller_sortCliente(LinkedList* this)
{
	int retorno = -1;
/*
	int option;
	if(this != NULL)
	{
		if(utn_getNumberInt("Como desea ordenar la lista:\n"
							"1-Por NOMBRE (Ascendente )\n"
							"2-Por NOMBRE (Descendente)\n"
							"3-Por SUELDO (Ascendente )\n"
							"4-Por SUELDO (Descendente)\n"
							"5-Por ID     (Ascendente )\n"
							"6-Por HORAS  (Ascendente )\n", "Error, ingrese una opción válida (1 - 5)\n", &option, 3, 1, 6)==0)
		{
			switch(option)
			{
			case 1:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR NOMBRE (A - Z)\n");
				retorno = ll_sort(this, cliente_compararNombre, 1);
				break;
			case 2:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR NOMBRE (Z - A)\n");
				retorno = ll_sort(this, cliente_compararNombre, 0);
				break;
			case 3:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR SUELDO (MENOR A MAYOR)\n");
				retorno = ll_sort(this, cliente_compararSueldo, 1);
				break;
			case 4:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR SUELDO (MAYOR A MENOR)\n");
				retorno = ll_sort(this, cliente_compararSueldo, 0);
				break;
			case 5:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR ID DE MANERA ASCENDENTE\n");
				retorno = ll_sort(this, cliente_compararId, 1);
				break;
			case 6:
				printf(	"	ESPERE UNOS SEGUNDOS POR FAVOR...\n"
						"	LA LISTA SE ESTA ORDENANDO POR MAYOR CANTIDAD DE HORAS TRABAJADAS\n");
				retorno = ll_sort(this, cliente_compararHoras, 0);
				break;
			}
		}
		if(retorno == 0)
		{
			printf("\n	GRACIAS POR ESPERAR\n"
					"	AHORA PUEDE ENTRAR A LA OPCION 6 PARA VER LA LISTA ORDENADA\n");
		}
	}
	*/
    return retorno;
}
/*
 *
 */
int controller_filtrarCliente(LinkedList* this)
{
	int retorno = -1;
	/*
	if(this != NULL)
	{
		retorno = ll_filter(this, cliente_filtrarSueldo);
	}
	*/
    return retorno;
}

/*
 * \brief 	Guarda los datos de los empleados en el archivo data.csv (modo texto).
 * \param 	char* path, nombre del archivo donde se guardara la lista activa en el programa
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL || path == NULL /
 * 			int -2 ERROR fpArchivo == NULL /
 * 			int 0 OK
 */
int controller_saveAsTextCliente(char* path , LinkedList* this)
{
	int retorno = -1;
	int i;
	int length;
	FILE* fpArchivo;
	Cliente* pBuffer;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	char auxId[LONG_NUMBER_VALUE];
	if(this != NULL && path != NULL)
	{
		length = ll_len(this);
		fpArchivo = fopen(path, "w");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			fprintf(fpArchivo,"Id,Nombre,Apellido,Cuit\n");
			for(i=0; i < length; i++)
			{
				pBuffer = ll_get(this, i);
				if(		cliente_getIdTxt(pBuffer, auxId) == 0 					&&
						cliente_getNombre(pBuffer, auxNombre) == 0 			&&
						cliente_getApellido(pBuffer, auxApellido) == 0		&&
						cliente_getCuit(pBuffer, auxCuit) == 0 )
				{
					fprintf(fpArchivo, "%s,%s,%s,%s\n",auxId, auxNombre, auxApellido, auxCuit );
				}
			}
			fclose(fpArchivo);
		}
		else
		{
			printf("No se pudo crear el archivo\n\n");
			retorno = -2;
		}
	}
	return retorno;
}
int controller_saveAsTextVentas(char* path , LinkedList* this)
{
	int retorno = -1;
	int i;
	int length;
	FILE* fpArchivo;
	Ventas* pBuffer;
	char auxNombre[LONG_NAME];
	char auxIdCliente[LONG_NAME];
	char auxCantAfiches[LONG_NAME];
	char auxId[LONG_NAME];
	char auxZona[LONG_NAME];
	char auxEstado[LONG_NAME];
	if(this != NULL && path != NULL)
	{
		length = ll_len(this);
		fpArchivo = fopen(path, "w");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			fprintf(fpArchivo,"id,cantidadAfiches,nombre,zona,estado,idCliente\n");
			for(i=0; i < length; i++)
			{
				pBuffer = ll_get(this, i);
				if(
					ventas_getIdTxt(pBuffer, auxId) == 0 &&
					ventas_getNombre(pBuffer, auxNombre) == 0 &&
					ventas_getIdClienteTxt(pBuffer, auxIdCliente) == 0 &&
					ventas_getCantidadAfichesTxt(pBuffer, auxCantAfiches)==0 &&
					ventas_getZona(pBuffer, auxZona) == 0 &&
					ventas_getACobrarTxt(pBuffer, auxEstado) == 0)
				{
					fprintf(fpArchivo, "%s,%s,%s,%s,%s,%s\n",auxId,auxCantAfiches, auxNombre, auxZona, auxEstado, auxIdCliente );
				}
			}
			fclose(fpArchivo);
		}
		else
		{
			printf("No se pudo crear el archivo\n\n");
			retorno = -2;
		}
	}
	return retorno;
}
/*
 * \brief 	Guarda los datos de los empleados en el archivo data2.csv (modo binario).
 * \param 	char* path, nombre del archivo donde se guardara la lista activa en el programa
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL || path == NULL /
 * 			int -2 ERROR fpArchivo == NULL /
 * 			int 0 OK
 */
/*
int controller_saveAsBinary(char* path , LinkedList* this)
{
	int retorno = -1;
	int i;
	FILE* pFile;
	Cliente* pCliente;
	int length;
	if(this != NULL && path != NULL)
	{
		length = ll_len(this);
		pFile = fopen(path, "wb");
		if(pFile != NULL)
		{
			retorno = 0;
			for(i = 0; i < length;i++)
			{
				pCliente = (Cliente*) ll_get(this, i);
				fwrite(pCliente, sizeof(Cliente), 1, pFile);
			}
			fclose(pFile);
		}
		else
		{
			retorno = -2;
			printf("No se pudo crear el archivo\n\n");
		}
	}
	return retorno;
}
*/
/*
 * \brief 	Da la opción de ELIMINAR la lista activa en el programa.
 * 			Primero vacia los elementos (ll_clear();) y luego la elimina (ll_deleteLinkedList();)
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 * 			int -1 ERROR en utn_getNumberInt(); /
 * 			int -2 ERROR en ll_clear(); /
 * 			int -3 ERROR en ll_deleteLinkedList(); /
 * 			int 0 OK
 */
int controller_deleteListCliente(LinkedList* this)
{
	int retorno = -1;
	int option;
	if(this != NULL)
	{
		if(utn_getNumberInt("\nYa hay una lista cargada.\n"
							"Desea eliminar la lista cargada?\n"
							"1-SI\n"
							"2-NO\n", "Error, ingrese 1 - 2", &option, 2, 1, 2)==0)
		{
			if(option == 1)
			{
				if(ll_clear(this) == 0)
				{
	    			if(ll_deleteLinkedList(this)==0)
	    			{
	    				printf(	"\nLista eliminada con exito\n"
	    						"Volviendo al MENÚ\n\n"
	    						"Ahora puede cargar otra lista en la opción 1 o 2\n\n");
	    				retorno = 0;
	    			}
					else
					{
						retorno = -3;
						printf("ERROR EN LL_DELETELINKEDLIST\n");
					}
				}
				else
				{
					retorno = -2;
					printf("ERROR EN LL_CLEAR\n");
				}
			}
		}
	}
	return retorno;
}
/*
 * \brief 	Recorre la lista buscando el id maximo
 * \param 	LinkedList* this
 * \return 	int -1 ERROR this == NULL /
 * 			int maximoId + 1 OK
*/
int controller_encontrarProximoId(LinkedList* this)
{
    int retorno=-1;
    int auxId;
    int maximoId;
    Cliente * auxCliente;
    int len = ll_len(this);
    if (this!=NULL)
    {
        for (int i = 0;i<len;i++)
        {
        	auxCliente=ll_get(this, i);
            cliente_getId(auxCliente, &auxId);
            if (i==1||auxId>maximoId)
            {
            	maximoId = auxId;
                retorno = maximoId+1;
            }
        }
    }
    return retorno;
}

int controller_encontrarProximoIdVentas(LinkedList* this)
{
    int retorno=-1;
    int auxId;
    int maximoId;
    Ventas* auxVentas;
    int len = ll_len(this);
    if (this!=NULL)
    {
        for (int i = 0;i<len;i++)
        {
        	auxVentas=ll_get(this, i);
            ventas_getId(auxVentas, &auxId);
            if (i==1||auxId>maximoId)
            {
            	maximoId = auxId;
                retorno = maximoId+1;
            }
        }
    }
    return retorno;
}
/*
 *
 */
int controller_saveAsTextCobradas(char* path, LinkedList* thisA, LinkedList* thisB, int estado )
{
	int retorno = -1;
	int length = ll_len(thisA);
	Cliente* pCliente = cliente_new();
	FILE* pFile;
	char auxNombre[LONG_NAME];
	char auxApellido[LONG_NAME];
	char auxCuit[LONG_NAME];
	char auxId[LONG_NUMBER_VALUE];
	int i;
	int ventasCobradas;
	int ventasSinCobrar;
	int idInt;
	if( pCliente != NULL && thisA != NULL && thisB != NULL && path != NULL && (estado == 1 || estado == 0))
	{
		pFile = fopen(path, "w");
		fprintf(pFile, "id_cliente,Nombre,Apellido,Cuit,cantidad_de_ventas\n");
		for(i= 0; i < length; i++)
		{
			pCliente = ll_get(thisA, i);
			if(	cliente_getIdTxt(pCliente, auxId) == 0 					&&
				cliente_getId(pCliente, &idInt) == 0 				&&
				cliente_getNombre(pCliente, auxNombre) == 0 			&&
				cliente_getApellido(pCliente, auxApellido) == 0		&&
				cliente_getCuit(pCliente, auxCuit) == 0 )
			{
				if(estado == 1)
				{

					ventasCobradas = ll_reduceIntDual(thisB, findCobradas, &idInt);
					fprintf(pFile, "%s,%s,%s,%s,%d\n",auxId, auxNombre, auxApellido, auxCuit,ventasCobradas );
					printf("ventas Cobradas: %d - %s\n", ventasCobradas,auxNombre);
				}
				else
				{
					if(estado == 0)
					{
						ventasSinCobrar = ll_reduceIntDual(thisB, findACobrar, &idInt);
						fprintf(pFile, "%s,%s,%s,%s,%d\n",auxId, auxNombre, auxApellido, auxCuit, ventasSinCobrar );
						printf("ventas sin cobrar: %d - %s\n", ventasSinCobrar, auxNombre);
					}
				}
				retorno = 0;
			}
		}
		fclose(pFile);
	}
	return retorno;
}

int findCobradas(void* pElemento, void* id)
{
	int retorno = -1;
	int estadoInt;
	int idClienteInt;
	int* auxId = (int*)id;
	Ventas* pVentas = (Ventas*)pElemento;
	if(pVentas != NULL && *auxId > 0)
	{
		ventas_getACobrar(pVentas, &estadoInt);
		ventas_getIdCliente(pVentas, &idClienteInt);
		if(estadoInt == 0 && idClienteInt == *auxId )
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}
int findACobrar(void* pElemento, void* id)
{
	int retorno = -1;
	int estadoInt;
	int idClienteInt;
	int* auxId = (int*)id;
	Ventas* pVentas = (Ventas*)pElemento;
	if(pVentas != NULL && *auxId > 0)
	{
		//printf("auxId %d\n", *auxId);
		ventas_getACobrar(pVentas, &estadoInt);
		ventas_getIdCliente(pVentas, &idClienteInt);
		if(estadoInt == 1 && idClienteInt == *auxId )
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

int controller_clienteMaxMinAfiches(LinkedList* thisA, LinkedList* thisB, int filtro )
{
	int retorno = -1;
	if(thisA != NULL && thisB != NULL && (filtro == 1 || filtro == 0))
	{
		if(informes_findMaxAndMin(thisA, thisB, filtro)==0)
		{
			retorno = 0;
		}
	}
	return retorno;
}
/*
 *
 */
int controller_ventaMaxCantidadAfiches(LinkedList* thisA, LinkedList* thisB)
{
	int retorno = -1;
	if(thisA != NULL && thisB != NULL)
	{
		/*
		if(informes_maxCantAficheEnVenta(thisA, thisB)==0)
		{
			retorno = 0;
		}
		*/
		if(informes_CANTIDADAFICHESMAXIMOSPORVENTA(thisA, thisB, 0) == 0)
		{
			retorno = 0;
		}
	}

	return retorno;
}

















