#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "vector_dinamico.h"

#define CAPAC_INICIAL 36;
#define COEF_REDIM 2

typedef struct heap heap_t

struct heap {
	vector_t* vec_dinam;
	cmp_func_t cmp;
	size_t cantidad;
};


/* ******************************************************************
 *                        PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t* heap_crear(cmp_func_t cmp) 
{
	if (!cmp) return NULL;
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->vec_dinam = vector_crear(CAPAC_INICIAL);
	if (!heap->vec_dinam) {
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	return heap;
}


size_t heap_cantidad(heap_t* heap) 
{
	if (!heap) return 0;
	return heap->cantidad;
}


bool heap_esta_vacio(const heap_t* heap)
{
	if (!heap) return true;
	return (heap_cantidad == 0);
}


void* heap_ver_max(const heap_t* heap)
{
	if (heap_esta_vacio(heap)) return NULL;
	return heap->vec_dinam[0];
}


void heap_destruir(heap_t* heap, void destruir_elem(void* e))
{
	if (!heap_esta_vacio(heap) && destruir_elem) {
		for (size_t index = 0; index <= heap->cantidad; ++index)
			destruir_elem(heap->vec_dinam[index]);
	}
	if (heap) {
		vector_destruir(heap->vec_dinam);
		free(heap);
	}
}