#ifndef CONTROLLER_H_
#define CONTROLLER_H_
	int controller_loadFromTextCliente(char* path , LinkedList* this);
	int controller_loadFromTextVentas(char* path , LinkedList* this);
	/*
	int controller_loadFromBinary(char* path , LinkedList* this);
	*/
	int controller_addCliente(LinkedList* this);
	int controller_addVentas(LinkedList* this, LinkedList* thisB);
	int controller_editCliente(LinkedList* this);
	int controller_editVentas(LinkedList* thisA, LinkedList* thisB);
	int controller_editVentasEstado(LinkedList* thisA, LinkedList* thisB );
	int controller_removeCliente(LinkedList* this);
	int controller_ListCliente(LinkedList* this);
	int controller_sortCliente(LinkedList* this);
	int controller_saveAsTextCliente(char* path , LinkedList* this);
	int controller_saveAsTextVentas(char* path , LinkedList* this);
	/*
	int controller_saveAsBinary(char* path , LinkedList* this);
	*/

	int controller_deleteListCliente(LinkedList* this);
	int controller_encontrarProximoId(LinkedList* this);
	int controller_encontrarProximoIdVentas(LinkedList* this);

	int controller_filtrarCliente(LinkedList* this);
	int controller_saveAsTextCobradas(char* path, LinkedList* thisA, LinkedList* thisB, int estado );
	int findCobradas(void* pElemento, void* id);
	int findACobrar(void* pElemento, void* id);
	int controller_clienteMaxMinAfiches(LinkedList* thisA, LinkedList* thisB, int filtro );
	int controller_ventaMaxCantidadAfiches(LinkedList* thisA, LinkedList* thisB);



	int soloSinCobrar(void* pElemento);
#endif /* CONTROLLER_H_ */
