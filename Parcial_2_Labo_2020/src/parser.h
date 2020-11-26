/*
 * parser.h
 *
 *  Created on: 3 nov. 2020
 *      Author: Nico
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_ClienteFromText(FILE* pFile , LinkedList* this);
int parser_ventasFromText(FILE* pFile , LinkedList* this);
/*
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* this);
*/

#endif /* PARSER_H_ */
