#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	int length;
	Node* nodoParaDevolver = NULL;
	if(this != NULL  )
	{
		length = ll_len(this);
		nodoParaDevolver = (Node*) malloc(sizeof(Node));
		if(nodoParaDevolver!=NULL && nodeIndex < length && nodeIndex >= 0)
		{
			nodoParaDevolver = this->pFirstNode; // nodeIndex = 0; termina aca no entra al for y todo joya xq devulve la direccion de memoria del primer nodo
			for(i=0; i < nodeIndex; i++)
			{
				nodoParaDevolver = nodoParaDevolver->pNextNode;
			}
		}
	}
    return nodoParaDevolver;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	if(this != NULL && nodeIndex >= 0 && nodeIndex < this->size)
	{
		pNode = getNode(this, nodeIndex);
	}
	return pNode;
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int length;
    Node* pNuevoNode = (Node*)malloc(sizeof(Node));
    Node* pPrevioNodo;
    if(this != NULL && (nodeIndex <= this->size) && (nodeIndex >= 0 ) && pNuevoNode != NULL)
    {
    	length = ll_len(this);
    	pNuevoNode->pElement = pElement; 	//asigno al campo pElement del nuevo Nodo generado guardarle el *pElement recibido como argumento
    	//Identifico donde quiero agregar el NODO
    	if(nodeIndex == 0)
    	{//AL PRINCIPIO
    		pNuevoNode->pNextNode = this->pFirstNode;
    		this->pFirstNode = pNuevoNode;
    	}
    	else if(nodeIndex == length)
    	{//AL FINAL
    		pPrevioNodo = getNode(this, nodeIndex - 1);
    		pPrevioNodo->pNextNode = pNuevoNode;
    		pNuevoNode->pNextNode = NULL;
    	}
    	else
    	{//EN EL MEDIO
    		pPrevioNodo = getNode(this, nodeIndex - 1);
    		pNuevoNode->pNextNode = pPrevioNodo->pNextNode;
    		pPrevioNodo->pNextNode = pNuevoNode;
    	}
    	this->size++;
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param 	pList LinkedList* Puntero a la lista
 * \param 	pElement void* Puntero al elemento a ser agregado
 * \return 	int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int length;
    Node* pNuevoNode = (Node*)malloc(sizeof(Node));
    if(this != NULL )
    {
    	length = this->size;
    	if(pNuevoNode != NULL)
    	{
    		returnAux = addNode(this, length, pElement);
    	}
    }
    return returnAux;
}

