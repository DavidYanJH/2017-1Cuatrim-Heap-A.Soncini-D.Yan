#include <stdlib.h>
#include <string.h>
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

void pruebas_heap_alumno(void) {
	prueba_crear_heap_vacio();
	prueba_heap_insersion();
}