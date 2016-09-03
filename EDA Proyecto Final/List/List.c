/*
 * List.c
 *
 *  Created on: 08/04/2016
 *      Author: LGUTIERREZ
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

struct strNode {
	Type data;
	struct strNode *prior, *next;
};
typedef struct strNode* Node;


struct strList {
	struct strNode *first, *last; //t
	struct strNode *preFirst, *postLast;
	int size;
};


//Crea un ejemplar List con memoria dinámica
//y asigna NULL, NULL y 0 a sus elementos.
List list_create(){
  List l = (List) malloc(sizeof(struct strList));
  l->first = NULL;
  l->last = NULL;
  l->size =0;
  l->preFirst = (Node) malloc(sizeof(struct strNode));
  l->preFirst->next =NULL;
  l->preFirst->prior =NULL;
  l->preFirst->data =NULL;

  l->postLast = (Node) malloc(sizeof(struct strNode));
  l->postLast->next =NULL;
  l->postLast->prior =NULL;
  l->postLast->data =NULL;


  return l;
}

//Elimina a todos los nodos y a la lista.
void lista_destroy(List l){
    Node current, next;
    current = l->first;
    if(l->first != NULL){
    	next= current->next;
    	while(next!=NULL){
    		free(current);
    		current = next;
    		next=current->next;
    	}
    	free(current);
    }
    free(l->preFirst);
    free(l->postLast);
	free(l);
}

//Extrae el tamaño de la lista.
int  list_size(List l){
  return l->size;
}

//Agrega un elemento al final de la lista.
//Incrementa el tamaño en uno
void list_add(List l, Type t){
    Node n = (Node) malloc (sizeof(struct strNode));
    n->data = t;
    n->next = NULL;

    if (l->size == 0){  //crear el primer elemento
    	n->prior = NULL;
    	l->first = n;
    	l->preFirst->next = l->first;
    }else{
    	n->prior = l->last;
    	l->last->next = n;
    }
    l->last = n;
    l->postLast->prior = l->last;
    l->size++;

}

//Devuelve el elemento en la posición p.
Type list_get(List l, int p){
    if(p<0 ||p >=l->size) return NULL;

    Node current = l->first;
    int i =0;
    for(i=0;i<p; i++)
    	current = current->next;

    return current->data;
}

//Reemplaza el elemento en la posición p por el valor recibido.
void list_set(List l, Type t, int p){
	if(p<0 ||p >=l->size) return;

	    Node current = l->first;
	    int i =0;
	    for(i=0;i<p; i++)
	    	current = current->next;

	    current->data  = t;
}

//Elimina y devuelve el elemento en la 	posición p.
//Decrementa el tamaño en uno.
Type list_remove(List l, int p){
	if(p<0 ||p >=l->size) return NULL;
	  Node current = l->first;
	  int i =0;
	  for(i=0;i<p; i++)
		  current = current->next;

	  Type datos = current->data;

	  if(current->prior!=NULL)  //no soy el primero
		  current->prior->next = current->next;
	  else {//soy el primer nodo
		  l->first = current->next;
		  l->preFirst->next= l->first;
	  }


	  if(current->next!=NULL) // no soy el último
		  current->next->prior = current->prior;
	  else{ //soy el último nodo
		  l->last = current->prior;
		  l->postLast->prior = l->last; //actualizar apuntador a last
	  }

	  free(current);
	  l->size--;

	  return datos;
}


//Devuelve el iterador al pre-inicio.
Iterator list_begin(List l){
	return l->preFirst;
}

//Devuelve al post-final.
Iterator list_end(List l){
	return l->postLast;

}

//Devuelve TRUE sólo si hay un nodo siguiente.
bool list_hasNext(Iterator ite){
    if(ite->next!=NULL) return TRUE;
    else return FALSE;
}

//Devuelve TRUE sólo si hay un nodo anterior.
bool list_hasPrior(Iterator ite){
	if(ite->prior!=NULL) return TRUE;
	    else return FALSE;
}

//Devuelve un iterador a la posición siguiente.
Iterator list_next(Iterator ite){
    if(!list_hasNext(ite))
    	  return NULL;
    else
    	return ite->next;
}

//Devuelve un iterador a la posición anterior.
Iterator list_prior(Iterator ite){
	if(!list_hasPrior(ite))
	    	  return NULL;
	    else
	    	return ite->prior;
}

//Devuelve el dato referido por el iterador.
Type list_data(Iterator ite){
    return ite->data;
}