/** \brief Devuelve el pElement buscado en el indice psado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int length;
    Node* pNodoADevolver;
    if(this != NULL && index >= 0)
    {
    	length = ll_len(this);
    	if(index < length)
    	{
        	pNodoADevolver = getNode(this, index);
        	if(pNodoADevolver != NULL)
        	{
            	returnAux = pNodoADevolver->pElement;
        	}
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int length;
    Node* retornoElemento = NULL;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(index >= 0 && index < length)
    	{
    		retornoElemento = getNode(this, index);
    		if(retornoElemento != NULL)
    		{
    			retornoElemento->pElement = pElement;
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int length;
    Node* pNodo = NULL;
    Node* pPrevioNodo = NULL;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(index >= 0 && index < length)
    	{
    		pNodo = getNode(this, index);
    		if(pNodo != NULL && index == 0)
    		{
    			this->pFirstNode = pNodo->pNextNode;
    		}
    		else
    		{
    			pPrevioNodo = getNode(this, (index - 1)); //Se le resta 1 para obtener el NODO PREVIO
    			if(pPrevioNodo != NULL)
    			{
    				pPrevioNodo->pNextNode = pNodo->pNextNode;
    			}
    		}
    		free(pNodo);
    		this->size--;
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int length;
    int i;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(length > 0)
    	{
    		for(i=0; i < length; i++)
    		{
    			ll_remove(this, i);
    		}
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int length;
    Node* pNodoAux;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(length > 0)
    	{
    		for(i = 0; i < length; i++)
    		{
    			pNodoAux = getNode(this, i);
    			if(pNodoAux->pElement == pElement)
    			{
    				returnAux = i;
    				break;
    			}
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int length;
    if(this != NULL)
    {
    	returnAux = 1;
    	length = ll_len(this);
    	//printf("LENGTH DE LA LISTA ENVIO: %d\n", length);
    	if(length > 0)
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int length;
    if(this != NULL )
    {
    	length = ll_len(this);
    	if(index >= 0 && index <= length)
    	{
    		if(addNode(this, index, pElement)==0)
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int nodeIndex)
{
    void* returnAux = NULL;
    int length;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(nodeIndex >= 0 && nodeIndex < length)
    	{
    		returnAux = ll_get(this, nodeIndex);
    		ll_remove(this, nodeIndex);
    	}
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int length;
    int i;
    Node* pNodoAux = NULL;
    if(this != NULL)
    {
    	returnAux = 0;
    	length = ll_len(this);
    	if(length > 0)
    	{
    		for(i = 0; i < length; i++)
    		{
    			pNodoAux = getNode(this, i);
    			if(pNodoAux->pElement == pElement)
    			{
    				returnAux = 1;
    				break;
    			}
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int length;
    void* pAuxElemento = NULL;
    int i;
    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	length = ll_len(this2);
    	if(length > 0 )
    	{
    		for(i = 0; i < length; i++)
    		{
    			pAuxElemento = ll_get(this2, i);
    			if(pAuxElemento != NULL)
    			{
    				if(ll_contains(this, pAuxElemento)==0)
    				{
    					returnAux = 0;
    					break;
    				}
    			}
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    Node* pAuxiliar = NULL;
    int length;
    int i;
    if(this != NULL && from >= 0 && to > from)
    {
    	length = ll_len(this);
    	if(length > 0 && from < length && to <= length)
    	{
    		cloneArray = ll_newLinkedList();
    		for( i = from; i < to; i++)
    		{
    			pAuxiliar = ll_get(this, i);
    			ll_add(cloneArray, pAuxiliar);
    		}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    Node* pAuxiliar = NULL;
    int length;
    int i;
    if(this != NULL)
    {
    	length = ll_len(this);
    	if(length > 0 )
    	{
    		cloneArray = ll_newLinkedList();
    		for( i = 0; i < length; i++)
    		{
    			pAuxiliar = ll_get(this, i);
    			ll_add(cloneArray, pAuxiliar);
    		}
    	}
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    Node* pElementA=NULL;
    Node* pElementB=NULL;
    int i;
    int length;
    int nuevoLimite;
    int flagSwap;
    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
    {
    	returnAux = 0;
    	length = ll_len(this);
    	if(length > 0)
    	{
    		nuevoLimite = length - 1;
    		do
    		{
    			flagSwap=0;
            	for(i=0; i < nuevoLimite; i++)
            	{
            		pElementA = ll_get(this, i);
            		pElementB = ll_get(this, i + 1);
            		if(	(order == 1 && pFunc(pElementA, pElementB) > 0) ||
            			(order == 0 && pFunc(pElementA, pElementB) < 0)	)
            		{
            			ll_set(this, i, pElementB);
            			ll_set(this, i + 1, pElementA);
            			flagSwap=1;
            		}
            	}
            	nuevoLimite--;
    		}while(flagSwap);
    	}
    }
    return returnAux;
}
/*
 *agarra cada uno de los elementos pasados y se los pasa a una funcion criterio
 *CADA llamada a funcion se realiza en forma independiente
 *retorna 0 todo ok / -2 la funcion criterio la cago
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int retorno = -1;
	int length;
	int i;
	void* pElemento;
	if(this != NULL && pFunc != NULL)
	{
		retorno = 0;
		length = ll_len(this);
		for(i=0; i < length; i++)
		{
			pElemento = ll_get(this, i);
			if(pFunc(pElemento) == -2)
			{
				printf("ERROR EN LA FUNCION CRITERIO EN MAP\n");
				break;
			}
		}
	}
	return retorno;
}
/*
 * RETORNA EL VALOR QUE DEVUUELVE LA FUNCION CRITERIO
 * retorno = 0 / si paso las validadiones de parametros pero la criterio no encontro nada
 * EJ: retorno = pFunc(pElemento, elemento);
 * 		if( retorno > 0) -> break;
 */
