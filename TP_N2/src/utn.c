/*
 * utn.c
 *      Author: Nico
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "utn.h"
#include "ArrayEmployees.h"
static int isNumber(char cadena[]);
static int isPhone(char cadena[]);
static int isAlphNum(char cadena[]);
static int isOnlyLettersAndSpace(char cadena[]);
static int getInt(int* pResultado);
static int myGets(char array[], int longitud);
static int utn_itIsAValidName(char array[], int limite);
static int getFloat(float* pResultado);
static int isNumberFloat(char cadena[]);
static int isAlphNum(char cadena[]);
static int utn_lowerCharArray(char pArray[]);
static int utn_upperCaseFirstChar(char pArray[]);
/**
 * \brief Solicita un entero al usuario, luego de verificar devuelve el resultado
 * \param char* pMensaje, Es el mensaje mostrado al usuario
 * \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int maximo, valor maximo admitido
 * \return (-1) Error / (0) Ok
 */
int utn_getNumberInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo)
{
	int retorno = -1;
	int buffer;

	if(		pMensaje != NULL &&
			pMensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			minimo <= maximo)
	{
		do
		{
			printf("%s", pMensaje);
			fflush(stdin);
			if(getInt(&buffer) == 0 && buffer >= minimo && buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break; //Para terminar el bucle del do while
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}
		while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}
/**
 * \brief
 * \param pResultado Puntero al espacio de memoria donde se dejata el resultado de la funcion
 * \return Retorno 0 Exito si obtiene un numero entero / (-1) ERROR
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[LIMITE_BUFFER_STRING];
	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer))==0 && isNumber(buffer))
		{
			retorno = 0;
			*pResultado = atoi(buffer);
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isNumber(char cadena[])
{
	int retorno = 1;
	int i = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if(cadena[i] < '0' || cadena[i] > '9')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
/**
* \brief Solicita un float al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param float minimo, valor minimo admitido
* \param float maximo, valor maximo admitido
* \return (-1) Error / (0) Ok
*/
int utn_getNumberFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo)
{
	int retorno = -1;
	float bufferFloat;

	if(pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", pMensaje);
			fflush(stdin);
			if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}
/**
 * \brief
 * \param float* pResultado Puntero al espacio de memoria donde se dejata el resultado de la funcion
 * \return Retorno 0 Exito si obtiene un numero entero / (-1) ERROR
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[LIMITE_BUFFER_STRING];
	if(myGets(buffer, sizeof(buffer))==0 && isNumberFloat(buffer))
	{
		retorno = 0;
		*pResultado = atof(buffer);
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica y puede contener signo en el primer indice o ningun o 1 punto.
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isNumberFloat(char cadena[])
{
	int retorno = 1;
	int i = 0;
	int flagPunto = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] != '.'))
		{
			retorno = 0;
			break;
		}
		if(cadena[i] == '.')
		{
			flagPunto++;
		}
		if(flagPunto > 1)
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
/*
* \brief Solicita un nombre al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param limite indica la cantidad maxima del nombre
 * return (-1) ERROR / 0 OK
 */
int utn_getName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;
	if(pMensaje != NULL && pMensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(utn_itIsAValidName(bufferString, limite) != 0) &&
				(utn_upperCaseFirstChar(bufferString)==0))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos>=0);
		if(reintentos < 0)
		{
			printf("Te quedaste sin intentos\n");
		}
	}
	return retorno;
}
/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un maximo de 'longitud -1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 EXITO / (-1) ERROR
 */
static int myGets(char array[], int longitud)
{
	int retorno = -1;
	fflush(stdin);
	if(array != NULL && longitud > 0 && fgets(array, longitud, stdin)==array)
	{
		if(array[strlen(array)-1] == '\n')
		{
			array[strlen(array)-1] = '\0';
		}
		retorno=0;
	}
	return retorno;
}
/*
* \brief Verifica una cadena como parametro para determinar si es nombre valido
* \param char cadena[], cadena a analizar
* \param limite indica la cantidad maxima del nombre
 * return (1) Es válido / (0) No es un nombre valido
 */
