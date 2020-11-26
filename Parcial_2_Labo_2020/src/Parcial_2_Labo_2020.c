#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "Cliente.h"
#include "Ventas.h"
#include "Controller.h"
#include "Informes.h"
int main(void) {
	setbuf(stdout, NULL);
	int opcion;
	int opcionInforme;
	LinkedList* listaCliente = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();

	if(	(controller_loadFromTextCliente("cliente-data.csv",listaCliente)==0) &&
		(controller_loadFromTextVentas("ventas-data.csv", listaVentas) == 0))
	{
		do
		{
			if(utn_getNumberInt("\n******************************************************************************\n"
								"INGRESE UNA OPCION:\n"
								"1-Agregar Cliente\n"
								"2-Vender Afiches\n"
								"3-Modificar Afiches\n"
								"4-Cobrar Venta\n"
								"5-Generar informe de cobros\n"
								"6-Generar informe de deudas\n"
								"7-Generar estadísticas\n"
								"8-Salir\n", "Error: ingrese 1 - 8\n", &opcion, 3, 1, 8)==0)
			{
				switch(opcion)
				{
					case 1:
						if(ll_isEmpty(listaCliente)==0)
						{
							if(controller_addCliente(listaCliente)==0)
							{
								printf("\nOK ALTA Cliente\n");
								if(controller_saveAsTextCliente("cliente-data.csv", listaCliente) == 0)
								{
									printf("OK SAVE TEXT CLIENTE\n");
								}
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 2:
						if(ll_isEmpty(listaVentas)==0)
						{
							if(controller_addVentas(listaVentas, listaCliente)==0)
							{
								printf("\nOK ALTA VENTA\n");
								if(controller_saveAsTextVentas("ventas-data.csv", listaVentas) == 0)
								{
									printf("OK SAVE TEXT VENTA\n");
								}
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 3:
						if(ll_isEmpty(listaVentas)==0)
						{
							if(controller_editVentasConParametro(listaVentas, listaCliente, 0)==0)
							{
								printf("OK EDIT VENTAS\n");
								if(controller_saveAsTextVentas("ventas-data.csv", listaVentas) == 0)
								{
									printf("OK SAVE TEXT VENTA\n");
								}
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 4:
						if(ll_isEmpty(listaVentas)==0)
						{
							if(controller_editVentasConParametro(listaVentas, listaCliente, 1)==0)
							{
								printf("OK EDIT VENTAS\n");
								if(controller_saveAsTextVentas("ventas-data.csv", listaVentas) == 0)
								{
									printf("OK SAVE TEXT VENTA\n");
								}
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 5:
						if(ll_isEmpty(listaVentas)==0)
						{
							if(controller_saveAsTextCobradas("ventasCobradas.csv", listaCliente, listaVentas, 1) == 0)
							{
								printf("OK SAVE VENTAS COBRADAS\n");
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 6:
						if(ll_isEmpty(listaVentas)==0)
						{
							if(controller_saveAsTextCobradas("ventasSinCobrar.csv", listaCliente, listaVentas, 0) == 0)
							{
								printf("OK SAVE VENTAS SIN COBRAR\n");
							}
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					case 7:
						if(ll_isEmpty(listaVentas)==0)
						{
							do
							{
								if(utn_getNumberInt("Seleccione el informe a generar:\n"
													"1- Cliente con más AFICHES VENDIDOS.\n"
													"2- CLiente con menos AFICHES VENDIDOS\n"
													"3- Venta con mayor cantidad de AFICHES VENDIDOS.\n"
													"4- Salir\n", "ERROR. (1 - 4)\n", &opcionInforme, 2, 1, 4)==0)
								{
									switch(opcionInforme)
									{
									case 1:/*IMPRIMIR MAS COBRADAS*/
										if(controller_clienteMaxMinAfiches(listaCliente, listaVentas, 0)==0)
										{
											printf("OK INFORME 7.a\n");
										}
										break;
									case 2:/*IMPRIMIR MENOS COBRADAS*/
										if(controller_clienteMaxMinAfiches(listaCliente, listaVentas, 1)==0)
										{
											printf("OK INFORME 7.b\n");
										}
										break;
									case 3:/*VENTA CON MAS AFICHES VENDIDOS MOSTRAR ID VENTA Y CUIT CLIENTE*/
										if(controller_ventaMaxCantidadAfiches(listaCliente, listaVentas) == 0)
										{
											printf("OK INFORME 7.c\n");
										}
										break;
									}
								}
							}while(opcionInforme != 4);
						}
						else
						{
							printf("NO se cargo la lista\n");
						}
						break;
					}
				}
		}while(opcion != 8);
	}
	else
	{
		printf("No se cargo el archivo BESTIA\n");
	}
	return EXIT_SUCCESS;
}























