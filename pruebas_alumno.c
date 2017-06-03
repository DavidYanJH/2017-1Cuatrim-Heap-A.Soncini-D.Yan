#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "testing.h"

/* ******************************************************************
 *                   FUNCIONES DE PRUEBA AUXILIARES
 * *****************************************************************/
int strcmpaux (const void* a, const void* b) {
	int inta = atoi(a);
	int intb = atoi(b);

	if (inta < intb)
		return -1;
	if (inta > intb)
		return 1;
	else return 0;
}

int strcmpaux2 (const void* a, const void* b) {
	return strcmp((char*) a, (char*) b);
}

 /* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear_heap_vacio(void) {
	heap_t* heap = heap_crear(strcmpaux);

	print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver maxima prioridad, es NULL, no existe", !heap_ver_max(heap));
    //print_test("Prueba heap eliminar maxima prioridad, es NULL, no existe", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

void prueba_heap_insersion(void) {
	heap_t* heap = heap_crear(strcmpaux);
	void* maximo;
	char* str1 = malloc(sizeof(char) + 1);
	char* str2 = malloc(sizeof(char) + 1);
	char* str3 = malloc(sizeof(char) + 1);
	
	strcpy(str1, "a");
	strcpy(str2, "b");
	strcpy(str3, "c");

	print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
	print_test("Prueba insertar 'a' inserta correctamente", heap_encolar(heap, str1));
	print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
	maximo = heap_ver_max(heap);
	print_test("Prueba heap maximo es 'a'", (strcmpaux(maximo,"a") == 0));

	print_test("Prueba insertar 'b' inserta correctamente", heap_encolar(heap, str2));
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
	maximo = heap_ver_max(heap);
	print_test("Prueba heap maximo es 'b'", (strcmpaux(maximo,"b") == 0));
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
	maximo = heap_ver_max(heap);
	print_test("Prueba heap maximo es 'b' (no se modifica heap al ver maximo)", (strcmpaux(maximo,"b") == 0));
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
	maximo = heap_ver_max(heap);
	print_test("Prueba heap maximo es 'b' (no se modifica heap al ver maximo)", (strcmpaux(maximo,"b") == 0));
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);

	maximo = heap_desencolar(heap);
	print_test("Prueba heap desencolar maximo es 'b'", (strcmpaux(maximo,"b") == 0));
	print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
	maximo = heap_desencolar(heap);
	print_test("Prueba heap desencolar maximo es 'a'", (strcmpaux(maximo,"a") == 0));
	print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

	print_test("Prueba insertar 'b' inserta correctamente", heap_encolar(heap, str2));
	print_test("Prueba insertar 'a' inserta correctamente", heap_encolar(heap, str1));
	print_test("Prueba insertar 'c' inserta correctamente", heap_encolar(heap, str3));
	print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);

	maximo = heap_desencolar(heap);
	print_test("Prueba heap desencolar maximo es 'c'", (strcmpaux(maximo,"c") == 0));
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
	free(maximo);
	maximo = heap_desencolar(heap);
	print_test("Prueba heap desencolar maximo es 'b'", (strcmpaux(maximo,"b") == 0));
	print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
	free(maximo);
	maximo = heap_desencolar(heap);
	print_test("Prueba heap desencolar maximo es 'a'", (strcmpaux(maximo,"a") == 0));
	print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
	free(maximo);

	heap_destruir(heap, free);
}

void prueba_heap_redimension_volumen(int size_test) {
	srand((int) time(NULL));
	int i;
	heap_t* heap = heap_crear(strcmpaux);
	bool OK = true;
	char* straux;
	char* straux2;
	for (i = 0; i < size_test; i++) {
		char strtmp[20];
		sprintf(strtmp, "%d", (int) rand());

		straux = malloc(sizeof(char) * strlen(strtmp) + 1);
		strcpy(straux, strtmp);
		heap_encolar(heap, straux);
	}

	print_test("Se encolaron 5000 elementos", heap_cantidad(heap) == size_test);

	straux = heap_desencolar(heap);
	while (!heap_esta_vacio(heap) && OK) {
		straux2 = heap_desencolar(heap);
		OK = (strcmpaux(straux, straux2) > 0);
		free(straux);
		straux = straux2;
	}
	free(straux);
	print_test("Se desencolaron todos los elementos correctamente", OK);
	print_test("El heap ahora esta vacio", heap_esta_vacio(heap));
	heap_destruir(heap, free);
}

void prueba_heap_crear_arr(int size_test) {
	srand((int) time(NULL));
	bool OK = true;
	char* straux;
	char* straux2;
	void* strvec[size_test];
	for (size_t i = 0; i < size_test; i++) {
		char strtmp[20];
		sprintf(strtmp, "%d", (int) rand());
		straux = malloc(sizeof(char) * strlen(strtmp) + 1);
		strcpy(straux, strtmp);
		strvec[i] = straux;
	}
	heap_t* heap = heap_crear_arr(strvec, size_test, strcmpaux);

	print_test("Heap creado a partir de un arreglo", heap);
	print_test("Tamaño de heap creado es igual a tamaño de arreglo inicial", heap_cantidad(heap) == size_test);

	straux = heap_desencolar(heap);
	while (!heap_esta_vacio(heap) && OK) {
		straux2 = heap_desencolar(heap);
		OK = (strcmpaux(straux, straux2) > 0);
		free(straux);
		straux = straux2;
	}
	free(straux);
	print_test("Se desencolaron todos los elementos correctamente", OK);
	print_test("El heap ahora esta vacio", heap_esta_vacio(heap));
	heap_destruir(heap, free);
}

void prueba_heapsort() {
	size_t i = 0;
	bool OK = true;
	char* strvec[] = {"9", "8", "7", "2", "1", "0", "6", "5", "4", "3", "110"};
	heap_sort((void*) strvec, 11, strcmpaux2);
	i = 0;
	while (i < 11 - 2 && OK) {
		OK  = (strcmpaux2(strvec[i], strvec[i + 1]) <= 0);
		i++;
	}
	print_test("Se ordena correctamente un arreglo inicialmente desordenado", OK);
}

void pruebas_heap_alumno(void) {
	prueba_crear_heap_vacio();
	prueba_heap_insersion();
	prueba_heap_redimension_volumen(5000);
	prueba_heap_crear_arr(5000);
	prueba_heapsort();
}