static int utn_itIsAValidName(char array[], int limite)
{
	int retorno = 1; //TODO OK
	int i=0;
	if(array[i]=='\0')
	{
		retorno = 0;
	}
	else
	{
		for(i = 0; i <= limite && array[i] != '\0'; i++)
		{
			if(isOnlyLettersAndSpace(array) == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada son letras, espacios pero no puede haber mas de uno seguido, tampoco
 * 			empezar con espacio.
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isOnlyLettersAndSpace(char cadena[])
{
	int retorno = 1;
	int i=0;
	int flagSpace = FALSE;
	if(cadena[i]==' ')
	{
		retorno = 0;
	}
	else
	{
		for( ; cadena[i] != '\0'; i++)
		{
			if(flagSpace == TRUE)
			{
				if(cadena[i] == ' ')
				{
					retorno = 0;
					break;
				}
				else
				{
					flagSpace = FALSE;
				}
			}
			if((cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				(cadena[i] != ' ') &&
				(cadena[i] < 'á' || cadena[i] > 'ú') &&
				(cadena[i] != 'é'))
			{
				retorno = 0;
				break;
			}
			if(cadena[i] == ' ')
			{
				flagSpace = TRUE;
			}

		}
	}
	return retorno;
}
/*
* \brief Solicita un char al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param char minimo, valor minimo admitido
* \param char maximo, valor maximo admitido
 * return (-1) ERROR / 0 OK
 */
int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}
/*
* \brief Solicita numeros y 1 o ningun guión
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param int limite, cantidad de espacio que puede almacenar la variable
 * return (-1) ERROR / 0 OK
 */
int utn_getPhone(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(isPhone(bufferString)==1))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica o si contiene menos de 2 guiones
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isPhone(char cadena[])
{
	int retorno = 1;
	int i;
	int flagGuion = 0;

	for(i=0; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] != '-'))
		{
			retorno = 0;
			break;
		}
		if(cadena[i] == '-')
		{
			flagGuion++;
		}
	}
	if(flagGuion > 1)
	{
		retorno = 0;
	}
	return retorno;
}
/*
* \brief Solicita numeros, letras y espacio al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param int limite, cantidad de espacio que puede almacenar la variable
 * return (-1) ERROR / 0 OK
 */
int utn_getAlphaNum(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(isAlphNum(bufferString)==1))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena son numeros, letras con o sin tilde y espacio
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isAlphNum(char cadena[])
{
	int retorno = 1;
	int i;

	for(i=0 ; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é') &&
			(cadena[i] < '0' || cadena[i] > '9'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
/*
* \brief Ordena el array desde el valor minimo al maximo
* \param int pArray[], recibe el array a ordenar
* \param int limite, recibe la cantidad maxima de elementos
* \return (-1) ERROR / 0 OK
 */
int utn_sortMin(int pArray[], int limite)
{
	int retorno = -1;
	int bufferInt;
	int i;
	int flagOrdenado;
	if(pArray != NULL && limite > 0)
	{
		do
		{
			flagOrdenado = 0;
			for(i = 0; i < (limite - 1); i++)
			{
				if(pArray[i] > pArray[i+1])
				{
					//Intercambiar (swap)
					bufferInt = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1] = bufferInt;
					flagOrdenado = 1;
				}
			}
		}while(flagOrdenado);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Calcula el numero maximo del Array recibido como parametro
 * \param int pArray[], Array a ser procesado
 * \param int cantidadElementos, cantidad de elementos a ser procesados
 * \param int* pResultado, numero maximo del Array
 * \return (-1) Error / (0) Ok
 */
int utn_calculateMaximum(int pArray[], int cantidadElementos, int* pResultado)
{
	int retorno = -1;
	int maximo;
	if(pArray != NULL && cantidadElementos > 0 && pResultado != NULL)
	{
		for(int i = 0; i < cantidadElementos; i++)
		{
			if(i == 0 || pArray[i] > maximo)
			{
				maximo = pArray[i];
			}
		}
		*pResultado = maximo;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Calcula el numero minimo del Array recibido como parametro
 * \param int pArray[], Array a ser procesado
 * \param int cantidadElementos, cantidad de elementos a ser procesados
 * \param int* pResultado, numero minimo del Array
 * \return (-1) Error / (0) Ok
 */
int utn_calculateMinimum(int pArray[], int cantidadElementos, int* pResultado)
{
	int retorno = -1;
	int minimo;
	int i;

	if(pArray != NULL && cantidadElementos > 0 && pResultado != NULL)
	{
		for(i = 0; i < cantidadElementos; i++)
		{
			if(i == 0 || pArray[i] < minimo)
			{
				minimo = pArray[i];
			}
		}
		*pResultado = minimo;
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief Calcula el promedio de los elementos del Array recibido como parametro
 * \param int pArray[], Array a ser procesado
 * \param int cantidadElementos, cantidad de elementos a ser procesados
 * \param float* pResultado, numero promedio del array
 * \return (-1) Error / (0) Ok
 */
int utn_calculateAverage(int pArray[], int cantidadElementos, float* pResultado)
{
	int retorno = -1;
	int promedio;
	int i;
	int suma = 0;

	if(pArray != NULL && cantidadElementos > 0 && pResultado != NULL)
	{
		for(i = 0; i < cantidadElementos; i++)
		{
			suma += pArray[i];
		}
		promedio = (float)suma / i;
		*pResultado = promedio;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime a modo de DEBUG la info de un array de enteros
 * \param int pArray[] es el puntero al array a ser ordenado
 * \param int limite Es la longitud del array
 * \return 0 si OK o -1 para indicar error
 */
int utn_printArrayInt(int pArray[], int limite)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && limite >= 0)
	{
		retorno = 0;
		for(i=0; pArray[i] != '\0'; i++)
		{
			printf("[DEBUG] Indice: %d - Valor: %d\n", i, pArray[i]);
		}
		printf("\n");
	}
	return retorno;
}
/**
 * \brief Ordena un array de enteros de manera DESCENDENTE
 * \param int pArray[] es el puntero al array a ser ordenado
 * \param int limite Es la longitud del array
 * \return la cantidad de iteraciones si OK o -1 para indicar error
 */
int utn_sortArrayInt(int pArray[], int limite)
{
	int flagSwap;
	int i;
	int contador = 0;
	int retorno = -1;
	int buffer;
	int nuevoLimite;

	if(pArray != NULL && limite >= 0)
	{
		do
		{
			nuevoLimite = limite -1;
			flagSwap = 0;
			for(i = 0; i < nuevoLimite; i++)
			{
				contador++;
				if(pArray[i] < pArray[i+1])
				{
					flagSwap = 1;
					buffer = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = buffer;
				}
			}
			nuevoLimite--;
			retorno = contador;
		}while(flagSwap);
	}
	return retorno;
}
/**
 * \brief Cuenta cuantos elementos pasados como 3er parametro se encuentran dentro del array
 * 			e imprime msj con el valor contado o que no hay ninguno
 * \param int pArray[] es el puntero al array a ser analizado
 * \param int limite Es la longitud del array
 * \param int numero es el numero a ser contado dentro del array
 * \return 0 OK / -1 para indicar error
 */
int utn_countInt(int pArray[], int limite, int numero)
{
	int retorno = -1;
	int i;
	int contadorNumero = 0;

	if(pArray != NULL && limite > 0)
	{
		for(i=0; pArray[i] != '\0'; i++)
		{

			if(pArray[i] == numero)
			{
				contadorNumero++;
			}
		}
		retorno = 0;
		if(contadorNumero > 0)
		{
			printf("La cantidad de %d es: %d\n",numero, contadorNumero);
		}
		else
		{
			printf("No hubo ocurrencias con el elemento %d\n", numero);
		}
	}
	return retorno;
}
/**
 * \brief Cuenta cuantos elementos pasados como 3er parametro se encuentran dentro del array
 * 		   y los devuelve por referencia a una direccion de memoria
 * \param int pArray[] es el puntero al array a ser analizado
 * \param int limite Es la longitud del array
 * \param int numero es el numero a ser contado dentro del array
 * \param int* pDireccion puntero a la direccion de memoria de la variable a ser guardada
 * \return 0 OK / -1 para indicar error
 */
int utn_countIntByReference(int pArray[], int limite, int numero, int* pDireccion)
{
	int retorno = -1;
	int i;
	int contadorNumero = 0;

	if(pArray != NULL && limite > 0 && pDireccion != NULL )
	{
		for(i=0; pArray[i] != '\0'; i++)
		{

			if(pArray[i] == numero)
			{
				contadorNumero++;
			}
		}
		*pDireccion = contadorNumero;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Cuenta cuantos elementos pasados como 3er parametro se encuentran dentro del array
 * 		   y los devuelve por referencia a una direccion de memoria
 * \param char pArray[] es el puntero al array a ser analizado
 * \param int limite Es la longitud del array
 * \param char elemento es el elemento a ser contado dentro del array
 * \param int* pDireccion puntero a la direccion de memoria de la variable a ser guardada
 * \return 0 OK / -1 para indicar error
 */
int utn_countCharByReference(char pArray[], char elemento, int* pElemento)
{
	int retorno = -1;
	int i;
	int contadorElemento = 0;

	if(pArray != NULL && pElemento != NULL)
	{
		for(i=0; pArray[i] != '\0'; i++)
		{
			if(pArray[i] == elemento)
			{
				contadorElemento++;
			}
		}
		*pElemento = contadorElemento;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Recibe una cadena de chars y la devuelve toda con LowerCase
 * \param char pArray[] es el puntero al array a ser analizado
 * \return 0 OK / -1 Error
 */
static int utn_lowerCharArray(char pArray[])
{
	int retorno = -1;
	char bufferChar;
	int i;
	if(pArray!=NULL)
	{
		for(i=0; pArray[i]!= '\0';i++)
		{
			if(pArray[i] >= 'A' && pArray[i] <= 'Z')
			{
				bufferChar = tolower(pArray[i]);
				pArray[i]=bufferChar;
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Recibe una cadena de chars devuelve la Primer letra en UpperCase y si tiene
 * 			algun espacio devuelve la siguiente letra con mayus
 * \param char pArray[] es el puntero al array a ser analizado
 * \return 0 OK / -1 Error
 */
static int utn_upperCaseFirstChar(char pArray[])
{
	int retorno=-1;
	int i;
	int flagSpace = 0;
	if(pArray!=NULL)
	{
		if(utn_lowerCharArray(pArray)==0)
		{
			pArray[0] = toupper(pArray[0]);
		}
		for(i=1; pArray[i]!= '\0';i++)
		{
			if(pArray[i] == ' ')
			{
				flagSpace++;
			}
			else
			{
				if(flagSpace > 0)
				{
					pArray[i] = toupper(pArray[i]);
					flagSpace--;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}






