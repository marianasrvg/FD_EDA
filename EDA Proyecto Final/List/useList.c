/*
 * useLIst.c
 *
 *  Created on: 14/04/2016
 *      Author: LGUTIERREZ
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int expediente;
	char nombre[30];
	float calificacion;
}Alumno;


int main(){
	List l = list_create();
	Alumno juan = {123, "JUAN PEREZ", 8.5};
	Alumno pedro = {434, "PEDRO LOPEZ", 5.5};
	Alumno maria = {5456, "MARIA RODRIGUEZ", 9.5};

	Alumno * luis = (Alumno*) malloc(sizeof(Alumno));
	strcpy(luis->nombre, "Luis Gutiérrez");
	luis->expediente = 34534;
	luis->calificacion = 7.8;

	list_add(l, &juan);
	list_add(l, &pedro);
	list_add(l, &maria);
	list_add(l, luis); //ya es apuntador no se pone &

	list_remove(l,1);   //borrar a pedro
    list_set(l,&pedro,0);

	/*int i =0;
	 for(i=0; i < list_size(l); i++){
		 Alumno* alumno = (Alumno*) list_get(l,i);
		 printf("Alumno: %s, Expediente: %d, Calificación: %.1f\n",alumno->nombre, alumno->expediente, alumno->calificacion);
	 }*/

	 //USANDO ITERADORES
	 Iterator it = list_begin(l);
	 while(list_hasNext(it)){
		 it = list_next(it);
		 Alumno* alum = (Alumno*) list_data(it);
		 printf("Alumno: %s, Expediente: %d, Calificación: %.1f\n",alum->nombre, alum->expediente, alum->calificacion);

	 }


	 printf("*********************\n");
	 it = list_end(l);
		 while(list_hasPrior(it)){
			 it = list_prior(it);
			 Alumno* alum = (Alumno*) list_data(it);
			 printf("Alumno: %s, Expediente: %d, Calificación: %.1f\n",alum->nombre, alum->expediente, alum->calificacion);

		 }





     lista_destroy(l);
 return 0;
}
