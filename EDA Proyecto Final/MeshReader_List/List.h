/*
 * List.h
 *
 *  Created on: 08/04/2016
 *      Author: LGUTIERREZ
 */

#ifndef LIST_H_
#define LIST_H_

typedef void* Type;
typedef struct strList* List;

//PARA ITERADORES
typedef struct strNode* Iterator;
typedef enum {FALSE, TRUE} bool;


//Crea un ejemplar List con memoria din�mica
//y asigna NULL, NULL y 0 a sus elementos.
List list_create();

//Elimina a todos los nodos y a la lista.
void lista_destroy(List);

//Extrae el tama�o de la lista.
int  list_size(List);

//Agrega un elemento al final de la lista.
//Incrementa el tama�o en uno
void list_add(List, Type);

//Devuelve el elemento en la posici�n p.
Type list_get(List, int p);

//Reemplaza el elemento en la posici�n p por el valor recibido.
void list_set(List, Type, int p);

//Elimina y devuelve el elemento en la 	posici�n p.
//Decrementa el tama�o en uno.
Type list_remove(List, int p);

///***********************ITERADORES *******************************

//Devuelve el iterador al pre-inicio.
Iterator list_begin(List);

//Devuelve al post-final.
Iterator list_end(List);

//Devuelve TRUE s�lo si hay un nodo siguiente.
bool list_hasNext(Iterator);

//Devuelve TRUE s�lo si hay un nodo anterior.
bool list_hasPrior(Iterator);

//Devuelve un iterador a la posici�n siguiente.
Iterator list_next(Iterator);

//Devuelve un iterador a la posici�n anterior.
Iterator list_prior(Iterator);

//Devuelve el dato referido por el iterador.
Type list_data(Iterator);




#endif /* LIST_H_ */

