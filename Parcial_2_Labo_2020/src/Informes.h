/*
 * Informes.h
 *
 *  Created on: 25 nov. 2020
 *      Author: Nico
 */

#ifndef INFORMES_H_
#define INFORMES_H_
int informes_findMaxAndMin(LinkedList* thisCliente, LinkedList* thisVentas, int filtro);
int contadorAfiches(void* pElemento, void* id);
int contadorAfichesPorVenta(void* pElemento, void* id);
int informes_CANTIDADAFICHESMAXIMOSPORVENTA(LinkedList* thisCliente, LinkedList* thisVentas, int filtro);
#endif /* INFORMES_H_ */
