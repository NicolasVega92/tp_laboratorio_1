/*
 * Informes.h
 *
 *  Created on: 25 nov. 2020
 *      Author: Nico
 */

#ifndef INFORMES_H_
#define INFORMES_H_
int informe_imprimirClienteConMasCobros(LinkedList* thisA, LinkedList* thisB, int filtro);
int informes_findMaxAndMin(LinkedList* thisCliente, LinkedList* thisVentas, int filtro);
int contadorAfiches(void* pElemento, void* id);
int cliente_imprimirPorId(void* this, void* elemento);
int ventas_cobradas(void* pElemento);
int informes_maxCantAficheEnVenta(LinkedList* thisCliente, LinkedList* thisVentas);
int contadorCantidadAfichesPorVenta(void* this);
int informes_CANTIDADAFICHESMAXIMOSPORVENTA(LinkedList* thisCliente, LinkedList* thisVentas, int filtro);
#endif /* INFORMES_H_ */
