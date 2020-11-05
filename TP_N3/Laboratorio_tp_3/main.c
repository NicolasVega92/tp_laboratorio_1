#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
	setbuf(stdout,NULL);

    int option;
    int listaCargada = FALSE;
    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
		if(utn_getNumberInt("******************************************************************************\n"
							"Ingrese opcion:\n"
							"1-Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
							"2-Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
							"3-Alta de empleado\n"
							"4-Modificar datos de empleado\n"
							"5-Baja de empleado\n"
							"6-Listar empleados\n"
							"7-Ordenar empleados\n"
							"8-Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
							"9-Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
							"10-Salir\n", "Error en la opcion ingresada\n", &option, 3, 1, 12)==0)
        {
			switch(option)
			{
            case 1://HACER logica para el MAXIMO ID CUANDO LEE
                if(listaCargada == FALSE)
                {
                	if(controller_loadFromText("data.csv",listaEmpleados)==0)
                    {
                    	listaCargada = TRUE;
                    	printf("OK CARGA TEXTO\n");
                    }
                }
                else
                {
                	if(controller_deleteListEmployee(listaEmpleados)==0)
                	{
            			listaCargada = FALSE;
            			listaEmpleados = ll_newLinkedList();
                	}
                }
                break;
            case 2://HACER LOGICA PARA EL MAXIMO ID CUANDO LEE
                if(listaCargada == FALSE)
                {
					if(controller_loadFromBinary("data2.csv", listaEmpleados)==0)
					{
						listaCargada = TRUE;
						printf("OK CARGA BINARIA\n");
					}
                }
                else
                {
                	if(controller_deleteListEmployee(listaEmpleados)==0)
                	{
            			listaCargada = FALSE;
            			listaEmpleados = ll_newLinkedList();
                	}
                }
                break;
            case 3:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
    				if(controller_addEmployee(listaEmpleados)==0)
    				{
    					printf("OK ALTA\n");
    				}
            	}
            	else
            	{
            		printf(ERROR_NOT_LOADED_LIST);
            	}

            	break;
            case 4:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		if(controller_editEmployee(listaEmpleados)==0)
            		{
            			printf("OK MODIFICACION\n");
            		}
            	}
            	else
            	{
            		printf(ERROR_NOT_LOADED_LIST);
            	}
                break;
            case 5:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		if(controller_removeEmployee(listaEmpleados)==0)
            		{
            			printf("OK REMOVIDO\n");
            		}
        		}
        		else
        		{
        			printf(ERROR_NOT_LOADED_LIST);
        		}
                break;
            case 6:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
					if(controller_ListEmployee(listaEmpleados)==0)
					{
						printf("OK PRINT\n");
					}
        		}
        		else
        		{
        			printf(ERROR_NOT_LOADED_LIST);
        		}
                break;
            case 7:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
            		if(controller_sortEmployee(listaEmpleados)==0)
            		{
            			printf("OK PRINT\n");
            		}
        		}
        		else
        		{
        			printf(ERROR_NOT_LOADED_LIST);
        		}
            	break;
            case 8:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
					if(controller_saveAsText("data.csv", listaEmpleados)==0)
					{
						printf("OK GUARDADO TEXTO\n");
					}
        		}
        		else
        		{
        			printf(ERROR_NOT_LOADED_LIST);
        		}
                break;
            case 9:
            	if(ll_isEmpty(listaEmpleados)==0)
            	{
					if(controller_saveAsBinary("data2.csv", listaEmpleados)==0)
					{
						printf("OK SAVE BINARY\n");
					}
        		}
        		else
        		{
        			printf(ERROR_NOT_LOADED_LIST);
        		}
                break;
			}
        }
    }while(option != 10);
    return EXIT_SUCCESS;
}

