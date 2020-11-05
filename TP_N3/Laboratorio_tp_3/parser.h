/*
 * parser.h
 *
 *  Created on: 3 nov. 2020
 *      Author: Nico
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);


#endif /* PARSER_H_ */
