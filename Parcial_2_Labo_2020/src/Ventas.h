/*
 * Ventas.h
 *
 *  Created on: 23 nov. 2020
 *      Author: Nico
 */

#ifndef VENTAS_H_
#define VENTAS_H_
static const char ESTADO[2][LONG_NAME] = {"Cobrada", "A cobrar"};
static const char ZONA[3][LONG_NAME] = {"CABA", "ZONA SUR", "ZONA OESTE"};
	typedef struct{
		char nombre[LONG_NAME];
		char zona[LONG_NAME];
		int idCliente;
		int cantidadAfiches;
		int id;
		int aCobrar;
	}Ventas;

	Ventas* ventas_new(void);
	Ventas* ventas_newParametrosTxt(char* id, char* aCobrar, char* idCliente, char* cantidadAfiches, char* nombre, char* zona);
	Ventas* ventas_newParametros(int* id, int* aCobrar, int* idCliente, int* cantidadAfiches, char* nombre, char* zona);
	void ventas_delete(Ventas* this);
	int ventas_getIdCliente(Ventas* this, int* idCliente);
	int ventas_setIdCliente(Ventas* this, int* idCliente);
	int isValidIdCliente(int* idCliente);
	int ventas_getCantidadAfiches(Ventas* this, int* cantidadAfiches);
	int ventas_setCantidadAfiches(Ventas* this, int* cantidadAfiches);
	int isValidCantidadAfiches(int* cantidadAfiches);
	int ventas_getNombre(Ventas* this, char* nombre);
	int ventas_setNombre(Ventas* this, char* nombre);
	int isValidNombreAfiche(char* nombre);
	int ventas_getZona(Ventas* this, char* zona);
	int ventas_setZona(Ventas* this, char* zona);
	int isValidZona(char* zona);
	int ventas_getIdClienteTxt(Ventas* this, char* idCliente);
	int ventas_setIdClienteTxt(Ventas* this, char* idCliente);
	int ventas_getCantidadAfichesTxt(Ventas* this, char* cantidadAfiches);
	int ventas_setCantidadAfichesTxt(Ventas* this, char* cantidadAfiches);
	int ventas_setId(Ventas* this, int* id);
	int ventas_getId(Ventas* this, int* id);
	int ventas_setIdTxt(Ventas* this, char* id);
	int ventas_getIdTxt(Ventas* this, char* id);
	int ventas_setACobrarTxt(Ventas* this, char* aCobrar);
	int ventas_getACobrarTxt(Ventas* this, char* aCobrar);
	int ventas_setACobrar(Ventas* this, int* aCobrar);
	int ventas_getACobrar(Ventas* this, int* aCobrar);
	int ventas_buscarIdCliente(LinkedList* this, int length, char* idCliente);
	int ventas_imprimirListaACobrar(void* this);
	int ventas_obtenerIdCliente(void* this, void* elemento);
	int ventas_imprimirListaACobrarParametro(void* this, void* pArgumento);
	int findCobradas(void* pElemento, void* id);
	int findACobrar(void* pElemento, void* id);
	int soloSinCobrar(void* pElemento);
	int ventas_cobradas(void* pElemento);
	//int contadorCantidadAfichesPorVenta(void* this);
#endif /* VENTAS_H_ */
