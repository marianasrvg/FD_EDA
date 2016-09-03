/*
 * Letras_Iónicas.c
 *
 *  Created on: 17/11/2015
 *      Author: Mariana
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 20
#define COLUMNAS 20
#define LETRAS 16
#define ELE 12

typedef struct valores{
	char nombre[ELE];
	int puntos;
} VALORES;


void imprimir_tablero(char tablero[FILAS][COLUMNAS]) {

	int i, x;
	printf("\n\t TABLERO \n");
	for (i = 0; i < FILAS; i++) {
		for (x = 0; x < COLUMNAS; x++) {
			if (tablero[i][x] < 123 && tablero[i][x] > 96) {
				printf("|%c", tablero[i][x]);
			} else
				printf("| ");
		}
		printf("|");
		printf("\n");
		for (x = 0; x < COLUMNAS; x++) {
			printf("__");
		}
		printf("\n");
	}

	return;
}

void imprimir_mano(char *mano) {
	int i = 0;

	printf("\n\n\t TUS LETRAS PARA JUGAR SON:\n\n");
	for (i = 0; i < LETRAS; i++) {
		if (mano[i] < 123 && mano[i] > 96) {
			printf("| %c ", mano[i]);
		} else {
			printf("|   ");
		}
	}
	printf("|\n");
	return;
}

void dar_mano(char *mano) {
	int i = 0;
	int j;

	for (i = 0; i < ((LETRAS/2)+2); i++) {
		if (mano[i] == '\0') {
			mano[i] = (((rand() % 25) + 1) + 97);
		}
	}
	for (i = 8; i < LETRAS; i++) {
		if (mano[i] == '\0') {
			j = ((rand() % 5) + 1);

			switch (j) {
			case 1:
				mano[i] = 'a';
				break;
			case 2:
				mano[i] = 'e';
				break;
			case 3:
				mano[i] = 'i';
				break;
			case 4:
				mano[i] = 'o';
				break;
			case 5:
				mano[i] = 'u';
				break;

			}
		}
	}
	return;
}

int checar_palabra(char *elemento) {
	FILE *archivo = fopen("elementos.txt", "rt");
	int fov = 0, i;
	char ele[ELE];

	if (archivo == NULL) {
		printf("VOY A EXPLOTAR, cierrame YA!");
		return fov;
	}

	while (fscanf(archivo, "%s\n", ele)) {
		system("PAUSE");
		for (i = 0; i <= ELE; i++) {
			printf("%c", ele[i]);
		}
		printf("\n");
		if (elemento == ele) {
			fov = 1;
		}
	}
	printf("\n");
	fclose(archivo);
	return fov;
}

int contar_letras(char *elemento) {
	int i;
	for (i = 0; elemento[i] != '\0'; i++)
		;
	return i;
}

int horizontal(char *elemento, int x, int y) {
	int tof = 0;
	int cantidad = contar_letras(elemento);

	if (((FILAS-1) - x) < cantidad) {
		tof = 0;

	} else {
		tof = 1;
	}
	return tof;
}

int vertical(char *elemento, int x, int y) {
	int tof = 0;
	int cantidad = contar_letras(elemento);

	if (((COLUMNAS-1) - y) < cantidad) {
		tof = 0;
	} else {
		tof = 1;
	}
	return tof;
}

int revisar_tablero_posicion(char *elemento, int x, int y, int hv) {
	int fov = 0;
	if (hv == 1) {
		//HORIZONTAL
		fov = horizontal(elemento, x, y);
	} else if (hv == 2) {
		fov = vertical(elemento, x, y);
		//VERTICAL
	} else {
		printf("No te doy permiso:D\n");
		return fov;
	}

	return fov;
}

int comparar_mano(char *elemento, char *mano) {
	int sin = 0;
	int i, x, cont = 0, letras;

	letras = contar_letras(elemento);
	for (i = 0; i < letras; i++) {
		for (x = 0; x <= LETRAS; x++) {
			if (elemento[i] == mano[x]) {
				cont++;
				x += LETRAS;
			}
		}
	}
	if (cont == letras) {
		return sin = 1;
	} else {
		return sin;
	}
}

int horizontal_letras(char *elemento, char tablero[FILAS][COLUMNAS], int x, int y){
	int sonp = 0;
	int letra = contar_letras(elemento);
	int i, cont = 0;
	int estable = y+letra;

	for (i = 0; y < estable; y++, i++){
		if (tablero[x][y] != '\0'){
			if (tablero[x][y] == elemento[i]){
				cont++;
			} else {
				printf("No puedes escribir la palabra aquí\n");
			}
		} else {
			cont++;
		}
	}

	if (cont == letra){
		return sonp = 1;
	} else {
		return sonp;
	}
}

int vertical_letras(char *elemento, char tablero[FILAS][COLUMNAS], int x, int y){
	int sonp = 0;
	int letra = contar_letras(elemento);
	int i, cont = 0;
	int estable = x+letra;

	for (i = 0; x < estable; x++, i++){
		if (tablero[x][y] != '\0'){
			if (tablero[x][y] == elemento[i]){
				cont++;
			} else {
				printf("No puedes escribir la palabra aquí\n");
			}
		} else {
			cont++;
		}
	}

	if (cont == letra){
		return sonp = 1;
	} else {
		return sonp;
	}
}

int revisar_tablero_tam(char *elemento, char tablero[FILAS][COLUMNAS], int x, int y, int hv){
	int sonp = 0;
	if (hv == 1){
		sonp = horizontal_letras(elemento, tablero, x, y);
	} else if (hv == 2){
		sonp = vertical_letras(elemento, tablero, x, y);
	} else {
		printf("No te doy permiso >:D\n");
	}
	return sonp;
}

void actualizar_tablero(char *elemento, char tablero[FILAS][COLUMNAS], int x, int y, int hv){
	int i;
	int letras = contar_letras(elemento);
	int cont = 0;
	if (hv == 1){
		//HORIZONTAL
		for (i = y, cont = 0; i < (letras+y); i++, cont++){
			tablero[x][i] = elemento[cont];
		}
	} else {
		for (i = x, cont = 0; i < (letras+x); i++, cont++){
			tablero[i][y] = elemento[cont];
		}
		//VERTICAL
	}

	return;
}

int sumar_puntos(char *elemento, int puntos, char tablero[FILAS][COLUMNAS], int x, int y, int hv){
	VALORES e;
	FILE *archivo = fopen ("elementos.txt", "rt");
	int z = 0;

	if (archivo == NULL){
		printf("No puedo abrir el archivo de los elementosD:\n");
		return puntos;
	}

	while(fscanf(archivo, "%s %d\n", e.nombre, &e.puntos)){
		if (strcmp(e.nombre, elemento) == 0){
			puntos += e.puntos;
			printf("%s - %s\n", e.nombre, elemento);
			fclose(archivo);
			actualizar_tablero(elemento, tablero, x, y, hv);
			return puntos;
		}
		z++;
		if (z == 120){
			fclose(archivo);
			printf("Esa palabra no es un elemento\n");
			return puntos;
		}
	}

	return puntos;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	srand(time(NULL));

	char tablero[FILAS][COLUMNAS];
	char mano_j1[LETRAS] = { '\0' };
	char elemento[12];
	int menu = 0;
	int i, x;
	int puntaje = 0;

	for (i = 0; i < FILAS; i++){
		for (x = 0; x < COLUMNAS; x++){
			tablero[i][x] = '\0';
		}
	}

	dar_mano(mano_j1);

	do {
		menu = 0;
		imprimir_tablero(tablero);
		printf("TU PUNTAJE ES IGUAL A: %d\n", puntaje);
		imprimir_mano(mano_j1);
		fflush(stdin);

		printf("\n¿Que quieres hacer?\n");
		printf("1.Cambiar mano\n");
		printf("2.Escribir en el tablero\n");
		printf("0.SALIR\nEscribe la opción que necesitas realizar:\t");
		scanf("%d", &menu);
		fflush(stdin);
		switch (menu) {
		case 1:
			for (i = 0; i <= LETRAS; i++) {
				mano_j1[i] = '\0';
			}
			dar_mano(mano_j1);
			break;
		case 2:
			printf("\n ¿Que palabra quieres ingresar?:\n");
			scanf("%s", elemento);
			fflush(stdin);
			int x = 21, y = 21, hv = 4, resultado;
			printf("RECUERDA QUE EMPIEZA DE 0 HASTA 19\n");
			do {
				fflush(stdin);
				printf(" Ingresa la coordenada en FILAS --:\n");
				scanf("%d", &x);
			} while (x > 20);
			do {
				fflush(stdin);
				printf(" Ingresa la coordenada en COLUMNAS |:\n");
				scanf("%d", &y);
			} while (y > 20);
			do {
				hv = 4;
				fflush(stdin);
				printf(" Ingresa 1 si quieres la palabra en HORIZONTAL\n Ingresa 2 si quieres la palabra en VERTICAL:\n");
			scanf("%d", &hv);
			} while (hv > 3);
			//COMPARAR MANO

			resultado = comparar_mano(elemento, mano_j1);
			if (resultado == 0) {
				printf("No tienes las letras para formar ese elemento\n");
				break;
			} else {
			}


			//REVISA EN TABLERO POR TAMAÑO
			resultado = revisar_tablero_posicion(elemento, x, y, hv);
			if (resultado == 0) {
				printf("No puedes poner esa palabra en esa posición\n");
				break;
			} else {
			}


			//REVISAR EN TABLERO POR POSICIÓN

			resultado = revisar_tablero_tam(elemento, tablero, x, y, hv);
			if (resultado == 0){
				printf("No puedes poner esa palabra porque se intersecta con otra que no va!\n");
				break;
			} else {
				//ESCRIBIR PALABRA EN TABLERO
				//printf("Si puedes ponerla ahí\n");

				puntaje = sumar_puntos(elemento, puntaje, tablero, x, y, hv);
				for (i = 0; i <= LETRAS; i++) {
					mano_j1[i] = '\0';
				}
				dar_mano(mano_j1);
			}

			system("PAUSE");
			break;
		case 0:
			printf("\nGracias por jugar! REGRESA PRONTO\n");
			return 0;
		default:
			break;
		}
	} while (menu != 0);

	return 0;
}
