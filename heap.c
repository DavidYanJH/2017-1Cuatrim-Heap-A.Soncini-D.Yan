#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define CAPAC_INICIAL 36
#define COEF_REDIM 2

struct heap {
	void** datos;
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

size_t obtener_hijo_izquierdo(size_t index) {	
	return index * 2 + 1;
}

size_t obtener_hijo_derecho(size_t index) {	
	return index * 2 + 2;
}

void swap_vectorial(void** vector, size_t x,  size_t y) {
	void* aux = vector[x];
	vector[x] = vector[y];
	vector[y] = aux;
}

void upheap(heap_t* heap, size_t actual) {
	if (actual == 0) return;
	size_t padre = obtener_padre(actual);
	if (heap->cmp(heap->datos[actual], heap->datos[padre]) > 0) {
		swap_vectorial(heap->datos, actual, padre);
		upheap(heap, padre);
	}
}


void downheap(heap_t* heap, size_t actual)
{
	size_t maximo = actual;
	size_t hijo_izq = obtener_hijo_izquierdo(actual);
	size_t hijo_der = obtener_hijo_derecho(actual);
	if (hijo_izq < heap->cantidad)
		if (heap->cmp(heap->datos[hijo_izq], heap->datos[maximo]) > 0)
			maximo = hijo_izq;
	if (hijo_der < heap->cantidad)
		if (heap->cmp(heap->datos[hijo_der], heap->datos[maximo]) > 0)
			maximo = hijo_der;
	if (maximo != actual) {
		swap_vectorial(heap->datos, maximo, actual);
		downheap(heap, maximo);
	}
}

bool heap_redimensionar(heap_t* heap) 
{
	size_t new_capacidad = heap->capacidad * COEF_REDIM;
	void** new_datos = realloc(heap->datos, sizeof(void*) * new_capacidad);
	if (!new_datos) return false;
	heap->datos = new_datos;
	heap->capacidad = new_capacidad;
	return true;
}

/* ******************************************************************
 *                        PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t* heap_crear(cmp_func_t cmp) 
{
	if (!cmp) return NULL;
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->datos = malloc(sizeof(void*) * CAPAC_INICIAL);
	if (!heap->datos) {
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
	return heap->datos[0];
}


void heap_destruir(heap_t* heap, void destruir_elem(void* e))
{
	if (!heap_esta_vacio(heap) && destruir_elem) {
		for (size_t index = 0; index < heap->cantidad; ++index) 
			destruir_elem(heap->datos[index]);
	}
	if (heap) {
		free(heap->datos);
		free(heap);
	}
}


bool heap_encolar(heap_t* heap, void* elem) {
	if (!heap || !elem) return false;
	if (heap->cantidad == heap->capacidad) {
		if (!heap_redimensionar(heap)) 
			return false;
	}
	heap->datos[heap->cantidad] = elem;
	upheap(heap, heap->cantidad);
	++heap->cantidad;
	return true;
}

void* heap_desencolar(heap_t* heap)
{
	if (heap_esta_vacio(heap)) return NULL;
	--heap->cantidad;
	if (heap->cantidad == 0) return heap->datos[0];
	swap_vectorial(heap->datos, 0, heap->cantidad);
	downheap(heap, 0);
	return heap->datos[heap->cantidad];
}


heap_t* heap_crear_arr(void* arreglo[], size_t n, cmp_func_t cmp)
{
	heap_t* heap = heap_crear(cmp);
	if (!heap) return NULL;
	for (size_t index = 0; index < n; ++index)
		if (!heap_encolar(heap, arreglo[index])) break;
	if (heap->cantidad == n) return heap;
	// En caso de sin inicializar el heap con la totalidad de elementos del arreglo 
	// debido a la falta de memoria en ejecución debería retorna NULL... 
	free(heap->datos);
	free(heap);
	return NULL;
}