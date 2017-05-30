#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define CAPAC_INICIAL 36
#define COEF_REDIM 2

struct heap {
	void** vec_dinam;
	cmp_func_t cmp;
	size_t cantidad;
	size_t capacidad;
};

/* ******************************************************************
 *                  FUNCIONES AUXILIARES DEL HEAP
 * *****************************************************************/
size_t obtener_padre(size_t index) {
	return (index - 1) / 2;
}

size_t obtener_hijo_izquierdo(size_t index) {	// Determinar si van a ser de utilidad
	return index * 2 + 1;
}

size_t obtener_hijo_derecho(size_t index) {	// Determinar si van a ser de utilidad
	return index * 2 + 2;
}

void swap(void** vector, size_t index_hijo, void* dato_hijo, size_t index_padre, void* dato_padre) {
	vector[index_hijo] = dato_padre;
	vector[index_padre] = dato_hijo;
}

void upheap(heap_t* heap, size_t index_hijo, void* dato_hijo) {
	if (index_hijo == 0) return;
	size_t index_padre = obtener_padre(index_hijo);
	void* dato_padre = heap->vec_dinam[index_padre];
	if (heap->cmp(dato_hijo, dato_padre) > 0) {
		swap(heap->vec_dinam, index_hijo, dato_hijo, index_padre, dato_padre);
		upheap(heap, index_padre, dato_hijo);
	}
}

/* ******************************************************************
 *                        PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t* heap_crear(cmp_func_t cmp) 
{
	if (!cmp) return NULL;
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->vec_dinam = malloc(sizeof(void*) * CAPAC_INICIAL);
	if (!heap->vec_dinam) {
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	heap->cantidad = 0;
	heap->capacidad = CAPAC_INICIAL;
	return heap;
}


size_t heap_cantidad(const heap_t* heap) 
{
	if (!heap) return 0;
	return heap->cantidad;
}


bool heap_esta_vacio(const heap_t* heap)
{
	if (!heap) return true;
	return (heap->cantidad == 0);
}


void* heap_ver_max(const heap_t* heap)
{
	if (heap_esta_vacio(heap)) return NULL;
	return heap->vec_dinam[0];
}


void heap_destruir(heap_t* heap, void destruir_elem(void* e))
{
	if (!heap_esta_vacio(heap) && destruir_elem) {
		for (size_t index = 0; index < heap->cantidad; ++index) {
			void* tmp = heap->vec_dinam[index];
			destruir_elem(tmp);
		}
	}
	if (heap) {
		free(heap->vec_dinam);
		free(heap);
	}
}

bool heap_encolar(heap_t *heap, void *elem) {
	if (!elem) return false;
	if (heap->cantidad == heap->capacidad) {
		void** new_vec_dinam = realloc(heap->vec_dinam, sizeof(void*) * heap->capacidad * COEF_REDIM);
		if (!new_vec_dinam) return false;
		else {
			heap->vec_dinam = new_vec_dinam;
			heap->capacidad = heap->capacidad * COEF_REDIM;
		}
	}
	heap->vec_dinam[heap->cantidad] = elem;
	upheap(heap, heap->cantidad, elem);
	heap->cantidad+=1;
	return true;
}