int ll_mapComparar(LinkedList* this, int (*pFunc)(void*, void*), void* elemento)
{
	int retorno = -1;
	int length;
	int i;
	void* pElemento;
	if(this != NULL && pFunc != NULL)
	{
		retorno = 0;
		length = ll_len(this);
		for(i=0; i < length; i++)
		{
			pElemento = ll_get(this, i);
			retorno = pFunc(pElemento, elemento);
			if( retorno == -2)
			{
				printf("ERROR EN LA FUNCION CRITERIO EN MAP\n");
				break;
			}
			else
			{
				if(retorno > 0)
				{
					break;
				}
			}
		}
	}
	return retorno;
}
/*
 *
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int retorno = -1;
	int length;
	int i;
	void* pElementAux = NULL;
	if(this != NULL && pFunc != NULL)
	{
		retorno = 0;
		length = ll_len(this);
		if(length > 0)
		{
			for(i=0; i < length; i++)
			{
				pElementAux = ll_get(this, i);
				if(pFunc(pElementAux) > 0)
				{
					ll_remove(this, i);
					length = ll_len(this); //se decremento el valor del size por eso vuelvo a llamar a la funcion ll_len
					i--;
				}
			}
		}
	}
	return retorno;
}
LinkedList* ll_filterRetornoList(LinkedList* this, int (*pFunc)(void*))
{
	int length;
	LinkedList* listaRetorno = NULL;
	int i;
	void* pElementAux = NULL;
	if(this != NULL && pFunc != NULL)
	{
		length = ll_len(this);
		if(length > 0)
		{
			for(i=0; i < length; i++)
			{
				pElementAux = ll_get(this, i);
				if(pFunc(pElementAux) > 0)
				{
					ll_remove(this, i);
					length = ll_len(this); //se decremento el valor del size por eso vuelvo a llamar a la funcion ll_len
					i--;
				}
			}
			listaRetorno = ll_clone(this);
		}
	}
	return listaRetorno;
}

/*
 * ACUMULAN EL VALOR OBTENIDO POR LA FUNCION CRITERIO
 * EJ: LA FUNC CRITE DEVUELVE 1 CADA VEZ Q ENCUENTRA ALGO Y LA REDUCE LOS VA SUMANDO
 * Y TE DICE AL FINAL CUANTOS SON
 * Y LO DEVUELVEN POR RETURN
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*))
{
	int retorno = -1;
	int acumulador = 0;
	int length;
	int i;
	void* pElemento;
	if(this != NULL && pFunc != NULL)
	{
		length = ll_len(this);
		for(i=0; i < length; i++)
		{
			pElemento = ll_get(this, i);
			if(pFunc(pElemento) == -1)
			{
				printf("ERROR EN LA FUNCION CRITERIO EN reduce\n");
				break;
			}
			else
			{
				acumulador = acumulador + pFunc(pElemento);
			}
		}
		retorno = acumulador;
	}
	return retorno;

}
/*
 *
 */
float ll_reduceFloat(LinkedList* this, float (*pFunc)(void*))
{
	int retorno = -1;

	return retorno;
}
/*
 *
 */
int ll_reduceIntDual(LinkedList* this, int (*pFunc)(void*, void*), void* parametroElemento)
{
	int retorno = -1;
	int length = ll_len(this);
	int acumulador = 0;
	int i;
	void* pElemento;
	if(this != NULL)
	{
		for(i = 0; i < length; i++)
		{
			pElemento = ll_get(this, i);
			if(pFunc(pElemento, parametroElemento) == -1)
			{
				printf("ERROR EN LA FUNCION CRITERIO EN reduce\n");
				break;
			}
			else
			{
				acumulador = acumulador + pFunc(pElemento, parametroElemento);
			}
		}
		retorno = acumulador;
	}
	return retorno;
}






